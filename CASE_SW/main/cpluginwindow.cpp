#include "cpluginwindow.h"
#include "ui_cpluginwindow.h"

//add header
#include <QMessageBox>
#include <QFileDialog>

//

#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include <cplugininterface.h>

#include <view/cmodelview.h>
#include <view/pmodelview.h>

CPluginWindow::CPluginWindow(CModelView *model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CPluginWindow),
    _dataModel(model->dataModel())
{
    ui->setupUi(this);
    this->setWindowTitle(QString("%1 - Generate SQL CREATE script")
                         .arg(model->name()));
    this->loadPlugins();

    login = new Autorization();
    connect(login, SIGNAL(sendConnect()), this, SLOT(Connect()));
    connect(login, SIGNAL(sendDisconnect()), this, SLOT(Disconnect()));
}

CPluginWindow::CPluginWindow(PModelView *model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CPluginWindow),
    _dataModel(model->dataModel())
{
    ui->setupUi(this);
    this->setWindowTitle(QString("%1 - Generate SQL CREATE script")
                         .arg(model->name()));
    this->loadPlugins();
    login = new Autorization();
    connect(login, SIGNAL(sendConnect()), this, SLOT(Connect()));
    connect(login, SIGNAL(sendDisconnect()), this, SLOT(Disconnect()));
}



CPluginWindow::~CPluginWindow()
{
    delete ui;
}

void CPluginWindow::on_pushConnect_clicked()
{
    if (ui->textBrowser->document()->isEmpty())
        return;
    if (ui->comboBox->currentText().contains("PostgreSQL")){
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    else if (ui->comboBox->currentText().contains("MySQL")){
        db = QSqlDatabase::addDatabase("QMYSQL");
    }
    else if (ui->comboBox->currentText().contains("SQLite")){
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    login->show();
}

void CPluginWindow::inceptionScript()
{
   QString sql = ui->textBrowser->document()->toPlainText();
   qDebug()<<sql;
   QSqlQuery query;
   query.exec(sql);
   db.close();
}

void CPluginWindow::on_pushGenerate_clicked()
{
    QString name = ui->comboBox->currentText();
    QString path = _plugins.value(name);

    qDebug() << "name: " << name << "path: " << path;

    QPluginLoader *loader = new QPluginLoader(path);
    loader->load();
    QObject *obj = loader->instance();
    CPluginInterface *plugin = qobject_cast<CPluginInterface *>(obj);
    ui->textBrowser->clear();
    if(plugin)
    {
        QString query = plugin->query(_dataModel->convertToPhysical());
        ui->textBrowser->setText(query);
    }
    loader->unload();
}

void CPluginWindow::Connect()
{
    db.setHostName(login->host);
    db.setPort(login->port);
    db.setDatabaseName(login->nameDB);
    db.setUserName(login->user);
    db.setPassword(login->password);
    login->hide();
    if(!db.open())
        QMessageBox::critical(this, tr("ERROR!"), db.lastError().databaseText());
    else{
        QMessageBox::information(this, tr("SUCCESS!"),tr("Соединение установлено!"));
        inceptionScript();
    }
}

void CPluginWindow::Disconnect()
{
    db.close();
}

void CPluginWindow::loadPlugins()
{
    ui->comboBox->clear();
    QString extension = "";
    QString prefix = "";

#ifdef Q_OS_WIN
    extension = "dll";
    prefix = "";
#endif

#ifdef Q_OS_LINUX
    extension = "so";
    prefix = "lib";
#endif

    QStringList nameFilter;
    nameFilter << QString("%1*.%2")
                  .arg(prefix)
                  .arg(extension);

    //qDebug() << LIB_PATH;
    QString currdir = QApplication::applicationDirPath() + "/lib/";
    QDir libDir(currdir);

    QStringList files = libDir.entryList(nameFilter);
    foreach (QString file, files) {
        // We load each file with plugin loader to check if it is indeed the right plugin
        // Then we unload that file because it is not needed yet
        //qDebug() << file;
        QPluginLoader loader(QString("%1/%2")
                             .arg(currdir)
                             .arg(file));
        loader.load();
        if(!loader.isLoaded())
        {
            qDebug() << "Can't load plugin!";
            qDebug() << "Error @ " + file + ": " + loader.errorString();
            continue;
        }
        QObject *obj = loader.instance();
        CPluginInterface *plugin = qobject_cast<CPluginInterface *>(obj);
        if(plugin)
        {
            QString pluginName = QString("%1 (%2)")
                    .arg(plugin->name())
                    .arg(plugin->version());
            ui->comboBox->addItem(pluginName);
            _plugins.insert(pluginName, QString("%1/%2")
                            .arg(currdir)
                            .arg(file));
        }
        loader.unload();
    }
}

void CPluginWindow::on_pushRefresh_clicked()
{
    this->loadPlugins();
}



void CPluginWindow::on_actionExport_as_triggered()
{
    //
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory lib"), "",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks
                                                        | QFileDialog::DontUseNativeDialog);
    if(dirPath.isEmpty())
        return;
    //-------------------------------------------------------------
    ui->comboBox->clear();
    QString extension = "";
    QString prefix = "";

#ifdef Q_OS_WIN
    extension = "dll";
    prefix = "";
#endif

#ifdef Q_OS_LINUX
    extension = "so";
    prefix = "lib";
#endif

    QStringList nameFilter;
    nameFilter << QString("%1*.%2")
                  .arg(prefix)
                  .arg(extension);

    //qDebug() << LIB_PATH;
    dirPath += '/';
    QDir libDir(dirPath);

    QStringList files = libDir.entryList(nameFilter);
    foreach (QString file, files) {
        // We load each file with plugin loader to check if it is indeed the right plugin
        // Then we unload that file because it is not needed yet
        //qDebug() << file;
        QPluginLoader loader(QString("%1/%2")
                             .arg(dirPath)
                             .arg(file));
        loader.load();
        if(!loader.isLoaded())
        {
            qDebug() << "Can't load plugin!";
            qDebug() << "Error @ " + file + ": " + loader.errorString();
            continue;
        }
        QObject *obj = loader.instance();
        CPluginInterface *plugin = qobject_cast<CPluginInterface *>(obj);
        if(plugin)
        {
            QString pluginName = QString("%1 (%2)")
                    .arg(plugin->name())
                    .arg(plugin->version());
            ui->comboBox->addItem(pluginName);
            _plugins.insert(pluginName, QString("%1/%2")
                            .arg(dirPath)
                            .arg(file));
        }
        loader.unload();
    }
}



#ifndef CPLUGINWINDOW_H
#define CPLUGINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QtSql>
#include <QSqlDatabase>
#include "../dialog/autorization.h"

namespace Ui {
class CPluginWindow;
}

class CModelView;
class PModelView;
class CDataModel;
class CPluginInterface;

class CPluginWindow : public QMainWindow
{
    Q_OBJECT

public:
    CPluginWindow(CModelView *model, QWidget *parent = 0);
    CPluginWindow(PModelView *model, QWidget *parent = 0);
    ~CPluginWindow();

public slots:
    void Connect();
    void Disconnect();

private slots:
    void on_pushRefresh_clicked();
    void on_pushGenerate_clicked();
    void on_actionExport_as_triggered();
    void on_pushConnect_clicked();

private:
    Ui::CPluginWindow *ui;
    QSqlDatabase db;
    Autorization* login;
    CDataModel *_dataModel;
    QMap<QString, QString> _plugins;
    void inceptionScript();
    void loadPlugins();
};

#endif // CPLUGINWINDOW_H

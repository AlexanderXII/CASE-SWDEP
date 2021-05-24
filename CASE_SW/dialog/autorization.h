#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QWidget>

namespace Ui {
class Autorization;
}

class Autorization : public QWidget
{
    Q_OBJECT

public:
    explicit Autorization(QWidget *parent = nullptr);
    ~Autorization();
    QString user;
    QString password;
    QString host;
    QString nameDB;
    int port;

signals:
    void sendConnect();
    void sendDisconnect();

private slots:
    void on_connect_clicked();
    void on_disconnect_clicked();

private:
    Ui::Autorization *ui;
};

#endif // AUTORIZATION_H

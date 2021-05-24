#include "autorization.h"
#include "ui_autorization.h"

Autorization::Autorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Autorization)
{
    ui->setupUi(this);
}

Autorization::~Autorization()
{
    delete ui;
}

void Autorization::on_connect_clicked()
{
    host = ui->hostLine->text();
    user = ui->userLine->text();
    password = ui->passwordLine->text();
    port = ui->portSpinBox->value();
    nameDB = ui->nameDBLine->text();
    emit sendConnect();
}

void Autorization::on_disconnect_clicked()
{
    ui->userLine->setText("");
    ui->passwordLine->setText("");
    emit sendDisconnect();
}

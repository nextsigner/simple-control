#include "dialogconfirmar.h"
#include "ui_dialogconfirmar.h"

DialogConfirmar::DialogConfirmar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfirmar)
{
    ui->setupUi(this);

}

DialogConfirmar::~DialogConfirmar()
{
    delete ui;
}

void DialogConfirmar::setPregunta(QString p)
{
    pregunta=p;
    ui->labelPregunta->setText(pregunta);
}

void DialogConfirmar::on_pushButtonBorrar_clicked()
{
    accept();
}

void DialogConfirmar::on_pushButtonCancelar_clicked()
{
    reject();
}

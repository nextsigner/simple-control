#include "dialogeditarmultiple.h"
#include "ui_dialogeditarmultiple.h"

DialogEditarMultiple::DialogEditarMultiple(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditarMultiple)
{
    ui->setupUi(this);
}

DialogEditarMultiple::~DialogEditarMultiple()
{
    delete ui;
}

void DialogEditarMultiple::setListProv(QStringList lp)
{
    ui->comboBoxProveedores->addItem("No Modificar");
    ui->comboBoxProveedores->addItems(lp);
}

void DialogEditarMultiple::on_pushButtonCancelar_clicked()
{
    reject();
}

void DialogEditarMultiple::on_pushButtonGuardar_clicked()
{
    if(ui->comboBoxCategorias->currentText() != "No Modificar"
            || ui->comboBoxProveedores->currentText() != "No Modificar"
            || ui->spinBoxPorcentaje->value() != 0
            ){
        emit modificando(ui->comboBoxCategorias->currentText(),
                         ui->comboBoxProveedores->currentText(),
                         ui->spinBoxPorcentaje->value());
        close();
    }
}

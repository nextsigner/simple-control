#include "dialogeditar.h"
#include "ui_dialogeditar.h"
#include <QDateTime>

DialogEditar::DialogEditar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditar)
{
    ui->setupUi(this);

}

DialogEditar::~DialogEditar()
{
    delete ui;
}

void DialogEditar::mostrarDatos(QString n, QString f, QString p, QString proveedor,QString cate)
{
    ui->lineEditNombre->setText(n);
    ui->lineEditFecha->setText(f);
    ui->lineEditPrecio->setText(p.mid(1, p.size()));
    ultimoprecio=ui->lineEditPrecio->text().toDouble();
    ui->labelInfoPrecio->setText(""+f+" - "+p);

    ui->comboBoxProveedores->setCurrentText(proveedor);
    ui->comboBoxCategorias->setCurrentText(cate);
}

void DialogEditar::setListProv(QStringList lp)
{
    ui->comboBoxProveedores->addItems(lp);
}

QString DialogEditar::arreglarCentavos(QString v)
{
    QString arreglo1;
    QString pesosArreglados;
    QString centavosArreglados;

    QStringList sl1 = v.split(".");
    QString p1;
    p1.append(sl1.at(0));
    int pf=p1.toInt();
    if(sl1.size()>1){
       QString nuevosCentavos;
       nuevosCentavos.append(sl1.at(1));
       if(nuevosCentavos.size()<2){
            nuevosCentavos.append("0");
       }
       int centavos = nuevosCentavos.toInt();
       if(centavos>50){
            centavosArreglados.append("00");
            pf++;
       }else{
           centavosArreglados.append("50");
       }
    }else{
        centavosArreglados.append("00");
    }
    arreglo1.append(QString::number(pf));
    arreglo1.append(".");
    arreglo1.append(centavosArreglados);

    return arreglo1;
}

void DialogEditar::on_pushButtonCancelar_clicked()
{
    close();
}

void DialogEditar::on_pushButtonGuardar_clicked()
{
    if(!ui->lineEditNombre->text().isEmpty() && !ui->lineEditFecha->text().isEmpty() && !ui->lineEditPrecio->text().isEmpty()){
        QByteArray nom;
        QByteArray fec;
        QByteArray pre;
        QByteArray prov;
        QByteArray cate;

        nom.append(ui->lineEditNombre->text());
        fec.append(ui->lineEditFecha->text());
        pre.append(ui->lineEditPrecio->text());
        prov.append(ui->comboBoxProveedores->currentText());
        cate.append(ui->comboBoxCategorias->currentText());

        emit modificando(nom, fec, pre, prov, cate);
        close();
    }
}

void DialogEditar::on_horizontalSlider_valueChanged(int value)
{
    //ui->labelPorcentaje->setText(QString::number(value)+"%");

    //int va =
    //ui->labelPorcentaje->setText(QString::number(va)+"%");
    double au = (double)ultimoprecio/100*value;
    //ui->labelPorcentaje->setText(QString::number(au)+"%");
    qreal np = (double)ultimoprecio+(double)au;



    ui->lineEditPrecio->setText(arreglarCentavos(QString::number(np)));
    ui->lineEditFecha->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy"));


}

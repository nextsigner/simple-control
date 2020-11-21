#include "dialogagregarpago.h"
#include "ui_dialogagregarpago.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DialogAgregarPago::DialogAgregarPago(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAgregarPago)
{
    ui->setupUi(this);
    setWindowTitle("Agregando Pago");
    QRegExp rx("(|\"||\\.|[0-9]){30}");
    ui->lineEditImporte->setValidator(new QRegExpValidator(rx, this));
}

DialogAgregarPago::~DialogAgregarPago()
{
    delete ui;
}

QString DialogAgregarPago::arreglarCentavos(QString v)
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

void DialogAgregarPago::setProvActual(QString p)
{
    provactual=p;
}


void DialogAgregarPago::on_pushButtonAceptar_clicked()
{
    if(!ui->lineEditFecha->text().isEmpty()){
    qreal ndeuda=0;
    double deuda = 0.0;

    double importeNuevo = ui->lineEditImporte->text().toDouble();

    QString ord;
    ord.append("select total from boletas where prov='"+provactual+"' order by id desc limit 1;");

    QSqlQuery cons;
    cons.prepare(ord);

    if(cons.exec()){
        //qDebug()<<"Se ha realizado la consulta correctamente.";
    }else{
        //qDebug()<<"NO Se ha realizado la consulta .";
        //qDebug()<<consultar.lastError();

    }

    while (cons.next()) {
        deuda = cons.value(0).toDouble();
    }

    ndeuda = (double)deuda-(double)importeNuevo;

    QString ordenes;
    ordenes.append("INSERT INTO boletas("
                   "fecha,"
                   "importe,"
                   "numfactura,"
                   "fechapago,"
                   "importepago,"
                   "prov,"
                   "total"
                   ")VALUES("
                   "'',"
                   "'',"
                   "'',"
                   "'"+ui->lineEditFecha->text()+"',"
                   "'"+ui->lineEditImporte->text()+"',"
                   "'"+provactual+"',"
                   "'"+arreglarCentavos(QString::number(ndeuda))+"'"
                   ");");

    QSqlQuery crear;
    crear.prepare(ordenes);

    if(crear.exec()){
        qDebug()<<"Se ha insertado un pago correctamente.";
    }else{
        qDebug()<<"NO Se insertado un pago correctamente.";
        qDebug()<<crear.lastError();

    }
    emit insertado();
    this->close();
    }
}

void DialogAgregarPago::on_pushButtonCancelar_clicked()
{
    this->close();
}

#include "dialogagregarboleta.h"
#include "ui_dialogagregarboleta.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
DialogAgregarBoleta::DialogAgregarBoleta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAgregarBoleta)
{
    ui->setupUi(this);
    setWindowTitle("Agregando Boleta");
    QRegExp rx("(|\"||\\.|[0-9]){30}");
    ui->lineEditImporte->setValidator(new QRegExpValidator(rx, this));

}

DialogAgregarBoleta::~DialogAgregarBoleta()
{
    delete ui;
}

QString DialogAgregarBoleta::arreglarCentavos(QString v)
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

void DialogAgregarBoleta::setProvActual(QString p)
{
    provactual = p;
}

void DialogAgregarBoleta::on_pushButtonCancelar_clicked()
{
    this->close();
}

void DialogAgregarBoleta::on_pushButtonAceptar_clicked()
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

    //double au = (double)ultimoprecio/100*value;
    //ui->labelPorcentaje->setText(QString::number(au)+"%");
    //if(deuda>0){
        ndeuda = (double)deuda+(double)importeNuevo;
    //}

    
    
    



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
                   "'"+ui->lineEditFecha->text()+"',"
                   "'"+ui->lineEditImporte->text()+"',"
                   "'"+ui->lineEditFactura->text()+"',"
                   "'',"
                   "'',"
                   "'"+provactual+"',"
                   "'"+arreglarCentavos(QString::number(ndeuda))+"'"
                   ");");

    QSqlQuery crear;
    crear.prepare(ordenes);

    if(crear.exec()){
        qDebug()<<"Se ha insertado una boleta correctamente.";
    }else{
        qDebug()<<"NO Se insertado una boleta correctamente.";
        qDebug()<<crear.lastError();

    }
    emit insertado();
    this->close();
    }
}



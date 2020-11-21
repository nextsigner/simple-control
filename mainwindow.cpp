#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Simple Control - Ferretería Salta");
    setWindowIcon(QIcon("logo.png"));
    ui->statusBar->setGeometry(0,0,500,30);

    listaDeColores.append("#BDBDBD");
    listaDeColores.append("#A4A4A4");
    color = 0;


    listaDeProveedores.append("Cerraduras Leo");
    listaDeProveedores.append("Fernando");
    listaDeProveedores.append("Cintoplom Diego");
    listaDeProveedores.append("Diego amigo Fer");
    listaDeProveedores.append("Distinción");
    listaDeProveedores.append("Dafys");
    listaDeProveedores.append("Distripel");
    listaDeProveedores.append("Distrifia");
    listaDeProveedores.append("Disapla");
    listaDeProveedores.append("El Albañil");
    listaDeProveedores.append("Electricidad Roman");
    listaDeProveedores.append("Electromartins");
    listaDeProveedores.append("Ferremax");
    listaDeProveedores.append("Grama");
    listaDeProveedores.append("Gancedo");
    listaDeProveedores.append("Ligus");
    listaDeProveedores.append("Luis Cueros");
    listaDeProveedores.append("Martinez Yonatan");
    listaDeProveedores.append("Marleda Damian");
    listaDeProveedores.append("PetroPack");
    listaDeProveedores.append("Zallenato");
    listaDeProveedores.append("Proveedores del Centro");
    listaDeProveedores.append("Simon");
    listaDeProveedores.append("Maral");
    listaDeProveedores.append("Electricidad Luis");
    listaDeProveedores.append("Parsecs");
    listaDeProveedores.append("Maderin");
    listaDeProveedores.append("Norberto");
    listaDeProveedores.append("Petrolux");

    leerProveedores();












    dEditar = new DialogEditar(this);
    dConfirmar = new DialogConfirmar(this);
    ui->pushButtonEditar->setEnabled(false);
    ui->pushButtonBorrar->setEnabled(false);

    dEditarM = new DialogEditarMultiple(this);

    ui->pushButtonAgregarAPedidos->setEnabled(false);
    filaSeleccionadaEnBusqueda = -1;

    filaSeleccionadaEnPedidos = -1;
    ui->pushButtonBorrarPedidos->setEnabled(false);

    qDebug()<<"Aplicación iniciada.";


    QString nombre = "productos.sqlite";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombre);

    db.open();


    //Creando Tabla Productos
    QString ordenes;
    ordenes.append("CREATE TABLE IF NOT EXISTS productos("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "nombre VARCHAR(100),"
                   "fecha VARCHAR(20),"
                   "precio VARCHAR(50),"
                   "prov VARCHAR(100),"
                   "cat VARCHAR(100)"
                   ");");

    QSqlQuery crear;
    crear.prepare(ordenes);

    if(crear.exec()){
        qDebug()<<"Tabla creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla "<< crear.lastError();

    }







    //Creando Tabla Ventas
    QString ordenes2;
    ordenes2.append("CREATE TABLE IF NOT EXISTS ventas("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "pesos VARCHAR(50),"
                    "hora VARCHAR(50),"
                    "fecha VARCHAR(50)"
                    ");");

    QSqlQuery crear2;
    crear2.prepare(ordenes2);

    if(crear2.exec()){
        qDebug()<<"Tabla Ventas creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla Ventas "<< crear2.lastError();

    }

    //Creando Tabla Pagos
    QString ordenes4;
    ordenes4.append("CREATE TABLE IF NOT EXISTS pagos("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "detalles VARCHAR(100),"
                    "pesos VARCHAR(50),"
                    "hora VARCHAR(50),"
                    "fecha VARCHAR(50)"
                    ");");

    QSqlQuery crear4;
    crear4.prepare(ordenes4);

    if(crear4.exec()){
        qDebug()<<"Tabla Pagos creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla Pagos "<< crear4.lastError();

    }

    //Creando Tabla Proveedores
    QString ordenes3;
    ordenes3.append("CREATE TABLE IF NOT EXISTS proveedores("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "proveedor VARCHAR(100)"
                    ");");

    QSqlQuery crear3;
    crear3.prepare(ordenes3);

    if(crear3.exec()){
        qDebug()<<"Tabla Proveedores creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla Proveedores "<< crear3.lastError();

    }
    QString ordenes6;
    ordenes6.append("DELETE FROM proveedores");
    QSqlQuery crear6;
    crear6.prepare(ordenes6);
    crear6.exec();

    for (int i = 0; i < listaDeProveedores.size(); ++i) {
        QString ordenes4;
        ordenes4.append("INSERT INTO proveedores("
                        "proveedor"
                        ")VALUES("
                        "'"+listaDeProveedores.at(i)+"');");
        QSqlQuery crear4;
        crear4.prepare(ordenes4);

        crear4.exec();

    }
    QString ordenes5;
    ordenes5.append("SELECT * FROM proveedores ORDER BY proveedor ASC ");
    QSqlQuery crear5;
    crear5.prepare(ordenes5);
    crear5.exec();
    qDebug()<<"Largo de Crear5 "<< crear5.size();
    listaDeProveedores.clear();
    while (crear5.next()) {
        ui->comboBoxProveedores->addItem(crear5.value(1).toByteArray());
        ui->comboBoxProveedoresBoletas->addItem(crear5.value(1).toByteArray());
        listaDeProveedores.append(crear5.value(1).toByteArray());
    }
    ui->comboBoxProveedoresPed->addItems(listaDeProveedores);
    ui->comboBoxProveedoresPagos->addItems(listaDeProveedores);


    //Creando Tabla Pedidos
    QString ordenes7;
    ordenes7.append("CREATE TABLE IF NOT EXISTS pedidos("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "prov VARCHAR(100)"
                    ");");

    QSqlQuery crear7;
    crear7.prepare(ordenes7);

    if(crear7.exec()){
        qDebug()<<"Tabla pedidos creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla pedidos"<< crear7.lastError();

    }


    //Creando Tabla Boletas
    QString ordenes8;
    ordenes8.append("CREATE TABLE IF NOT EXISTS boletas("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "fecha VARCHAR(50),"
                    "importe VARCHAR(10),"
                    "numfactura VARCHAR(50),"
                    "fechapago VARCHAR(50),"
                    "importepago VARCHAR(10),"
                    "prov VARCHAR(50),"
                    "total VARCHAR(10)"
                    ");");

    QSqlQuery crear8;
    crear8.prepare(ordenes8);

    if(crear8.exec()){
        qDebug()<<"Tabla Boletas creada o existente.";
    }else{
        qDebug()<<"Error al crear tabla Boletas "<< crear8.lastError();

    }




    //Seteando Estilos de Visualización
    ui->tableWidgetProductos->setColumnWidth(0,90);
    ui->tableWidgetProductos->setColumnWidth(1,350);
    ui->tableWidgetProductos->setColumnWidth(2,160);
    ui->tableWidgetProductos->setColumnWidth(3,130);
    ui->tableWidgetProductos->setColumnWidth(4,300);
    ui->tableWidgetProductos->setColumnWidth(5,180);

    ui->tableWidgetResultados->setColumnWidth(0,90);
    ui->tableWidgetResultados->setColumnWidth(1,400);
    ui->tableWidgetResultados->setColumnWidth(2,300);
    ui->tableWidgetResultados->setColumnWidth(3,100);
    ui->tableWidgetResultados->setColumnWidth(4,300);


    ui->tableWidgetBoletas->setColumnWidth(0,200);
    ui->tableWidgetBoletas->setColumnWidth(1,160);
    ui->tableWidgetBoletas->setColumnWidth(2,300);
    ui->tableWidgetBoletas->setColumnWidth(3,200);
    ui->tableWidgetBoletas->setColumnWidth(4,160);
    ui->tableWidgetBoletas->setColumnWidth(5,200);
    //ui->tableWidgetResultados->setColumnWidth(1,400);
    //ui->tableWidgetResultados->setColumnWidth(2,300);
    //ui->tableWidgetResultados->setColumnWidth(3,100);
    //ui->tableWidgetResultados->setColumnWidth(4,300);



    QHeaderView *verticalHeader = ui->tableWidgetProductos->verticalHeader();
    //verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(38);

    QHeaderView *verticalHeaderR = ui->tableWidgetResultados->verticalHeader();
    //verticalHeaderR->sectionResizeMode(QHeaderView::Fixed);
    verticalHeaderR->setDefaultSectionSize(38);

    QHeaderView *verticalHeaderV = ui->tableWidgetListaVentas->verticalHeader();
    //verticalHeaderR->sectionResizeMode(QHeaderView::Fixed);
    verticalHeaderV->setDefaultSectionSize(38);


    setearEstilos();

    ui->lineEditFecha->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy"));



    QString estiloDeAlmanaque=""
                              "QAbstractItemView {selection-background-color: rgb(255, 174, 0);}"
                              "";
    ui->Almanaque->setStyleSheet(estiloDeAlmanaque);
    ui->AlmanaquePagos->setStyleSheet(estiloDeAlmanaque);

    QRegExp rx("(|\"|/|\\.|[-0-9]){30}");
    ui->lineEditVenta->setValidator(new QRegExpValidator(rx, this));
    ui->lineEditPrecio->setValidator(new QRegExpValidator(rx, this));
    ui->lineEditPago->setValidator(new QRegExpValidator(rx, this));

    //QRegExp rxPagos("(|\"|/|\\.|[-0-9]){30}");

    actualizarTablaProductos();
    actualizarTablaListaVentas(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    actualizarTablaPedidos();
    actualizarTablaListaPagos(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    buscar("", 1);

    /*QRect rec = QApplication::desktop()->screenGeometry();
    setGeometry(0,100,rec.width()/2, rec.height()/2);*/
    showMaximized();
    ui->tabWidgetTareas->setCurrentIndex(2);

    //import("C:\\lista_1.xlsx",1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setearEstilos()
{
    QByteArray estilo;
    estilo.append("QWidget{"
                  "font-size:20pt;"
                  "}"
                  "QTabWidget {"
                  //"border: 10;"
                  "}"
                  "QTabWidget::pane {"
                  "background-color:#ffffff;"
                  "color: #000000;"
                  "border: 3px solid #5a93f1;"
                  "}"
                   "QTabBar::tab {"
                    "background-color:#cccccc;"
                    "color: #000000;"
                    "border-top: 1px solid #000;"
                    "border-left: 1px solid #000;"
                    "border-right: 1px solid #000;"
                    "border-bottom-color: #000;"
                    "border-top-left-radius: 4px;"
                    "border-top-right-radius: 4px;"
                  "padding: 10px;"
                  "margin-top: 2px;"
                  "margin-left: 2px;"
                  "margin-bottom: 0px;"
                    "}"
                    "QTabBar::tab:selected{"
                    "background-color:#ffffff;"
                    "color: #000000;"
                    "border-top: 3px solid #5a93f1;"
                    "border-left: 3px solid #5a93f1;"
                    "border-right: 3px solid #5a93f1;"
                    "border-bottom-color: #5a93f1;"
                    "border-top-left-radius: 4px;"
                    "border-top-right-radius: 4px;"
                    "padding: 10px;"
                    "margin-top: 2px;"
                    "margin-left: 2px;"
                    "margin-bottom: 0px;"
                    "}"
                    "QTabBar::hover{"
                    "background-color:#cccccc;"
                    "color:#000000;"
                    "}"
                    );
        setStyleSheet(estilo);
}

void MainWindow::leerProveedores()
{
    QFile proveedores("proveedores.txt");
    if(proveedores.exists() && proveedores.open(QIODevice::ReadOnly)){
        qDebug()<< "Se leyo el archivo de proveedores.";
        listaDeProveedores.clear();
        QTextStream entranDatos(&proveedores);

        while(!entranDatos.atEnd()) {
            QString renglon = entranDatos.readLine();
            listaDeProveedores.append(renglon);
            //ui->comboBoxProveedoresBoletas
        }

        proveedores.close();
    }else{
        if(!proveedores.exists()){
            //qDebug()<< "No leyo el archivo de proveedores.";
            QMessageBox::information(
                        this,
                        tr(NOMBRE_DE_APP),
                        tr("El archivo \"proveedores.txt ha sido borrado!\""));
        }else{
            qDebug()<< "No leyo el archivo de proveedores.";
            QMessageBox::information(
                        this,
                        tr(NOMBRE_DE_APP),
                        tr("El archivo existe pero hay\nproblemas de lectura en archivo \"proveedores.txt.\""));
        }
    }
}

void MainWindow::imprimirFila(QByteArray cod, QByteArray nombre, QByteArray fecha, QByteArray precio, QByteArray prov, QByteArray cat)
{
    QTableWidgetItem *celdaCod = new QTableWidgetItem();
    celdaCod->setText(cod.constData());
    celdaCod->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaNombre = new QTableWidgetItem();
    celdaNombre->setText(nombre.constData());
    celdaNombre->setTextAlignment(Qt::AlignLeft);

    QTableWidgetItem *celdaFecha = new QTableWidgetItem();
    celdaFecha->setText(fecha.constData());
    celdaFecha->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaPrecio = new QTableWidgetItem();
    celdaPrecio->setText(QString("$")+precio.constData());
    celdaPrecio->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaProv = new QTableWidgetItem();
    celdaProv->setText(prov.constData());
    celdaProv->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaCat = new QTableWidgetItem();
    celdaCat->setText(cat.constData());
    celdaCat->setTextAlignment(Qt::AlignHCenter);

    if (color==0) {
        celdaCod->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaNombre->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaFecha->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaPrecio->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaProv->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaCat->setBackgroundColor(QColor(listaDeColores.at(0)));
        color=1;
    }else{
        celdaCod->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaNombre->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaFecha->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaPrecio->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaProv->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaCat->setBackgroundColor(QColor(listaDeColores.at(1)));
        color=0;
    }


    ui->tableWidgetProductos->insertRow(0);
    ui->tableWidgetProductos->setItem(0, 0, celdaCod);
    ui->tableWidgetProductos->setItem(0, 1, celdaNombre);
    ui->tableWidgetProductos->setItem(0, 2, celdaFecha);
    ui->tableWidgetProductos->setItem(0, 3, celdaPrecio);
    ui->tableWidgetProductos->setItem(0, 4, celdaProv);
    ui->tableWidgetProductos->setItem(0, 5, celdaCat);


}

void MainWindow::imprimirFilaResultados(QByteArray cod, QByteArray nombre, QByteArray fecha, QByteArray precio, QByteArray prov)
{
    QTableWidgetItem *celdaCod = new QTableWidgetItem();
    celdaCod->setText(cod.constData());
    celdaCod->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaNombre = new QTableWidgetItem();
    celdaNombre->setText(nombre.constData());
    celdaNombre->setTextAlignment(Qt::AlignLeft);

    QTableWidgetItem *celdaFecha = new QTableWidgetItem();
    celdaFecha->setText(fecha.constData());
    celdaFecha->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaPrecio = new QTableWidgetItem();
    celdaPrecio->setText(QString("$")+precio.constData());
    celdaPrecio->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaProv = new QTableWidgetItem();
    celdaProv->setText(prov.constData());
    celdaProv->setTextAlignment(Qt::AlignHCenter);

    if (color==0) {
        celdaCod->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaNombre->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaFecha->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaPrecio->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaProv->setBackgroundColor(QColor(listaDeColores.at(0)));
        color=1;
    }else{
        celdaCod->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaNombre->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaFecha->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaPrecio->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaProv->setBackgroundColor(QColor(listaDeColores.at(1)));
        color=0;
    }


    ui->tableWidgetResultados->insertRow(0);
    ui->tableWidgetResultados->setItem(0, 0, celdaCod);
    ui->tableWidgetResultados->setItem(0, 1, celdaNombre);
    ui->tableWidgetResultados->setItem(0, 2, celdaFecha);
    ui->tableWidgetResultados->setItem(0, 3, celdaPrecio);
    ui->tableWidgetResultados->setItem(0, 4, celdaProv);
}

void MainWindow::imprimirFilaVentas(QByteArray pesos, QByteArray hora)
{
    QTableWidgetItem *celdaPesos = new QTableWidgetItem();
    celdaPesos->setText(pesos.constData());
    celdaPesos->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaHora = new QTableWidgetItem();
    celdaHora->setText(hora.constData());
    celdaHora->setTextAlignment(Qt::AlignHCenter);



    if (color==0) {
        celdaPesos->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaHora->setBackgroundColor(QColor(listaDeColores.at(0)));
        color=1;
    }else{
        celdaPesos->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaHora->setBackgroundColor(QColor(listaDeColores.at(1)));
        color=0;
    }


    ui->tableWidgetListaVentas->insertRow(0);
    ui->tableWidgetListaVentas->setItem(0, 0, celdaPesos);
    ui->tableWidgetListaVentas->setItem(0, 1, celdaHora);

}

void MainWindow::imprimirFilaPagos(QByteArray detalles, QByteArray pesos, QByteArray hora)
{
    QTableWidgetItem *celdaDetalles = new QTableWidgetItem();
    celdaDetalles->setText(detalles.constData());
    celdaDetalles->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaPesos = new QTableWidgetItem();
    celdaPesos->setText(pesos.constData());
    celdaPesos->setTextAlignment(Qt::AlignHCenter);

    QTableWidgetItem *celdaHora = new QTableWidgetItem();
    celdaHora->setText(hora.constData());
    celdaHora->setTextAlignment(Qt::AlignHCenter);



    if (color==0) {
        celdaDetalles->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaPesos->setBackgroundColor(QColor(listaDeColores.at(0)));
        celdaHora->setBackgroundColor(QColor(listaDeColores.at(0)));
        color=1;
    }else{
        celdaDetalles->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaPesos->setBackgroundColor(QColor(listaDeColores.at(1)));
        celdaHora->setBackgroundColor(QColor(listaDeColores.at(1)));
        color=0;
    }


    ui->tableWidgetListaPagos->insertRow(0);
    ui->tableWidgetListaPagos->setItem(0, 0, celdaDetalles);
    ui->tableWidgetListaPagos->setItem(0, 1, celdaPesos);
    ui->tableWidgetListaPagos->setItem(0, 2, celdaHora);
}

void MainWindow::actualizarTablaProductos()
{
    ui->tableWidgetProductos->setRowCount(0);

    if (ui->lineEditNombre->text().isEmpty()) {

    QString ordenes;
    ordenes.append("SELECT * FROM productos");

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta .";
        qDebug()<<consultar.lastError();

    }

    while (consultar.next()) {
        imprimirFila(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray(), consultar.value(5).toByteArray());
    }
    }else{
        buscar(ui->lineEditNombre->text(), 2);
    }
    ui->lineEditNombre->setFocus();
}

void MainWindow::actualizarTablaListaVentas(QString f)
{
    ui->tableWidgetListaVentas->setRowCount(0);

    QString ordenes;
    ordenes.append("SELECT * FROM ventas WHERE fecha='"+f+"' ORDER BY id DESC");

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta en ventas correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en ventas.";
        qDebug()<<consultar.lastError();

    }

    while (consultar.next()) {
        imprimirFilaVentas(consultar.value(1).toByteArray(), consultar.value(2).toByteArray());
    }

    double totalManana=0;
    double totalTarde=0;
    double totalDia=0;


    for (int i = 0; i < ui->tableWidgetListaVentas->rowCount(); ++i) {
        QTableWidgetItem *pesos=ui->tableWidgetListaVentas->item(i,0);

        QTableWidgetItem *hora=ui->tableWidgetListaVentas->item(i,1);
        QStringList l1 = hora->text().split(":");
        int horaDeVenta = QString(l1.at(0)).toInt();
        if(horaDeVenta<=14){
            totalManana+=pesos->text().toDouble();
        }else{
            totalTarde+=pesos->text().toDouble();
        }
        totalDia=totalManana+totalTarde;

        ui->labelManana->setText("Mañana: $"+arreglarCentavos(QString::number(totalManana)));
        ui->labelTarde->setText("Tarde: $"+arreglarCentavos(QString::number(totalTarde)));
        ui->labelTotal->setText("Total: $"+arreglarCentavos(QString::number(totalDia)));

    }
    ui->tableWidgetListaVentas->scrollToBottom();

    int totalDeMes = 0;

    QString ordenesCalcularVentasMes;
    ordenesCalcularVentasMes.append("SELECT * FROM ventas WHERE fecha LIKE '%"+f.mid(2, 9)+"' ORDER BY id DESC");
    qDebug()<<"Buscando ventas --> " << ordenesCalcularVentasMes;

    QSqlQuery consultarCalcularVentasMes;
    consultarCalcularVentasMes.prepare(ordenesCalcularVentasMes);

    if(consultarCalcularVentasMes.exec()){
        qDebug()<<"Se ha realizado la consulta en ventas DE MES correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en ventas DE MES.";
        qDebug()<<consultarCalcularVentasMes.lastError();

    }

    while (consultarCalcularVentasMes.next()) {
        totalDeMes+=consultarCalcularVentasMes.value(1).toInt();
    }
    ui->labelVentasDeMes->setText("Este Mes: $"+arreglarCentavos(QString::number(totalDeMes)));


}

void MainWindow::actualizarTablaListaPagos(QString f)
{
    ui->tableWidgetListaPagos->setRowCount(0);

    QString ordenes;
    ordenes.append("SELECT * FROM pagos WHERE fecha='"+f+"' ORDER BY id DESC");

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta en pagos correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en pagos.";
        qDebug()<<consultar.lastError();

    }

    while (consultar.next()) {
        imprimirFilaPagos(consultar.value(1).toByteArray(),consultar.value(2).toByteArray(), consultar.value(3).toByteArray());
    }


    double totalDia=0;


    for (int i = 0; i < ui->tableWidgetListaPagos->rowCount(); ++i) {
        QTableWidgetItem *pesos=ui->tableWidgetListaPagos->item(i,1);
        totalDia+=pesos->text().toDouble();

        ui->labelPagosHoy->setText("Hoy: $"+arreglarCentavos(QString::number(totalDia)));

    }
    ui->tableWidgetListaPagos->scrollToBottom();






    int totalDeMes = 0;

    QString ordenesCalcularPagosMes;
    ordenesCalcularPagosMes.append("SELECT * FROM pagos WHERE fecha LIKE '%"+f.mid(2, 9)+"' ORDER BY id DESC");
    qDebug()<<"Buscando pagos --> " << ordenesCalcularPagosMes;

    QSqlQuery consultarCalcularPagosMes;
    consultarCalcularPagosMes.prepare(ordenesCalcularPagosMes);

    if(consultarCalcularPagosMes.exec()){
        qDebug()<<"Se ha realizado la consulta en pagos DE MES correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en pagos DE MES.";
        qDebug()<<consultarCalcularPagosMes.lastError();

    }

    while (consultarCalcularPagosMes.next()) {
        totalDeMes+=consultarCalcularPagosMes.value(2).toInt();
    }
    ui->labelPagosDeMes->setText("Este Mes: $"+arreglarCentavos(QString::number(totalDeMes)));
}

void MainWindow::actualizarTablaListaBoletas()
{
    ui->tableWidgetBoletas->setRowCount(0);
    QString ordenes;
    ordenes.append("SELECT * FROM boletas WHERE prov='"+ui->comboBoxProveedoresBoletas->currentText()+"' ORDER BY id ASC");
    //qDebug()<<"Buscando s --> " << ordenesCalcularPagosMes;

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta en tabla boletas correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en tabla boletas.";
        qDebug()<<consultar.lastError();

    }

    //int color
    while (consultar.next()) {
        //QTableWidgetItem *fecha=consultar.value(1).toString();

        QByteArray dFecha;
        dFecha.append(consultar.value(1).toString());

        QByteArray dImporte;
        dImporte.append(consultar.value(2).toString());

        QByteArray dFactura;
        dFactura.append(consultar.value(3).toString());

        QByteArray dFechaPago;
        dFechaPago.append(consultar.value(4).toString());

        QByteArray dImportePago;
        dImportePago.append(consultar.value(5).toString());

        QByteArray dTotal;
        dTotal.append(consultar.value(7).toString());

        QTableWidgetItem *celdaFecha = new QTableWidgetItem();
        celdaFecha->setText(dFecha.constData());
        celdaFecha->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *celdaImporte = new QTableWidgetItem();
        if(dImporte!=""){
            celdaImporte->setText(QString("$")+dImporte.constData());
        }else{
            celdaImporte->setText(dImporte.constData());
        }
        celdaImporte->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *celdaFactura = new QTableWidgetItem();
        celdaFactura->setText(dFactura.constData());
        celdaFactura->setTextAlignment(Qt::AlignHCenter);



        QTableWidgetItem *celdaFechaPago = new QTableWidgetItem();
        celdaFechaPago->setText(dFechaPago.constData());
        celdaFechaPago->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *celdaImportePago = new QTableWidgetItem();
        if(dImportePago!=""){
            celdaImportePago->setText(QString("$")+dImportePago.constData());
        }else{
            celdaImportePago->setText(dImportePago.constData());
        }
        celdaImportePago->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *celdaTotal = new QTableWidgetItem();
        celdaTotal->setText(QString("$")+dTotal.constData());
        celdaTotal->setTextAlignment(Qt::AlignHCenter);


            celdaFecha->setBackgroundColor(QColor(listaDeColores.at(0)));
            celdaImporte->setBackgroundColor(QColor(listaDeColores.at(0)));
            celdaFactura->setBackgroundColor(QColor(listaDeColores.at(0)));
            celdaFechaPago->setBackgroundColor(QColor(listaDeColores.at(1)));
            celdaImportePago->setBackgroundColor(QColor(listaDeColores.at(1)));
            celdaTotal->setBackgroundColor(QColor(listaDeColores.at(0)));
            color=1;

        int ulfila=ui->tableWidgetBoletas->rowCount();
        ui->tableWidgetBoletas->insertRow(ulfila);
        ui->tableWidgetBoletas->setItem(ulfila, 0, celdaFecha);
        ui->tableWidgetBoletas->setItem(ulfila, 1, celdaImporte);
        ui->tableWidgetBoletas->setItem(ulfila, 2, celdaFactura);
        ui->tableWidgetBoletas->setItem(ulfila, 3, celdaFechaPago);
        ui->tableWidgetBoletas->setItem(ulfila, 4, celdaImportePago);
        ui->tableWidgetBoletas->setItem(ulfila, 5, celdaTotal);
        //ui->tableWidgetBoletas->setItem(ulfila, 6, new QTableWidgetItem(dFecha.constData()));
        //totalDeMes+=consultarCalcularPagosMes.value(2).toInt();

    }
    ui->tableWidgetBoletas->scrollToBottom();
}

void MainWindow::actualizarTablaPedidos()
{
    ui->tableWidgetPedidos->setRowCount(0);

    QString ordenes;
    ordenes.append("SELECT * FROM pedidos WHERE prov='"+ui->comboBoxProveedoresPed->currentText()+"' ORDER BY id ASC");

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta en pedidos correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta en pedidos.";
        qDebug()<<consultar.lastError();

    }

    while (consultar.next()) {
        int nuevaFila = ui->tableWidgetPedidos->rowCount();
        ui->tableWidgetPedidos->insertRow(nuevaFila);
        ui->tableWidgetPedidos->setItem(nuevaFila,0, new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
    }
    ui->tableWidgetPedidos->scrollToBottom();
}

void MainWindow::buscar(QString b, int t)
{
    if (t==1) {
        ui->tableWidgetResultados->setRowCount(0);
        QString ordenes;
        if(ui->comboBoxCategoriasResultados->currentText()==QString("Todas")){
            QStringList m1 = ui->lineEdit->text().split(" ");
            if(m1.size()<=1){
            ordenes.append("SELECT * FROM productos "
                           "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");
            }else{
                ordenes.append("SELECT * FROM productos WHERE nombre LIKE '%");
                for (int i = 0; i < m1.size(); ++i) {
                    if(!QString(m1.at(i)).isEmpty()){
                    ordenes.append(m1.at(i));
                    ordenes.append("%");
                    }
                }
                ordenes.append("';");
                qDebug()<<"Consulta de Busqueda: "<<ordenes;
                /*ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");*/
            }
        }else{
            ordenes.append("SELECT * FROM productos "
                           "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%' "
                                                                       " AND cat='"+ui->comboBoxCategoriasResultados->currentText()+"'"
                                                                                                                                    ";");
        }

        QSqlQuery consultar;
        consultar.prepare(ordenes);

        if(consultar.exec()){
            qDebug()<<"Se ha realizado la consulta correctamente.";
        }else{
            qDebug()<<"NO Se ha realizado la consulta .";
            qDebug()<<consultar.lastError();

        }
        int veces=0;

        while (consultar.next()) {
            imprimirFilaResultados(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray());
            veces++;
        }
        if(veces==0 && !ui->lineEdit->text().isEmpty()){
            ordenes.clear();
            if(ui->comboBoxCategoriasResultados->currentText()==QString("Todas")){
                QStringList m1 = ui->lineEdit->text().split(" ");
                if(m1.size()<=1){
                ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");
                }else{
                    ordenes.append("SELECT * FROM productos WHERE nombre LIKE '%");
                    int tamM1 = m1.size();
                    for (int i = tamM1; i > 0; --i) {
                        qDebug()<<"Iterador inverso: "<<i;
                        if(!QString(m1.at(i-1)).isEmpty()){
                        ordenes.append(m1.at(i-1));
                        ordenes.append("%");
                        }
                    }
                    ordenes.append("';");
                    qDebug()<<"Consulta de Busqueda: "<<ordenes;
                    /*ordenes.append("SELECT * FROM productos "
                                   "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");*/
                }
            }else{
                ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%' "
                                                                           " AND cat='"+ui->comboBoxCategoriasResultados->currentText()+"'"
                                                                                                                                        ";");
            }

            QSqlQuery consultar;
            consultar.prepare(ordenes);

            if(consultar.exec()){
                qDebug()<<"Se ha realizado la consulta correctamente.";
            }else{
                qDebug()<<"NO Se ha realizado la consulta .";
                qDebug()<<consultar.lastError();

            }
            while (consultar.next()) {
                imprimirFilaResultados(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray());
            }

        }
    }else{
        //COMIENZA A BUSCAR EN CARGAR PRODUCTOS
        ui->tableWidgetProductos->setRowCount(0);
        QString ordenes;
        if(ui->comboBoxCategoriasResultados->currentText()==QString("Todas")){
            QStringList m1 = ui->lineEditNombre->text().split(" ");
            if(m1.size()<=1){
            ordenes.append("SELECT * FROM productos "
                           "WHERE nombre LIKE '%"+ui->lineEditNombre->text()+"%';");
            }else{
                ordenes.append("SELECT * FROM productos WHERE nombre LIKE '%");
                for (int i = 0; i < m1.size(); ++i) {
                    if(!QString(m1.at(i)).isEmpty()){
                    ordenes.append(m1.at(i));
                    ordenes.append("%");
                    }
                }
                ordenes.append("';");
                qDebug()<<"Consulta de Busqueda: "<<ordenes;
                /*ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");*/
            }
        }else{
            ordenes.append("SELECT * FROM productos "
                           "WHERE nombre LIKE '%"+ui->lineEditNombre->text()+"%' "
                                                                       " AND cat='"+ui->comboBoxCategorias->currentText()+"'"
                                                                                                                                    ";");
        }

        QSqlQuery consultar;
        consultar.prepare(ordenes);

        if(consultar.exec()){
            qDebug()<<"Se ha realizado la consulta correctamente 102.";
        }else{
            qDebug()<<"NO Se ha realizado la consulta .";
            qDebug()<<consultar.lastError();

        }
        int veces=0;

        while (consultar.next()) {
            imprimirFila(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray(), consultar.value(5).toByteArray());
            veces++;
        }
        if(veces==0 && !ui->lineEditNombre->text().isEmpty()){
            ordenes.clear();
            //if(ui->comboBoxCategorias->currentText()==QString("Todas")){
                QStringList m1 = ui->lineEditNombre->text().split(" ");
                if(m1.size()<=1){
                ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEditNombre->text()+"%';");
                }else{
                    ordenes.append("SELECT * FROM productos WHERE nombre LIKE '%");
                    int tamM1 = m1.size();
                    for (int i = tamM1; i > 0; --i) {
                        qDebug()<<"Iterador inverso 2: "<<i;
                        if(!QString(m1.at(i-1)).isEmpty()){
                        ordenes.append(m1.at(i-1));
                        ordenes.append("%");
                        }
                    }
                    ordenes.append("';");
                    qDebug()<<"Consulta de Busqueda 103: "<<ordenes;
                    /*ordenes.append("SELECT * FROM productos "
                                   "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");*/
                }
            /*}else{
                ordenes.append("SELECT * FROM productos "
                               "WHERE nombre LIKE '%"+ui->lineEditNombre->text()+"%' "
                                                                           " AND cat='"+ui->comboBoxCategorias->currentText()+"'"
                                                                                                                                        ";");
            }*/

            QSqlQuery consultar;
            consultar.prepare(ordenes);

            if(consultar.exec()){
                qDebug()<<"Se ha realizado la consulta correctamente.";
            }else{
                qDebug()<<"NO Se ha realizado la consulta .";
                qDebug()<<consultar.lastError();

            }
            while (consultar.next()) {
                imprimirFila(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray(), consultar.value(5).toByteArray());
            }

        }
    }



}

void MainWindow::modificarDatos(QByteArray n, QByteArray f,QByteArray p, QByteArray prov, QByteArray cate)
{
    ui->statusBar->showMessage("Modificando datos en fila "+ filaSeleccionada, 4000);

    QString ordenes;
    ordenes.append("UPDATE productos SET "
                   "nombre='"+n+"',"
                                "fecha='"+f+"',"
                                            "precio='"+p+"',"
                                                         "prov='"+prov+"',"
                                                                       "cat='"+cate+"'"
                                                                                    " WHERE id="+QString::number(filaSeleccionada)+";");

    QSqlQuery crear;
    crear.prepare(ordenes);

    if(crear.exec()){
        //qDebug()<<"";
        ui->statusBar->showMessage("Se ha MODIFICADO el dato correctamente."+ filaSeleccionada, 4000);
    }else{
        qDebug()<<"NO Se ha MODIFICADO el dato correctamente.";
        qDebug()<<crear.lastError();

    }
    actualizarTablaProductos();
}

void MainWindow::modificarMultiple(QString cat, QString prov, int porc)
{
    if(cat!="No Modificar"){

        for (int i = 0; i < listaDeIdSeleccionados.size(); ++i) {

            QString ordenes;
            ordenes.append("UPDATE productos SET "
                           "cat='"+cat+"'"
                                       " WHERE id="+listaDeIdSeleccionados.at(i)->text()+";");

            QSqlQuery crear;
            crear.prepare(ordenes);

            if(crear.exec()){
                qDebug()<<"Se ha MODIFICADO [cat] correctamente.";
            }else{
                qDebug()<<"NO se ha MODIFICADO [cat] correctamente";
                qDebug()<<crear.lastError();
            }
        }


    }
    if(prov!="No Modificar"){
        for (int i = 0; i < listaDeIdSeleccionados.size(); ++i) {
            QString ordenes;
            ordenes.append("UPDATE productos SET "
                           "prov='"+prov+"'"
                                         " WHERE id="+listaDeIdSeleccionados.at(i)->text()+";");

            QSqlQuery crear;
            crear.prepare(ordenes);

            if(crear.exec()){
                qDebug()<<"Se ha MODIFICADO [prov] correctamente.";
            }else{
                qDebug()<<"NO se ha MODIFICADO [prov] correctamente";
                qDebug()<<crear.lastError();
            }
        }

    }
    if(porc!=0){
        for (int i = 0; i < listaDeIdSeleccionados.size(); ++i) {

            QString celdaPrecio = listaDePreciosSeleccionados.at(i)->text();
            celdaPrecio.replace("$", "");
            double pv = celdaPrecio.toDouble();
            double au = (double)pv/100*porc;
            double np = (double)pv+(double)au;

            QString ordenes;
            ordenes.append("UPDATE productos SET "
                           "precio='"+arreglarCentavos(QString::number(np))+"'"
                                                                            " WHERE id="+listaDeIdSeleccionados.at(i)->text()+";");

            QSqlQuery crear;
            crear.prepare(ordenes);

            if(crear.exec()){
                qDebug()<<"Se ha MODIFICADO [precio-porc] correctamente.";
            }else{
                qDebug()<<"NO se ha MODIFICADO [precio-porc] correctamente";
                qDebug()<<crear.lastError();
            }
        }

    }
    actualizarTablaProductos();
}

void MainWindow::import(QString fileName, int sheetNumber)
{

    /*QAxObject* excel = new QAxObject( "Excel.Application", 0 );
            QAxObject* workbooks = excel->querySubObject( "Workbooks" );
            QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", fileName );
            QAxObject* sheets = workbook->querySubObject( "Worksheets" );
            int sheetCount = sheets->dynamicCall("Count()").toInt();        //worksheets count
            QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

            // Find the cells that actually have content
            QAxObject* usedrange = sheet->querySubObject( "UsedRange");
            QAxObject * rows = usedrange->querySubObject("Rows");
            QAxObject * columns = usedrange->querySubObject("Columns");
            int intRowStart = usedrange->property("Row").toInt();
            int intColStart = usedrange->property("Column").toInt();
            int intCols = columns->property("Count").toInt();
            int intRows = rows->property("Count").toInt();

            // replicate the Excel content in the QTableWidget
            ui->tableWidgetExcel->setColumnCount(intColStart+intCols);
            ui->tableWidgetExcel->setRowCount(intRowStart+intRows);
            for (int row=intRowStart ; row < intRowStart+intRows ; row++) {
                for (int col=intColStart ; col < intColStart+intCols ; col++) {
                    QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row, col );
                    QVariant value = cell->dynamicCall( "Value()" );
                    if (value.toString().isEmpty())
                        continue;

                    QTableWidgetItem * twi = new QTableWidgetItem(value.toString());
                    ui->tableWidgetExcel->setItem(row-1, col-1, twi);
                }
            }

            // clean up and close up
            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");*/

}

int MainWindow::existeProducto(QString p)
{
    int retorna = -1;

    QString ordenes;
    ordenes.append("SELECT * FROM productos "
                   "WHERE nombre='"+p+"';");

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha chequeado existencia del producto correctamente.";
    }else{
        qDebug()<<"No se ha chequeado existencia del producto correctamente.";
        qDebug()<<consultar.lastError();

    }


    while (consultar.next()) {
        retorna = consultar.value(0).toInt();
        qDebug()<<"Retornando: "<<QString::number(retorna);
        break;
    }

    return retorna;
}


QString MainWindow::arreglarCentavos(QString v)
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

void MainWindow::on_pushButtonGrabar_clicked()
{
    qDebug()<<"Empieza a Grabar...";
    int cheqExiste=existeProducto(ui->lineEditNombre->text());

    if(cheqExiste==-1 && !ui->lineEditNombre->text().isEmpty() && !ui->lineEditFecha->text().isEmpty() && !ui->lineEditPrecio->text().isEmpty()){


        QString ordenes;
        ordenes.append("INSERT INTO productos("
                       "nombre,"
                       "fecha,"
                       "precio,"
                       "prov,"
                       "cat"
                       ")VALUES("
                       "'"+ui->lineEditNombre->text()+"',"
                                                      "'"+ui->lineEditFecha->text()+"',"
                                                                                    "'"+ui->lineEditPrecio->text()+"',"
                                                                                                                   "'"+ui->comboBoxProveedores->currentText()+"',"
                                                                                                                                                              "'"+ui->comboBoxCategorias->currentText()+"'"
                                                                                                                                                                                                        ");");

        QSqlQuery crear;
        crear.prepare(ordenes);

        if(crear.exec()){
            qDebug()<<"Se ha grabado el dato correctamente.";
        }else{
            qDebug()<<"NO Se ha grabado el dato correctamente.";
            qDebug()<<crear.lastError();

        }

        actualizarTablaProductos();

    }else{

        //qDebug()<<"Hay campos vacios, no se grabó nada.";
        if(cheqExiste==-1){
            ui->statusBar->showMessage("Hay campos vacios, no se grabó nada.", 1000);
        }else{
            QByteArray mens;
            mens.append("Ya existe un\nproducto con este nombre\n\""+ui->lineEditNombre->text()+"\".");
            /*mens.append("Ya existe un\nproducto con este nombre\n\""+ui->lineEditNombre->text()+"\".");
            mens.append("Ya existe un\nproducto con este nombre\n\""+ui->lineEditNombre->text()+"\".");*/
            QMessageBox::information(
                        this,
                        tr(NOMBRE_DE_APP),
                        tr(mens));
        }
    }
}

void MainWindow::on_tableWidgetProductos_cellEntered(int row, int column)
{
    ui->statusBar->showMessage("Entered en celda.", 2000);
}

void MainWindow::on_pushButtonEditar_clicked()
{
    ui->pushButtonEditar->setEnabled(false);
    ui->pushButtonBorrar->setEnabled(false);
    int numeroDeFila = ui->tableWidgetProductos->currentRow();

    QItemSelectionModel *selections = ui->tableWidgetProductos->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    int cantidadSeleccionada = selected.size();
    qDebug()<<"Cantidad de Filas Seleccionada: "<< QString::number(cantidadSeleccionada);

    if(cantidadSeleccionada<=6){
        QTableWidgetItem *celdaNombre = ui->tableWidgetProductos->item(numeroDeFila, 1);
        QTableWidgetItem *celdaFecha = ui->tableWidgetProductos->item(numeroDeFila, 2);
        QTableWidgetItem *celdaPrecio = ui->tableWidgetProductos->item(numeroDeFila, 3);
        QTableWidgetItem *celdaProv = ui->tableWidgetProductos->item(numeroDeFila, 4);
        QTableWidgetItem *celdaCat = ui->tableWidgetProductos->item(numeroDeFila, 5);

        dEditar = new DialogEditar(this);
        dEditar->setListProv(listaDeProveedores);
        dEditar->mostrarDatos(celdaNombre->text(), celdaFecha->text(), celdaPrecio->text(), celdaProv->text(), celdaCat->text());

        connect(dEditar, SIGNAL(modificando(QByteArray,QByteArray,QByteArray,QByteArray,QByteArray)), this, SLOT(modificarDatos(QByteArray,QByteArray,QByteArray,QByteArray,QByteArray)));

        dEditar->exec();
    }else{
        listaDeIdSeleccionados.clear();
        listaDePreciosSeleccionados.clear();
        listaDeProvSeleccionados.clear();
        listaDeCatSeleccionados.clear();

        for( int i = 0 ; i < selected.size(); i+=6 )
        {
            int rowid = selected[i].row();
            //qDebug()<<"Fila Seleccionada: "<< QString::number(rowid);
            listaDeIdSeleccionados.append(ui->tableWidgetProductos->item(rowid,0));
            listaDePreciosSeleccionados.append(ui->tableWidgetProductos->item(rowid,3));
            listaDeProvSeleccionados.append(ui->tableWidgetProductos->item(rowid,4));
            listaDeCatSeleccionados.append(ui->tableWidgetProductos->item(rowid,5));

        }


        dEditarM = new DialogEditarMultiple(this);
        dEditarM->setListProv(listaDeProveedores);
        connect(dEditarM, SIGNAL(modificando(QString,QString,int)), this, SLOT(modificarMultiple(QString,QString,int)));
        dEditarM->exec();

    }
}

void MainWindow::on_tableWidgetProductos_itemClicked(QTableWidgetItem *item)
{

    QTableWidgetItem *itemSeleccionado=ui->tableWidgetProductos->item(item->row(),0);
    filaSeleccionada = itemSeleccionado->text().toInt();

    ui->pushButtonEditar->setEnabled(true);
    ui->pushButtonBorrar->setEnabled(true);
    ui->statusBar->showMessage("Se ha habilitado el boton Editar. "+QString::number(filaSeleccionada), 3000);



}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    buscar(arg1, 1);
}

void MainWindow::on_pushButtonBorrar_clicked()
{
    ui->pushButtonEditar->setEnabled(false);
    ui->pushButtonBorrar->setEnabled(false);

    QItemSelectionModel *selections = ui->tableWidgetProductos->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    int cantidadSeleccionada = selected.size();
    qDebug()<<"Cantidad de Filas Seleccionada: "<< QString::number(cantidadSeleccionada);

    if(cantidadSeleccionada<=6){

        QTableWidgetItem *itemSeleccionado=ui->tableWidgetProductos->item(ui->tableWidgetProductos->currentRow(),1);
        QString nombreABorrar = itemSeleccionado->text();
        dConfirmar=new DialogConfirmar(this);
        dConfirmar->setPregunta("Realmente desea borrar\n\""+nombreABorrar+"\"?");

        int dialogCode = dConfirmar->exec();
        if(dialogCode == QDialog::Accepted){
            ui->statusBar->showMessage("Se borró el producto",3000);



            QString ordenes;
            ordenes.append("DELETE FROM productos "
                           "WHERE id="+QString::number(filaSeleccionada)+";");

            QSqlQuery consultar;
            consultar.prepare(ordenes);

            if(consultar.exec()){
                qDebug()<<"Se ha borrado el producto correctamente.";
            }else{
                qDebug()<<"NO Se ha borrado el producto .";
                qDebug()<<consultar.lastError();

            }

            ui->tableWidgetProductos->setRowCount(0);
            actualizarTablaProductos();

        }else{
            ui->statusBar->showMessage("Se canceló el borrado",3000);

        }
    }else{
        dConfirmar=new DialogConfirmar(this);
        dConfirmar->setPregunta("Realmente desea borrar\ntodos los productos seleccionados?");

        int dialogCode = dConfirmar->exec();
        if(dialogCode == QDialog::Accepted){
            ui->statusBar->showMessage("Borrando varios productos",1000);
            for( int i = 0 ; i < selected.size(); i+=6 )
            {
                int rowid = selected[i].row();
                qDebug()<<"Fila Seleccionada para borrar: "<< ui->tableWidgetProductos->item(rowid,0)->text();
                QString ordenes;
                ordenes.append("DELETE FROM productos "
                               "WHERE id="+ui->tableWidgetProductos->item(rowid,0)->text()+";");

                QSqlQuery consultar;
                consultar.prepare(ordenes);

                if(consultar.exec()){
                    qDebug()<<"Se ha borrado el producto "+ui->tableWidgetProductos->item(rowid,0)->text()+" correctamente.";
                }else{
                    qDebug()<<"NO Se ha borrado el producto .";
                    qDebug()<<consultar.lastError();

                }
            }
            actualizarTablaProductos();
        }
    }

}

void MainWindow::on_comboBoxCategoriasResultados_currentTextChanged(const QString &arg1)
{
    ui->tableWidgetResultados->setRowCount(0);

    QString ordenes;
    if(ui->comboBoxCategoriasResultados->currentText()==QString("Todas")){
        ordenes.append("SELECT * FROM productos "
                       "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%';");
    }else{
        ordenes.append("SELECT * FROM productos "
                       "WHERE nombre LIKE '%"+ui->lineEdit->text()+"%' "
                                                                   " AND cat='"+ui->comboBoxCategoriasResultados->currentText()+"'"
                                                                                                                                ";");
    }

    QSqlQuery consultar;
    consultar.prepare(ordenes);

    if(consultar.exec()){
        qDebug()<<"Se ha realizado la consulta correctamente.";
    }else{
        qDebug()<<"NO Se ha realizado la consulta .";
        qDebug()<<consultar.lastError();

    }

    while (consultar.next()) {
        imprimirFilaResultados(consultar.value(0).toByteArray(), consultar.value(1).toByteArray(), consultar.value(2).toByteArray(),  consultar.value(3).toByteArray(), consultar.value(4).toByteArray());
    }
}

void MainWindow::on_lineEditVenta_editingFinished()
{
    if(!ui->lineEditVenta->text().isEmpty()){
        QString ordenes;
        ordenes.append("INSERT INTO ventas("
                       "pesos,"
                       "hora,"
                       "fecha"
                       ")VALUES("
                       "'"+ui->lineEditVenta->text()+"',"
                                                     "'"+QDateTime::currentDateTime().toString("hh:mm")+"',"
                                                                                                        "'"+QDateTime::currentDateTime().toString("dd/MM/yyyy")+"'"
                                                                                                                                                                ");");

        QSqlQuery crear;
        crear.prepare(ordenes);

        if(crear.exec()){
            qDebug()<<"Se ha grabado el dato en ventas correctamente.";
        }else{
            qDebug()<<"NO Se ha grabado el dato en ventas correctamente.";
            qDebug()<<crear.lastError();

        }
        actualizarTablaListaVentas(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
        ui->Almanaque->setSelectedDate(QDate::currentDate());
    }
    ui->lineEditVenta->setText("");
}

void MainWindow::on_Almanaque_clicked(const QDate &date)
{
    ui->statusBar->showMessage("Fecha seleccionada: "+date.toString("dd/MM/yyyy"), 3000);
    actualizarTablaListaVentas(date.toString("dd/MM/yyyy"));
}

void MainWindow::on_lineEditNombre_textChanged(const QString &arg1)
{
    buscar(arg1, 2);
}

void MainWindow::on_pushButtonAgregarAPedidos_clicked()
{

    ui->pushButtonAgregarAPedidos->setEnabled(false);

    QTableWidgetItem *celdaNombre = ui->tableWidgetResultados->item(filaSeleccionadaEnBusqueda,1);
    QTableWidgetItem *celdaProv = ui->tableWidgetResultados->item(filaSeleccionadaEnBusqueda,4);
    //qDebug()<<"celdaProv="<<celdaProv->text();
    //qDebug()<<"celdaNombre="<<celdaNombre->text();

    QString ordenes;
    ordenes.append("INSERT INTO pedidos("
                   "nombre,"
                   "prov"
                   ")VALUES("
                   "'"+celdaNombre->text()+"',"
                                           "'"+celdaProv->text()+"'"
                                                                 ");");

    QSqlQuery crear;
    crear.prepare(ordenes);

    if(crear.exec()){
        qDebug()<<"Se ha grabado el dato en pedidos correctamente.";
    }else{
        qDebug()<<"NO Se ha grabado el dato en pedidos correctamente.";
        qDebug()<<crear.lastError();

    }


    ui->tabWidgetTareas->setCurrentIndex(3);
    ui->comboBoxProveedoresPed->setCurrentText(celdaProv->text());
    actualizarTablaPedidos();
}

void MainWindow::on_tableWidgetResultados_clicked(const QModelIndex &index)
{
    filaSeleccionadaEnBusqueda = index.row();
    ui->pushButtonAgregarAPedidos->setEnabled(true);
}

void MainWindow::on_comboBoxProveedoresPed_currentTextChanged(const QString &arg1)
{
    ui->pushButtonBorrarPedidos->setEnabled(true);
    actualizarTablaPedidos();
}

void MainWindow::on_pushButtonBorrarPedidos_clicked()
{
    dConfirmar=new DialogConfirmar(this);
    dConfirmar->setPregunta("Realmente desea borrar\n los pedidos del proveedor\n\""+ui->comboBoxProveedoresPed->currentText()+"\"?");

    int dialogCode = dConfirmar->exec();
    if(dialogCode == QDialog::Accepted){


        ui->pushButtonBorrarPedidos->setEnabled(false);
        QString ordenes;
        ordenes.append("DELETE FROM pedidos WHERE prov='"+ui->comboBoxProveedoresPed->currentText()+"';");

        QSqlQuery crear;
        crear.prepare(ordenes);

        if(crear.exec()){
            qDebug()<<"Se han eliminado los pedidos correctamente.";
        }else{
            qDebug()<<"No se han eliminado los pedidos correctamente.";
            qDebug()<<crear.lastError();

        }
        actualizarTablaPedidos();
    }
}

void MainWindow::on_tableWidgetProductos_clicked(const QModelIndex &index)
{
    //ui->tableWidgetProductos->setSe
}

void MainWindow::on_tabWidgetTareas_currentChanged(int index)
{
    if(index==0){
        buscar(ui->lineEdit->text(), 1);
    }
    if(index==5){
        actualizarTablaListaBoletas();

    }
}

void MainWindow::on_AlmanaquePagos_clicked(const QDate &date)
{
    ui->statusBar->showMessage("Fecha seleccionada: "+date.toString("dd/MM/yyyy"), 3000);
    actualizarTablaListaPagos(date.toString("dd/MM/yyyy"));
}

void MainWindow::on_pushButtonGuardarPago_clicked()
{
    if(!ui->lineEditPago->text().isEmpty()){
        QString ordenes;
        ordenes.append("INSERT INTO pagos("
                       "detalles,"
                       "pesos,"
                       "hora,"
                       "fecha"
                       ")VALUES("
                       "'"+ui->comboBoxProveedoresPagos->currentText()+"',"
                       "'"+ui->lineEditPago->text()+"',"
                       "'"+QDateTime::currentDateTime().toString("hh:mm")+"',"
                       "'"+QDateTime::currentDateTime().toString("dd/MM/yyyy")+"'"
                       ");");

        QSqlQuery crear;
        crear.prepare(ordenes);

        if(crear.exec()){
            qDebug()<<"Se ha grabado el dato en pagos correctamente.";
        }else{
            qDebug()<<"NO Se ha grabado el dato en pagos correctamente.";
            qDebug()<<crear.lastError();

        }
        actualizarTablaListaPagos(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
        ui->AlmanaquePagos->setSelectedDate(QDate::currentDate());
    }
    ui->lineEditPago->setText("");
}

void MainWindow::on_pushButtonAgregarBoleta_clicked()
{
    DialogAgregarBoleta *dab = new DialogAgregarBoleta(this);
    dab->setProvActual(ui->comboBoxProveedoresBoletas->currentText());
    dab->show();
    connect(dab, SIGNAL(insertado()), this, SLOT(actualizarTablaListaBoletas()));
}

void MainWindow::on_pushButtonAgregarPago_clicked()
{
    DialogAgregarPago *dap = new DialogAgregarPago(this);
    dap->setProvActual(ui->comboBoxProveedoresBoletas->currentText());
    dap->show();
    connect(dap, SIGNAL(insertado()), this, SLOT(actualizarTablaListaBoletas()));
}


void MainWindow::on_comboBoxProveedoresBoletas_currentIndexChanged(const QString &arg1)
{
    actualizarTablaListaBoletas();
}

void MainWindow::on_pushButtonBorrarFilaBoletas_clicked()
{

    dConfirmar=new DialogConfirmar(this);
    dConfirmar->setPregunta("Realmente desea borrar esta fila?");

    int dialogCode = dConfirmar->exec();
    if(dialogCode == QDialog::Accepted){


        QString ordenes;
        ordenes.append("delete from boletas where id=(select id from boletas where prov='"+ui->comboBoxProveedoresBoletas->currentText()+"' order by id desc);");

        QSqlQuery crear;
        crear.prepare(ordenes);

        if(crear.exec()){
            qDebug()<<"Se ha borrado ultima fila de boleta correctamente.";
            actualizarTablaListaBoletas();
        }else{
            qDebug()<<"NO Se borrado ultima fila de boleta correctamente.";
            qDebug()<<crear.lastError();

        }

    }
}

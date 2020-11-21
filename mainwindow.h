#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QFile>
#include <QTextStream>

#include <QTableWidgetItem>
#include <QDateTime>

#include <ActiveQt/QAxObject>

#include "dialogeditar.h"
#include "dialogeditarmultiple.h"
#include "dialogconfirmar.h"
#include "dialogagregarboleta.h"
#include "dialogagregarpago.h"
#include <QScrollBar>
#include <QMessageBox>

#include "definiciones.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setearEstilos();
    void leerProveedores();




private slots:
    void imprimirFila(QByteArray cod, QByteArray nombre, QByteArray fecha, QByteArray precio, QByteArray prov, QByteArray cat);
    void imprimirFilaResultados(QByteArray cod, QByteArray nombre, QByteArray fecha, QByteArray precio, QByteArray prov);
    void imprimirFilaVentas(QByteArray pesos, QByteArray hora);
    void imprimirFilaPagos(QByteArray detalles, QByteArray pesos, QByteArray hora);
    void actualizarTablaProductos();
    void actualizarTablaListaVentas(QString f);
    void actualizarTablaListaPagos(QString f);
    void actualizarTablaListaBoletas();
    void actualizarTablaPedidos();
    void buscar(QString b, int t);
    void modificarDatos(QByteArray n, QByteArray f, QByteArray p, QByteArray prov, QByteArray cate);
    void modificarMultiple(QString cat, QString prov, int porc);
    //void grabarProductos();

    void import(QString fileName, int sheetNumber=1);

    int existeProducto(QString p);
    QString arreglarCentavos(QString v);

    void on_pushButtonGrabar_clicked();

    void on_tableWidgetProductos_cellEntered(int row, int column);

    void on_pushButtonEditar_clicked();

    void on_tableWidgetProductos_itemClicked(QTableWidgetItem *item);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonBorrar_clicked();

    void on_comboBoxCategoriasResultados_currentTextChanged(const QString &arg1);

    void on_lineEditVenta_editingFinished();

    void on_Almanaque_clicked(const QDate &date);

    void on_lineEditNombre_textChanged(const QString &arg1);

    void on_pushButtonAgregarAPedidos_clicked();

    void on_tableWidgetResultados_clicked(const QModelIndex &index);

    void on_comboBoxProveedoresPed_currentTextChanged(const QString &arg1);

    void on_pushButtonBorrarPedidos_clicked();

    void on_tableWidgetProductos_clicked(const QModelIndex &index);

    void on_tabWidgetTareas_currentChanged(int index);

    void on_AlmanaquePagos_clicked(const QDate &date);

    void on_pushButtonGuardarPago_clicked();

    void on_pushButtonAgregarBoleta_clicked();

    void on_pushButtonAgregarPago_clicked();

    void on_comboBoxProveedoresBoletas_currentIndexChanged(const QString &arg1);

    void on_pushButtonBorrarFilaBoletas_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    DialogEditar *dEditar;
    DialogEditarMultiple *dEditarM;
    int filaSeleccionada;
    int filaSeleccionadaEnBusqueda;
    int filaSeleccionadaEnPedidos;
    DialogConfirmar *dConfirmar;
    DialogAgregarBoleta *dAgregarBoleta;

    QStringList listaDeProveedores;

    //Para imprimir filas
    QStringList listaDeColores;
    int color;

    QList<QTableWidgetItem*> listaDeIdSeleccionados;
    QList<QTableWidgetItem*> listaDePreciosSeleccionados;
    QList<QTableWidgetItem*> listaDeProvSeleccionados;
    QList<QTableWidgetItem*> listaDeCatSeleccionados;

};

#endif // MAINWINDOW_H

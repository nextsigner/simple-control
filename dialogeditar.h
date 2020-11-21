#ifndef DIALOGEDITAR_H
#define DIALOGEDITAR_H

#include <QDialog>

namespace Ui {
class DialogEditar;
}

class DialogEditar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditar(QWidget *parent = 0);
    ~DialogEditar();

    void mostrarDatos(QString n,QString f,QString p,QString proveedor,QString cate);
    void setListProv(QStringList lp);

    QString nombre;
    QString fecha;
    QString precio;
    QString prov;
    QString cat;

signals:
    void modificando(QByteArray n, QByteArray f, QByteArray p, QByteArray prov, QByteArray c);

private slots:
    QString arreglarCentavos(QString v);
    void on_pushButtonCancelar_clicked();

    void on_pushButtonGuardar_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::DialogEditar *ui;
    double ultimoprecio;


};

#endif // DIALOGEDITAR_H

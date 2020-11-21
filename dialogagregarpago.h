#ifndef DIALOGAGREGARPAGO_H
#define DIALOGAGREGARPAGO_H

#include <QDialog>

namespace Ui {
class DialogAgregarPago;
}

class DialogAgregarPago : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAgregarPago(QWidget *parent = 0);
    ~DialogAgregarPago();
signals:
    void insertado();

public slots:
    QString arreglarCentavos(QString v);
    void setProvActual(QString p);

private slots:
    void on_pushButtonAceptar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::DialogAgregarPago *ui;
    QString provactual;
};

#endif // DIALOGAGREGARPAGO_H

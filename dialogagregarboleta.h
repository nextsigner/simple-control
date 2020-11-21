#ifndef DIALOGAGREGARBOLETA_H
#define DIALOGAGREGARBOLETA_H

#include <QDialog>

namespace Ui {
class DialogAgregarBoleta;
}

class DialogAgregarBoleta : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAgregarBoleta(QWidget *parent = 0);
    ~DialogAgregarBoleta();

signals:
    void insertado();

public slots:
    QString arreglarCentavos(QString v);
    void setProvActual(QString p);
private slots:

    void on_pushButtonCancelar_clicked();
    
    void on_pushButtonAceptar_clicked();
    
private:
    Ui::DialogAgregarBoleta *ui;
    QString provactual;
};

#endif // DIALOGAGREGARBOLETA_H

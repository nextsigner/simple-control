#ifndef DIALOGCONFIRMAR_H
#define DIALOGCONFIRMAR_H

#include <QDialog>

namespace Ui {
class DialogConfirmar;
}

class DialogConfirmar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfirmar(QWidget *parent = 0);
    ~DialogConfirmar();
    void setPregunta(QString p);

private slots:
    void on_pushButtonBorrar_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::DialogConfirmar *ui;
    QString pregunta;

};

#endif // DIALOGCONFIRMAR_H

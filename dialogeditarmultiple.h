#ifndef DIALOGEDITARMULTIPLE_H
#define DIALOGEDITARMULTIPLE_H

#include <QDialog>

namespace Ui {
class DialogEditarMultiple;
}

class DialogEditarMultiple : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditarMultiple(QWidget *parent = 0);
    ~DialogEditarMultiple();
    void setListProv(QStringList lp);

signals:
    void modificando(QString cat, QString prov, int porc);

private slots:
    void on_pushButtonCancelar_clicked();

    void on_pushButtonGuardar_clicked();

private:
    Ui::DialogEditarMultiple *ui;
};

#endif // DIALOGEDITARMULTIPLE_H

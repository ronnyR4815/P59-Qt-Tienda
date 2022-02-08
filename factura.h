#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>

#include "tienda.h"

namespace Ui {
class factura;
}

class factura : public QDialog
{
    Q_OBJECT

public:
    explicit factura(QWidget *parent = nullptr);
    ~factura();
    void datosCliente(QString cedula,
                      QString nombre,
                      QString telefono,
                      QString email,
                      QString direccion);

    void listaCompras(QString lista, QString subtotal, QString iva, QString total);


private slots:
    void on_btn_imprimir_released();

    void on_btn_cerrar_released();

private:
    Ui::factura *ui;

    QString m_cedula;
    QString m_nombre;
    QString m_telefono;
    QString m_email;
    QString m_direccion;
    QString m_listaCompras;
    QString m_subtotal;
    QString m_iva;
    QString m_total;

    QString tiendaToString();
    QString clienteToString();
    void guardar();
};

#endif // FACTURA_H

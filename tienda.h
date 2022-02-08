#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <QVector>
#include <QInputDialog>

#include "producto.h"
#include "factura.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private slots:
    void on_in_producto_currentIndexChanged(int index);

    void on_btn_agregar_released();

    void on_btn_facturar_released();

    void on_out_cedula_textEdited(const QString &arg1);

    void on_actionNuevo_triggered();

    void on_actionAgregar_triggered();

    void on_actionFinalizar_triggered();

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    void cargarProductos();
    float m_subtotal;
    void calcular(float subtotal);
    bool validarCedula(QString a);
    void listaCompras();
    void facturar();

    QString m_cedula;
    QString m_nombre;
    QString m_telefono;
    QString m_email;
    QString m_direccion;
    QString m_listaCompras;
    QString m_subt;
    QString m_IVA;
    QString m_total;
};
#endif // TIENDA_H

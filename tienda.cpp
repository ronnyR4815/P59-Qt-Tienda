#include "tienda.h"
#include "ui_tienda.h"

#include <QDebug>

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    foreach(Producto *p, m_productos){
        ui->in_producto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "P. Unitario", "Subtotal"};
    ui->out_detalle->setColumnCount(4);
    ui->out_detalle->setHorizontalHeaderLabels(cabecera);

    this->m_subtotal = 0;
}

/*
 * Investigar como ordenar la lista
 * de productos en orden alfabetico
 * */

Tienda::~Tienda()
{
    delete ui;
}

/**
 * @brief Tienda::cargarProductos
 * Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    // Crear productos "quemados" en el codigo
    m_productos.append(new Producto(1, "Leche", 0.80));
    m_productos.append(new Producto(2, "Pan",   0.15));
    m_productos.append(new Producto(3, "Queso", 2.50));
    /* Podria leerse de una base de datos
     * de un archivo
     * o incluso de internet */
}

void Tienda::calcular(float subtotal)
{
    // Calcular valores
    m_subtotal += subtotal;
    float iva = m_subtotal * IVA / 100;
    float total = m_subtotal + iva;

    // Mostrar valores en GUI
    ui->out_subtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->out_IVA->setText("$ " + QString::number(iva, 'f', 2));
    ui->out_total->setText("$ " + QString::number(total, 'f', 2));
}

void Tienda::on_in_producto_currentIndexChanged(int index)
{
    // Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio en la etiqueta
    ui->out_precio->setText("$ " + QString::number(precio, 'f', 2));
    // Resetear el spinbox de cantidad
    ui->in_cantidad->setValue(0);
}

void Tienda::on_btn_agregar_released()
{
    // Validar que no se agregen productos con 0 cantidad
    int cantidad = ui->in_cantidad->value();
    if(cantidad == 0){
        return;
    }
    // Obtener los datos de la GUI
    int i = ui->in_producto->currentIndex();
    Producto *p = m_productos.at(i);

    // Calcular el subtotal del producto
    float subtotal = p->precio() * cantidad;

    // Agregar los datos a la tabla
    int fila = ui->out_detalle->rowCount();
    ui->out_detalle->insertRow(fila);
    ui->out_detalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
    ui->out_detalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
    ui->out_detalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(), 'f', 2)));
    ui->out_detalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subtotal, 'f', 2)));

    // Limpiar datos
    ui->in_cantidad->setValue(0);
    ui->in_producto->setFocus();

    // Actualizar subtotales
    calcular(subtotal);
}


#include "tienda.h"
#include "ui_tienda.h"

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
    QStringList cabecera = {"Cantidad", "Producto", "Subtotal"};
    ui->out_detalle->setColumnCount(3);
    ui->out_detalle->setHorizontalHeaderLabels(cabecera);
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


/*
 * Icono extraido de flaticon
 * <a href="https://www.flaticon.es/iconos-gratis/carrito-de-compras" title="carrito de compras iconos">Carrito de compras iconos creados por Pixel perfect - Flaticon</a>
 * */
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
    QStringList cabecera = {tr("Cantidad"), tr("Producto"), tr("P. Unitario"), tr("Subtotal")};
    ui->out_detalle->setColumnCount(4);
    ui->out_detalle->setHorizontalHeaderLabels(cabecera);

    this->m_subtotal = 0;

    this->m_cedula = "";
    this->m_nombre = "";
    this->m_telefono = "";
    this->m_email = "";
    this->m_direccion = "";
    this->m_listaCompras = "";
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
    m_productos.append(new Producto(1, tr("Leche"), 0.80));
    m_productos.append(new Producto(2, tr("Pan"),   0.15));
    m_productos.append(new Producto(3, tr("Queso"), 2.50));
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

bool Tienda::validarCedula(QString a)
{
    int i = 0;

    // Validacion solo de numeros
    while(i < a.length()){
        if(a.at(i).isDigit()){
            i++;
        }else{
            return false;
        }
    }

    // Validacion consumidor final
    if(a.toDouble() == 9999999999){
        return true;
    }

    // Validacion de cedula
    if(a.length() == 10){
        // Primeros dos digitos de la region
        int dig_region = a.at(0).digitValue()*10
                + a.at(1).digitValue();

        if(dig_region >= 1 && dig_region <= 24){
            // Ultimo digito
            int dig_ultimo = a.at(9).digitValue();

            // Agrupo todos los pares
            int pares = a.at(1).digitValue() +
                    a.at(3).digitValue() +
                    a.at(5).digitValue() +
                    a.at(7).digitValue();

            // Agrupo los impares y se los multiplica por 2
            // Si el resultado es mayor a 9 le restamos 9
            int num1 = a.at(0).digitValue();
            num1 = num1 * 2;
            if(num1 > 9)
                num1 = num1 - 9;

            int num3 = a.at(2).digitValue();
            num3 = num3 * 2;
            if(num3 > 9)
                num3 = num3 - 9;

            int num5 = a.at(4).digitValue();
            num5 = num5 * 2;
            if(num5 > 9)
                num5 = num5 - 9;

            int num7 = a.at(6).digitValue();
            num7 = num7 * 2;
            if(num7 > 9)
                num7 = num7 - 9;

            int num9 = a.at(8).digitValue();
            num9 = num9 * 2;
            if(num9 > 9)
                num9 = num9 - 9;

            int impares = num1 + num3 + num5 + num7 + num9;

            // Suma total
            int suma_total = pares + impares;

            // Se extrae el primer digito
            int primer_dig_suma = suma_total/10;
            // Decena inmediata superior
            int decena = (primer_dig_suma + 1) * 10;

            // Digito validador
            int dig_validador = decena - suma_total;
            if(dig_validador == 10)
                dig_validador = 0;

            if(dig_validador == dig_ultimo)
                return true;
            else
                return false;
        }
    }
    return false;
}

void Tienda::listaCompras()
{
    int fila = ui->out_detalle->rowCount();
    QString lista = "";

    for(int i = 0 ; i < fila ; i++){
        lista += "  " + ui->out_detalle->item(i, 0)->text() + "\t" +
                ui->out_detalle->item(i, 1)->text() + "\t" +
                ui->out_detalle->item(i, 2)->text() + "\t" +
                ui->out_detalle->item(i, 3)->text() + "\n";
    }
    m_listaCompras = lista;
}

void Tienda::facturar()
{
    // Cambiar color de fondo de LineText de cedula
    if(validarCedula(ui->out_cedula->text())){
        // Se recuperan los datos de los campos de texto
        this->m_cedula = ui->out_cedula->text();
        this->m_nombre = ui->out_nombre->text();
        this->m_telefono = ui->out_telefono->text();
        this->m_email = ui->out_email->text();
        this->m_direccion = ui->out_direccion->toPlainText();
        // Se recuperan los datos de la lista de compras
        listaCompras();
        // Se recuperan precios subtotal, IVA, total
        this->m_subt = ui->out_subtotal->text();
        this->m_IVA = ui->out_IVA->text();
        this->m_total = ui->out_total->text();

        // Se verifica que los campos no esten vacios
        if((m_cedula != "" && m_nombre != "" && m_telefono != "" && m_email != "" && m_direccion != "" && m_listaCompras != "")
                || (m_cedula == "9999999999" && m_listaCompras != "")){
            // Se envian los datos a la clase factura
            factura *m_factura = new factura();
            m_factura->datosCliente(m_cedula, m_nombre, m_telefono, m_email, m_direccion);
            m_factura->listaCompras(m_listaCompras, m_subt, m_IVA, m_total);
            m_factura->exec();
        }
    }else{
        return;
    }
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

    // Asignar cantidad de filas existentes
    int fila = ui->out_detalle->rowCount();
    // Crear una fila nueva para insertar los elementos
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

void Tienda::on_btn_facturar_released()
{
    facturar();
}

void Tienda::on_out_cedula_textEdited(const QString &arg1)
{
    // Cambiar el color del texto de acuerdo al cambio del texto
    if(validarCedula(arg1)){
        ui->out_cedula->setStyleSheet("background-color: rgb(143, 255, 128)");
    }else if(arg1 == ""){
        ui->out_cedula->setStyleSheet("background-color: white");
    }else{
        ui->out_cedula->setStyleSheet("background-color: rgb(255, 140, 140)");
    }
}

void Tienda::on_actionNuevo_triggered()
{
    ui->out_cedula->setText("");
    ui->out_cedula->setStyleSheet("background-color: white");
    ui->out_nombre->setText("");
    ui->out_telefono->setText("");
    ui->out_email->setText("");
    ui->out_direccion->setPlainText("");
    ui->in_cantidad->setValue(0);
    ui->out_subtotal->setText("0.00");
    ui->out_IVA->setText("0.00");
    ui->out_total->setText("0.00");
    m_subtotal = 0;
    // Limpiar tabla
    for(int i = 0 ; i < ui->out_detalle->rowCount() ; i++){

        ui->out_detalle->removeRow(i);
    }
    ui->out_detalle->removeRow(0);
}

void Tienda::on_actionAgregar_triggered()
{
    on_btn_agregar_released();
}

void Tienda::on_actionFinalizar_triggered()
{
    on_btn_facturar_released();
}


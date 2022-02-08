/*
 * Icono extraido de flaticon
 * <a href="https://www.flaticon.es/iconos-gratis/carrito-de-compras" title="carrito de compras iconos">Carrito de compras iconos creados por Pixel perfect - Flaticon</a>
 * */
#include "factura.h"
#include "ui_factura.h"

factura::factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::factura)
{
    ui->setupUi(this);
}

factura::~factura()
{
    delete ui;
}

void factura::datosCliente(QString cedula, QString nombre, QString telefono, QString email, QString direccion)
{
    m_cedula = cedula;
    m_nombre = nombre;
    m_telefono = telefono;
    m_email = email;
    m_direccion = direccion;
    ui->out_factura->setPlainText(clienteToString());
}

void factura::listaCompras(QString lista, QString subtotal, QString iva, QString total)
{
    m_listaCompras = lista;
    m_subtotal = subtotal;
    m_iva = iva;
    m_total = total;
    ui->out_factura->appendPlainText(tiendaToString());
}

QString factura::clienteToString()
{
    QString str;
    str.append(tr("\t     MI TIENDA\n\n"));
    str.append(tr(" FACTURA\n"));
    str.append("------------------------------------\n\n");
    str.append(tr(" CEDULA NO\t: ") + m_cedula + "\n");
    str.append(tr(" NOMBRE   \t: ") + m_nombre + "\n");
    str.append(tr(" TELEFONO \t: ") + m_telefono + "\n");
    str.append(tr(" E-MAIL   \t: ") + m_email + "\n");
    str.append(tr(" DIRECCION\t: ") + m_direccion + "\n\n");
    str.append("------------------------------------\n\n");
    return str;
}

QString factura::tiendaToString()
{
    QString str;
    str.append(tr(" CANT.\tPROD.\tP.UNIT.\tSUBTOTAL\n"));
    str.append("------------------------------------\n");
    str.append(m_listaCompras);
    str.append(tr("\n\t\tSUBTOTAL : ") + m_subtotal + "\n");
    str.append(tr("\t\tIVA 12%  : ") + m_iva + "\n");
    str.append(tr("\t\tTOTAL    : ") + m_total + "\n");
    return str;
}

void factura::guardar()
{
    // Guardar tiempo actual del sistema
    QTime tiempo(QTime::currentTime());
    // Guardar fecha actual del sistema
    QDate fecha(QDate::currentDate());

    // Guardar ruta del sistema + nombre del documento
    QString path = QDir::home().absoluteFilePath("downloads/") +
                    QString::number(fecha.day()) + "-" +
                    QString::number(fecha.month()) + "-" +
                    QString::number(fecha.year()) + "-" +
                    QString::number(tiempo.second()) +
                    QString::number(tiempo.minute()) +
                    QString::number(tiempo.hour()) + "-" +
                    m_cedula;

    /* Abrir cuadro de dialogo para
     * seleccionar una ubicacion para
     * guardar un archivo */
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         path,
                                                         "Documento de texto (*.txt)");
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir archivo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un "stream" de texto (flujo)
        QTextStream datos(&archivo);
        datos << ui->out_factura->toPlainText();

    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(
                    this,
                    "Guardar informacion",
                    "No se pudo guardar la informacion");
    }
    // Cerrar el archivo
    archivo.close();
    close();
}

void factura::on_btn_imprimir_released()
{
    guardar();
}

void factura::on_btn_cerrar_released()
{
    close();
}


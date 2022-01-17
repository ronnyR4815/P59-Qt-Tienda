#include "producto.h"

Producto::Producto(QObject *parent) : QObject(parent)
{

}

Producto::Producto(int codigo, const QString &nombre, float precio, QObject *parent) : QObject(parent),
    m_codigo(codigo),
    m_nombre(nombre),
    m_precio(precio)
{}

int Producto::codigo() const
{
    return m_codigo;
}

void Producto::setCodigo(int newCodigo)
{
    m_codigo = newCodigo;
}

const QString &Producto::nombre() const
{
    return m_nombre;
}

void Producto::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

float Producto::precio() const
{
    return m_precio;
}

void Producto::setPrecio(float newPrecio)
{
    m_precio = newPrecio;
}

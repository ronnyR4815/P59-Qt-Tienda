#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QObject>

class Producto : public QObject
{
    Q_OBJECT
public:
    explicit Producto(QObject *parent = nullptr);
    Producto(int codigo, const QString &nombre, float precio, QObject *parent = nullptr);

    int codigo() const;
    void setCodigo(int newCodigo);
    const QString &nombre() const;
    void setNombre(const QString &newNombre);
    float precio() const;
    void setPrecio(float newPrecio);

signals:

private:
    int m_codigo;
    QString m_nombre;
    float m_precio;
};

#endif // PRODUCTO_H

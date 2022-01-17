#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>

#include "producto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    void cargarProductos();
};
#endif // TIENDA_H

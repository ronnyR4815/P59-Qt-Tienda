#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>

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
};
#endif // TIENDA_H

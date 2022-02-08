#include "tienda.h"

#include <QApplication>
#include <QTranslator>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QDateTime tiempo(QDateTime::currentDateTime());
    QApplication a(argc, argv);
    if(!tiempo.timeZoneAbbreviation().contains("Sudamérica")){
        QTranslator T;
        QStringList langs;
        langs << "Español" << "Ingles";
        const QString lang = QInputDialog::getItem(NULL,
                                                   "Idiomas",
                                                   "Selecciona un idioma",
                                                   langs);
        if(lang == "Ingles"){
            T.load(":/tienda_en.qm");
        }
        if(lang != "Español"){
            a.installTranslator(&T);
        }
    }
    Tienda w;
    w.show();
    return a.exec();
}

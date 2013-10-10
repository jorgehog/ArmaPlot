#include "armaplot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPen pen(Qt::red);

    ArmaPlot AP;
    AP.setPen(&pen);

    vec X = arma::sin(linspace<vec>(0, 2*arma::datum::pi, 101));

    AP.plot(X%X%X, hold::on);
    AP.plot(X%X);

    pen.setColor(Qt::blue);
    AP.plot(X);
    AP.show();

    return a.exec();
}

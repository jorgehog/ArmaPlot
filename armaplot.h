#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

#include <armadillo>

using namespace arma;

namespace Ui {
class ArmaPlot;
}

struct hold {
    enum HOLDSTATE {on, off, keep};
};

class ArmaPlot : public QDialog
{
    Q_OBJECT

public:
    explicit ArmaPlot(QWidget *parent = 0);
    ~ArmaPlot();

    void plot(const vec & X, const vec & Y, hold::HOLDSTATE _hold = hold::keep);
    void plot(const vec & Y, hold::HOLDSTATE _hold = hold::keep);

    void setSpanCap_y(double val);

    void setPen(QPen* pen){
        this->pen = pen;
    }

private:

    hold::HOLDSTATE _hold;

    double ySpanCap;

    Ui::ArmaPlot *ui;
    QGraphicsScene * scene;
    QPen * pen;

    void getScales(int &scale_x, int &scale_y, const vec & X, const vec & Y);


};

#endif // ARMAPLOT_H

#include "armaplot.h"
#include "ui_armaplot.h"

#include <assert.h>
#include <iostream>

ArmaPlot::ArmaPlot(QWidget *parent) :
    QDialog(parent),
    _hold(hold::off),
    ySpanCap(0.95),
    ui(new Ui::ArmaPlot),
    pen(new QPen)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 300, 225);
    ui->graphicsView->scale(1,-1);

    ui->graphicsView->setScene(scene);

}

ArmaPlot::~ArmaPlot()
{
    delete ui;
}

void ArmaPlot::plot(const vec &X, const vec &Y, hold::HOLDSTATE _hold)
{
    assert(X.n_elem == Y.n_elem && "X and Y must have the same shape.");

    if (this->_hold == hold::off) {
        scene->clear();
    }

    int scale_x, scale_y;

    getScales(scale_x, scale_y, X, Y);

    double X0 = scene->sceneRect().left();
    double Y0 = scene->sceneRect().top() - Y.min()*scale_y;

    for (unsigned int i = 0; i < X.n_elem - 1; ++i) {
        scene->addLine(X0 + X.at(i)*scale_x,
                       Y0 + Y.at(i)*scale_y,
                       X0 + X.at(i+1)*scale_x,
                       Y0 + Y.at(i+1)*scale_y,
                       *pen);
    }

    if (_hold != hold::keep) {
        this->_hold = _hold;
    }
}

void ArmaPlot::plot(const vec &Y, hold::HOLDSTATE _hold)
{
    vec X = linspace(0, Y.n_elem - 1, Y.n_elem);
    plot(X, Y, _hold);
}

void ArmaPlot::setSpanCap_y(double val)
{
    assert(val >= 0 && val <= 1 && "clearing must be between 0 and 1");

    ySpanCap = val;

}

void ArmaPlot::getScales(int &scale_x, int &scale_y, const vec &X, const vec &Y)
{

    double spanX = X.max() - X.min();
    double spanY = Y.max() - Y.min();

    scale_x = (int)(scene->width()/spanX);
    scale_y = (int)(scene->height()/spanY*ySpanCap);

}


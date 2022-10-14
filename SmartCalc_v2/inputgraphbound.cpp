#include "inputgraphbound.h"
#include "ui_inputgraphbound.h"
#include <iostream>
#include "graphwindow.h"

namespace s21 {
InputGraphBound::InputGraphBound(QString expression, Controller *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputGraphBound) {
    ui->setupUi(this);
    this->controller_ = controller;
    this->expression_ = expression;
    this->setFixedSize(this->width(), this->height());
}

InputGraphBound::~InputGraphBound() {
    this->controller_ = nullptr;
    this->expression_ = nullptr;
    delete ui;
}

void InputGraphBound::on_pushButtonOk_clicked() {
    this->close();
    GraphWindow graph(this->expression_, this->controller_,
                      this->ui->spinBoxXMin->value(), this->ui->spinBoxXMax->value(),
                      this->ui->spinBoxYMin->value(), this->ui->spinBoxYMax->value());
    graph.exec();
}

void InputGraphBound::on_spinBoxXMin_valueChanged(double arg1) {
    if (arg1 >= ui->spinBoxXMax->value()) {
        ui->spinBoxXMin->setValue(ui->spinBoxXMax->value() - 0.1);
    }
    ui->spinBoxXMax->setMinimum(ui->spinBoxXMin->value() + 0.1);
}
}  //  namespace s21

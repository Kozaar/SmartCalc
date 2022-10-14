#ifndef SRC_SMARTCALC_V2_GRAPHWINDOW_H_
#define SRC_SMARTCALC_V2_GRAPHWINDOW_H_

#include <QDialog>
#include <QGraphicsTextItem>
#include <cmath>
#include <vector>
#include "controller.h"

#include <iostream>

namespace Ui {
class GraphWindow;
}

namespace s21 {
class GraphWindow : public QDialog {
    Q_OBJECT

 public:
    explicit GraphWindow(QString expression, Controller *controller,
                         double minX, double maxX, double minY, double maxY, QWidget *parent = nullptr);
    ~GraphWindow();

 private:
    Ui::GraphWindow *ui;
    Controller *controller_;
    double minX_;
    double maxX_;
    double minY_;
    double maxY_;
    double centerX_;
    double centerY_;

    void drawAxis();
    void drawStep();
    void drawGraph();
    void findCenter();
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_GRAPHWINDOW_H_

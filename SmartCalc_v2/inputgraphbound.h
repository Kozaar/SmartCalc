#ifndef SRC_SMARTCALC_V2_INPUTGRAPHBOUND_H_
#define SRC_SMARTCALC_V2_INPUTGRAPHBOUND_H_

#include <QDialog>
#include "controller.h"

namespace Ui {
class InputGraphBound;
}

namespace s21 {
class InputGraphBound : public QDialog {
    Q_OBJECT

 public:
    explicit InputGraphBound(QString expression, Controller *controller, QWidget *parent = nullptr);
    ~InputGraphBound();

 private slots:
    void on_pushButtonOk_clicked();

    void on_spinBoxXMin_valueChanged(double arg1);

 private:
    Ui::InputGraphBound *ui;
    Controller *controller_;
    QString expression_;
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_INPUTGRAPHBOUND_H_

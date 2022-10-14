#ifndef SRC_SMARTCALC_V2_CREDITCALC_H_
#define SRC_SMARTCALC_V2_CREDITCALC_H_

#include <QDialog>
#include <vector>
#include "controller.h"
#include "creditoutput.h"


namespace Ui {
class CreditCalc;
}
namespace s21 {
class CreditCalc : public QDialog {
    Q_OBJECT

 public:
    explicit CreditCalc(Controller *controller, QWidget *parent = nullptr);
    ~CreditCalc();

 private slots:
    void on_pushButton_clicked();

 private:
    Ui::CreditCalc *ui;
    Controller *controller_;
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_CREDITCALC_H_

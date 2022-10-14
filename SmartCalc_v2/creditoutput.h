#ifndef SRC_SMARTCALC_V2_CREDITOUTPUT_H_
#define SRC_SMARTCALC_V2_CREDITOUTPUT_H_

#include <QDialog>
#include <QStandardItemModel>
#include <vector>
#include "model.h"

namespace Ui {
class CreditOutput;
}
namespace s21 {
class CreditOutput : public QDialog {
    Q_OBJECT

 public:
    explicit CreditOutput(const Model::creditOutput &monthlyPayment, QWidget *parent = nullptr);
    ~CreditOutput();

 private slots:
    void on_pushButton_clicked();

 private:
    Ui::CreditOutput *ui;
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_CREDITOUTPUT_H_

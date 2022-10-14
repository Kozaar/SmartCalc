#include "creditcalc.h"
#include "ui_creditcalc.h"

namespace s21 {
CreditCalc::CreditCalc(Controller *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditCalc) {
    ui->setupUi(this);
    this->controller_ = controller;
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle("Credit calculator");
}

CreditCalc::~CreditCalc() {
    delete ui;
}

void CreditCalc::on_pushButton_clicked() {
    Model::creditOutput monthlyPayment;
    if (ui->radioButtonAnnuityType->isChecked()) {
        bool a = ui->comboBox->currentText() == "Years" ? true : false;
        monthlyPayment = this->controller_->calculateAnnuityCredit(
                                                               ui->doubleSpinBoxTotalCreditAmount->value(),
                                                               ui->spinBoxTerm->value(),
                                                               a, ui->doubleSpinBoxInterestRate->value());
    } else {
        bool a = ui->comboBox->currentText() == "Years" ? true : false;
        monthlyPayment = this->controller_->calculateDifferentiatedCredit(
                                                               ui->doubleSpinBoxTotalCreditAmount->value(),
                                                               ui->spinBoxTerm->value(),
                                                               a, ui->doubleSpinBoxInterestRate->value());
    }
    CreditOutput creditoutput(monthlyPayment);
    creditoutput.exec();
}
}  //  namespace s21

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "model.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->radioButtonDrawGraph->setVisible(false);
    ui->radioButtonInputX->setVisible(false);
    ui->spinBoxValueX->setVisible(false);
    this->countWritedSymbols = 0;
    this->setFixedSize(this->width(), this->height());
    ui->label->setFixedWidth(650);
    this->setWindowTitle("SmartCalc_v2.0");
}

MainWindow::~MainWindow() {
    this->controller.allClear();
    delete ui;
}

void MainWindow::on_button0_clicked() {
    this->addNumberToExpression(0);
}

void MainWindow::on_button1_clicked() {
    this->addNumberToExpression(1);
}

void MainWindow::on_button2_clicked() {
    this->addNumberToExpression(2);
}

void MainWindow::on_button3_clicked() {
    this->addNumberToExpression(3);
}

void MainWindow::on_button4_clicked() {
    this->addNumberToExpression(4);
}

void MainWindow::on_button5_clicked() {
    this->addNumberToExpression(5);
}

void MainWindow::on_button6_clicked() {
    this->addNumberToExpression(6);
}

void MainWindow::on_button7_clicked() {
    this->addNumberToExpression(7);
}

void MainWindow::on_button8_clicked() {
    this->addNumberToExpression(8);
}

void MainWindow::on_button9_clicked() {
    this->addNumberToExpression(9);
}

void MainWindow::on_bottonEqual_clicked() {
    try {
        double res = 0;
        if (MainWindow::ui->spinBoxValueX->isVisible()) {
            MainWindow::ui->radioButtonDrawGraph->setVisible(false);
            MainWindow::ui->radioButtonInputX->setVisible(false);
            MainWindow::ui->spinBoxValueX->setVisible(false);
            if (MainWindow::ui->radioButtonInputX->isChecked()) {
                res = this->controller.calculateExpression(MainWindow::ui->spinBoxValueX->value());
                MainWindow::ui->label->setText(QString::number(res, 'f', 7));
            } else {
                InputGraphBound getGraphBound(this->ui->label->text(), &controller);
                getGraphBound.exec();
                MainWindow::ui->label->setText("0.");
            }
        } else {
            res = this->controller.calculateExpression();
            MainWindow::ui->label->setText(QString::number(res, 'f', 7));
        }
        this->removeInsignificantZero();
        this->countWritedSymbols = 0;
        this->controller.allClear();
    } catch (std::exception& e) {
        this->outputError(&e);
    }
}

void MainWindow::on_buttonPlus_clicked() {
    this->addOperationToExpression("+");
}

void MainWindow::on_buttonMinus_clicked() {
    this->addOperationToExpression("-");
}

void MainWindow::on_buttonMult_clicked() {
    this->addOperationToExpression("*");
}

void MainWindow::on_buttonDivision_clicked() {
    this->addOperationToExpression("/");
}

void MainWindow::on_buttonPower_clicked() {
    this->addOperationToExpression("^");
}

void MainWindow::on_buttonOpenBracket_clicked() {
    this->addOperationToExpression("(");
}

void MainWindow::on_buttonCloseBracket_clicked() {
    this->addOperationToExpression(")");
}

void MainWindow::on_buttonAllClean_clicked() {
    this->controller.allClear();
    MainWindow::ui->label->setText("0");
    this->countWritedSymbols = 0;
    MainWindow::ui->radioButtonDrawGraph->setVisible(false);
    MainWindow::ui->radioButtonInputX->setVisible(false);
    MainWindow::ui->spinBoxValueX->setVisible(false);
}

void MainWindow::on_buttonDot_clicked() {
    if (this->checkMaxLengthLabel() > 0) {
        try {
            this->controller.operationButtonClicked('.');
            this->addSymbolToLabel(".");
        } catch (std::exception& e) {
            this->outputError(&e);
        }
    }
}

void MainWindow::addSymbolToLabel(QString symbol) {
    QString a = MainWindow::ui->label->text();
    a.insert(a.count(), symbol);
    MainWindow::ui->label->setText(a);
    this->countWritedSymbols += symbol.count();
}

int MainWindow::checkMaxLengthLabel() {
    int res = 255;
    if (this->countWritedSymbols == 0) {
        MainWindow::ui->label->setText("");
    } else {
        res = res - this->countWritedSymbols;
    }
    return res;
}

void MainWindow::outputError(std::exception *e) {
    MainWindow::ui->label->setText(QString("ERROR: ") + e->what());
    this->countWritedSymbols = 0;
    this->controller.allClear();
    MainWindow::ui->radioButtonDrawGraph->setVisible(false);
    MainWindow::ui->radioButtonInputX->setVisible(false);
    MainWindow::ui->spinBoxValueX->setVisible(false);
}

void MainWindow::removeInsignificantZero() {
    QString labelText = ui->label->text();
    while (labelText.back() == '0') {
        labelText.remove(labelText.count()-1, 1);
    }
    if (labelText.back() == '.') {
        labelText.remove(labelText.count()-1, 1);
    }
    ui->label->setText(labelText);
}

void MainWindow::on_buttonSqrt_clicked() {
    this->addOperationToExpression(QString("sqrt"));
}

void MainWindow::on_buttonMod_clicked() {
    if (this->checkMaxLengthLabel() > 3) {
        this->controller.operationButtonClicked('m');
        this->addSymbolToLabel("mod");
    }
}

void MainWindow::on_buttonCos_clicked() {
    this->addOperationToExpression(QString("cos"));
}

void MainWindow::on_buttonAcos_clicked() {
    this->addOperationToExpression("acos");
}

void MainWindow::on_buttonSin_clicked() {
    this->addOperationToExpression("sin");
}

void MainWindow::on_buttonAsin_clicked() {
    this->addOperationToExpression("asin");
}

void MainWindow::on_buttonTan_clicked() {
    this->addOperationToExpression("tan");
}

void MainWindow::on_buttonAtan_clicked() {
    this->addOperationToExpression("atan");
}

void MainWindow::on_buttonLog_clicked() {
    this->addOperationToExpression("log");
}

void MainWindow::on_pushButton_31_clicked() {
    this->addOperationToExpression("log10");
}

void MainWindow::on_buttonX_clicked() {
    if (this->checkMaxLengthLabel() > 1) {
        this->controller.buttonXClicked();
        this->addSymbolToLabel("x");
        MainWindow::ui->radioButtonDrawGraph->setVisible(true);
        MainWindow::ui->radioButtonInputX->setVisible(true);
        MainWindow::ui->spinBoxValueX->setVisible(true);
    }
}

void MainWindow::addNumberToExpression(int number) {
    if (this->checkMaxLengthLabel() > 0) {
        this->controller.numberButtonClicked(number);
        this->addSymbolToLabel(QString::number(number, 'g', 1));
    }
}

void MainWindow::addOperationToExpression(QString str) {
    if (str.count() == 1) {
        if (this->checkMaxLengthLabel() > 0) {
            if (str == "π") {
                this->controller.numberButtonClicked(M_PI);
            } else if (str == "e") {
                this->controller.buttonEClicked();
            } else {
                char a = str[0].toLatin1();
                this->controller.operationButtonClicked(a);
            }
            this->addSymbolToLabel(str);
        }
    } else {
        if (this->checkMaxLengthLabel() > str.count()) {
            if (str == QString("sqrt")) this->controller.operationButtonClicked('q');
            if (str == QString("cos")) this->controller.operationButtonClicked('c');
            if (str == QString("acos")) this->controller.operationButtonClicked('o');
            if (str == QString("sin")) this->controller.operationButtonClicked('s');
            if (str == QString("asin")) this->controller.operationButtonClicked('i');
            if (str == QString("tan")) this->controller.operationButtonClicked('t');
            if (str == QString("atan")) this->controller.operationButtonClicked('a');
            if (str == QString("log")) this->controller.operationButtonClicked('n');
            if (str == QString("log10")) this->controller.operationButtonClicked('l');
            this->controller.operationButtonClicked('(');
            this->addSymbolToLabel(str + "(");
        }
    }
}

void MainWindow::on_pushButtonCredit_clicked() {
    CreditCalc creditWindow(&(this->controller));
    creditWindow.exec();
}

void MainWindow::on_radioButtonDrawGraph_clicked() {
    ui->spinBoxValueX->setEnabled(false);
}


void MainWindow::on_radioButtonInputX_clicked() {
    ui->spinBoxValueX->setEnabled(true);
}


void MainWindow::on_pushButtonPi_clicked() {
    this->addOperationToExpression("π");
}


void MainWindow::on_pushButtonE_clicked() {
    this->addOperationToExpression("e");
}

}  //  namespace s21

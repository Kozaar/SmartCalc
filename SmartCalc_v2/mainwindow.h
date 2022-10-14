#ifndef SRC_SMARTCALC_V2_MAINWINDOW_H_
#define SRC_SMARTCALC_V2_MAINWINDOW_H_

#include <QMainWindow>
#include "controller.h"
#include "inputgraphbound.h"
#include "creditcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_buttonPlus_clicked();

    void on_bottonEqual_clicked();

    void on_buttonMinus_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_buttonMult_clicked();

    void on_buttonDivision_clicked();

    void on_buttonPower_clicked();

    void on_buttonOpenBracket_clicked();

    void on_buttonCloseBracket_clicked();

    void on_button0_clicked();

    void on_buttonAllClean_clicked();

    void on_buttonDot_clicked();

    void on_buttonSqrt_clicked();

    void on_buttonMod_clicked();

    void on_buttonCos_clicked();

    void on_buttonAcos_clicked();

    void on_buttonSin_clicked();

    void on_buttonAsin_clicked();

    void on_buttonTan_clicked();

    void on_buttonAtan_clicked();

    void on_buttonLog_clicked();

    void on_pushButton_31_clicked();

    void on_buttonX_clicked();

    void on_pushButtonCredit_clicked();

    void on_radioButtonDrawGraph_clicked();

    void on_radioButtonInputX_clicked();

    void on_pushButtonPi_clicked();

    void on_pushButtonE_clicked();

 private:
    Ui::MainWindow *ui;
    Controller controller;
    int countWritedSymbols;

    void addNumberToExpression(int number);
    void addOperationToExpression(QString str);
    void addSymbolToLabel(QString symbol);
    int checkMaxLengthLabel();
    void outputError(std::exception *e);
    void removeInsignificantZero();
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_MAINWINDOW_H_

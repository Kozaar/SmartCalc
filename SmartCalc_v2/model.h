#ifndef SRC_SMARTCALC_V2_MODEL_H_
#define SRC_SMARTCALC_V2_MODEL_H_

#include <cmath>
#include <queue>
#include <list>
#include <stack>
#include <iostream>
#include <vector>

namespace s21 {
class Model {
 private:
    struct ElemQueue {
        bool isNumber_;
        int scale_;
        double data_;
        int priority_;
        char operation_;
    };
    std::list<ElemQueue> expression;
    bool isXInExpression;

 public:
    Model();
    ~Model();

    struct creditOutput {
        std::vector<std::pair<double, double> > monthlyPayment;
        double overpayment;
        double totalPayment;
    };

    double getData();
    void addElemToList(bool isNumber, int scale, double data, int priority, char operation);
    void addElemToList(const ElemQueue& elemQueue);
    void addNumber(double number);
    void addOperation(char operation);
    void addX();
    void addE();
    void addScaleToNumber();
    void transformExpressionToPolishNotation();
    void calculatePolishNotatin(double x = 0);
    std::vector<std::pair<double, double> > calculatePointCoordinates(double minX, double maxX);
    void clear();
    creditOutput calculateAnnuityCredit(double totalAmount, int term, bool termInYear, double rate);
    creditOutput calculateDifferentiatedCredit(double totalAmount, int term, bool termInYear, double rate);
    double calculateResultExpression(double x);
    void addElemToExpressionWithE(const ElemQueue &elemQueue);
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_MODEL_H_

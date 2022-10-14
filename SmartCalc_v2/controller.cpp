#include "controller.h"

namespace s21 {
Controller::Controller() {}

void Controller::numberButtonClicked(double number) {
    this->a.addNumber(number);
}

void Controller::operationButtonClicked(char operation) {
    this->a.addOperation(operation);
}

void Controller::buttonXClicked() {
    this->a.addX();
}

void Controller::buttonEClicked() {
    this->a.addE();
}

void Controller::allClear() {
    this->a.clear();
}

double Controller::calculateExpression(double x) {
    return this->a.calculateResultExpression(x);
//    this->a.printExpression();
//    this->a.transformExpressionToPolishNotation();
//    this->a.calculatePolishNotatin(x);
//    return this->a.getData();
}

Model::creditOutput Controller::calculateAnnuityCredit(double totalAmount, int term,
                                                       bool termInYear, double rate) {
    return this->a.calculateAnnuityCredit(totalAmount, term, termInYear, rate);
}

Model::creditOutput Controller::calculateDifferentiatedCredit(double totalAmount, int term,
                                                              bool termInYear, double rate) {
    return this->a.calculateDifferentiatedCredit(totalAmount, term, termInYear, rate);
}

std::vector<std::pair<double, double> > Controller::calculateGraphCordinates(double minX, double maxX) {
    return this->a.calculatePointCoordinates(minX, maxX);
}
}  //  namespace s21

#ifndef SRC_SMARTCALC_V2_CONTROLLER_H_
#define SRC_SMARTCALC_V2_CONTROLLER_H_

#include <vector>
#include "model.h"

namespace s21 {
class Controller {
 private:
    Model a;

 public:
    Controller();

    void numberButtonClicked(double number);
    void operationButtonClicked(char operation);
    void buttonXClicked();
    void buttonEClicked();
    void allClear();
    double calculateExpression(double x = 0);
    Model::creditOutput calculateAnnuityCredit(double totalAmount, int term, bool termInYear, double rate);
    Model::creditOutput calculateDifferentiatedCredit(double totalAmount, int term,
                                                      bool termInYear, double rate);
    std::vector<std::pair<double, double> > calculateGraphCordinates(double minX, double maxX);
};
}  //  namespace s21

#endif  //  SRC_SMARTCALC_V2_CONTROLLER_H_

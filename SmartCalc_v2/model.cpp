#include "model.h"

namespace s21 {
Model::Model() {
    this->expression.clear();
    this->isXInExpression = false;
}

Model::~Model() {
    this->expression.clear();
    this->isXInExpression = false;
}

void Model::addElemToList(bool isNumber, int scale, double data, int priority, char operation) {
    if (!expression.empty() && expression.back().operation_ == '-' &&
            expression.back().priority_ == 0 && isNumber) {
        expression.pop_back();
        data *= -1;
    }
    ElemQueue curent{isNumber, scale, data, priority, operation};
    this->addElemToList(curent);
}

void Model::addElemToList(const ElemQueue &elemQueue) {
    if (elemQueue.operation_ == 'x') {
        this->isXInExpression = true;
    }
    if (!expression.empty() && expression.back().isNumber_ && elemQueue.isNumber_) {
        expression.back().data_ *= 10;
        if (expression.back().data_ >= 0) {
            expression.back().data_ += elemQueue.data_;
        } else {
            expression.back().data_ -= elemQueue.data_;
        }
        if (expression.back().scale_ != -1) {
            expression.back().scale_++;
            }
    } else if (!expression.empty() && expression.back().operation_ == 'e') {
        addElemToExpressionWithE(elemQueue);
    } else if (!expression.empty() && expression.back().priority_ == 4 && elemQueue.priority_ == 4) {
        if (elemQueue.operation_ == '-') {
            expression.back().operation_ = expression.back().operation_ == '+' ? '-' : '+';
        }
    } else if (!expression.empty() && elemQueue.priority_ == 4 &&
               !expression.back().isNumber_ && expression.back().operation_ != ')') {
        if (elemQueue.operation_ == '-') {
            if (expression.back().operation_ == '-' && expression.back().priority_ == 0) {
                expression.pop_back();
            } else {
                this->addElemToList(false, -1, -1., 0, '-');
            }
        }
    } else if (elemQueue.priority_ == 4 && expression.empty()) {
        if (elemQueue.operation_ == '-') {
            this->addElemToList(true, -1, 0, 0, 0);
            this->addElemToList(false, -1, -1., 0, '-');
        }
    } else if (!expression.empty() && expression.back().operation_ == '(' && elemQueue.operation_ == ')') {
        addElemToList(false, -1, 0, 1, '^');
        expression.push_back(elemQueue);
    } else {
        expression.push_back(elemQueue);
    }
}

void Model::addElemToExpressionWithE(const ElemQueue &elemQueue) {
    if (!elemQueue.isNumber_) {
        if (expression.back().isNumber_) {
            expression.back().operation_ = 0;
            addElemToList(false, -1, 0, 6, ')');
            addElemToList(elemQueue);
        } else {
            if (elemQueue.operation_ == '-') {
                expression.back().data_ = expression.back().data_ == -1 ? 1 : -1;
            }
        }
    } else {
        ElemQueue el(elemQueue);
        if (expression.back().data_ == -1) {
            el.data_ *= -1;
        }
        el.operation_ = 'e';
        expression.pop_back();
        addElemToList(el);
    }
}

void Model::addNumber(double number) {
    if (!expression.empty()) {
        if (expression.back().operation_ == 'x' || expression.back().data_ == M_PI ||
                expression.back().data_ == M_E) {
            addElemToList(false, -1, 0, 1, '^');
        }
        if (expression.back().isNumber_ &&  number == M_PI) {
            addElemToList(false, -1, 0, 3, '*');
        }
    }
    this->addElemToList(true, -1, number, 0, 0);
}

void Model::addOperation(char operation) {
    if (operation == '(' || operation == ')') {
        this->addElemToList(false, -1, 0, 6, operation);
    } else if (operation == 'm') {
        this->addElemToList(false, -1, 0, 5, operation);
    } else if (operation == '+' || operation == '-') {
        this->addElemToList(false, -1, 0, 4, operation);
    } else if (operation == '*' || operation == '/') {
        this->addElemToList(false, -1, 0, 3, operation);
    } else if (operation == '^') {
        this->addElemToList(false, -1, 0, 1, operation);
    } else if (operation == '.') {
        this->addScaleToNumber();
    } else {
        this->addElemToList(false, -1, 0, 2, operation);
    }
}

void Model::addX() {
    if (!expression.empty() && expression.back().isNumber_) {
        this->addElemToList(false, -1, 0, 3, '*');
    }
    this->addElemToList(true, -1, 0, 0, 'x');
}

void Model::addE() {
    if (!expression.empty() && expression.back().isNumber_) {
        std::list<ElemQueue>::iterator it = expression.end();
        --it;
        expression.insert(it, ElemQueue{false, -1, 0, 6, '('});
        addElemToList(false, -1, 0, 3, '*');
        addElemToList(true, -1, 10, 0, 0);
        addElemToList(false, -1, 0, 1, '^');
        addElemToList(false, -1, 0, 0, 'e');
    } else {
        addElemToList(true, -1, M_E, 0, 0);
    }
}

void Model::addScaleToNumber() {
    if (expression.back().isNumber_) {
        if (expression.back().scale_ == -1 && expression.back().operation_ == 0) {
            expression.back().scale_ = 0;
        } else {
            throw std::invalid_argument("Wrong dot");
        }
    } else {
        this->addElemToList(true, 0, 0, 0, 0);
    }
}

void Model::transformExpressionToPolishNotation() {
    std::list<ElemQueue> polishNotation;
    std::stack<ElemQueue> stackOperations;
    while (!expression.empty()) {
        if (expression.front().operation_ == 0 || expression.front().operation_ == 'x') {
            while (expression.front().scale_ > 0) {
                expression.front().data_ /= 10;
                expression.front().scale_--;
            }
            polishNotation.push_back(expression.front());
        } else if (expression.front().operation_ != ')' && expression.front().operation_ != '(' &&
                    !(expression.front().priority_ == 1 &&
                      !stackOperations.empty() && stackOperations.top().priority_ == 1)) {
            while (!stackOperations.empty() &&
                   expression.front().priority_ >= stackOperations.top().priority_) {
                polishNotation.push_back(stackOperations.top());
                stackOperations.pop();
            }
            stackOperations.push(expression.front());
        } else if (expression.front().operation_ == ')') {
            if (!stackOperations.empty()) {
                while (!stackOperations.empty() && stackOperations.top().operation_ != '(') {
                    polishNotation.push_back(stackOperations.top());
                    stackOperations.pop();
                }
                if (stackOperations.empty() || stackOperations.top().operation_ != '(') {
                    throw std::invalid_argument("Too much ')'");
                } else {
                    stackOperations.pop();
                }
            } else {
                throw std::invalid_argument("Too much ')'");
            }
        } else if (expression.front().operation_ == '(') {
            stackOperations.push(expression.front());
        } else if (expression.front().priority_ == 1 && !stackOperations.empty() &&
                    stackOperations.top().priority_ == 1) {
            stackOperations.push(expression.front());
        } else {
            throw std::invalid_argument("Something wrong");
        }
        expression.pop_front();
    }
    while (!stackOperations.empty()) {
        polishNotation.push_back(stackOperations.top());
        stackOperations.pop();
    }
    expression.swap(polishNotation);
}

void Model::calculatePolishNotatin(double x) {
    std::stack<ElemQueue> numbers;
    while (!expression.empty()) {
        if (expression.front().operation_ == 0) {
            numbers.push(expression.front());
            expression.pop_front();
        } else if (expression.front().operation_ == 'x')  {
            expression.front().data_ = x;
            expression.front().operation_ = 0;
            numbers.push(expression.front());
            expression.pop_front();
        } else {
            if (!numbers.empty()) {
                ElemQueue numbre1;
                ElemQueue numbre2;
                numbre1 = numbers.top();
                numbers.pop();
                if (expression.front().operation_ == '+' || expression.front().operation_ == '-' ||
                    expression.front().operation_ == '*' || expression.front().operation_ == '/' ||
                    expression.front().operation_ == '^' || expression.front().operation_ == 'm') {
                        if (!numbers.empty()) {
                            numbre2 = numbers.top();
                            numbers.pop();
                        } else {
                            throw std::invalid_argument("Need more numbers");
                        }
                }
                switch (expression.front().operation_) {
                    case '+': numbre1.data_ = numbre1.data_ + numbre2.data_; break;
                    case '-': numbre1.data_ = numbre2.data_ - numbre1.data_; break;
                    case '*': numbre1.data_ = numbre2.data_ * numbre1.data_; break;
                    case '/': numbre1.data_ = numbre2.data_ / numbre1.data_; break;
                    case '^': numbre1.data_ = pow(numbre2.data_, numbre1.data_); break;
                    case 'm': numbre1.data_ = fmod(numbre2.data_, numbre1.data_); break;
                    case 's': numbre1.data_ = sin(numbre1.data_); break;
                    case 'c': numbre1.data_ = cos(numbre1.data_); break;
                    case 't': numbre1.data_ = tan(numbre1.data_); break;
                    case 'i': numbre1.data_ = asin(numbre1.data_); break;
                    case 'o': numbre1.data_ = acos(numbre1.data_); break;
                    case 'a': numbre1.data_ = atan(numbre1.data_); break;
                    case 'q': numbre1.data_ = sqrt(numbre1.data_); break;
                    case 'n': numbre1.data_ = log(numbre1.data_); break;
                    case 'l': numbre1.data_ = log10(numbre1.data_); break;
                    default: throw std::invalid_argument("Something wrong"); break;
                }
                numbers.push(numbre1);
                expression.pop_front();
            } else {
                throw std::invalid_argument("Need more numbers");
            }
        }
    }
    if (!numbers.empty()) {
        expression.push_back(numbers.top());
        numbers.pop();
        if (!numbers.empty()) {
            throw std::invalid_argument("Too much numbers");
        }
    } else {
        throw std::invalid_argument("Need more numbers");
    }
}

std::vector<std::pair<double, double> > Model::calculatePointCoordinates(double minX, double maxX) {
    double step = (maxX - minX) / M_PI / 5000;
    std::vector<std::pair<double, double> > res;
    this->transformExpressionToPolishNotation();
    for (double i = minX; i <= maxX + step; i += step) {
        std::list<ElemQueue> copyExpression(this->expression);
        this->calculatePolishNotatin(i);
        res.push_back(std::pair<double, double>(i, this->getData()));
        this->expression.swap(copyExpression);
    }
    this->clear();
    return res;
}

void Model::clear() {
    this->expression.clear();
    this->isXInExpression = false;
}

Model::creditOutput Model::calculateAnnuityCredit(double totalAmount, int term,
                                                  bool termInYear, double rate) {
    double monthlyPayment, rateInMonth, termInMonth, totalPayment = 0;
    rateInMonth = (rate / 100) / 12;
    if (termInYear) {
        termInMonth = term * 12;
    } else {
        termInMonth = term;
    }
    monthlyPayment = totalAmount * (rateInMonth + (rateInMonth / (pow(1 + rateInMonth, termInMonth) - 1)));
    creditOutput res;
    res.totalPayment = 0;
    std::pair<double, double> payment;
    double remainsTotalAmount = totalAmount;
    for (int i = 0; i < termInMonth; i++) {
        payment.first = round(monthlyPayment*100)/100;
        payment.second = round(remainsTotalAmount * rateInMonth*100)/100;
        remainsTotalAmount -= (payment.first - payment.second);
        res.monthlyPayment.push_back(payment);
        totalPayment += monthlyPayment;
        res.totalPayment += payment.first;
    }
    res.overpayment = totalPayment - totalAmount;
    res.totalPayment = round(res.totalPayment*100)/100;
    res.overpayment = round(res.overpayment*100)/100;

    return res;
}

Model::creditOutput Model::calculateDifferentiatedCredit(double totalAmount, int term,
                                                         bool termInYear, double rate) {
    double debtPathMonthlyPayment, termInMonth, rateInMonth;
    rateInMonth = (rate / 100) / 12;
    creditOutput res;
    res.totalPayment = 0;
    std::pair<double, double> payment;
    if (termInYear) {
        termInMonth = term * 12;
    } else {
        termInMonth = term;
    }
    debtPathMonthlyPayment = totalAmount / termInMonth;
    double remainsTotalAmount = totalAmount;
    for (int i = 0; i < termInMonth; i++) {
        payment.first = debtPathMonthlyPayment + (remainsTotalAmount * rateInMonth);
        payment.second = round(remainsTotalAmount * rateInMonth*100)/100;
        res.monthlyPayment.push_back(payment);
        res.totalPayment += payment.first;
        res.monthlyPayment[i].first = round(res.monthlyPayment[i].first*100)/100;
        remainsTotalAmount -= (payment.first - payment.second);
    }
    res.overpayment = res.totalPayment - totalAmount;
    res.totalPayment = round(res.totalPayment*100)/100;
    res.overpayment = round(res.overpayment*100)/100;
    return res;
}

double Model::calculateResultExpression(double x) {
    if (!expression.empty() && expression.back().operation_ == 'e' && expression.back().isNumber_) {
        expression.back().operation_ = 0;
        addElemToList(false, -1, 0, 6, ')');
    }
    transformExpressionToPolishNotation();
    calculatePolishNotatin(x);
    return getData();
}

double Model::getData() {
    return expression.front().data_;
}
}  //  namespace s21

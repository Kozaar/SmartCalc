#include "SmartCalc_v2/model.h"
#include <gtest/gtest.h>

TEST(operations_suit, normal_arithmetic_operations_test) {
    s21::Model model;
    model.addNumber(6);
    model.addOperation('.');
    model.addNumber(6);
    model.addOperation('/');
    model.addNumber(2);
    model.addOperation('^');
    model.addOperation('-');
    model.addOperation('-');
    model.addNumber(3);
    model.addOperation('^');
    model.addNumber(4);

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    // ASSERT_NO_THROW(model.transformExpressionToPolishNotation());
    // ASSERT_NO_THROW(model.calculatePolishNotatin());
    ASSERT_TRUE(model.getData() < pow(10, -7));
    ASSERT_TRUE(model.getData() > -pow(10, -7));

    model.clear();

    model.addNumber(2);
    model.addOperation('+');
    model.addNumber(9);
    model.addOperation('m');
    model.addNumber(2);
    model.addOperation('*');
    model.addNumber(4);
    model.addOperation('^');
    model.addNumber(0.5);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_EQ(model.getData(), 3);

    model.clear();


    model.addNumber(2);
    model.addOperation('+');
    model.addX();
    ASSERT_NO_THROW(model.calculateResultExpression(3));
    ASSERT_EQ(model.getData(), 5);
}

TEST(operations_suit, normal_trigonometric_operations_test) {
    s21::Model model;
    model.addOperation('s');
    model.addX();
    ASSERT_NO_THROW(model.calculateResultExpression(1));
    ASSERT_EQ(model.getData(), sin(1.));

    model.clear();

    model.addOperation('c');
    model.addOperation('(');
    model.addNumber(0.2);
    model.addOperation(')');
    model.addOperation('-');
    model.addOperation('o');
    model.addOperation('(');
    model.addOperation('q');
    model.addOperation('(');
    model.addNumber(0.04);
    model.addOperation(')');
    model.addOperation(')');

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() + 0.3893718 < pow(10, -7) && model.getData() + 0.3893718 > -pow(10, -7));

    model.clear();

    model.addOperation('n');
    model.addOperation('(');
    model.addNumber(1);
    model.addOperation(')');
    model.addOperation('+');
    model.addOperation('l');
    model.addOperation('(');
    model.addNumber(1);
    model.addOperation(')');

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_EQ(model.getData(), 0);
}

TEST(bracket_test_suit, normal_case) {
    s21::Model model;
    model.addOperation('-');
    model.addOperation('-');
    model.addNumber(6);
    model.addScaleToNumber();
    model.addNumber(6);
    model.addOperation('/');
    model.addOperation('(');
    model.addNumber(2);
    model.addOperation('^');
    model.addNumber(3);
    model.addOperation(')');
    model.addOperation('^');
    model.addNumber(4);

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    // ASSERT_TRUE(model.getData() + 0.3893718 < pow(10, -7) && model.getData() + 0.3893718 > -pow(10, -7));
    ASSERT_EQ(model.getData(), 6.6/(pow(pow(2, 3), 4)));

    model.clear();

    model.addOperation('-');
    model.addOperation('(');
    model.addOperation('-');
    model.addNumber(6);
    model.addScaleToNumber();
    model.addNumber(2);
    model.addNumber(3);
    model.addOperation(')');

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - 6.23 < pow(10, -7) && model.getData() - 6.23 > -pow(10, -7));

    model.clear();

    model.addScaleToNumber();
    model.addNumber(2);
    model.addOperation('+');
    model.addOperation('(');
    model.addOperation('-');
    model.addNumber(3);
    model.addOperation(')');

    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() + 2.8 < pow(10, -7) && model.getData() + 2.8 > -pow(10, -7));
}

TEST(bracket_test_suit, abnormal_case) {
    s21::Model model;
    model.addNumber(22);
    model.addOperation('-');
    model.addOperation('c');
    model.addOperation('(');
    model.addNumber(3);

    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.clear();

    model.addOperation('i');
    model.addOperation('(');
    model.addNumber(0.3);
    model.addOperation(')');
    model.addOperation('-');
    model.addOperation('-');
    model.addNumber(0.3);
    model.addOperation(')');

    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.clear();

    model.addOperation('(');
    model.addOperation(')');
    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.clear();

    model.addOperation('(');
    model.addNumber(0.3);
    model.addOperation(')');
    model.addOperation(')');
    ASSERT_ANY_THROW(model.calculateResultExpression(0));
}

TEST(operations_suit, abnormal_tests) {
    s21::Model model;
    model.addNumber(22);
    model.addOperation('^');

    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.clear();

    model.addOperation('-');
    model.addOperation('-');
    model.addOperation('-');

    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.clear();

    model.addOperation('(');
    model.addOperation('a');
    model.addOperation('t');
    model.addOperation(')');

    ASSERT_ANY_THROW(model.calculateResultExpression(0));

    model.addNumber(3);
    model.addScaleToNumber();
    model.addNumber(6);
    ASSERT_ANY_THROW(model.addScaleToNumber());

    model.clear();
}

TEST(exponenta_suit, exponenta_tests) {
    s21::Model model;
    model.addNumber(1);
    model.addOperation('+');
    model.addE();
    model.addOperation('-');
    model.addNumber(2);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - (M_E -1) < pow(10, -7) && model.getData() - (M_E -1) > -pow(10, -7));
}

TEST(exponenta_suit, scientific_notation_tests) {
    s21::Model model;
    model.addNumber(2);
    model.addE();
    model.addNumber(2);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - (2 * pow(10, 2)) < pow(10, -7) && model.getData() - (2 * pow(10, 2)) > -pow(10, -7));

    model.clear();

    model.addNumber(2);
    model.addE();
    model.addOperation('+');
    model.addNumber(2);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - (2 * pow(10, 2)) < pow(10, -7) && model.getData() - (2 * pow(10, 2)) > -pow(10, -7));

    model.clear();

    model.addNumber(2);
    model.addE();
    model.addOperation('-');
    model.addNumber(2);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - (2 * pow(10, -2)) < pow(10, -7) && model.getData() - (2 * pow(10, -2)) > -pow(10, -7));

    model.clear();

    model.addNumber(1);
    model.addOperation('+');
    model.addNumber(2);
    model.addE();
    model.addNumber(2);
    model.addOperation('-');
    model.addNumber(4);
    ASSERT_NO_THROW(model.calculateResultExpression(0));
    ASSERT_TRUE(model.getData() - (1 + 2 * pow(10, 2) - 4) < pow(10, -7) &&
                model.getData() - (1 + 2 * pow(10, 2) - 4) > -pow(10, -7));
}

TEST(graph_suit, graph_x_test) {
    s21::Model model;
    model.addX();
    std::vector<std::pair<double, double> > res = model.calculatePointCoordinates(-10, 10);
    for (size_t i = 0; i < res.size(); i++) {
        ASSERT_EQ(res[i].first, res[i].second);
    }
}

TEST(credit_calc_suit, annuity_credit_test) {
    s21::Model model;
    s21::Model::creditOutput res = model.calculateAnnuityCredit(10000, 1, true, 9);
    ASSERT_EQ(res.monthlyPayment.front().first, 874.51);
    ASSERT_EQ(res.overpayment, 494.18);
    ASSERT_EQ(res.totalPayment, 10494.12);
}

TEST(credit_calc_suit, differentiated_credit_test) {
    s21::Model model;
    s21::Model::creditOutput res = model.calculateDifferentiatedCredit(10000, 1, true, 9);
    ASSERT_EQ(res.monthlyPayment.front().first, 908.33);
    ASSERT_EQ(res.monthlyPayment.back().first, 839.58);
    ASSERT_EQ(res.overpayment, 487.50);
    ASSERT_EQ(res.totalPayment, 10487.50);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

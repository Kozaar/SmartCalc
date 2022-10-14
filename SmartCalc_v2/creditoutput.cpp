#include "creditoutput.h"
#include "ui_creditoutput.h"

namespace s21 {
CreditOutput::CreditOutput(const Model::creditOutput &monthlyPayment, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditOutput) {
    ui->setupUi(this);
    this->setWindowTitle("Payment schedule");
    this->setFixedSize(this->width(), this->height());
    QStandardItemModel *model = new QStandardItemModel(monthlyPayment.monthlyPayment.size(), 2, this);
    ui->tableView->setModel(model);
    for (size_t row = 0; row < monthlyPayment.monthlyPayment.size(); row++) {
        model->setData(model->index(row, 0, QModelIndex()),
                       monthlyPayment.monthlyPayment[row].first);
        model->setData(model->index(row, 1, QModelIndex()),
                       monthlyPayment.monthlyPayment[row].second);
    }
    ui->labelOverpayment->setText(QString("Overpayment on credit: ") +
                                  QString::number(monthlyPayment.overpayment, 'f', 2));
    ui->labelTotalPayment->setText(QString("Total payment: ") +
                                   QString::number(monthlyPayment.totalPayment, 'f', 2));
    model->setHeaderData(0, Qt::Horizontal, "Monthly payment");
    model->setHeaderData(1, Qt::Horizontal, "Percentage of interest");
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

CreditOutput::~CreditOutput() {
    delete ui->tableView->model();
    delete ui;
}

void CreditOutput::on_pushButton_clicked() {
    this->close();
}
}  //  namespace s21

#include "graphwindow.h"
#include "ui_graphwindow.h"

namespace s21 {
GraphWindow::GraphWindow(QString expression, Controller *controller,
                         double minX, double maxX, double minY, double maxY, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow) {
    this->setFixedSize(900, 900);
    ui->setupUi(this);
    this->setWindowTitle(expression);
    this->controller_ = controller;
    this->minX_ = minX;
    this->maxX_ = maxX;
    this->minY_ = minY;
    this->maxY_ = maxY;
    QGraphicsScene *scene = new QGraphicsScene;
    this->ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(ui->graphicsView->width()/2, ui->graphicsView->height()/2);
    ui->graphicsView->setSceneRect(0, 0, ui->graphicsView->width()-40, ui->graphicsView->height()-40);
    findCenter();
    drawAxis();
    drawStep();
    drawGraph();
}

GraphWindow::~GraphWindow() {
    delete ui;
}

void GraphWindow::drawAxis() {
    this->ui->graphicsView->scene()->addLine(0, this->centerY_,
                                             ui->graphicsView->sceneRect().width(), this->centerY_);
    this->ui->graphicsView->scene()->addLine(this->centerX_, 0, this->centerX_,
                                             ui->graphicsView->sceneRect().height());
}

void GraphWindow::drawStep() {
    double stepXValue = (maxX_ - minX_) / 20;
    double stepXInScene = this->ui->graphicsView->sceneRect().width() / 20;
    for (int i = 0; i <= 20; i++) {
        if (minX_ + stepXValue*i == 0) continue;
        QGraphicsTextItem *text = new QGraphicsTextItem;
        text->setPos(stepXInScene*i - 12, this->centerY_);
        text->setPlainText(QString::number(minX_ + stepXValue*i, 'g', 4));
        text->setFont(QFont("Times", 10));
        this->ui->graphicsView->scene()->addItem(text);
        this->ui->graphicsView->scene()->addLine(stepXInScene*i, this->centerY_-3,
                                                 stepXInScene*i, this->centerY_+3);
        this->ui->graphicsView->scene()->addLine(stepXInScene*i, 0,
                                                 stepXInScene*i, ui->graphicsView->height(),
                                                 QPen(QBrush(Qt::lightGray), 0.3));
    }
    double stepYValue = (maxY_ - minY_) / 20;
    double stepYInScene = this->ui->graphicsView->sceneRect().height() / 20;
    for (int i = 0; i <= 20; i++) {
        if (maxY_ - stepYValue*i == 0) continue;
        QGraphicsTextItem *text = new QGraphicsTextItem;
        text->setPos(this->centerX_, stepYInScene*i - 12);
        text->setPlainText(QString::number((maxY_ - stepYValue*i), 'g', 4));
        text->setFont(QFont("Times", 10));
        this->ui->graphicsView->scene()->addItem(text);
        this->ui->graphicsView->scene()->addLine(this->centerX_-3, stepYInScene*i,
                                                 this->centerX_+3, stepYInScene*i);
        this->ui->graphicsView->scene()->addLine(0, stepYInScene*i,
                                                 ui->graphicsView->width(), stepYInScene*i,
                                                 QPen(QBrush(Qt::lightGray), 0.3));
    }
    QGraphicsTextItem *text = new QGraphicsTextItem;
    text->setPos(this->centerX_, this->centerY_);
    text->setPlainText("0");
    text->setDefaultTextColor(Qt::red);
    this->ui->graphicsView->scene()->addItem(text);
}

void GraphWindow::drawGraph() {
    double scaleX = this->ui->graphicsView->sceneRect().width() / (fabs(this->minX_) + this->maxX_);
    double scaleY = this->ui->graphicsView->sceneRect().height() / (fabs(this->minY_) + this->maxY_);
    if (minX_ > 0) {
        scaleX = this->ui->graphicsView->sceneRect().width() / (maxX_ - minX_);
        centerX_ = minX_ * (-1) * scaleX;
    } else if (maxX_ < 0) {
        scaleX = this->ui->graphicsView->sceneRect().width() / (maxX_ - minX_);
        centerX_ = this->ui->graphicsView->sceneRect().width() + maxX_ * scaleX * (-1);
    }
    if (minY_ > 0) {
        scaleY = this->ui->graphicsView->sceneRect().height() / (maxY_ - minY_);
        centerY_ = this->ui->graphicsView->sceneRect().height() + minY_ * scaleY;
    } else if (maxY_ < 0) {
        scaleY = this->ui->graphicsView->sceneRect().height() / (maxY_ - minY_);
        centerY_ = maxY_ * scaleY;
    }
    QPen pen(QColor(0, 0, 255), 2);
    std::vector<std::pair<double, double> > pointCoordinates;
    pointCoordinates = this->controller_->calculateGraphCordinates(this->minX_, this->maxX_);
    for (size_t i = 1; i < pointCoordinates.size(); i++) {
        this->ui->graphicsView->scene()->addLine(centerX_ + pointCoordinates[i-1].first * scaleX,
                centerY_ - pointCoordinates[i-1].second * scaleY,
                centerX_ + pointCoordinates[i].first * scaleX,
                centerY_ - pointCoordinates[i].second * scaleY, pen);
    }
}

void GraphWindow::findCenter() {
    if (maxX_ <= 0) {
        this->centerX_ = this->ui->graphicsView->sceneRect().width();
    } else if (minX_ >= 0) {
        this->centerX_ = 0;
    } else if (fabs(this->minX_) == this->maxX_) {
        double width = this->ui->graphicsView->sceneRect().width();
        this->centerX_ = width / 2;
    } else {
        double stepX = this->ui->graphicsView->sceneRect().width() / (fabs(this->minX_) + this->maxX_);
        this->centerX_ = stepX * fabs(this->minX_);
    }
    if (maxY_ <= 0) {
        this->centerY_ = 0;
    } else if (minY_ >= 0) {
        this->centerY_ = this->ui->graphicsView->sceneRect().height();
    } else if (fabs(minY_) == maxY_) {
        double height = this->ui->graphicsView->sceneRect().height();
        this->centerY_ = height / 2;
    } else {
        double stepY = this->ui->graphicsView->sceneRect().height() / (fabs(minY_) + maxY_);
        this->centerY_ = stepY * maxY_;
    }
}
}  //  namespace s21

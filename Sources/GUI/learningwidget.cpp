#include "learningwidget.h"
#include "ui_learningwidget.h"

LearningWidget::LearningWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LearningWidget)
{
    ui->setupUi(this);
}

LearningWidget::~LearningWidget()
{
    delete ui;
}

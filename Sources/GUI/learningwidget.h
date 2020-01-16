#pragma once

#include <QtWidgets/QWidget>

namespace Ui
{
class LearningWidget;
}

class LearningWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LearningWidget( QWidget* parent = nullptr );
    ~LearningWidget( );

private:
    Ui::LearningWidget* ui;
};

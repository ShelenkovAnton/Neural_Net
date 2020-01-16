#pragma once

#include <QtWidgets/QWidget>

namespace Ui
{
class SetupNetWidget;
}

class SetupNetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetupNetWidget( QWidget* parent = nullptr );
    ~SetupNetWidget( );

private:
    auto init( ) -> void;
    auto init_styles( ) -> void;
    auto init_connections( ) -> void;

private:
    Ui::SetupNetWidget* ui;
};

#pragma once

#include <QtWidgets/QWidget>

namespace Ui
{
class Layoutitem;
}

class Layoutitem : public QWidget
{
    Q_OBJECT

public:
    explicit Layoutitem( QWidget* parent = nullptr );
    ~Layoutitem( );

    auto get_neurons_count( ) const -> int;

private:
    Ui::Layoutitem* ui;
};

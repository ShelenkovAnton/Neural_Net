#pragma once

#include <QMouseEvent>
#include <QtWidgets/QWidget>

namespace Ui
{
class LayerItem;
}

class LayerItem final : public QWidget
{
    Q_OBJECT

public:
    explicit LayerItem( QWidget* parent = nullptr );
    ~LayerItem( ) override;

    auto get_neurons_count( ) const -> int;
    auto is_selected( ) const -> bool;

protected:
    auto mousePressEvent( QMouseEvent* event ) -> void override;

private:
    auto init( ) -> void;
    auto init_styles( ) -> void;

private:
    Ui::LayerItem* ui;

    bool m_selected{false};
};

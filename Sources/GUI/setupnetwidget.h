#pragma once

#include <QtWidgets/QWidget>

class LayerItem;

namespace Ui
{
class SetupNetWidget;
}

class SetupNetWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit SetupNetWidget( QWidget* parent = nullptr );
    ~SetupNetWidget( );

signals:
    void s_load_from_file( );
    void s_start_learning( );

private:
    auto on_add_layer( ) -> void;
    auto on_remove_layer( ) -> void;
    auto on_start_learning( ) -> void;
    auto on_load_from_file( ) -> void;

private:
    auto init( ) -> void;
    auto init_styles( ) -> void;
    auto init_connections( ) -> void;

private:
    Ui::SetupNetWidget* ui;
    std::list<LayerItem*> m_items;
};

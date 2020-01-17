#include "layeritem.h"
#include "ui_layeritem.h"

LayerItem::LayerItem( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::LayerItem )
{
    ui->setupUi( this );
}

LayerItem::~LayerItem( )
{
    delete ui;
}

auto LayerItem::get_neurons_count( ) const -> int
{
    return ui->spinBox->value( );
}

auto LayerItem::is_selected( ) const -> bool
{
    return m_selected;
}

auto LayerItem::mousePressEvent( QMouseEvent* event ) -> void
{
    m_selected = !m_selected;

    // change style

    QWidget::mousePressEvent( event );
}

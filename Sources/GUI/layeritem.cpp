#include "layeritem.h"
#include "ui_layeritem.h"

#include "styles.h"

LayerItem::LayerItem( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::LayerItem )
{
    ui->setupUi( this );
    init( );
}

LayerItem::~LayerItem( )
{
    delete ui;
}

auto LayerItem::init( ) -> void
{
    init_styles( );
}

auto LayerItem::init_styles( ) -> void
{
    // Styles::aply_main_style( this );
    //    Styles::aply_group_box_style( ui->groupBox );
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

    if ( m_selected )
    {
        Styles::aply_selected_style( ui->frame );
    }
    else
    {
        Styles::remove_selected_style( ui->frame );
    }

    QWidget::mousePressEvent( event );
}

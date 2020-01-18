#include "setupnetwidget.h"
#include "ui_setupnetwidget.h"

#include "layeritem.h"
#include "styles.h"

SetupNetWidget::SetupNetWidget( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::SetupNetWidget )
{
    ui->setupUi( this );

    init( );
}

SetupNetWidget::~SetupNetWidget( )
{
    delete ui;
}

auto SetupNetWidget::init( ) -> void
{
    init_styles( );
    init_connections( );
}

auto SetupNetWidget::init_styles( ) -> void
{
    // Styles::aply_main_style( this );

    // ui->scrollArea->setStyleSheet( "QScrollArea { background: transparent; }" );
    // Styles::aply_background_style( this, Qt::red );

    // Styles::aply_group_box_style( ui->frNetSetup );
}

auto SetupNetWidget::init_connections( ) -> void
{
    connect( ui->btnAddLayer, &QPushButton::clicked, this, &SetupNetWidget::on_add_layer );
    connect( ui->btnRemoveLayer, &QPushButton::clicked, this, &SetupNetWidget::on_remove_layer );
    connect( ui->btnLoadFromFile, &QPushButton::clicked, this, &SetupNetWidget::on_load_from_file );
    connect( ui->btnStartLearning, &QPushButton::clicked, this, &SetupNetWidget::on_start_learning );
}

auto SetupNetWidget::on_add_layer( ) -> void
{
    const auto layer_item = new LayerItem( );
    ui->layerLayout->insertWidget( static_cast<int>( m_items.size( ) ), layer_item );
    m_items.push_back( layer_item );
}

auto SetupNetWidget::on_remove_layer( ) -> void
{
    if ( m_items.empty( ) )
    {
        return;
    }

    std::list<LayerItem*> selected_items;

    std::copy_if( m_items.begin( ), m_items.end( ), std::back_inserter( selected_items ), []( const auto& item ) { return item->is_selected( ); } );

    if ( selected_items.empty( ) )
    {
        selected_items.push_back( m_items.back( ) );
    }

    for ( const auto& item : selected_items )
    {
        ui->layerLayout->removeWidget( item );
        m_items.remove( item );
        delete item;
    }
    selected_items.clear( );
}

auto SetupNetWidget::on_start_learning( ) -> void
{
    emit s_start_learning( );
}

auto SetupNetWidget::on_load_from_file( ) -> void
{
    emit s_load_from_file( );
}

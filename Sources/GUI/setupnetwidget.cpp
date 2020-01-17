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
    Styles::aply_btn_style( ui->frame_btn );
    Styles::aply_group_box_style( ui->frNetSetup );
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
    ui->layerLayout->addWidget( layer_item );
    m_items.push_back( layer_item );
}

auto SetupNetWidget::on_remove_layer( ) -> void
{
    for ( const auto& item : m_items )
    {
        if ( item->is_selected( ) || ( item == m_items.back( ) ) )
        {
            ui->layerLayout->removeWidget( item );
            m_items.remove( item );
            item->deleteLater( );
            break;
        }
    }
}

auto SetupNetWidget::on_start_learning( ) -> void
{
    emit s_start_learning( );
}

auto SetupNetWidget::on_load_from_file( ) -> void
{
    emit s_load_from_file( );
}

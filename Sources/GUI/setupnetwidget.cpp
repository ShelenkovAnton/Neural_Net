#include "setupnetwidget.h"
#include "ui_setupnetwidget.h"

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
}

auto SetupNetWidget::init_connections( ) -> void
{
}

#include "layoutitem.h"
#include "ui_layoutitem.h"

Layoutitem::Layoutitem( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Layoutitem )
{
    ui->setupUi( this );
}

Layoutitem::~Layoutitem( )
{
    delete ui;
}

auto Layoutitem::get_neurons_count( ) const -> int
{
    return ui->spinBox->value( );
}

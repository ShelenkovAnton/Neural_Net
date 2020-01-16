#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QButtonGroup>

#include "styles.h"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , m_setup_net_wgt{new QLabel( "setup" )}
    , m_learning_wgt{new QLabel( "learning" )}
    , m_painting_wgt{new PaintWidget( )}
{
    ui->setupUi( this );

    init( );
}

MainWindow::~MainWindow( )
{
    delete ui;
}

auto MainWindow::init( ) -> void
{
    hide_widgets( );
    add_widgets( );
    init_btn_group( );
    init_connections( );
    init_styles( );
}

auto MainWindow::add_widgets( ) -> void
{
    ui->centralLayout->addWidget( m_learning_wgt );
    ui->centralLayout->addWidget( m_painting_wgt );
    ui->centralLayout->addWidget( m_setup_net_wgt );
}

auto MainWindow::init_styles( ) -> void
{
    Styles::aply_background_style( this, {Styles::Colors::window_background} );
    Styles::aply_checkable_btn_style( ui->frame_btn );
}

auto MainWindow::init_connections( ) -> void
{
    connect( ui->btnSetupNet, &QPushButton::clicked, this, &MainWindow::show_setup_net_wgt );
    connect( ui->btnLearning, &QPushButton::clicked, this, &MainWindow::show_learning_wgt );
    connect( ui->btnPainting, &QPushButton::clicked, this, &MainWindow::show_painting_wgt );
}

auto MainWindow::init_btn_group( ) -> void
{
    const auto group = new QButtonGroup( );
    group->addButton( ui->btnSetupNet );
    group->addButton( ui->btnLearning );
    group->addButton( ui->btnPainting );
}

auto MainWindow::show_setup_net_wgt( ) -> void
{
    hide_widgets( );
    m_setup_net_wgt->setVisible( true );
}

auto MainWindow::show_learning_wgt( ) -> void
{
    hide_widgets( );
    m_learning_wgt->setVisible( true );
}

auto MainWindow::show_painting_wgt( ) -> void
{
    hide_widgets( );
    m_painting_wgt->setVisible( true );
}

auto MainWindow::hide_widgets( ) -> void
{
    m_learning_wgt->setVisible( false );
    m_painting_wgt->setVisible( false );
    m_setup_net_wgt->setVisible( false );
}

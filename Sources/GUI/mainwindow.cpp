#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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
    init_connections( );
    init_styles( );
}

MainWindow::~MainWindow( )
{
    delete ui;
}

auto MainWindow::init_styles( ) -> void
{
    Styles::aply_background_style( this, {Styles::Colors::background} );
}

auto MainWindow::init_connections( ) -> void
{
    connect( ui->btnSetupNet, &QPushButton::clicked, this, &MainWindow::show_setup_net_wgt );
    connect( ui->btnLearning, &QPushButton::clicked, this, &MainWindow::show_learning_wgt );
    connect( ui->btnPainting, &QPushButton::clicked, this, &MainWindow::show_painting_wgt );
}

auto MainWindow::init( ) -> void
{
    m_learning_wgt->setVisible( false );
    m_painting_wgt->setVisible( false );
    m_setup_net_wgt->setVisible( false );

    ui->centralLayout->addWidget( m_learning_wgt );
    ui->centralLayout->addWidget( m_painting_wgt );
    ui->centralLayout->addWidget( m_setup_net_wgt );
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

#include "DataSet/mnistset.h"
#include "net.h"

#include <QDebug>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

#include <QObject>

#include "painter/paintwidget.h"
#include <iostream>

void paint( std::vector<float> inputs )
{
    std::for_each( inputs.begin( ), inputs.end( ), []( auto& input ) { input = ( input != 0 ) ? 1 : 0; } );

    for ( size_t i = 0; i < inputs.size( ); i++ )
    {
        std::cout << inputs[i];
        if ( i % 28 == 0 )
        {
            std::cout << std::endl;
        }
    }
}

void create_paint_widget( net::Net& net )
{
    const auto p = new PaintWidget( );
    p->show( );

    QObject::connect( p, &PaintWidget::s_net_input, [&]( const auto& inputs ) {
        paint( inputs );
        const auto out = net.propagate( inputs );

        qDebug( ) << "net outputs is " << std::distance( out.begin( ), std::max_element( out.begin( ), out.end( ) ) );

        auto index{0};
        for ( const auto& o : out )
        {
            qDebug( ) << index++ << " === " << o;
        }
    } );
}

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    net::Net net;

    net.create_layer( 100, /*! <- neuron count */ 784 /*! <- inputs count */ );
    net.create_layer( 10 );

    net.learn( net::MnistSet{} );
    create_paint_widget( net );

    return a.exec( );
}

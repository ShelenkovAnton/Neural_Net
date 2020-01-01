#include "paintwidget.h"
#include <QtWidgets>

constexpr auto pixSize{28};
constexpr auto penSize  = 30;
constexpr auto penColor = Qt::black;

PaintWidget::PaintWidget( )
{
}

auto PaintWidget::paintEvent( QPaintEvent* ) -> void
{
    QPainter painter{this};
    painter.drawPixmap( 0, 0, mPixmap );
}

auto PaintWidget::resizeEvent( QResizeEvent* ) -> void
{
    auto newRect = mPixmap.rect( ).united( this->rect( ) );

    QPixmap newPixmap{newRect.size( )};
    QPainter painter{&newPixmap};
    painter.fillRect( newPixmap.rect( ), Qt::white );
    painter.drawPixmap( 0, 0, mPixmap );
    mPixmap = newPixmap;
}

auto PaintWidget::mousePressEvent( QMouseEvent* event ) -> void
{
    mPixmap.fill( Qt::white );
    draw( event->pos( ) );
}

auto PaintWidget::mouseMoveEvent( QMouseEvent* event ) -> void
{
    draw( event->pos( ) );
}

auto PaintWidget::draw( const QPoint& pos ) -> void
{
    QPainter painter{&mPixmap};
    painter.setRenderHint( QPainter::RenderHint::HighQualityAntialiasing );
    painter.setPen( {penColor, penSize} );
    painter.drawPoint( pos );
    QWidget::update( );
}

auto PaintWidget::get_image_rect( ) const -> QRect
{
    const auto image = mPixmap.toImage( );

    auto x{mPixmap.width( )}, y{mPixmap.height( )}, w{0}, h{0};

    for ( int width = 0; width < image.width( ); ++width )
    {
        for ( int height = 0; height < image.height( ); ++height )
        {
            if ( image.pixelColor( width, height ) == penColor )
            {
                x = std::min( x, width );
                y = std::min( y, height );
                w = std::max( w, width );
                h = std::max( h, height );
            }
        }
    }

    w -= x;
    h -= y;

    QRect rect{x, y, w, h};

    const auto center = rect.center( );
    auto delta        = std::max( w, h );

    const auto mod = ( delta % pixSize );
    delta += ( mod == 0 ) ? 0 : ( pixSize - mod );
    delta /= 2;

    const QPoint margin{delta + delta / 5, delta + delta / 5};

    rect.setTopLeft( center - margin );
    rect.setBottomRight( center + margin );

    return rect;
}

auto PaintWidget::mouseReleaseEvent( QMouseEvent* ) -> void
{
    auto img = mPixmap.copy( get_image_rect( ) ).toImage( );

    const auto scaled_image = scale_image( img );

    mPixmap.fill( Qt::white );

    const auto label = new QLabel( this );
    label->setPixmap( QPixmap::fromImage( scaled_image ).scaled( 200, 200 ) );
    label->show( );
    label->setFrameStyle( 1 );

    QWidget::update( );

    emit s_net_input( get_image_colors( scaled_image ) );
}

auto PaintWidget::scale_image( const QImage& image ) const -> QImage
{
    const auto scale = image.width( ) / pixSize;

    auto pixel_color = [&]( const auto& x, const auto& y ) {
        int red{0}, green{0}, blue{0};

        for ( int i = scale * x; i < ( scale * ( x + 1 ) ); ++i )
        {
            for ( int j = scale * y; j < ( scale * ( y + 1 ) ); ++j )
            {
                const auto c = image.pixelColor( i, j );

                red += c.red( );
                green += c.green( );
                blue += c.blue( );
            }
        }

        const auto s = std::pow( scale, 2 );
        return QColor{static_cast<int>( red / s ), static_cast<int>( green / s ), static_cast<int>( blue / s )};
    };

    QImage output_image{pixSize, pixSize, QImage::Format::Format_RGB32};

    for ( int x = 0; x < pixSize; ++x )
    {
        for ( int y = 0; y < pixSize; ++y )
        {
            output_image.setPixelColor( x, y, pixel_color( x, y ) );
        }
    }

    return output_image;
}

auto PaintWidget::get_image_colors( const QImage& img ) const -> std::vector<float>
{
    std::vector<float> imageVector;
    imageVector.reserve( pixSize * pixSize );

    for ( auto w = 0; w < pixSize; ++w )
    {
        for ( auto h = 0; h < pixSize; ++h )
        {
            imageVector.push_back( static_cast<float>( img.pixelColor( h, w ).black( ) ) / 255.0f );
        }
    }

    return imageVector;
}

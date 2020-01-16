#pragma once

#include <QImage>
#include <QMouseEvent>
#include <QWidget>

namespace Ui
{
class PaintWidget;
}

class PaintWidget final : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget( ) = default;

signals:
    void s_net_input( std::vector<float> );

protected:
    auto paintEvent( QPaintEvent* ) -> void override;
    auto resizeEvent( QResizeEvent* ) -> void override;

    auto mousePressEvent( QMouseEvent* ) -> void override;
    auto mouseMoveEvent( QMouseEvent* ) -> void override;
    auto mouseReleaseEvent( QMouseEvent* ) -> void override;

private:
    auto get_image_colors( const QImage& ) const -> std::vector<float>;
    auto grab_image( const QRect& ) -> void;
    auto draw( const QPoint& ) -> void;
    auto get_image_rect( ) const -> QRect;
    auto scale_image( const QImage& ) const -> QImage;

private:
    QPixmap mPixmap;
};

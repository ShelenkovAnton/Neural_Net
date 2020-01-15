#include "styles.h"

#include <QWidget>

#include <QDebug>

auto Styles::aply_background_style( QWidget* const widget, const QColor& color ) -> void
{
    const auto style = QString{R"(%1{ background-color: %2; })"}.arg( widget->objectName( ) ).arg( color.name( ) );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

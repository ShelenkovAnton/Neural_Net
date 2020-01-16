#include "styles.h"

#include <QWidget>

#include <QDebug>

auto Styles::aply_background_style( QWidget* const widget, const QColor& color ) -> void
{
    const auto style = QString{R"(%1{ background-color: %2; })"}.arg( widget->objectName( ) ).arg( color.name( ) );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

auto Styles::aply_btn_style( QWidget* const widget ) -> void
{
    const auto style = QString( R"(
    QAbstractButton
    {
        background-color: %1;
    }
    QPushButton:checked
    {
        background-color: %2;
    }
    QPushButton:hover
    {
        background-color: %3;
    }
)" )
                           .arg( Styles::colors.btn_background )
                           .arg( Styles::colors.checked_btn_background )
                           .arg( Styles::colors.hovered_btn_background );

    widget->setStyleSheet( style );
}

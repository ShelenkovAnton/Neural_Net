#include "styles.h"

#include <QWidget>

#include <QDebug>

auto Styles::aply_background_style( QWidget* const widget, const QColor& color ) -> void
{
    const auto style = QString{R"(%1{ background-color: %2; })"}.arg( widget->objectName( ) ).arg( color.name( ) );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

auto Styles::aply_group_box_style( QWidget* const widget ) -> void
{
    const auto style = QString( R"(
    QGroupBox
    {
        color: white;
    }
)" );

    widget->setStyleSheet( widget->styleSheet( ) + style );
}

auto Styles::aply_selected_style( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ) + get_selected_style( ) );
}

auto Styles::remove_selected_style( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ).remove( get_selected_style( ) ) );
}

auto Styles::get_selected_style( ) -> QString
{
    const auto style = QString( R"(
    QFrame
    {
        background-color: %1;
    }
    )" )
                           .arg( Styles::colors.selected_frame_color );
    return style;
}

auto Styles::aply_main_style( QWidget* const widget ) -> void
{
    widget->setStyleSheet( widget->styleSheet( ) + get_main_style( ) );
}

auto Styles::get_main_style( ) -> QString
{
    const auto style = QString( R"(
    QWidget
    {
        background-color: %1;
    }

    QAbstractButton
    {
        background-color: %2;
        color: white;
    }
    QAbstractButton:checked
    {
        background-color: %3;
    }
    QAbstractButton:hover
    {
        background-color: %4;
    }
    QGroupBox
    {
        color: white;
    }
    QComboBox
    {
        color: white;
    }
)" )

                           .arg( Styles::colors.window_background )
                           .arg( Styles::colors.btn_background )
                           .arg( Styles::colors.checked_btn_background )
                           .arg( Styles::colors.hovered_btn_background );

    return style;
}

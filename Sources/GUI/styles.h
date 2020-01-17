#pragma once

#include <QColor>

class QWidget;

class Styles
{
public:
    static auto aply_background_style( QWidget* const, const QColor& ) -> void;
    static auto aply_btn_style( QWidget* const ) -> void;
    static auto aply_group_box_style( QWidget* const ) -> void;

    static const struct Colors
    {
        static constexpr auto window_background      = "#27292D";
        static constexpr auto btn_background         = "#1F2023";
        static constexpr auto checked_btn_background = "#0000FF";
        static constexpr auto hovered_btn_background = "#414144";
    } colors;
};

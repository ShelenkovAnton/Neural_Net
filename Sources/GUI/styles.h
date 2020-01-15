#pragma once

#include <QColor>

class QWidget;

class Styles
{
public:
    static auto aply_background_style( QWidget* const, const QColor& ) -> void;

    static const struct Colors
    {
        static constexpr auto background = "#27292D";
    } colors;
};

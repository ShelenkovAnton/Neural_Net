#pragma once

#include <QtWidgets/QMainWindow>

#include <QLabel> // test

#include "paintwidget.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow( );

private:
    auto show_setup_net_wgt( ) -> void;
    auto show_learning_wgt( ) -> void;
    auto show_painting_wgt( ) -> void;

private:
    auto init( ) -> void;
    auto init_styles( ) -> void;
    auto init_connections( ) -> void;
    auto hide_widgets( ) -> void;

private:
    Ui::MainWindow* ui;

    QLabel* m_setup_net_wgt{nullptr}; // change Qlabel to proper widgets
    QLabel* m_learning_wgt{nullptr};  // change Qlabel to proper widgets
    PaintWidget* m_painting_wgt{nullptr};
};

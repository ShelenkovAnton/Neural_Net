#pragma once

#include <QtWidgets/QMainWindow>

class SetupNetWidget;
class PaintWidget;
class LearningWidget;

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
    auto init_btn_group( ) -> void;
    auto add_widgets( ) -> void;

private:
    Ui::MainWindow* ui;

    SetupNetWidget* m_setup_net_wgt{nullptr};
    LearningWidget* m_learning_wgt{nullptr};
    PaintWidget* m_painting_wgt{nullptr};
};

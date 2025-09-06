#ifndef VIEW_MAINWINDOW_HPP
#define VIEW_MAINWINDOW_HPP

#include <ftxui/component/screen_interactive.hpp>

class MainWindow final
{
public:
    explicit MainWindow();

    void Run();

private:
    ftxui::ScreenInteractive m_screen = ftxui::ScreenInteractive::Fullscreen();
    ftxui::Component m_mainComponent;
    ftxui::Component m_buttons;
    int m_value = 50;
};

#endif // VIEW_MAINWINDOW_HPP

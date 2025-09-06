#include "MainWindow.hpp"

#include <ftxui/component/component.hpp>

using namespace ftxui;

static ButtonOption ButtonStyle()
{
    auto option = ButtonOption::Animated();

    option.transform = [](const EntryState& s) {
        Element element = text(s.label);

        if (s.focused)
        {
            element |= bold;
        }

        return element | center | border | flex;
    };

    return option;
}

MainWindow::MainWindow()
{
    m_buttons = Container::Horizontal({
        Button("-1", [this] { m_value--; }, ButtonStyle()),
        Button("+1", [this] { m_value++; }, ButtonStyle()),
        Button("-10", [this] { m_value -= 10; }, ButtonStyle()),
        Button("+10", [this] { m_value += 10; }, ButtonStyle()),
    });

    m_mainComponent = Renderer(m_buttons, [this] {
        return vbox({
                text("value = " + std::to_string(m_value)) | center,
                separator(),
                m_buttons->Render()
                }) | flex | border;
    });
}

void MainWindow::Run()
{
    m_screen.Loop(m_mainComponent);
}

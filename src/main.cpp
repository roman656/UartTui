#include <View/MainWindow.hpp>
#include <Port/Port.hpp>

int main()
{
    Port port;

    port.Test();

    MainWindow window;

    window.Run();

    return 0;
}

# UartTui

TUI-приложение для взаимодействия с UART. Проверка идей

## Зависимости
- Asio (standalone)
- FTXUI
- GoogleTest (для тестов)

## Сборка
```bash
git clone <repo-url> UartTui
cd UartTui

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

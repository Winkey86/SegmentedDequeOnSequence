@echo off
g++ -std=c++11 cpp\main.cpp cpp\ArraySequence.cpp cpp\ListSequence.cpp cpp\DynamicArray.cpp cpp\LinkedList.cpp cpp\SegmentedDeque.cpp cpp\Types.cpp cpp\SegDeqMenu.cpp -o program.exe
if %errorlevel% neq 0 (
    echo Компиляция завершилась с ошибками.
    pause
    exit /b %errorlevel%
)
program.exe
pause

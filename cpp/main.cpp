#include <fstream>
#include <iostream>
#include <string>
#include "SegDeqMenu.h"

int main()
{

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "CAN`T OPEN input.txt\n";
        return 1;
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "CAN`T OPEN output.txt\n";
        return 1;
    }

    MenuDeque menu;
    std::string line;

    while (std::getline(inputFile, line))
    {
        if (!line.empty() && line[0] != '#')
        {
            std::cout << "[Main] Processing command: " << line << std::endl;
            menu.processCommand(line, outputFile);
            outputFile << "\n";
            outputFile.flush();
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "[Main] End\n";
    return 0;
}

#include <iostream>
#include <string>
#include "common.h"
#include "Utils.h"
#include "Cpu.h"

int main()
{
    Cpu cpu;
    std::string m;
    stream a;
    bool debugMode = true;
    std::cout << "Enter integer and get Fibonacci number on that index: ";
    std::cin >> m;
    a = std::stoi(m);
    std::cout << "The Fibonacci number on position "<< m << " is " << Utils::binaryToInt(cpu.run(a, debugMode)) << std::endl;
}
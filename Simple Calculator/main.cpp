#include <iostream>
#include "calculator.hpp"

int main(int argc, const char *argv[])
{
    Calculator calculator;
    bool isRunning = true;

    std::cout << "Welcome to the calculator! Type \"exit\" to terminate the calculator." << std::endl;

    while (isRunning)
    {
        std::cout << "\nPlease enter the expression to calculate: ";
        std::string expression = "";
        std::getline(std::cin, expression);

        if (expression == "exit")
        {
            isRunning = false;
        }
        else
        {
            double calculation = 0.0;
            try
            {
                calculation = calculator.calculate(expression);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }

            std::cout << "The calculated result was " << calculation << std::endl;
        }
    }

    std::cout << "Thank you for using the calculator! Good day!\n" << std::endl;
    return 0;
}

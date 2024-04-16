#include <iostream>
#include "calculator.hpp"

int main(int argc, const char *argv[])
{
    std::string expression = "2 / (2 * 3 - 6)";
    std::cout << "The expression to calculate: " << expression << std::endl;

    double answer = 0.0;
    try
    {
        answer = Calculator().calculate(expression);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "The calculated result was " << answer << std::endl;
    return 0;
}

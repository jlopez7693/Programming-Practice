#include <iostream>
#include "calculator.hpp"

int main(int argc, const char *argv[])
{
    std::string expression = "2 / (2 + 3)";
    std::cout << "The expression to calculate: " << expression << std::endl;

    double answer = Calculator().calculate(expression);
    std::cout << "The calculated result was " << answer << std::endl;

    return 0;
}

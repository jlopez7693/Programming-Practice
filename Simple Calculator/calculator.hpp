#ifndef calculator_h
#define calculator_h

#include <string>
#include <stack>

class Calculator
{
  public:
    Calculator();

    ~Calculator();

    double calculate(std::string s);

  private:
    enum Operator
    {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION
    };

    typedef std::stack<double> *OperandStack;

    typedef std::stack<std::pair<std::stack<double> *, Operator>> ExpressionStack;

    static constexpr double epsilon = 1e-10;

    void initialize();

    void deinitialize();

    void handleOperand(double operand);

    double evaluateOperands();

    OperandStack operands;
    ExpressionStack expressions;
    Operator currOp;
};

#endif

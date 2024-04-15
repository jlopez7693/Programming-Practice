#include "calculator.hpp"

Calculator::Calculator() : operands(nullptr), expressions(), currOp(ADDITION)
{
}

Calculator::~Calculator()
{
    if (this->operands)
    {
        delete this->operands;
    }
    while (!this->expressions.empty())
    {
        delete this->expressions.top().first;
        this->expressions.pop();
    }
}

double Calculator::calculate(std::string s)
{
    this->initialize();

    for (int i = 0; i < s.size(); i++)
    {
        char ch = s[i];

        if (isdigit(ch))
        {
            double num = 0;
            while (i < s.size() && isdigit(s[i]))
            {
                num = (num * 10) + (s[i] - '0');
                i++;
            }
            i--;

            this->handleOperand(num);
        }
        else
        {
            if (ch == '-')
            {
                this->currOp = SUBTRACTION;
            }
            else if (ch == '*')
            {
                this->currOp = MULTIPLICATION;
            }
            else if (ch == '/')
            {
                this->currOp = DIVISION;
            }
            else if (ch == '(')
            {
                this->expressions.push(std::make_pair(this->operands, currOp));
                this->initialize();
            }
            else if (ch == ')')
            {
                double num = this->evaluateOperands();

                this->operands = this->expressions.top().first;
                this->currOp = this->expressions.top().second;
                this->expressions.pop();

                this->handleOperand(num);
            }
        }
    }

    double answer = this->evaluateOperands();
    return answer;
}

void Calculator::initialize()
{
    this->operands = new std::stack<double>;
    this->currOp = ADDITION;
}

void Calculator::handleOperand(double operand)
{
    if (this->currOp == ADDITION)
    {
        this->operands->push(operand);
    }
    else if (this->currOp == SUBTRACTION)
    {
        this->operands->push(-1 * operand);
    }
    else if (this->currOp == MULTIPLICATION)
    {
        double lhs = this->operands->top();
        this->operands->pop();
        this->operands->push(lhs * operand);
    }
    else if (this->currOp == DIVISION)
    {
        // TODO: Handle division by zero more gracefully
        double lhs = this->operands->top();
        this->operands->pop();
        this->operands->push(lhs / operand);
    }

    this->currOp = ADDITION;
}

double Calculator::evaluateOperands()
{
    double retVal = 0.0;
    while (!this->operands->empty())
    {
        retVal += this->operands->top();
        this->operands->pop();
    }

    delete this->operands;
    this->operands = nullptr;

    return retVal;
}

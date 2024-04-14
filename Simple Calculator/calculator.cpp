#include "calculator.hpp"

Calculator::Calculator() : operands(nullptr), expressions(), currOp(ADDITION) {};

Calculator::~Calculator() {};

double Calculator::calculate(std::string s)
{
    this->operands = new std::stack<double>;
    Operator currOp = ADDITION;

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

            if (currOp == ADDITION)
            {
                this->operands->push(num);
            }
            else if (currOp == SUBTRACTION)
            {
                this->operands->push(-1 * num);
            }
            else if (currOp == MULTIPLICATION)
            {
                double lhs = this->operands->top();
                this->operands->pop();
                this->operands->push(lhs * num);
            }
            else if (currOp == DIVISION)
            {
                // TODO: Handle division by zero more gracefully
                double lhs = this->operands->top();
                this->operands->pop();
                this->operands->push(lhs / num);
            }

            currOp = ADDITION;
        }
        else
        {
            if (ch == '-')
            {
                currOp = SUBTRACTION;
            }
            else if (ch == '*')
            {
                currOp = MULTIPLICATION;
            }
            else if (ch == '/')
            {
                currOp = DIVISION;
            }
            else if (ch == '(')
            {
                this->expressions.push(std::make_pair(this->operands, currOp));
                this->operands = new std::stack<double>;
                currOp = ADDITION;
            }
            else if (ch == ')')
            {
                double num = 0.0;
                while (!this->operands->empty())
                {
                    num += this->operands->top();
                    this->operands->pop();
                }
                delete this->operands;

                this->operands = this->expressions.top().first;
                currOp = this->expressions.top().second;
                this->expressions.pop();

                if (currOp == ADDITION)
                {
                    this->operands->push(num);
                }
                else if (currOp == SUBTRACTION)
                {
                    this->operands->push(-1 * num);
                }
                else if (currOp == MULTIPLICATION)
                {
                    double lhs = this->operands->top();
                    this->operands->pop();
                    this->operands->push(lhs * num);
                }
                else if (currOp == DIVISION)
                {
                    // TODO: Handle division by zero more gracefully
                    double lhs = this->operands->top();
                    this->operands->pop();
                    this->operands->push(lhs / num);
                }

                currOp = ADDITION;
            }
        }
    }

    double answer = 0.0;
    while (!this->operands->empty())
    {
        answer += this->operands->top();
        this->operands->pop();
    }
    delete this->operands;

    return answer;
}

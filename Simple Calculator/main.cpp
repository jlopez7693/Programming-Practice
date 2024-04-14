#include <iostream>
#include <stack>

class Calculator {
public:
    double calculate(std::string s) {
        std::stack<double>* operandStack = new std::stack<double>;
        std::stack<std::pair<std::stack<double>*, Operation>> expressionStack;
        Operation currOp = ADDITION;
        
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            
            if (isdigit(ch)) {
                double num = 0;
                while (i < s.size() && isdigit(s[i])) {
                    num = (num * 10) + (s[i] - '0');
                    i++;
                }
                i--;
                
                if (currOp == ADDITION) {
                    operandStack->push(num);
                } else if (currOp == SUBTRACTION) {
                    operandStack->push(-1 * num);
                } else if (currOp == MULTIPLICATION) {
                    double lhs = operandStack->top();
                    operandStack->pop();
                    operandStack->push(lhs * num);
                } else if (currOp == DIVISION) {
                    // TODO: Handle division by zero more gracefully
                    double lhs = operandStack->top();
                    operandStack->pop();
                    operandStack->push(lhs / num);
                }
                
                currOp = ADDITION;
            } else {
                if (ch == '-') {
                    currOp = SUBTRACTION;
                } else if (ch == '*') {
                    currOp = MULTIPLICATION;
                } else if (ch == '/') {
                    currOp = DIVISION;
                } else if (ch == '(') {
                    expressionStack.push(std::make_pair(operandStack, currOp));
                    operandStack = new std::stack<double>;
                    currOp = ADDITION;
                } else if (ch == ')') {
                    double num = 0.0;
                    while (!operandStack->empty()) {
                        num += operandStack->top();
                        operandStack->pop();
                    }
                    delete operandStack;
                    
                    operandStack = expressionStack.top().first;
                    currOp = expressionStack.top().second;
                    expressionStack.pop();
                    
                    if (currOp == ADDITION) {
                        operandStack->push(num);
                    } else if (currOp == SUBTRACTION) {
                        operandStack->push(-1 * num);
                    } else if (currOp == MULTIPLICATION) {
                        double lhs = operandStack->top();
                        operandStack->pop();
                        operandStack->push(lhs * num);
                    } else if (currOp == DIVISION) {
                        // TODO: Handle division by zero more gracefully
                        double lhs = operandStack->top();
                        operandStack->pop();
                        operandStack->push(lhs / num);
                    }
                    
                    currOp = ADDITION;
                }
            }
        }
        
        double answer = 0.0;
        while (!operandStack->empty()) {
            answer += operandStack->top();
            operandStack->pop();
        }
        delete operandStack;
        
        return answer;
    }
    
private:
    enum Operation {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION
    };
};

int main(int argc, const char * argv[]) {
    std::string expression = "2 / (2 + 2)";
    std::cout << "The expression to calculate: " << expression << std::endl;
    
    double answer = Calculator().calculate(expression);
    std::cout << "The calculated result was " << answer << std::endl;
    
    return 0;
}

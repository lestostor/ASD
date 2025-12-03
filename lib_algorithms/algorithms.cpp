#include "algorithms.h"

Type check_circles(Circle first, Circle second) {
    float frad = first.get_radius(), srad = second.get_radius();
    Point fcentre(first.get_centre()), scentre(second.get_centre());
    float distance = fcentre.distance(scentre);

    if (frad + srad == distance)
        return Type::touch;
    else if (frad + srad < distance)
        return Type::not_touch;
    else if (distance < frad + srad && distance > abs(frad - srad))
        return intersect;
    else return inside;
}

Type check_spheres(Sphere first, Sphere second) {
    float frad = first.get_radius(), srad = second.get_radius();
    Point3D fcentre(first.get_centre()), scentre(second.get_centre());
    float distance = fcentre.distance(scentre);

    if (frad + srad == distance)
        return Type::touch;
    else if (frad + srad < distance)
        return Type::not_touch;
    else if (distance < frad + srad && distance > abs(frad - srad))
        return intersect;
    else return inside;
}

bool check_brackets(std::string str) {
    Stack<char> stack(str.size());
    
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') continue;
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
            stack.push(str[i]);
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (stack.is_empty()) return false;
            char bracket = stack.top();
            switch (bracket)
            {
            case '(':
                if (str[i] != ')') return false;
                break;
            case '[':
                if (str[i] != ']') return false;
                break;
            case '{':
                if (str[i] != '}') return false;
                break;
            default:
                return false;
                break;
            }
            stack.pop();
        }
        else return false;
    }
    return stack.is_empty();
}

std::string read_number(std::string str, int pos) {
    std::string number = "";
    for (int i = pos; i < str.size(); i++) {
        if (is_operation(str[i]) || is_letter(str[i]) ||
            is_closed_bracket(str[i]) || is_opened_bracket(str[i]) || str[i] == '|')
            return number;

        if (is_digit(str[i])) {
            number += str[i];
            continue;
        }

        if (str[i] != ' ' && !is_closed_bracket(str[i]))
            throw std::invalid_argument("Unexpected symbol: " + str[i]);
    }
    return number;
}

std::string read_variable(std::string str, int pos) {
    std::string variable = "";
    for (int i = pos; i < str.size(); i++) {
        if (is_operation(str[i]) || is_closed_bracket(str[i]) || str[i] == ' ' || str[i] == '|') break;
        if (is_letter(str[i]) || is_digit(str[i]) || str[i] == '_') {
            variable += str[i];
            continue;
        }

        if (str[i] != ' ' && !is_closed_bracket(str[i]) && str[i] != '|')
            throw std::invalid_argument("Unexpected symbol: " + str[i]);
    }
    return variable;
}

bool is_operation(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

bool is_digit(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool is_letter(char symbol) {
    return symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z';
}

bool is_opened_bracket(char symbol) {
    return symbol == '(' || symbol == '{' || symbol == '[';
}

bool is_closed_bracket(char symbol) {
    return symbol == ')' || symbol == '}' || symbol == ']';
}

bool is_function(std::string str) {
    return str == "sin" || str == "cos" || str == "tg";
}

void pop_operation(Stack<char>& operations, Stack<std::string>& operands) {
    if (operands.is_empty() && operations.top() != '-')
        return;  // missed operand
    operations.pop();
    if (!operands.is_empty())
        operands.pop();
}

void read_math_expression(std::string expression) {
    Stack<char> operations(2), brackets(expression.size());
    Stack<std::string> operands(2);
    int i = 0;

    while (i != expression.size()) {
        if (is_letter(expression[i])) {
            std::string str = read_variable(expression, i);

            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty())
                    throw std::logic_error("Operand was missed");
            }
            operands.push(expression);
            if (operands.is_full() || operations.is_full())
                throw std::logic_error("Operation was missed");

            i += str.size();
            continue;
        }
        else if (is_digit(expression[i])) {
            std::string num = read_number(expression, i);
            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty())
                    throw std::logic_error("Operand was missed");
            }
            operands.push(num);
            if (operands.is_full() || operations.is_full())
                throw std::logic_error("Operation was missed");

            i += num.size();
            continue;
        }
        else if (is_operation(expression[i])) {
            if (operations.is_full())
                throw std::logic_error("Extra operation");
            if (operands.is_empty() && expression[i] != '-')
                throw std::logic_error("Operand was missed");

            operations.push(expression[i]);
        }
        else if (is_opened_bracket(expression[i]) || expression[i] == '|' &&
            (brackets.is_empty() || !brackets.is_empty() && brackets.top() != '|')) {
            if (operations.is_empty() && i != 0 && !operands.is_empty() && !is_function(operands.top()))
                throw std::logic_error("Operation was missed");

            if (!operands.is_empty() && is_function(operands.top()))
                operands.pop();

            brackets.push(expression[i]);
            if (!operations.is_empty())
                pop_operation(operations, operands);
        }
        else if (is_closed_bracket(expression[i]) || expression[i] == '|') {
            if (brackets.is_empty())
                throw std::logic_error("Opened bracket was missed");
            brackets.pop();
        }

        i++;
    }

    if (!operations.is_empty())
        throw std::logic_error("Operand was missed");
    if (!brackets.is_empty())
        throw std::logic_error("Closed bracket was missed");
}

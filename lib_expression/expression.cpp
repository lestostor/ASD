#include "expression.h"

// Expression

Expression::Expression(std::string expression) {
    _lexems = Parser::parse(expression);
    toPolish();
}

Expression::Expression(const List<Lexem>& lexems) {
    _lexems = lexems;
    toPolish();
}

void Expression::toPolish() {
    Stack<Lexem> stack(_lexems.get_size());
    List<Lexem>::Iterator it = _lexems.begin();

    for (it; it != _lexems.end(); it++) {
        Lexem lexem = (*it);
        if (lexem._type == TypeLexem::OpenedBracket || lexem._type == TypeLexem::AbsOpened)
            stack.push(*it);
        else if (lexem._type == TypeLexem::ClosedBracket || lexem._type == TypeLexem::AbsClosed) {
            while (!stack.is_empty() && stack.top()._type != TypeLexem::OpenedBracket && stack.top()._type != TypeLexem::AbsOpened) {
                _PolishRecord.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
            if (lexem._type == TypeLexem::AbsClosed)
                _PolishRecord.push_back(lexem);
        }
        else if (lexem._type == TypeLexem::Operation || lexem._type == TypeLexem::Function|| lexem._type == TypeLexem::UnOperator) {
            while (!stack.is_empty()) {
                Lexem last = stack.top();

                if (last._type != TypeLexem::OpenedBracket &&
                    last._type != TypeLexem::AbsOpened &&
                    lexem._priority <= last._priority) {
                    stack.pop();
                    _PolishRecord.push_back(last);
                }
                else {
                    break;
                }
            }
            stack.push(lexem);
        }
        else if (lexem._type == TypeLexem::Constant || lexem._type == TypeLexem::Variable)
            _PolishRecord.push_back(lexem);
    }
    while (!stack.is_empty()) {
        _PolishRecord.push_back(stack.top());
        stack.pop();
    }
}

void Expression::set_variables(std::string var, double value) {
    List<Lexem>::Iterator it = _PolishRecord.begin();

    for (it; it != _lexems.end(); it++) {
        if ((*it)._name == var) {
            (*it)._value = value;
            return;
        }
    }
    throw std::invalid_argument("Variable " + var + " wasn't found");
}

double Expression::calculate() {
    Stack<double> values(_PolishRecord.get_size());

    List<Lexem>::Iterator it = _PolishRecord.begin();
    for (it; it != _PolishRecord.end(); it++) {
        Lexem lexem = *it;

        if (lexem._type == TypeLexem::Constant ||
            lexem._type == TypeLexem::Variable && lexem._value != DBL_MAX)
            values.push(lexem._value);
        else if (lexem._name == "+")
            add(values);
        else if (lexem._name == "-")
            sub(values);
        else if (lexem._name == "*")
            mul(values);
        else if (lexem._name == "/")
            div(values);
        else if (lexem._name == "^")
            power(values);
        else if (lexem._type == TypeLexem::UnOperator) {
            double val = -values.top();
            values.pop();
            values.push(val);
        }
        else if (lexem._type == TypeLexem::Function) {
            double val = lexem._function(values.top());
            values.pop();
            values.push(val);
        }
        else if (lexem._type == TypeLexem::AbsClosed) {
            double val = abs(values.top());
            values.pop();
            values.push(val);
        }
        else if (lexem._type == TypeLexem::Variable && lexem._value == DBL_MAX)
            throw std::logic_error("Values for variables are not specified");
    }

    return values.top();
}

void Expression::add(Stack<double>& values) {
    double second = values.top();
    values.pop();
    double first = values.top();
    values.pop();

    values.push(first + second);
}

void Expression::sub(Stack<double>& values) {
    double second = values.top();
    values.pop();
    double first = values.top();
    values.pop();

    values.push(first - second);
}

void Expression::mul(Stack<double>& values) {
    double second = values.top();
    values.pop();
    double first = values.top();
    values.pop();

    values.push(first * second);
}

void Expression::div(Stack<double>& values) {
    double second = values.top();
    values.pop();
    double first = values.top();
    values.pop();

    values.push(first / second);
}

void Expression::power(Stack<double>& values) {
    double second = values.top();
    values.pop();
    double first = values.top();
    values.pop();

    values.push(pow(first, second));
}

// Parser

std::string Parser::read_number(std::string str, int pos) {
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

std::string Parser::read_variable(std::string str, int pos) {
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

std::string Parser::read_function(std::string str, int pos) {
    std::string function = "";
    bool is_func = true;
    for (int i = pos; i < str.size(); i++) {
        if (is_operation(str[i]) || is_closed_bracket(str[i]) || str[i] == '|' || str[i] == '_' ||
            is_digit(str[i]) && function != "sin" && function != "cos" && function != "tg") {
            is_func = false;
            break;
        }
        if (is_opened_bracket(str[i]) || is_digit(str[i]) || str[i] == '|') break;
        if (is_letter(str[i])) {
            function += str[i];
            continue;
        }

        if (str[i] != ' ' && str[i] != '|' && !is_closed_bracket(str[i]))
            throw std::invalid_argument("Unexpected symbol: " + str[i]);
    }

    if (is_func) return function;
    return "";
}

bool Parser::is_operation(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

bool Parser::is_digit(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool Parser::is_letter(char symbol) {
    return symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z';
}

bool Parser::is_opened_bracket(char symbol) {
    return symbol == '(' || symbol == '{' || symbol == '[';
}

bool Parser::is_closed_bracket(char symbol) {
    return symbol == ')' || symbol == '}' || symbol == ']';
}

bool Parser::is_opened_bracket(std::string symbol) {
    return symbol == "(" || symbol == "{" || symbol == "[";
}

bool Parser::is_closed_bracket(std::string symbol) {
    return symbol == ")" || symbol == "}" || symbol == "]";
}

void Parser::pop_operation(Stack<char>& operations, Stack<std::string>& operands) {
    if (operands.is_empty() && operations.top() != '-')
        return;  // missed operand
    operations.pop();
    if (!operands.is_empty())
        operands.pop();
}

bool Parser::is_valid(std::string expression) {
    Stack<char> operations(2), brackets(expression.size());
    Stack<std::string> operands(2);
    int i = 0;

    while ( i != expression.size()) {
        if (is_letter(expression[i])) {
            std::string str = read_function(expression, i);

            if (str == "") str = read_variable(expression, i);
            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty()) return false;
            }
            operands.push(str);
            if (operands.is_full() || operations.is_full()) return false;  // missed operation

            i += str.size();
            continue;
        }
        else if (is_digit(expression[i])) {
            std::string num = read_number(expression, i);
            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty()) return false;
            }
            operands.push(num);
            if (operands.is_full() || operations.is_full()) return false;  // missed operation

            i += num.size();
            continue;
        }
        else if (is_operation(expression[i])) {
            if (operations.is_full() || operands.is_empty() && expression[i] != '-')
                return false;  // extra operation or missed operand
            operations.push(expression[i]);
        }
        else if (is_opened_bracket(expression[i]) || expression[i] == '|' &&
            (brackets.is_empty() || !brackets.is_empty() && brackets.top() != '|')) {
            if (operations.is_empty() && i != 0 &&
                operands.top() != "sin" && operands.top() != "cos" && operands.top() != "tg")
                return false;  // missed operation
            if (!operands.is_empty() && (operands.top() == "sin" || operands.top() == "cos" || operands.top() == "tg"))
                operands.pop();
            brackets.push(expression[i]);
            if (!operations.is_empty())
                pop_operation(operations, operands);
        }
        else if (is_closed_bracket(expression[i]) || expression[i] == '|') {
            if (brackets.is_empty()) return false;
            brackets.pop();
        }

        i++;
    }
    return operations.is_empty() && brackets.is_empty();
}

List<Lexem> Parser::parse(std::string expression) {
    if (!is_valid(expression))
        throw std::invalid_argument("Expression isn't correct");

    List<Lexem> lexems;
    int i = 0;
    bool abs_opened = false;

    while (i != expression.size()) {
        if (is_letter(expression[i])) {
            std::string str = read_function(expression, i);

            if (str == "") {
                str = read_variable(expression, i);
                Lexem var(str, TypeLexem::Variable);
                lexems.push_back(var);
            }
            else {
                if (str == "sin") {
                    Lexem func(str, TypeLexem::Function, DBL_MAX, 5, Functions::sin);
                    lexems.push_back(func);
                }
                else if (str == "cos") {
                    Lexem func(str, TypeLexem::Function, DBL_MAX, 5, Functions::cos);
                    lexems.push_back(func);
                }
                else if (str == "tg") {
                    Lexem func(str, TypeLexem::Function, DBL_MAX, 5, Functions::tg);
                    lexems.push_back(func);
                }
            }

            i += str.size();
            continue;
        }
        else if (is_digit(expression[i])) {
            std::string num = read_number(expression, i);
            Lexem number(num, TypeLexem::Constant, std::atoi(num.c_str()));
            lexems.push_back(number);

            i += num.size();
            continue;
        }
        else if (is_operation(expression[i])) {
            std::string str = std::string(1, expression[i]);
            int priority;
            if (expression[i] == '+')
                priority = 1;
            else if (expression[i] == '*' || expression[i] == '/')
                priority = 2;
            else if (expression[i] == '^')
                priority = 4;
            else if (expression[i] == '-' && (lexems.is_empty() ||
                lexems.tail()->_value._type == TypeLexem::OpenedBracket || lexems.tail()->_value._type == TypeLexem::AbsOpened)) {
                Lexem op("~", TypeLexem::UnOperator, DBL_MAX, 3);
                lexems.push_back(op);
                i++;
                continue;
            }
            else priority = 1;
            Lexem op(str, TypeLexem::Operation, DBL_MAX, priority);
            lexems.push_back(op);
        }
        else if (is_opened_bracket(expression[i])) {
            std::string str = std::string(1, expression[i]);
            Lexem bracket(str, TypeLexem::OpenedBracket, DBL_MAX, 6);
            lexems.push_back(bracket);
        }
        else if (is_closed_bracket(expression[i])) {
            abs_opened = false;
            std::string str = std::string(1, expression[i]);
            Lexem bracket(str, TypeLexem::ClosedBracket, DBL_MAX, 6);
            lexems.push_back(bracket);
        }
        else if (expression[i] == '|' && !abs_opened) {
            abs_opened = true;
            Lexem abs_bracket("|", TypeLexem::AbsOpened, DBL_MAX, 6);
            lexems.push_back(abs_bracket);
        }
        else if (expression[i] == '|' && abs_opened) {
            abs_opened = false;
            Lexem abs_bracket("|", TypeLexem::AbsClosed, DBL_MAX, 6);
            lexems.push_back(abs_bracket);
        }

        i++;
    }
    return lexems;
}

// Functions

double Functions::sin(double x) {
    int n = 0;
    double eps = 0.0001;

    double cur = x, s = 0.0;

    while (fabs(cur) > eps) {
        s += cur;
        n++;
        cur *= -x * x / (2 * n * (2 * n + 1));
    }

    return s;
}

double Functions::cos(double x) {
    int n = 0;
    double eps = 0.0001;

    double cur = 1, s = 0.0;

    do {
        s += cur;
        n++;
        cur *= -x * x / (2 * n * (2 * n - 1));
    } while (fabs(cur) > eps);

    return s;
}

double Functions::tg(double x) {
    double num = sin(x);
    double denum = cos(x);
    return num / denum;
}
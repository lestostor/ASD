#include "expression.h"

// Expression

Expression::Expression() {
    _lexems = List<Lexem>();
    _PolishRecord = List<Lexem>();
}

Expression::Expression(std::string expression) {
    _lexems = Parser::parse(expression);
    toPolish();
}

Expression::Expression(const List<Lexem>& lexems) {
    _lexems = lexems;
    toPolish();
}

Expression::Expression(const Expression& other) {
    this->_lexems = other._lexems;
    this->_PolishRecord = other._PolishRecord;
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

std::string Expression::toString() const {
    List<Lexem>::Iterator it = _lexems.begin();
    std::string str;

    for (it; it != _lexems.end(); it++)
        str += (*it)._name;
    return str;
}

List<Lexem> Expression::get_variables() const noexcept {
    List<Lexem>::Iterator it = _PolishRecord.begin();
    List<Lexem> variables;

    for (it; it != _PolishRecord.end(); it++) {
        Lexem lexem = *it;
        if (lexem._type == TypeLexem::Variable)
            variables.push_back(lexem);
    }

    return variables;
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
            is_digit(str[i]) && !is_function(function)) {
            is_func = false;
            break;
        }
        if (is_opened_bracket(str[i]) || is_digit(str[i]) || str[i] == '|') break;
        if (is_letter(str[i])) {
            function += str[i];
            if (!is_function(function) && i == str.size() - 1)
                return "";
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

bool Parser::is_function(std::string str) {
    return str == "sin" || str == "cos" || str == "tg";
}

void Parser::pop_operation(Stack<char>& operations, Stack<std::string>& operands) {
    if (operands.is_empty() && operations.top() != '-')
        return;  // missed operand
    operations.pop();
    if (!operands.is_empty())
        operands.pop();
}

int Parser::return_priority(char operation) {
    if (operation == '+' || operation == '-')
        return 1;
    else if (operation == '*' || operation == '/')
        return 2;
    else if (operation == '^')
        return 4;
}

List<Lexem> Parser::parse(std::string expression) {
    Stack<char> operations(2), brackets(expression.size());
    Stack<std::string> operands(2);
    int i = 0;

    List<Lexem> lexems;
    while ( i != expression.size()) {
        if (is_letter(expression[i])) {
            std::string str = read_function(expression, i);

            if (str == "sin")
                lexems.push_back(Lexem (str, TypeLexem::Function, DBL_MAX, 5, Functions::sin));
            else if (str == "cos")
                lexems.push_back(Lexem(str, TypeLexem::Function, DBL_MAX, 5, Functions::cos));
            else if (str == "tg")
                lexems.push_back(Lexem(str, TypeLexem::Function, DBL_MAX, 5, Functions::tg));
            else {
                str = read_variable(expression, i);
                lexems.push_back(Lexem(str, TypeLexem::Variable));
            }

            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty())
                    throw std::logic_error("Operand was missed\n" + show_error(expression, i));
            }
            operands.push(str);
            if (operands.is_full() || operations.is_full())
                throw std::logic_error("Operation was missed\n" + show_error(expression, i));

            i += str.size();
            continue;
        }
        else if (is_digit(expression[i])) {
            std::string num = read_number(expression, i);
            if (!operations.is_empty()) {
                pop_operation(operations, operands);
                if (!operands.is_empty())
                    throw std::logic_error("Operand was missed\n" + show_error(expression, i));
            }
            operands.push(num);
            if (operands.is_full() || operations.is_full())
                throw std::logic_error("Operation was missed\n" + show_error(expression, i));

            lexems.push_back(Lexem (num, TypeLexem::Constant, std::atoi(num.c_str())));

            i += num.size();
            continue;
        }
        else if (is_operation(expression[i])) {
            if (operations.is_full())
                throw std::logic_error("Extra operation\n" + show_error(expression, i));
            if (operands.is_empty() && expression[i] != '-')
                throw std::logic_error("Operand was missed\n" + show_error(expression, i));

            operations.push(expression[i]);

            if (expression[i] == '-' && (lexems.is_empty() || lexems.tail()->_value._type == TypeLexem::OpenedBracket ||
                lexems.tail()->_value._type == TypeLexem::AbsOpened))
                lexems.push_back(Lexem("~", TypeLexem::UnOperator, DBL_MAX, 3));
            else
                lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::Operation, DBL_MAX, return_priority(expression[i])));
        }
        else if (is_opened_bracket(expression[i]) || expression[i] == '|' &&
            (brackets.is_empty() || !brackets.is_empty() && brackets.top() != '|')) {
            if (operations.is_empty() && i != 0 && !operands.is_empty() && !is_function(operands.top()))
                throw std::logic_error("Operation was missed\n" + show_error(expression, i));

            if (!operands.is_empty() && is_function(operands.top()))
                operands.pop();

            brackets.push(expression[i]);
            if (!operations.is_empty())
                pop_operation(operations, operands);

            if (expression[i] != '|')
                lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::OpenedBracket, DBL_MAX, 6));
            else lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::AbsOpened, DBL_MAX, 6));
        }
        else if (is_closed_bracket(expression[i]) || expression[i] == '|') {
            if (brackets.is_empty())
                throw std::logic_error("Opened bracket was missed\n" + show_error(expression, i));
            brackets.pop();
            if (expression[i] != '|')
                lexems.push_back(Lexem (std::string(1, expression[i]), TypeLexem::ClosedBracket, DBL_MAX, 6));
            else lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::AbsClosed, DBL_MAX, 6));
        }

        i++;
    }

    if (!operations.is_empty())
        throw std::logic_error("Operand was missed\n" + show_error(expression, i));
    if (!brackets.is_empty())
        throw std::logic_error("Closed bracket was missed\n" + show_error(expression, i));

    return lexems;
}

std::string Parser::show_error(std::string expression, int pos) {
    std::string error_msg = expression + "\n";

    for (int i = 0; i <= expression.size(); i++) {
        if (i == pos) error_msg += "^";
        else error_msg += " ";
    }

    return error_msg;
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
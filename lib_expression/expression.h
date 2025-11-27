#ifndef EXPRESSION_EXPRESSION_H
#define EXPRESSION_EXPRESSION_H

#include "../lib_list/list.h"
#include "../lib_stack/stack.h"
#include <string>

enum TypeLexem { Constant, Variable, OpenedBracket, ClosedBracket, Function, Operation, UnOperator, AbsOpened, AbsClosed };

struct Lexem {
    std::string _name;
    TypeLexem _type;
    double _value;
    int _priority;
    double (*_function)(double);
    Lexem() {
        _name = "";
        _type = TypeLexem::Constant;
    }
    Lexem(std::string name, TypeLexem type, double value = DBL_MAX, int priority = -1, double(*function)(double) = nullptr) {
        _name = name;
        _type = type;
        _value = value;
        _priority = priority;
        _function = function;
    }
};

class Expression {
    List<Lexem> _lexems;
    List<Lexem> _PolishRecord;

public:
    Expression(std::string);
    Expression(const List<Lexem>&);

    void set_variables(std::string, double);
    double calculate();

private:
    void toPolish();

    void add(Stack<double>&);
    void sub(Stack<double>&);
    void mul(Stack<double>&);
    void div(Stack<double>&);
    void power(Stack<double>&);
};

namespace Parser {
    List<Lexem> parse(std::string);

    bool is_valid(std::string);

    std::string read_number(std::string, int);
    std::string read_variable(std::string, int);
    std::string read_function(std::string, int);

    bool is_operation(char);
    bool is_digit(char);
    bool is_letter(char);
    bool is_opened_bracket(char);
    bool is_closed_bracket(char);
    bool is_opened_bracket(std::string);
    bool is_closed_bracket(std::string);

    void pop_operation(Stack<char>&, Stack<std::string>&);
};

namespace Functions {
    double sin(double);

    double cos(double);

    double tg(double);
};

#endif // !EXPRESSION_EXPRESSION_H

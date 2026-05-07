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

Matrix<bool> create_labyrinth(int m, int n, int enter, int exit) {
    DSU labyrinth(m * n);
    Matrix<bool> walls(2 * m + 1, 2 * n + 1);
    srand(time(0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int num = i * n + j;
            int right_wall = rand() % 100;
            int down_wall = rand() % 100;

            if (num == enter || num == exit) {
                if (i == 0 && 2 * j + 1 < walls.get_columns())
                    walls[0][2 * j + 1] = false;  // up
                else if (j == 0 && 2 * i + 1 < walls.get_lines())
                    walls[2 * i + 1][0] = false;  // left
                else if (j == n - 1 && 2 * i + 1 < walls.get_lines() && 2 * j + 2 < walls.get_columns())
                    walls[2 * i + 1][2 * j + 2] = false;  // right
                else if (2 * i + 2 < walls.get_lines() && 2 * j + 1 < walls.get_columns())
                    walls[walls.get_lines() - 1][2 * j + 1] = false;  // down
            }

            if (right_wall >= 50 && j + 1 != n) {
                labyrinth.unite(num, num + 1);
                walls[2 * i + 1][2 * j + 2] = false;
            }
            if (down_wall >= 50 && i + 1 != m) {
                labyrinth.unite(num, num + n);
                walls[2 * i + 2][2 * j + 1] = false;
            }
        }
    }

    int curr = enter;
    while (labyrinth.find(curr) != labyrinth.find(exit)) {
        int enter_i = curr / n, enter_j = curr % n,
            exit_i = exit / n, exit_j = exit % n;

        if (enter_i < exit_i) {
            labyrinth.unite(curr, curr + n);
            walls[2 * enter_i + 2][2 * enter_j + 1] = false;
            curr += n;
        }
        else if (enter_i > exit_i) {
            labyrinth.unite(curr, curr - n);
            walls[2 * enter_i][2 * enter_j + 1] = false;
            curr -= n;
        }
        else if (enter_j < exit_j) {
            labyrinth.unite(curr, curr + 1);
            walls[2 * enter_i + 1][2 * enter_j + 2] = false;
            curr += 1;
        }
        else if (enter_j > exit_j) {
            labyrinth.unite(curr, curr - 1);
            walls[2 * enter_i + 1][2 * enter_j] = false;
            curr -= 1;
        }
    }

    return walls;
}

void print(Matrix<bool>& labyrinth, std::vector<Vertex<int>*> way) {
    int lines = labyrinth.get_lines(), cols = labyrinth.get_columns();

    int num = 0;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 == 0 && j % 2 == 0)
                std::cout << "+";
            else if (labyrinth[i][j] && i % 2 == 0 && j % 2 != 0)
                std::cout << "-";
            else if (labyrinth[i][j] && i % 2 != 0 && j % 2 == 0)
                std::cout << "|";
            else if (labyrinth[i][j] && i % 2 != 0 && j % 2 != 0) {
                bool is_found = false;
                for (int k = 0; k < way.size(); k++) {
                    if (num == way[k]->_value) {
                        std::cout << "*";
                        is_found = true;
                        break;
                    }
                }

                if (!is_found)
                    std::cout << " ";
                num++;
            }
            else std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void print_way(Matrix<bool>& labyrinth, int enter, int exit) {
    int m = (labyrinth.get_lines() - 1) / 2, n = (labyrinth.get_columns() - 1) / 2;
    std::vector<std::pair<int, int>> edges;
    ListGraph<int> graph(edges);

    // create graph
    for (int i = 0; i < m * n; i++) {
        if ((i + 1) % n != 0)
            graph.add_edge(i, i + 1);
        if (i + n < m * n)
            graph.add_edge(i, i + n);
    }

    int num = 0;
    for (int i = 1; i < labyrinth.get_lines(); i += 2) {
        for (int j = 1; j < labyrinth.get_columns(); j += 2, num++) {
            if ((num + 1) % n != 0 && labyrinth[i][j + 1])
                graph.delete_edge(num, num + 1);
            if (num + n < m * n && labyrinth[i + 1][j])
                graph.delete_edge(num, num + n);
        }
    }

    std::vector<Vertex<int>*> way = find_min_way(graph, enter, exit);

    print(labyrinth, way);
}

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
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
            stack.push(str[i]);
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (stack.is_empty()) return false;
            stack.pop();
        }
    }
    if (stack.is_empty()) return true;
    else return false;
}

bool check_math_expression(std::string str) {
    Stack<char> operations(str.size());
    Stack<char> variables(2);
    Stack<std::string> numbers(2);
    if (!check_brackets(str)) return false;

    std::string num = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            num += str[i];
            if (!operations.is_empty())
                operations.pop();
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
            variables.push(str[i]);
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
            str[i] == '^' || str[i] == ' ' || str[i] == '(' || str[i] == ')') {
            if (num != "") {
                numbers.push(num);
                num = "";
            }
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
                operations.push(str[i]);
        }
    }
    return operations.is_empty() && !variables.is_full() && !numbers.is_full();
}

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

bool check_math_expression(std::string str) {
    Stack<char> operations(str.size());
    Stack<char> variables(2);
    Stack<char> brackets(str.size());
    Stack<std::string> numbers(2);

    std::string num = "";
    for (int i = 0; i < str.size(); i++) {
        if ((numbers.is_full() || variables.is_full() ||
            num != "" && !variables.is_empty() && !variables.is_full()))  // check if operaion was missed
            return false;

        if (str[i] >= '0' && str[i] <= '9') {
            num += str[i];
            if (!operations.is_empty()) {
                operations.pop();
                if (!variables.is_empty() && !variables.is_full())
                    variables.pop();
            }
        }
        else if (str[i] >= 'a' && str[i] <= 'z') {
            if (!operations.is_empty()) {
                operations.pop();
                if (!variables.is_empty() && !variables.is_full())
                    variables.pop();
                if (!numbers.is_empty() && !numbers.is_full())
                    numbers.pop();
            }
            variables.push(str[i]);
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
            operations.push(str[i]);
            if (!numbers.is_empty() && !numbers.is_full() && num != "")  // one number in stack
                numbers.pop();

            if (num != "") {
                numbers.push(num);
                num = "";
            }
            if (numbers.is_empty() && variables.is_empty() && str[i] != '-') 
                return false;  // check if first argument was missed

            if (!variables.is_empty() && !variables.is_full())  // one var in stack
                variables.pop();
        }
        else if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            if (num != "" || operations.is_empty() && i != 0) return false;  // check if missed operation
            brackets.push(str[i]);
            if (!operations.is_empty())
                operations.pop();
            if (!numbers.is_empty() && !numbers.is_full())
                numbers.pop();
        }
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (brackets.is_empty()) return false;
            brackets.pop();
            if (num != "") {
                if (!numbers.is_empty() && !numbers.is_full())
                    numbers.pop();
                numbers.push(num);
                num = "";
            }
        }
    }
    return operations.is_empty() &&brackets.is_empty();
}

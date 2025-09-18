// Copyright 2024 Marina Usova

//#define EASY_EXAMPLE
//#define CHECK_CIRCLES
#define MATRIX_APP
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE


#ifdef CHECK_CIRCLES
#include <iostream>
#include "circle.h"

enum Type { intersect, touch, inside, not_touch };

template <class T>
Type check_circles(T first, T second) {
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

void print_result(Type result) {
    if (result == Type::intersect)
        std::cout << "intersect" << std::endl;
    else if (result == Type::touch)
        std::cout << "touch" << std::endl;
    else if (result == Type::inside)
        std::cout << "inside" << std::endl;
    else if (result == Type::not_touch)
        std::cout << "not_touch" << std::endl;
}

int main() {
    Circle circle1(0, 0, 2), circle2(0, 0, 3);
    Type result = check_circles(circle1, circle2);
    print_result(result);

    Circle circle3(-1, -1, 1), circle4(2, 2, 1);
    result = check_circles(circle3, circle4);
    print_result(result);

    Circle circle5(0, 0, 1), circle6(0, 2, 1);
    result = check_circles(circle5, circle6);
    print_result(result);

    Circle circle7(0, 0, 1), circle8(0, 1, 1);
    result = check_circles(circle7, circle8);
    print_result(result);

    return 0;
}

#endif

#ifdef MATRIX_APP

#include "trianglematrix.h"
#include <cstdlib>

#define DEBUG

void print_main_menu() {
    std::cout << "                                          Matrix application                                          " << std::endl;
    std::cout << "1) Create matrix" << std::endl;
    std::cout << "2) Matrix operation" << std::endl;
    std::cout << "3) Exit" << std::endl;
}

void print_matrix_operation_menu() {
    std::cout << "1) Add" << std::endl;
    std::cout << "2) Sub" << std::endl;
    std::cout << "3) Mul" << std::endl;
    std::cout << "4) Div" << std::endl;
    std::cout << "5) transpose" << std::endl;
    std::cout << "6) Back" << std::endl;
}

template <class T>
void print_matrix(T matrix, char matrix_name) {
    std::cout << "Matrix " << matrix_name << std::endl;
    std::cout << matrix;
}

template <class T>
Matrix<T> create_matrix() {
    int m, n;

    while (true) {
        std::cout << "Enter quantity of lines: ";
        std::cin >> m;
        if (m <= 1)
            std::cout << "Enter number >= 2: " << std::endl;
        else break;
    }

    while (true) {
        std::cout << "Enter quantity of columns: ";
        std::cin >> n;
        if (n <= 1)
            std::cout << "Enter number >= 2: " << std::endl;
        else break;
    }

    Matrix<T> matrix(m, n);
    std::cout << "Enter matrix " << m << "x" << n << ":" << std::endl;
    std::cin >> matrix;
#ifdef DEBUG
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> matrix[i][j];
#endif // DEBUG
    return matrix;
}

template <class T>
Matrix<T> create_triangle_matrix() {
    int  n;

    while (true) {
        std::cout << "Enter size of matrix: ";
        std::cin >> n;
        if (n <= 1)
            std::cout << "Enter number >= 2: " << std::endl;
        else break;
    }

    TriangleMatrix<T> matrix(n);
    std::cout << "Enter matrix " << n << "x" << n << ":" << std::endl;
    std::cin >> matrix;
#ifdef DEBUG
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            std::cin >> matrix[i][j];  // ввод без нулей
#endif // DEBUG
    return matrix;
}

int choose_action(int count, std::string text) {
    while (true) {
        int action;
        std::cout << text;
        std::cin >> action;

        if (action >= 1 && action <= count) return action;
        else std::cout << "Uncorrect enter" << std::endl;
    }
}

int main() {
    Matrix<int> matrix_a, matrix_b, matrix_c;
    int count = 0, type_matrix, operation;
    while (true) {
        //system("cls");
        if (count >= 1) {
            print_matrix(matrix_a, 'A');
            if (count > 1)
                print_matrix(matrix_b, 'B');
        }

        print_main_menu();
        int action = choose_action(3, "Choose action: ");
        system("cls");

        switch (action) {
        case 1:
            std::cout << "1) Standart" << std::endl;
            std::cout << "2) Triangle" << std::endl;
            std::cout << "3) Back" << std::endl;
            type_matrix = choose_action(3, "Choose type of matrix: ");

            if (type_matrix == 1 && count == 0)
                matrix_a = create_matrix<int>();
            else if (type_matrix == 1 && count == 1)
                matrix_b = create_matrix<int>();
            if (type_matrix == 2 && count == 0)
                matrix_a = create_triangle_matrix<int>();
            else if (type_matrix == 2 && count == 1)
                matrix_b = create_triangle_matrix<int>();
            else if (type_matrix == 3) {
                system("cls");
                break;
            }

            system("cls");
            count++;
            break;
        case 2:
            if (count == 0) {
                std::cout << "No matrix" << std::endl;
                break;
            }
            print_matrix_operation_menu();

            operation = choose_action(6, "Choose operation: ");
            if (operation >= 1 && operation <= 4) {  //operations +, -, *, /
                if (count == 1) {
                    system("cls");
                    std::cout << "Needs 2 matrixes. You have 1 matrix" << std::endl;
                    break;
                }
                switch (operation) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                }
            }
            else if (operation == 5) {  // transpose
                system("cls");
                break;
            }
            break;
        case 3:
            return 0;
        }
    }
}

#endif // !MATRIX_APP

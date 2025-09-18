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
    std::cout << "2) Matrix operations" << std::endl;
    std::cout << "3) Output" << std::endl;
    std::cout << "4) Exit" << std::endl;
}

void print_matrix_operation_menu() {
    std::cout << "1) Add" << std::endl;
    std::cout << "2) Subtract" << std::endl;
    std::cout << "3) Multiply" << std::endl;
    std::cout << "4) Transpose" << std::endl;
    std::cout << "5) Back" << std::endl;
}

void print_matrix_mul_menu() {
    std::cout << "1) A matrix by a matrix" << std::endl;
    std::cout << "2) A matrix by a number" << std::endl;
    std::cout << "3) Back" << std::endl;
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
TriangleMatrix<T> create_triangle_matrix() {
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
            std::cin >> matrix[i][j];  // enter without 0
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

char choose_matrix(int count) {
    char name = 'A';
    if (count >= 2)
        while (true) {
            std::cout << "Enter name of matrix: ";
            std::cin >> name;
            if (name == 'B' && count >= 2 || name == 'C' && count == 3)
                break;
            std::cout << "No matrix with this name" << std::endl;
        }
    return name;
}

int main() {
    Matrix<int> matrix_a, matrix_b, matrix_c;
    TriangleMatrix<int> tmatrix_a, tmatrix_b, tmatrix_c;
    int count = 0, type_matrix = 0, operation;
    char name;
    while (true) {

        print_main_menu();
        int action = choose_action(4, "Choose action: ");
        system("cls");

        switch (action) {
        case 1:
            if (type_matrix == 0) {
                std::cout << "1) Standart" << std::endl;
                std::cout << "2) Triangle" << std::endl;
                std::cout << "3) Back" << std::endl;
                type_matrix = choose_action(3, "Choose type of matrix: ");
            }

            if (type_matrix == 1 && count == 0)
                matrix_a = create_matrix<int>();
            else if (type_matrix == 1 && count == 1)
                matrix_b = create_matrix<int>();
            if (type_matrix == 2 && count == 0)
                tmatrix_a = create_triangle_matrix<int>();
            else if (type_matrix == 2 && count == 1)
                tmatrix_b = create_triangle_matrix<int>();
            else if (type_matrix == 3) {
                system("cls");
                break;
            }

            system("cls");
            std::cout << "Matrix created" << std::endl;
            count++;
            break;
        case 2:
            if (count == 0) {
                std::cout << "No matrix" << std::endl;
                break;
            }

            print_matrix_operation_menu();
            operation = choose_action(5, "Choose operation: ");
            system("cls");

            if (operation == 1 || operation == 2) {  //operations +, -
                if (count == 1) {
                    system("cls");
                    std::cout << "Needs 2 matrixes. You have 1 matrix" << std::endl;
                    break;
                }

                switch (operation) {
                case 1:
                    if (type_matrix == 1)
                        matrix_c = matrix_a + matrix_b;
                    else tmatrix_c = tmatrix_a + tmatrix_b;
                    system("cls");
                    std::cout << "Matrixes was added" << std::endl;
                    break;
                case 2:
                    std::cout << "1) A-B" << std::endl;
                    std::cout << "2) B-A" << std::endl;
                    std::cout << "3) Back" << std::endl;
                    operation = choose_action(3, "Choose operation: ");

                    if (type_matrix == 1 && operation == 1)
                        matrix_c = matrix_a - matrix_b;
                    else if (type_matrix == 2 && operation == 1)
                        tmatrix_c = tmatrix_a - tmatrix_b;
                    else if (type_matrix == 1 && operation == 2)
                        matrix_c = matrix_b - matrix_a;
                    else if (type_matrix == 2 && operation == 2)
                        tmatrix_c = tmatrix_b - tmatrix_a;
                    else {
                        system("cls");
                        break;
                    }
                    system("cls");
                    std::cout << "Matrixes was subtracted" << std::endl;
                    break;
                }
                count++;
                break;
            }
            else if (operation == 3) {  // operation *
                print_matrix_mul_menu();
                operation = choose_action(3, "Choose operation: ");
                system("cls");

                if (operation == 1 && count == 2) {
                    if (type_matrix == 1) {
                        std::cout << "1) A*B" << std::endl;
                        std::cout << "2) B*A" << std::endl;
                        std::cout << "3) Back" << std::endl;
                        operation = choose_action(3, "Choose operation: ");

                        if (operation == 1)
                            matrix_c = matrix_a * matrix_b;
                        else if (operation == 2)
                            matrix_c = matrix_b * matrix_a;
                    }
                    else tmatrix_c = tmatrix_a * tmatrix_b;
                    count++;
                    system("cls");
                    std::cout << "Matrixes was multiplied" << std::endl;
                }
                else if (operation == 1 && count == 1) {
                    system("cls");
                    std::cout << "Needs 2 matrixes. You have 1 matrix" << std::endl;
                    break;
                }
                else if (operation == 2) {  // mul matrix by a number
                    system("cls");
                    int num;
                    std::cout << "Enter number: ";
                    std::cin >> num;

                    name = choose_matrix(count);
                    if (name == 'A' && type_matrix == 1) matrix_a = matrix_a * num;
                    else if (name == 'A' && type_matrix == 2) tmatrix_a = tmatrix_a * num;
                    else if (name == 'B' && type_matrix == 1) matrix_b = matrix_b * num;
                    else if (name == 'B' && type_matrix == 2) tmatrix_b = tmatrix_b * num;
                    else if (name == 'C' && type_matrix == 1) matrix_c = matrix_c * num;
                    else if (name == 'C' && type_matrix == 2) tmatrix_c = tmatrix_c * num;
                    system("cls");
                    std::cout << "Matrix was multiplied" << std::endl;
                }
            }
            else if (operation == 4) {
                name = choose_matrix(count);
                if (name == 'A' && type_matrix == 1) matrix_a.transpose();
                else if (name == 'A' && type_matrix == 2) tmatrix_a.transpose();
                else if (name == 'B' && type_matrix == 1) matrix_b.transpose();
                else if (name == 'B' && type_matrix == 2) tmatrix_b.transpose();
                else if (name == 'C' && type_matrix == 1) matrix_c.transpose();
                else if (name == 'C' && type_matrix == 2) tmatrix_c.transpose();
                system("cls");
                std::cout << "Matrix was transposted" << std::endl;
            }
            break;
        case 3:
            if (count == 0) {
                system("cls");
                std::cout << "No matrix" << std::endl;
                break;
            }

            name = choose_matrix(count);
            if (name == 'A' && type_matrix == 1)
                print_matrix(matrix_a, name);
            else if (name == 'A' && type_matrix == 2)
                print_matrix(tmatrix_a, name);
            else if (name == 'B' && type_matrix == 1)
                print_matrix(matrix_b, name);
            else if (name == 'B' && type_matrix == 2)
                print_matrix(tmatrix_b, name);
            else if (name == 'C' && type_matrix == 1)
                print_matrix(matrix_c, name);
            else if (name == 'C' && type_matrix == 2)
                print_matrix(tmatrix_c, name);
            break;
        case 4:
            return 0;
        }
    }
}

#endif // !MATRIX_APP

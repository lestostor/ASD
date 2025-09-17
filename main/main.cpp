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

#include "matrix.h"
#include <cstdlib>

void print_main_menu() {
    std::cout << "                                          Matrix application                                          " << std::endl;
    std::cout << "1) Create matrix" << std::endl;
    std::cout << "2) Matrix operation" << std::endl;
    std::cout << "3) Exit" << std::endl;
}

template <class T>
void print_matrix(Matrix<T> matrix, char matrix_name) {

    std::cout << "Matrix " << matrix_name << std::endl;
    //std::cout << matrix;
}


template <class T>
Matrix<T> create_matrix() {
    int m, n;

    std::cout << "Enter quantity of lines: ";
    std::cin >> m;

    std::cout << "Enter quantity of columns: ";
    std::cin >> n;

    Matrix<T> matrix(m, n);

    return matrix;
}

int choose_action(int count) {

    while (true) {
        int action;
        std::cout << "Choose action: ";
        std::cin >> action;

        if (action >= 1 && action <= count) return action;
        else std::cout << "Uncorrect enter" << std::endl;
    }
}

enum Type {Standart, Triangle};
int main() {
    int count = 0;
    Type type;
    Matrix<int> matrix_a, matrix_b;
    while (true) {
        system("cls");
        if (count >= 1) {
            print_matrix(matrix_a, 'A');
            if (count > 1)
                print_matrix(matrix_b, 'B');
        }
        
        print_main_menu();
        int action = choose_action(3);
        system("cls");

        switch(action) {
        case 1:
            if (count == 0) {
                std::cout << "1) Standart" << std::endl;
                std::cout << "2) Triangle" << std::endl;

                while (true) {
                    int type_matrix;
                    std::cout << "Choose type of matrix: ";
                    std::cin >> type_matrix;

                    if (type_matrix == 1) {
                        type = Type::Standart;
                        break;
                    }
                    else if (type_matrix == 2) {
                        type = Type::Triangle;
                        break;
                    }
                    else std::cout << "Uncorrect enter" << std::endl;
                }
            }
                matrix_a = create_matrix<int>();
            count++;
            break;
        case 2:

            break;
        }
    }

    return 0;
}

#endif // !MATRIX_APP

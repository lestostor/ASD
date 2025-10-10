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

int find_local_min(Matrix<int> matrix) {
    srand(time(0));
    int n = matrix.get_lines(), i = rand() % n, j = rand() % n, current = matrix[i][j], minimum;

    while (true) {
        minimum = min(matrix, &i, &j);
        if (minimum != current) {
            current = minimum;
        }
        else break;
    }
    return minimum;
}

int min(Matrix<int> matrix, int* i, int* j) {
    int min = matrix[*i][*j];
    if (*i - 1 >= 0 && matrix[*i - 1][*j] < min) {
        min = matrix[*i - 1][*j];
        (*i)--;
    }
    if (*j - 1 >= 0 && matrix[*i][*j - 1] < min) {
        min = matrix[*i][*j - 1];
        (*j)--;
    }
    if (*i + 1 < matrix.get_lines() && matrix[*i + 1][*j] < min) {
        min = matrix[*i + 1][*j];
        (*i)++;
    }
    if (*j + 1 < matrix.size() && matrix[*i][*j + 1] < min) {
        min = matrix[*i][*j + 1];
        (*j)++;
    }
    return min;
}

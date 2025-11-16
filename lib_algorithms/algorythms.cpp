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

void unite_neighbours(DSU& dsu, const Matrix<int> matrix, const int line, const int col) {
    int m = matrix.get_lines(), n = matrix.get_columns();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (abs(i) == abs(j)) continue;

            if (line + i >= 0 && line + i < m &&
                col + j >= 0 && col + j < n &&
                matrix[line + i][col + j] == 1)
                dsu.unite(line * m + col % n,(line + i) * m + (col + j) % n);
        }
    }
}

int count_islands(Matrix<int> matrix) {
    int m = matrix.get_lines(), n = matrix.get_columns(),
        count = 0;
    DSU dsu(m * n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                matrix[i][j] = -1;
                unite_neighbours(dsu, matrix, i, j);
            }
        }
    }

    // count
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1 && dsu.find(i * m + j % n) == i * m + j % n)
                count++;
        }
    }
    return count;
}

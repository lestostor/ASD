#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_matrix/matrix.h"
#include "../lib_dsu/dsu.h"
#include <cstdlib>
#include <ctime>
#include <climits>

enum Type { intersect, touch, inside, not_touch };

Type check_circles(Circle, Circle);

Type check_spheres(Sphere, Sphere);

int find_local_min(Matrix<int>);

int min(Matrix<int>, int*, int*);

int count_islands(Matrix<int>);

void unite_neighbours(DSU&, const Matrix<int>, const int, const int);
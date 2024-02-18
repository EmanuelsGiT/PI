#include "utils.hpp"
#include <valarray>

#ifdef __unix__
#include <unistd.h>
#define getDir getcwd
static const std::string slash = "/";
#else
#include <direct.h>
#define getDir _getcwd
static const std::string slash = "\\";
#endif

using namespace utils;
using namespace matrix;

// cria um ponto com as dadas coordenadas, e adiciona-o à lista de pontos da figura
void figure::addPoint(float a, float b, float c) {
    point p;
    p.x = a;
    p.y = b;
    p.z = c;
    pontos.push_back(p);
}

void figure::addNormalPoint(float a, float b, float c) {
    point p;
    p.x = a;
    p.y = b;
    p.z = c;
    normal.push_back(p);
}

void figure::addTexPoint(float a, float b, float c) {
    point p;
    p.x = a;
    p.y = b;
    p.z = c;
    texCoord.push_back(p);
}

point normalizeVector(float x, float y, float z) {
    point vector;
    float l = sqrt(x * x + y * y + z * z);
    vector.x = x / l;
    vector.y = y / l;
    vector.z = z / l;
    return vector;
}

void matrix::multMatrixVector(float* m, float* v, float* res){
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void matrix::buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void matrix::cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void matrix::normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}
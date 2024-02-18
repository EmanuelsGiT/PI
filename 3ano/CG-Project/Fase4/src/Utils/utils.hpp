#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <stdio.h>
#include <stdlib.h>
#include <cstring>

namespace utils
{
    struct point 
    {
        float x;
        float y;
        float z;
    };

    class figure 
    {

    public:
        std::vector<point> pontos;
        std::vector<int> indices;
        std::vector<point> normal;
        std::vector<point> texCoord;
        void addPoint(float, float, float);
        void addNormalPoint(float, float, float);
        void addTexPoint(float, float, float);
        utils::point normalizeVector(float , float, float);
    };
}

namespace matrix
{
    void multMatrixVector(float*, float*, float*);
    void buildRotMatrix(float*, float*, float*, float*);
    void cross(float *, float *, float *);
    void normalize(float *);
}

#endif
#ifndef FASE3_BEZIER_HPP
#define FASE3_BEZIER_HPP

#include "../Utils/utils.hpp"

using namespace utils;

namespace bezier{
    void getBezierPoint(float, float, float**, float**, float**, float*);
    figure generateBezierPatches(figure, std::vector<size_t>, int);
}

#endif
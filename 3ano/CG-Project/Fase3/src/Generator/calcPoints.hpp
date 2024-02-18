#include "../Utils/utils.hpp"

using namespace utils;

namespace generate
{
    figure calcPlane(float, float);
    figure calcBox(float, float);
    figure calcSphere(float, int, int);
    figure calcCone(float, float, int, int);
    figure calcTorus(float, float, int, int);
}

namespace bezier
{
    void getBezierPoint(float, float, float**, float**, float**, float*);
    figure generateBezierPatches(figure, std::vector<size_t>, int);
}

#include "../Utils/utils.hpp"
#include <map>
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

namespace draw {

    void drawFigure(utils::figure);

}

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class World {
    private:
        float Window_width = 0;
        float Window_height = 0;

        float Camera_position[3];
        float Camera_lookAt[3];
        float Camera_up[3];
        float Camera_projection[3];

        map<int,figure> Group_models;
        

    public:
        World(int w, int h,
              float pos[3], float look[3], float up[3], float proj[3],
              map<int,figure> models) {
            this->Window_width = w;
            this->Window_height = h;
            for(int i = 0; i < 3; i++) {
                this->Camera_position[i] = pos[i];
                this->Camera_lookAt[i] = look[i];
                this->Camera_up[i] = up[i];
                this->Camera_projection[i] = proj[i];
            }
            this->Group_models = models;
        }

        World() {};

    int getWindowWidth() const { return Window_width; }
    int getWindowHeight() const { return Window_height; }

    const float* getCameraPosition() const { return Camera_position; }
    const float* getCameraLookAt() const { return Camera_lookAt; }
    const float* getCameraUp() const { return Camera_up; }
    const float* getCameraProjection() const { return Camera_projection; }

    void setCameraPosition(float pos[3]) {
        for(int i = 0; i < 3; i++) {
            this->Camera_position[i] = pos[i];
        }
    }

    const map<int,figure>& getGroupModels() const { return Group_models; }
       
};



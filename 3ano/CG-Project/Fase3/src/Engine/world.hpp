#include "../Utils/utils.hpp"
#include <map>
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



namespace transformations {
    
    enum class trans_type {none, translate, rotate, scale, rotate_time, translate_time, color};

    class Transform {
        private:
            trans_type type;
            bool align;
            float angle;
            int time;
            float coords[3];
            std::vector<utils::point> points;
            std::vector<utils::point> curvePoints;

        public:
            Transform() {};
            void setTransform(float[], float, trans_type);
            void setTranslateTime(int, bool, std::vector<utils::point>);
            void setRotateTime(int, float[]);
            void setCurvePoints();
            float* getCoords();
            std::vector<utils::point> getPoints();
            std::vector<utils::point> getCurvePoints();
            trans_type getType();
            int getTime();
            bool getAlign();
            float getAngle();

    };
}



class Group {
    public:
        vector<transformations::Transform> transforms;
        vector<Group> child_nodes;
        size_t fSizes = 0;
    public:
        Group() {};
        vector<transformations::Transform> getTrans();
        vector<Group> getChilds();
        size_t getFSizes();
        void addGroup(Group g); 
        void addTransform(transformations::Transform);
        void addFSize(size_t);
};


class World {
    private:
        float Window_width = 0;
        float Window_height = 0;
        float Camera_position[3];
        float Camera_lookAt[3];
        float Camera_up[3];
        float Camera_projection[3];
        int StartTime;        
        std::vector<float> VBOpoints;
        size_t VBORead = 0;
        GLuint buffers[1];
        Group Group_models;
        

    public:
        World() {};
        World(int, int, float[], float[], float[], float[]);
        int getWindowWidth(); 
        int getWindowHeight();
        float* getCameraPosition();
        float* getCameraLookAt();
        float* getCameraUp();
        float* getCameraProjection();
        void setCameraPosition(float[]);
        int getStartTime();
        void setStartTime(int);
        size_t getVBORead();
        void setVBORead(size_t);
        std::vector<float> getVBOpoints();
        void addVBOpoint(float);
        GLuint* getBuffers();
        Group getGroupModels();
        void setGroup(Group);
       
};


namespace draw {

    void drawFigure(utils::figure,bool);
    void drawCatmull(std::vector<utils::point>);

}

namespace catmull{
    void getCatmullRomPoint(float, utils::point[], float*, float*);
    void getGlobalCatmullRomPoint(transformations::Transform*, float , float* , float* );
}

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
    
    enum class trans_type {none, translate, rotate, scale, color};
    
    class Transform {
        private:
            float coords[3];
            float angle;
            trans_type transformation;
            
        public:
            Transform(float[], float, trans_type);
            void setTransform(float[], float, trans_type);
            float* getCoords();
            float getAngle();
            trans_type getType();
    };
}



class Group {
    private:
        vector<figure> models;
        vector<transformations::Transform> transforms;
        vector<Group> child_nodes;
    public:
        Group() {};
        Group(vector<figure> figs, vector<transformations::Transform> transforms, vector<Group> child_nodes);
        vector<figure> getModels();
        vector<transformations::Transform> getTrans();
        vector<Group> getChilds();
        void addGroup(Group g); 
        void addTransform(transformations::Transform); 
        void addFigure(utils::figure); 
};


class World {
    private:
        float Window_width = 0;
        float Window_height = 0;
        float Camera_position[3];
        float Camera_lookAt[3];
        float Camera_up[3];
        float Camera_projection[3];
        Group Group_models;
        

    public:
        World() {};
        World(int, int, float[], float[], float[], float[], Group);
        int getWindowWidth(); 
        int getWindowHeight();
        float* getCameraPosition();
        float* getCameraLookAt();
        float* getCameraUp();
        float* getCameraProjection();
        void setCameraPosition(float[]);
        Group getGroupModels();
       
};


namespace draw {

    void drawFigure(utils::figure,bool);
    void drawFigures(Group);

}
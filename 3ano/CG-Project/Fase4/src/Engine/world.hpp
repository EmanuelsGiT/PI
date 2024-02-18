#include "../Utils/utils.hpp"
#include <map>
#include <iostream>
#include <sstream>

using namespace std;
using namespace utils;

#include <GL/glew.h>
#include <GL/glut.h>

namespace lights {

    enum class light_type {none, point, directional, spotlight};

    class Light {
        private:
            light_type light;
            float pos[3];
            float dir[3];
            float cutoff;
        public:
            Light() {};
            void setPointLight(float[]);
            void setDirLight(float[]);
            void setSpotLight(float[], float[], float);
            float* getPos();
            float* getDir();
            float getCutoff();
            light_type getLightType();
    };


}

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

class Model {
    public:
        float colors[4][3] = { {200.0f,200.0f,200.0f},
                                {50.0f,50.0f,50.0f},
                                {0.0f,0.0f,0.0f},
                                {0.0f,0.0f,0.0f}};
        float shininess = 0;
		std::vector<float> vertices;
		std::vector<size_t> indices;
		std::vector<float> normal;
		std::vector<float> texCoords;
		bool vboGerados = 0;
		GLuint verticesVBO;
		GLuint indicesVBO;
		GLuint normaisVBO;
		GLuint texPontos;
		GLuint texImagem;
		std::string texName = "";

	public:
		void setDiffuse(float, float, float);
		void setAmbient(float, float, float);
		void setSpecular(float, float, float);
		void setEmissive(float, float, float);
		void setShininess(float);
        void generateVBOs();
		void loadTexture();

		float* getDiffuse();
		float* getAmbient();
		float* getSpecular();
		float* getEmissive();
        float getShininess();
};


class Group {
    private:      
        vector<Model> models;
        vector<transformations::Transform> transforms;
        vector<Group> child_nodes;
        size_t fSizes = 0;
    public:
        Group() {};
        vector<transformations::Transform> getTrans();
        vector<Group> getChilds();
        vector<Model> getModels();
        void setModels(vector<Model>);
        void setChilds(vector<Group>);
        size_t getFSizes();
        void addGroup(Group); 
        void addModel(Model);
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
        vector<lights::Light> light_config;
        int n_lights = 0;
        Group Group_models;
        

    public:
        World() {};
        World(int, int, float[], float[], float[], float[], vector<lights::Light>);
        int getWindowWidth(); 
        int getWindowHeight();
        float* getCameraPosition();
        float* getCameraLookAt();
        float* getCameraUp();
        float* getCameraProjection();
        void setCameraPosition(float[]);
        vector<lights::Light> getLights();
        int getNLights();
        Group getGroupModels();
        void setGroup(Group);
       
};


namespace draw {

    void drawFigure(utils::figure,bool);
    void drawCatmull(std::vector<utils::point>);
    void drawReferencial();

}

namespace catmull{
    void getCatmullRomPoint(float, utils::point[], float*, float*);
    void getGlobalCatmullRomPoint(transformations::Transform*, float , float* , float* );
}

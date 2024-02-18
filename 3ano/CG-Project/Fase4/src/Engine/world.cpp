#include "world.hpp"
#include <cstddef>
#include <IL/il.h>

#ifdef __unix__
    static const std::string slash = "/";
#else
    static const std::string slash = "\\";
#endif

using namespace transformations;
using namespace lights;

// funçao auxiliar que desenha triangulos
void drawTriangle(point p1, point p2, point p3, bool random_color) {

	glBegin(GL_TRIANGLES);
	
	if (random_color)
		glColor3ub(rand() % 255, rand() % 255, rand() % 255);

	//desenhar os 3 vertices do triangulo
	/*glBegin(GL_LINE_LOOP);   //caso se pretenda apenas desenhar as arestas dos triangulos
	glColor3f(1, 1, 1);*/
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);

	glEnd();
}


// recebe a lista de pontos, e o n�mero de pontos contidos na lista
void draw::drawFigure(figure f, bool random_color) {
	int i;
	int n = f.pontos.size();
	for (i = 0; i+2 <= n; i+=3) {
		//desenha os triangulos partindo da lista de pontos da figura
		drawTriangle(f.pontos[i], f.pontos[i + 1], f.pontos[i + 2], random_color);
	}
}


void draw::drawCatmull(std::vector<utils::point> pontos) {
    glBegin(GL_LINES);
    for (size_t i = 0; i < pontos.size() - 1; i++) {
        float pos1[3] = { pontos[i].x, pontos[i].y, pontos[i].z };
        glVertex3fv(pos1);
        float pos2[3] = { pontos[i + 1].x, pontos[i + 1].y, pontos[i + 1].z };
        glVertex3fv(pos2);
    }
    glEnd();
}

void draw::drawReferencial() {

    float red[4] = {1,0,0,1};
    float green[4] = {0,1,0,1};
    float blue[4] = {0,0,1,1};
	// Desenhar referencial
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glBegin(GL_LINES);

	// X axis in red
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,red);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);

	// Y Axis in Green
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

	// Z Axis in Blue
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	
	glEnd();
}

void Light::setPointLight(float nPos[3]) {

	light = light_type::point;
	
	for (int i = 0; i<3; i++) {
		pos[i] = nPos[i];
	}
}

void Light::setDirLight(float nDir[3]) {

    light = light_type::directional;
	
	for (int i = 0; i<3; i++) {
		dir[i] = nDir[i];
	}
}

void Light::setSpotLight(float nPos[3], float nDir[3], float nCutoff) {

    light = light_type::spotlight;
	
	for (int i = 0; i<3; i++) {
		pos[i] = nPos[i];
		dir[i] = nDir[i];
	}

	cutoff = nCutoff;
}

float* Light::getPos() {return pos;}
float* Light::getDir() {return dir;}
float Light::getCutoff() {return cutoff;}
light_type Light::getLightType() {return light;}

void Transform::setTransform(float nCoords[3], float at, trans_type tt)
{
	for (int i = 0; i<3; i++)
	{
		coords[i] = nCoords[i];
	}
	angle = at;
	type = tt;
}


void Transform::setTranslateTime(int timer, bool align_, std::vector<utils::point> p) {
    type = trans_type::translate_time;
    align = align_;
	time = timer;
    points = p;
    for (int i = 0; i<3; i++) {
		coords[i] = 0;
	}
}

void Transform::setRotateTime(int timer, float nCoords[3]) {
    for (int i = 0; i<3; i++) {
		coords[i] = nCoords[i];
	}
    time = timer;
    type = trans_type::rotate_time;
}

void Transform::setCurvePoints() {
    float res[3];
    float deriv[3];
    float t;
    for (t = 0; t < 1; t += 0.01) {
        catmull::getGlobalCatmullRomPoint(this, t, res, deriv);
        utils::point p;
        p.x = res[0];
        p.y = res[1];
        p.z = res[2];
        curvePoints.push_back(p);
    }

}

float* Transform::getCoords() {return coords;}
std::vector<utils::point> Transform::getPoints() {return points;}
std::vector<utils::point> Transform::getCurvePoints() {return curvePoints;}
trans_type Transform::getType() {return type;}
int Transform::getTime() {return time;}
bool Transform::getAlign() {return align;}
float Transform::getAngle() {return angle;}


vector<Transform> Group::getTrans() {return transforms;}
vector<Group> Group::getChilds() {return child_nodes;}
vector<Model> Group::getModels() {return models;}
size_t Group::getFSizes() {return fSizes;}

void Group::setModels(vector<Model> m) {
    models = m;
}

void Group::setChilds(vector<Group> g) {
    child_nodes = g;
}

void Group::addGroup(Group g)
{
	child_nodes.push_back(g);
}

void Group::addModel(Model m) {
	models.push_back(m);
}

void Group::addTransform(Transform transf)
{
	transforms.push_back(transf);
}

void Group::addFSize(size_t s) {
    fSizes += s;
}

World::World(int w, int h, float pos[3], float look[3], float up[3], float proj[3], vector<lights::Light> lights) {
	this->Window_width = w;
	this->Window_height = h;
	for(int i = 0; i < 3; i++) {
		this->Camera_position[i] = pos[i];
		this->Camera_lookAt[i] = look[i];
		this->Camera_up[i] = up[i];
		this->Camera_projection[i] = proj[i];
	}
	this->light_config = lights;
    this->n_lights = lights.size();
}

int World::getNLights() {return n_lights; }
int World::getWindowWidth() { return Window_width; }
int World::getWindowHeight() { return Window_height; }

float* World::getCameraPosition() { return Camera_position; }
float* World::getCameraLookAt() { return Camera_lookAt; }
float* World::getCameraUp() { return Camera_up; }
float* World::getCameraProjection() { return Camera_projection; }

void World::setCameraPosition(float pos[3]) 
{
	for(int i = 0; i < 3; i++) 
		this->Camera_position[i] = pos[i];
	
}

Group World::getGroupModels() { return Group_models; }
vector<lights::Light> World::getLights() {return light_config;}
void World::setGroup(Group g) {Group_models = g;}

void Model::setDiffuse(float r, float g, float b) {
    colors[0][0] = r;
    colors[0][1] = g;
    colors[0][2] = b;
}

void Model::setAmbient(float r, float g, float b) {
    colors[1][0] = r;
    colors[1][1] = g;
    colors[1][2] = b;
}

void Model::setSpecular(float r, float g, float b) {
    colors[2][0] = r;
    colors[2][1] = g;
    colors[2][2] = b;
}
void Model::setEmissive(float r, float g, float b) {
    colors[3][0] = r;
    colors[3][1] = g;
    colors[3][2] = b;
}

void Model::setShininess(float s) {shininess = s;}

float* Model::getDiffuse() {return colors[0];}
float* Model::getAmbient() {return colors[1];}
float* Model::getSpecular() {return colors[2];}
float* Model::getEmissive() {return colors[3];}
float Model::getShininess() {return shininess;}

void Model::generateVBOs() {
    glGenBuffers(1, &indicesVBO);
    glGenBuffers(1, &verticesVBO);
    glGenBuffers(1, &normaisVBO);
    glGenBuffers(1, &texPontos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(size_t), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normaisVBO);
    glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(float), normal.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texPontos);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);

    if (texName.compare("") != 0) loadTexture();

    vboGerados = 1;
}

void Model::loadTexture() {
    unsigned int t, tw, th;
    unsigned char* texData;
    //unsigned int texID;
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage( (ILstring)("../../texImages/" + texName).c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texImagem);

    glBindTexture(GL_TEXTURE_2D, texImagem);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        tw,
        th,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}
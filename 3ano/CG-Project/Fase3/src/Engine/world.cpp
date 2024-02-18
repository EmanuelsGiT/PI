#include "world.hpp"
#include <cstddef>
using namespace transformations;

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
size_t Group::getFSizes() {return fSizes;}

void Group::addGroup(Group g)
{
	child_nodes.push_back(g);
}

void Group::addTransform(Transform transf)
{
	transforms.push_back(transf);
}

void Group::addFSize(size_t s) {
    fSizes += s;
}

World::World(int w, int h, float pos[3], float look[3], float up[3], float proj[3]) {
	this->Window_width = w;
	this->Window_height = h;
	for(int i = 0; i < 3; i++) {
		this->Camera_position[i] = pos[i];
		this->Camera_lookAt[i] = look[i];
		this->Camera_up[i] = up[i];
		this->Camera_projection[i] = proj[i];
	}

}

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
GLuint* World::getBuffers() {return buffers;}
int World::getStartTime() {return StartTime;}
std::vector<float> World::getVBOpoints() {return VBOpoints;}
void World::addVBOpoint(float f) {
	VBOpoints.push_back(f);
}
size_t World::getVBORead() {return VBORead;}
void World::setVBORead(size_t l) {VBORead = l;}
void World::setGroup(Group g) {Group_models = g;}
void World::setStartTime(int time) {StartTime = time;}
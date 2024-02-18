#include "world.hpp"
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

void draw::drawFigures(Group g) {
    glPushMatrix();
    bool random_color = true;
	for (Transform t : g.getTrans()) {
        switch (t.getType()) {
            case trans_type::translate:
                glTranslatef(t.getCoords()[0], t.getCoords()[1], t.getCoords()[2]);
                break;
            case trans_type::rotate:
                glRotatef(t.getAngle(),t.getCoords()[0], t.getCoords()[1], t.getCoords()[2]);
                break;
            case trans_type::scale:
                glScalef(t.getCoords()[0], t.getCoords()[1], t.getCoords()[2]);
                break;
			case trans_type::color:
                glColor3f(t.getCoords()[0], t.getCoords()[1], t.getCoords()[2]);
				random_color = false;
                break;
            default:
                break;
        }
    }
    for (figure fig : g.getModels()) {
        drawFigure(fig,random_color);
    }
    for (Group gr : g.getChilds()) {
        drawFigures(gr);
    }
    glPopMatrix();
}


Transform::Transform(float nCoords[3], float nAngle, trans_type nTransformation)
{
	for (int i = 0; i<3; i++)
	{
		this->coords[i] = nCoords[i];
	}

	this->angle = nAngle;
	this->transformation = nTransformation;
}


void Transform::setTransform(float nCoords[3], float at, trans_type tt)
{
	for (int i = 0; i<3; i++)
	{
		coords[i] = nCoords[i];
	}
	angle = at;
	transformation = tt;
}

float* Transform::getCoords() {return coords;}
float Transform::getAngle() {return angle;}
trans_type Transform::getType() {return transformation;}

Group::Group(vector<figure> nModel, vector<Transform> nTransforms, vector<Group> nChild_nodes)
{
	this->models= nModel;
	this->transforms = nTransforms;
	this->child_nodes = nChild_nodes;
}

vector<figure> Group::getModels() {return models;}
vector<Transform> Group::getTrans() {return transforms;}
vector<Group> Group::getChilds() {return child_nodes;}

void Group::addGroup(Group g)
{
	child_nodes.push_back(g);
}

void Group::addTransform(Transform transf)
{
	transforms.push_back(transf);
}

void Group::addFigure(utils::figure fig)
{	
	models.push_back(fig);
}

World::World(int w, int h, float pos[3], float look[3], float up[3], float proj[3], Group models) {
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
#include "../tinyXML/tinyxml.h"
#include "world.hpp"
#include <GL/freeglut_std.h>
#include <fstream>
#include <string>
#include <math.h>

World world;
int changeFig = 0;
float alphaCam = M_PI/4;
float betaCam = M_PI/4;
float radiusCam = 5;

int readXMLfile(string xml_file) 
{
    TiXmlDocument file; // Create a new instance of TiXmlDocument and load the XML file
    bool loadOkay = file.LoadFile(xml_file.c_str()); // need to check this in the future

    if (!loadOkay) // Check if the file was loaded successfully
    {
        std::cerr << "Could not load XML file." << std::endl;
        return -1; 
    }

    TiXmlElement* root = file.RootElement(); // Get a pointer to the root element ('world')

    // Get the 'window' element and its attributes
    TiXmlElement* windowElement = root->FirstChildElement("window");
    float width = stoi(windowElement->Attribute("width"));
    float height = stoi(windowElement->Attribute("height"));

    // Get the 'camera' element and its child elements
    TiXmlElement* cameraElement = root->FirstChildElement("camera");
    TiXmlElement* positionElement = cameraElement->FirstChildElement("position");
    TiXmlElement* lookAtElement = cameraElement->FirstChildElement("lookAt");
    TiXmlElement* upElement = cameraElement->FirstChildElement("up");
    TiXmlElement* projectionElement = cameraElement->FirstChildElement("projection");
    
    float posX = stoi(positionElement->Attribute("x"));
    float posY = stoi(positionElement->Attribute("y"));
    float posZ = stoi(positionElement->Attribute("z"));
    float pos[3] = {posX,posY,posZ};
    
    float lookAtX = stoi(lookAtElement->Attribute("x"));
    float lookAtY = stoi(lookAtElement->Attribute("y"));
    float lookAtZ = stoi(lookAtElement->Attribute("z"));
    float look[3] = {lookAtX, lookAtY, lookAtZ};
    
    float upX = stoi(upElement->Attribute("x"));
    float upY = stoi(upElement->Attribute("y"));
    float upZ = stoi(upElement->Attribute("z"));
    float up[3] = {upX,upY,upZ};

    float fov = stoi(projectionElement->Attribute("fov"));
    float near = stoi(projectionElement->Attribute("near"));
    float far = stoi(projectionElement->Attribute("far"));
    float proj[3] = {fov,near,far};
    

    // Get the 'model' element(s) and their attributes
    TiXmlElement* groupElement = root->FirstChildElement("group");
    TiXmlElement* modelsElement = groupElement->FirstChildElement("models");
 
    
    map<int,figure> models;
    int i = 0;

    for (TiXmlElement* modelElement = modelsElement->FirstChildElement("model"); modelElement != nullptr; modelElement = modelElement->NextSiblingElement()) {
            
        const char* fil = modelElement->Attribute("file");
        char path[30] = "../out/";
        strcat(path,fil);
        fstream fs;

        fs.open(path); //ver isto

        if(fs.is_open()) {
            figure fig;
            string line;
            float x1, y1, z1 = 0.0f;

            while(getline(fs, line)) {
                float coords[3];
                
                string delimiter = " ";
                size_t pos = 0;
                string token;
                int i = 0;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    coords[i] = std::stof(token); 
                    i++;
                    line.erase(0, pos + delimiter.length());
                }
                x1=coords[0],y1=coords[1],z1=coords[2];
                fig.addPoint(x1,y1,z1);
            }
            fs.close();
            models.insert(pair<int, figure>(i,fig));
            i++;
        }

        else {
            std::cout << "Can't open file!"<< std::endl;
            return -1;
        }
                    
    }
    world = World(width,height,pos,look,up,proj,models);

    return 1;
}


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(world.getCameraProjection()[0], ratio, world.getCameraProjection()[1], world.getCameraProjection()[2]);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(){
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set camera
	glLoadIdentity();
	gluLookAt(world.getCameraPosition()[0], world.getCameraPosition()[1], world.getCameraPosition()[2],
		world.getCameraLookAt()[0], world.getCameraLookAt()[1], world.getCameraLookAt()[2],
		world.getCameraUp()[0], world.getCameraUp()[1], world.getCameraUp()[2]);


	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,-100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f,-100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
    
    map<int,figure> figures = world.getGroupModels();

    for(int i = 0; i < (int) figures.size(); i++) {
        draw::drawFigure(figures.at(i));
    }
    

	// End of frame
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {

	switch(key)
	{
		case GLUT_KEY_UP:
            betaCam += M_PI/16; 
			if (betaCam > 1.5) betaCam = 1.5;            
			break; 
		case GLUT_KEY_DOWN:
            betaCam -= M_PI/16; 
			if (betaCam < -1.5) betaCam = -1.5;
			break;
		case GLUT_KEY_LEFT:
			alphaCam += M_PI/16;
			break;
		case GLUT_KEY_RIGHT:
			alphaCam -= M_PI/16;
			break;
        case GLUT_KEY_PAGE_DOWN: 
            radiusCam -= 0.1f;
		    if (radiusCam < 0.1f)
		    	radiusCam = 0.1f;
		    break;
	    case GLUT_KEY_PAGE_UP: 
            radiusCam += 0.1f; 
            break;
        case GLUT_KEY_F1:
            glPolygonMode(GL_FRONT, GL_LINE);
            break;
        case GLUT_KEY_F2:
            glPolygonMode(GL_FRONT, GL_FILL);
            break;

	}

    float pos[3] = {radiusCam * cos(betaCam) * sin(alphaCam), radiusCam * sin(betaCam), radiusCam * cos(betaCam) * cos(alphaCam)};
    world.setCameraPosition(pos);

	glutPostRedisplay();
}



int main(int argc, char** argv){
    if (argc <=1) {
        std::cout << "\nMissing arguments\n" << std::endl;
    }
    else if(argc > 2){
        std::cout << "\nToo many arguments\n" << std::endl;
    }
    else {
        std::cout << "\nReading .... ..... ....\n" << std::endl;
        if(readXMLfile(argv[1])==1) {
        
            // put GLUT init here
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(world.getWindowWidth(), world.getWindowHeight());
            glutCreateWindow("Projeto-CG");



            // put callback registry here
            glutDisplayFunc(renderScene);
            glutReshapeFunc(changeSize);

            glutSpecialFunc(processSpecialKeys);

            // some OpenGL settings
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            // enter GLUT�s main cycle
            glutMainLoop();

        }
    }

	return 1;
}
#include "../tinyXML/tinyxml.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "world.hpp"
#include <IL/il.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace draw;
using namespace transformations;
using namespace lights;

int timebase = 0, frame = 0;

World world;
string backName = "backGround.jpg";
GLuint backTexture;
bool first = 1;
float alphaCam = M_PI/4;
float betCam = M_PI/4;
float radiusCam = 5;
float aux_y[3] = { 0,1,0 };
bool referencial = 0;
bool orbitas = 1;
bool showBackground = 1;

// CÂMARAS
/*
Tipos de Camara:
    camera1 - Camara que que se movimenta sempre a olhar para o centro do referencial
    camera2 - Camara em primeira pessoa
*/
float cameraMoves[3];
bool cameraType = 0; // 0 -> camera1; 1 -> camera2

// variaveis camera1

float alfa = 0.0f, bet = 0.0f, radius = 15.0f; 
int startX, startY, tracking = 0;

// variaveis camera2

float xrot = 0; float yrot = 0;
float lastx, lasty;
bool valid = false;

// Movimentar camera2 no referencial

void camera(void) {
    glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on the x - axis(up and down)
    glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(left and right)
    glTranslated(-world.getCameraPosition()[0], -world.getCameraPosition()[1], -world.getCameraPosition()[2]); //translate the screen to the position of our camera
}


 //Inicializar camera1
void spherical2Cartesian() {

    cameraMoves[0] = radius * cos(bet) * sin(alfa);
    cameraMoves[1] = radius * sin(bet);
    cameraMoves[2] = radius * cos(bet) * cos(alfa);
}

void drawFigures(Group* g) {
    glPushMatrix();
	for (Transform t : g->getTrans()) {
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
                break;
            case trans_type::translate_time: {
                std::vector<utils::point> pontos = t.getCurvePoints();
                
                if (orbitas) {
                    glPushMatrix();
                    draw::drawCatmull(pontos);
                    glPopMatrix();
                }
                
                float pos[3] = { 0.0, 0.0, 0.0 };
                float deriv[3] = { 0.0, 0.0, 0.0 };

                float timeT = ((float) glutGet(GLUT_ELAPSED_TIME) / 1000) / (float)(t.getTime());
                catmull::getGlobalCatmullRomPoint(&t, timeT, (float*)pos, (float*)deriv);

                glTranslatef(pos[0], pos[1], pos[2]);

                if(t.getAlign()) {
                    float m[4][4];
                    float x[3], z[3];

                    matrix::cross(deriv, aux_y, z);
                    matrix::cross(z, deriv, aux_y);
                    matrix::normalize(deriv);
                    matrix::normalize(aux_y);
                    matrix::normalize(z);
                    matrix::buildRotMatrix(deriv, aux_y, z, *m);
                    glMultMatrixf(*m);
                } 
                break;
            }
            case trans_type::rotate_time: {
                float angle = (((float)glutGet(GLUT_ELAPSED_TIME) / 1000) * 360) / (float)t.getTime();
                glRotatef(angle, t.getCoords()[0],t.getCoords()[1],t.getCoords()[2]);
                break;
            }
            default:
                break;
        }
    }
        
    //draw_VBO
    vector<Model> modelos;
    for (Model md : g->getModels()) {
        
        // Para desenhar
        glMaterialfv(GL_FRONT, GL_DIFFUSE, md.getDiffuse());
        glMaterialfv(GL_FRONT, GL_AMBIENT, md.getAmbient());
        glMaterialfv(GL_FRONT, GL_SPECULAR, md.getSpecular());
        glMaterialfv(GL_FRONT, GL_EMISSION, md.getEmissive());
        glMaterialf(GL_FRONT, GL_SHININESS, md.getShininess());
        
        if (!md.vboGerados) {
            md.generateVBOs();
            modelos.push_back(md);
        }

        glBindBuffer(GL_ARRAY_BUFFER, md.verticesVBO); 
        glVertexPointer(3, GL_FLOAT, 0, 0); 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, md.indicesVBO); 

        glBindBuffer(GL_ARRAY_BUFFER, md.normaisVBO);
        glNormalPointer(GL_FLOAT, 0, 0);

        if (md.texName.compare("") != 0) {
            glEnable(GL_TEXTURE_2D);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, md.texPontos);
            glTexCoordPointer(2, GL_FLOAT, 0, 0);

            glBindTexture(GL_TEXTURE_2D, md.texImagem);
            
        }
        else {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisable(GL_TEXTURE_2D);
        }

        glDrawElements(GL_TRIANGLES, md.indices.size(),GL_UNSIGNED_INT,0);

    }

    
    if (first) {
        g->setModels(modelos);
        vector<Group> filhosRes;
        for (Group gr : g->getChilds()) {
            drawFigures(&gr);
            filhosRes.push_back(gr);
        }
        g->setChilds(filhosRes);
    }
    else {
        for (Group gr : g->getChilds()) {
            drawFigures(&gr);
        }
    }
    
    glPopMatrix();
}

void drawBackground(void)
{
    float w = 0.0f;  // Largura da janela
    float h = 0.0f;  // Altura da janela

    // Pretende-se que o background não seja sujeito a transformações e que
    // permaneça no fundo da janela
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Calculam-se a altura e a largura da janela
    w = (float)glutGet(GLUT_WINDOW_WIDTH);
    h = (float)glutGet(GLUT_WINDOW_HEIGHT);

    gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, backTexture);

    // Desenha-se um plano com as dimensões da janela e aplica-se a textura
    // com o background
    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, h, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(w, h, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(w, 0.0f, 0.0f);

    glEnd();


    // Retorna-se às configurações iniciais
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


void loadBackground(void) {
    unsigned int t = 0;
    unsigned int tw = 0;
    unsigned int th = 0;
    unsigned char* texData;

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)("../../texImages/" + backName).c_str());

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &backTexture);

    glBindTexture(GL_TEXTURE_2D, backTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}


Group readXMLmodels(string file, Group g, Model md) {
    char path[30] = "../../out/";
    strcat(path,file.c_str());
    fstream fs;
    fs.open(path); 
    if (fs.is_open()) {

        string line;
        float x1, y1, z1 = 0.0f; //Inicializa as coordenadas de cada ponto

        //Ler a linha dos indices
        if (getline(fs, line)) {
            std::string delimiter = ",";
            std::string token;
            size_t pos = 0;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                int indice = std::stoi(token); //converte para float e guarda a coordenada
                md.indices.push_back(indice);
                line.erase(0, pos + delimiter.length());
            }
        }
        //printf("Indices: %d\n", g.indices.size());
        // ler restante ficheiro
        for (size_t j = 0; j < 3; j++) {
            int pointNumber = 0;
            if (getline(fs, line)) {
                pointNumber = atoi(line.c_str());
            }
            //Lê linha a linha do ficheiro, não esquecendo que cada linha é um vértice/ponto  
            for (size_t linha = 0; linha < pointNumber; linha++) {
                if (getline(fs, line)) {
                    float cood[3]; //guarda num array as coordenadas de cada ponto

                    std::string delimiter = " ";
                    size_t pos = 0;
                    std::string token;
                    int i = 0;
                    while ((pos = line.find(delimiter)) != std::string::npos) {
                        token = line.substr(0, pos);
                        cood[i] = std::stof(token); //converte para float e guarda a coordenada
                        i++;
                        line.erase(0, pos + delimiter.length());
                    }
                    if (j == 0) {
                        md.vertices.push_back(cood[0]);
                        md.vertices.push_back(cood[1]);
                        md.vertices.push_back(cood[2]);
                        
                    }
                    else {
                        if (j == 1) {
                            md.normal.push_back(cood[0]);
                            md.normal.push_back(cood[1]);
                            md.normal.push_back(cood[2]);
                           
                        }
                        else {
                            md.texCoords.push_back(cood[0]);
                            md.texCoords.push_back(cood[1]);
                        }
                    }
                    
                }
            }
        }

        g.addModel(md);
        //printf("PontosVBO: %d\n", md.vertices.size() / 3);
        //printf("Normais: %d\n", md.normal.size()/3 );
        //printf("Texturas: %d\n", md.texCoords.size() / 2);

        fs.close();
    }

    else{
        std::cout << "Can't open file! "<< file << std::endl;
    }

    
    return g;
}

Group readXMLgroup(TiXmlElement* g, Group group) {
        
    float angle = 0;

    for (TiXmlElement* groupElement = g->FirstChildElement()->ToElement(); 
        groupElement != nullptr; 
        groupElement = groupElement->NextSiblingElement()) {
        

        if(strcmp(groupElement->Value(), "transform") == 0) {
            TiXmlElement* transElement = groupElement->FirstChildElement();
            
            while(transElement != nullptr) {
                transElement = transElement->ToElement();
                if(strcmp(transElement->Value(), "translate") == 0) {
                    if(transElement->Attribute("time")) {
                        int time = atoi(transElement->Attribute("time"));
                        bool align = strcmp(transElement->Attribute("align"), "true") == 0;
                        TiXmlElement *point = transElement->FirstChildElement("point");
                        std::vector<utils::point> pontos;
                        while (point) {
                            utils::point p;
                            p.x = atof(point->Attribute("x"));
                            p.y = atof(point->Attribute("y"));
                            p.z = atof(point->Attribute("z"));
                            pontos.push_back(p);
                            //next sibling
                            point = point->NextSiblingElement("point");
                        }
                        Transform transTime;
                        transTime.setTranslateTime(time, align, pontos);
                        transTime.setCurvePoints();
                        group.addTransform(transTime);   
                    } else {
                        float translateV[3];
                        translateV[0] = stof(transElement->Attribute("x"));
                        translateV[1] = stof(transElement->Attribute("y"));
                        translateV[2] = stof(transElement->Attribute("z"));
                        Transform t = Transform();
                        t.setTransform(translateV,angle,trans_type::translate);
                        group.addTransform(t);
                    }
                }

                else if(strcmp(transElement->Value(), "rotate") == 0) {
                    if(transElement->Attribute("time")) {
                        int time = atoi(transElement->Attribute("time"));
                        float coords[3];
                        coords[0] = atof(transElement->Attribute("x"));
                        coords[1] = atof(transElement->Attribute("y"));
                        coords[2] = atof(transElement->Attribute("z"));
                        Transform transTime;
                        transTime.setRotateTime(time, coords);
                        group.addTransform(transTime);
                        
                    } else {
                        float rotateV[3];                    
                        angle = stof(transElement->Attribute("angle"));
                        rotateV[0] = stof(transElement->Attribute("x"));
                        rotateV[1] = stof(transElement->Attribute("y"));
                        rotateV[2] = stof(transElement->Attribute("z"));
                        Transform t = Transform();
                        t.setTransform(rotateV,angle,trans_type::rotate);
                        group.addTransform(t);
                    }
                }

                else if(strcmp(transElement->Value(), "scale") == 0) {
                    float scaleV[3];
                    scaleV[0] = stof(transElement->Attribute("x"));
                    scaleV[1] = stof(transElement->Attribute("y"));
                    scaleV[2] = stof(transElement->Attribute("z"));
                    Transform t = Transform();
                    t.setTransform(scaleV,angle,trans_type::scale);
                    group.addTransform(t);
                }
                
                else if(strcmp(transElement->Value(), "color") == 0) {
                    float colorV[3];
                    colorV[0] = stof(transElement->Attribute("R"));
                    colorV[1] = stof(transElement->Attribute("G"));
                    colorV[2] = stof(transElement->Attribute("B"));
                    Transform t = Transform();
                    t.setTransform(colorV,angle,trans_type::color);
                    group.addTransform(t);
                }

                transElement = transElement->NextSiblingElement();
            
            } 
        }

        else if(strcmp(groupElement->Value(), "models") == 0) {
            for (TiXmlElement* modelElement = groupElement->FirstChildElement()->ToElement(); 
                modelElement != nullptr; 
                modelElement = modelElement->NextSiblingElement()) {
                    
                
                    Model md;
                    const char *ficheiro = modelElement->Attribute("file");
                    
                    // --->> modelsUtils::model md;
                    //textured  model
                    TiXmlElement* model = modelElement->FirstChildElement();
                    while (model != nullptr) {
                        model = model->ToElement();
                        if(strcmp(model->Value(), "texture") == 0) {
                            glewInit();
                            string texture = model->Attribute("file");
                            md.texName = texture;
                        }
                        else if(strcmp(model->Value(), "color") == 0) {
                            TiXmlElement* color = model->FirstChildElement()->ToElement();
                            while (color != nullptr) {
                                if(strcmp(color->Value(), "diffuse") == 0) {
                                    float d1 = atof(color->Attribute("R"));
                                    float d2 = atof(color->Attribute("G"));
                                    float d3 = atof(color->Attribute("B"));
                                    md.setDiffuse(d1/255.0, d2/255.0, d3/255.0);
                                }
                                
                                if(strcmp(color->Value(), "ambient") == 0) {
                                    float a1 = atof(color->Attribute("R"));
                                    float a2 = atof(color->Attribute("G"));
                                    float a3 = atof(color->Attribute("B"));
                                    md.setAmbient(a1/255.0, a2/255.0, a3/255.0);
                                }
                                
                                if(strcmp(color->Value(), "specular") == 0) {
                                    float s1 = atof(color->Attribute("R"));
                                    float s2 = atof(color->Attribute("G"));
                                    float s3 = atof(color->Attribute("B"));
                                    md.setSpecular(s1/255.0, s2/255.0, s3/255.0);
                                }
                                
                                if(strcmp(color->Value(), "emissive") == 0) {
                                    float e1 = atof(color->Attribute("R"));
                                    float e2 = atof(color->Attribute("G"));
                                    float e3 = atof(color->Attribute("B"));
                                    md.setEmissive(e1/255.0, e2/255.0, e3/255.0);
                                }
                                
                                if(strcmp(color->Value(), "shininess") == 0) {
                                    float shininess = atof(color->Attribute("value"));
                                    md.setShininess(shininess);
                                }

                                color = color->NextSiblingElement();
                            }
                        }
                        model = model->NextSiblingElement();
                                           
                    }
                group = readXMLmodels(ficheiro, group,md);
            }
        }
        
        else if(strcmp(groupElement->Value(), "group") == 0) {
            Group grupo;
            grupo = readXMLgroup(groupElement, grupo);
            group.addGroup(grupo);
        }
    }

    return group;

}


vector<lights::Light> parseLights(TiXmlElement * tag) {
    vector<lights::Light> lights;

    TiXmlElement *light = tag->FirstChildElement("light");

        while (light) {
        if (strcmp(light->Attribute("type"),"point")==0){
            float pos[3];
            pos[0] = atof(light->Attribute("posx"));
            pos[1] = atof(light->Attribute("posy"));
            pos[2] = atof(light->Attribute("posz"));
            Light l = Light();
            l.setPointLight(pos);
            lights.push_back(l);
        }
        else if (strcmp(light->Attribute("type"),"directional")==0){
            float dir[3];
            dir[0] = atof(light->Attribute("dirx"));
            dir[1] = atof(light->Attribute("diry"));
            dir[2] = atof(light->Attribute("dirz"));
            Light l = Light();
            l.setDirLight(dir);
            lights.push_back(l);
        }
        else if (strcmp(light->Attribute("type"),"spot")==0){
            float pos[3], dir[3];
            pos[0] = atof(light->Attribute("posx"));
            pos[1] = atof(light->Attribute("posy"));
            pos[2] = atof(light->Attribute("posz"));
            dir[0] = atof(light->Attribute("dirx"));
            dir[1] = atof(light->Attribute("diry"));
            dir[2] = atof(light->Attribute("dirz"));
            float cutoff = atof(light->Attribute("cutoff"));
            Light l = Light();
            l.setSpotLight(pos,dir,cutoff);
            lights.push_back(l);
        }
        
        //next sibling
        light = light->NextSiblingElement("light");
    }

    return lights;
}

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
    float width = stof(windowElement->Attribute("width"));
    float height = stof(windowElement->Attribute("height"));

    // Get the 'camera' element and its child elements
    TiXmlElement* cameraElement = root->FirstChildElement("camera");
    TiXmlElement* positionElement = cameraElement->FirstChildElement("position");
    TiXmlElement* lookAtElement = cameraElement->FirstChildElement("lookAt");
    TiXmlElement* upElement = cameraElement->FirstChildElement("up");
    TiXmlElement* projectionElement = cameraElement->FirstChildElement("projection");
    
    float posX = stof(positionElement->Attribute("x"));
    float posY = stof(positionElement->Attribute("y"));
    float posZ = stof(positionElement->Attribute("z"));
    float pos[3] = {posX,posY,posZ};
    
    float lookAtX = stof(lookAtElement->Attribute("x"));
    float lookAtY = stof(lookAtElement->Attribute("y"));
    float lookAtZ = stof(lookAtElement->Attribute("z"));
    float look[3] = {lookAtX, lookAtY, lookAtZ};
    
    float upX = stof(upElement->Attribute("x"));
    float upY = stof(upElement->Attribute("y"));
    float upZ = stof(upElement->Attribute("z"));
    float up[3] = {upX,upY,upZ};

    float fov = stof(projectionElement->Attribute("fov"));
    float near = stof(projectionElement->Attribute("near"));
    float far = stof(projectionElement->Attribute("far"));
    float proj[3] = {fov,near,far};
    

    TiXmlElement* lightElement = root->FirstChildElement("lights");
    vector<lights::Light> lights = {};

    if(lightElement) {
        lights = parseLights(lightElement);
    }

    world = World(width,height,pos,look,up,proj,lights);

    // Get the 'model' element(s) and their attributes
    TiXmlElement* groupElement = root->FirstChildElement("group");
    
    Group grupo;
    
    grupo = readXMLgroup(groupElement,grupo);

    world.setGroup(grupo);

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

void renderScene(void){
	
    float fps;
	int time;
	char s[64];
    
    // clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    if (showBackground)
        drawBackground();
    if (world.getNLights() != 0) {
        int i = 0;
        for(Light l : world.getLights()) {
            glEnable(GL_LIGHT0 + i);

            if(l.getLightType() == light_type::point) {
                GLfloat pos[4] = { l.getPos()[0], l.getPos()[1], l.getPos()[2], 1.0f };
                glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
            }
            else if(l.getLightType() == light_type::directional) {
                GLfloat dir[4] = { l.getDir()[0], l.getDir()[1], l.getDir()[2], 0.0f };
                glLightfv(GL_LIGHT0 + i, GL_POSITION, dir);   
            }
            else if(l.getLightType() == light_type::spotlight) {
                GLfloat pos[4] = { l.getPos()[0], l.getPos()[1], l.getPos()[2], 1.0f };
                GLfloat dir[3] = { l.getDir()[0], l.getDir()[1], l.getDir()[2] };
                GLfloat c[1] = {l.getCutoff()};
                glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
                glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, dir);
                glLightfv(GL_LIGHT0 + i, GL_SPOT_CUTOFF, c);
            }
            i++;
        }
    }

	// set camera
	glLoadIdentity();

    if (cameraType) {
        camera();
    }
    else {
        gluLookAt(world.getCameraPosition()[0], world.getCameraPosition()[1], world.getCameraPosition()[2],
		world.getCameraLookAt()[0], world.getCameraLookAt()[1], world.getCameraLookAt()[2],
		world.getCameraUp()[0], world.getCameraUp()[1], world.getCameraUp()[2]);
    }

    glDisable(GL_LIGHTING);
    if (referencial) drawReferencial();
    glEnable(GL_LIGHTING);
    
    drawFigures(&world.getGroupModels());
    if(first) first = 0;

    frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0; 
		sprintf(s, "Projeto-CG FPS: %.2f ", fps);
		glutSetWindowTitle(s);
	} 

	// End of frame
	glutSwapBuffers();
}

void processMouseButtons(int button, int state, int xx, int yy) {
    if (cameraType) {
        lastx = xx;
        lasty = yy;
        valid = state == GLUT_DOWN;
    }
    else {
        if (state == GLUT_DOWN) {
            startX = xx;
            startY = yy;
            if (button == GLUT_LEFT_BUTTON)
                tracking = 1;
            else if (button == GLUT_RIGHT_BUTTON)
                tracking = 2;
            else
                tracking = 0;
        }
        else if (state == GLUT_UP) {

            if (tracking == 1) {
                alfa += (xx - startX);
                bet += (yy - startY);
            }
            else if (tracking == 2) {

                radius -= yy - startY;
                if (radius < 3)
                    radius = 3.0;
            }

            tracking = 0;
        }
    }
    
}

void processMouseMotion(int xx, int yy) {
    if (cameraType) {
        if (valid) {
            int diffx = xx - lastx; //check the difference between the current x and the last x position
            int diffy = yy - lasty; //check the difference between the current y and the last y position
            lastx = xx; //set lastx to the current x position
            lasty = yy; //set lasty to the current y position
            if (xrot < -87) xrot = -87;
            else {
                if (xrot > 87) xrot = 87;
                else {
                    xrot -= (float)diffy / 10;  //set the xrot to xrot with the addition of the difference in the y position
                }
            }
            yrot -= (float)diffx / 10;    //set the xrot to yrot with the addition of the difference in the x position
        }
    }
    else {
        int deltaX, deltaY;
        int alphaAux, betAux;
        int rAux;

        if (!tracking)
            return;

        deltaX = xx - startX;
        deltaY = yy - startY;

        if (tracking == 1) {


            alphaAux = alfa + deltaX;
            betAux = bet + deltaY;

            if (betAux > 85.0)
                betAux = 85.0;
            else if (betAux < -85.0)
                betAux = -85.0;

            rAux = radius;
        }
        else if (tracking == 2) {

            alphaAux = alfa;
            betAux = bet;
            rAux = radius - deltaY;
            if (rAux < 3)
                rAux = 3;
        }

        float camera[3];
        camera[0] = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betAux * 3.14 / 180.0);
        camera[2] = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betAux * 3.14 / 180.0);
        camera[1] = rAux * sin(betAux * 3.14 / 180.0);
        world.setCameraPosition(camera);
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        cameraType = 0;
        xrot = 0; yrot = 0;
    }
    if (key == '2') {
        cameraType = 1;
    }
    if (key == 'x') {
        referencial = !referencial;
    }
    if (key == 'o') {
        orbitas = !orbitas;
    }
    if (key == 'b') {
        showBackground = !showBackground;
    }
    if (cameraType) {

        if (key == 'w') // frente
        {
            float xrotrad, yrotrad;
            float camera[3];
            yrotrad = (yrot / 180 * M_PI);
            xrotrad = (xrot / 180 * M_PI);
            camera[0] = world.getCameraPosition()[0] + float(sin(yrotrad)) * 0.2;
            camera[2] = world.getCameraPosition()[2] - float(cos(yrotrad)) * 0.2;
            camera[1] =  world.getCameraPosition()[1] - float(sin(xrotrad)) * 0.2;
            world.setCameraPosition(camera);
        }

        if (key == 's') // tras
        {
            float xrotrad, yrotrad;
            float camera[3];
            yrotrad = (yrot / 180 * M_PI);
            xrotrad = (xrot / 180 * M_PI);
            camera[0] = world.getCameraPosition()[0] - float(sin(yrotrad)) * 0.2;
            camera[2] = world.getCameraPosition()[2] + float(cos(yrotrad)) * 0.2;
            camera[1] = world.getCameraPosition()[1] + float(sin(xrotrad)) * 0.2;
            world.setCameraPosition(camera);
        }

        if (key == 'd') // direita
        {
            float yrotrad;
            float camera[3];
            yrotrad = (yrot / 180 * M_PI);
            camera[0] = world.getCameraPosition()[0] + float(cos(yrotrad)) * 0.2;
            camera[2] = world.getCameraPosition()[2] + float(sin(yrotrad)) * 0.2;
            camera[1] = world.getCameraPosition()[1];
            world.setCameraPosition(camera);
        }

        if (key == 'a') // esquerda
        {
            float yrotrad;
            float camera[3];
            yrotrad = (yrot / 180 * M_PI);
            camera[0] = world.getCameraPosition()[0] - float(cos(yrotrad)) * 0.2;
            camera[2] = world.getCameraPosition()[2] - float(sin(yrotrad)) * 0.2;
            camera[1] = world.getCameraPosition()[1];
            world.setCameraPosition(camera);
        }
    }
    glutPostRedisplay();
}

void info() {
    std::cout << "------------------------- KEYBOARD CONTROLS -------------------------\n"
        "1: Ativa camera1\n"
        "2: Ativa camera2\n"
        "x: Mostra/Esconde eixos\n"
        "o: Mostra/Esconde orbitas\n"
        "b: Mostra/Esconde background image\n"
        "Camera1: \n"
        "   Mouse: segurar botão esquerdo e mover para rodar a camara\n"
        "   Mouse: segurar botão direito e mover cima/baixo para ir longe/perto\n\n"
        "Camera2: \n"
        "   w : mover para a frente\n"
        "   s : mover para tras\n"
        "   a : mover para a esquerda\n"
        "   d : mover para a direita\n"
        "   Mouse: segurar botão esquerdo e mover para rodar a camara\n\n" << std::endl;  
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
            
            // GLUT init here
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(world.getWindowWidth(), world.getWindowHeight());
            glutCreateWindow("Projeto-CG");



            // callback registration
            glutDisplayFunc(renderScene);
            glutIdleFunc(renderScene);
            glutReshapeFunc(changeSize);

            glutMotionFunc(processMouseMotion);
            glutMouseFunc(processMouseButtons);
            glutKeyboardFunc(keyboard);

            #ifndef __APPLE__
                glewInit();
            #endif

            // some OpenGL settings
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);

            if (world.getNLights() > 0) {
                glEnable(GL_LIGHTING);
                float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
                float white[4] = { 1.0, 1.0, 1.0, 1.0 };
                //float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
                for (int i = 0; i < world.getNLights(); i++) {
                    glEnable(GL_LIGHT0 + i);
                    glLightfv(GL_LIGHT0 + i, GL_AMBIENT, dark);
                    glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
                    glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);
                }
                glEnable(GL_RESCALE_NORMAL);
            }
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnable(GL_TEXTURE_2D);
            
            float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
            
            ilInit();
            ilEnable(IL_ORIGIN_SET);
            ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

            loadBackground();

            info();

            // enter GLUT�s main cycle
            //world.setStartTime(glutGet(GLUT_ELAPSED_TIME));
            glutMainLoop();

        }
    }

	return 1;
}
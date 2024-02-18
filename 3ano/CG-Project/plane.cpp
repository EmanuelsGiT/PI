#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha = 1;
float alphaCam = M_PI/4;
float betaCam = M_PI/4;
float radiusCam = 5;


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawPlane(float length, float divisions) {

	length = 1;
	divisions = 4;
	float x = length / 2;
    float aux = length / divisions;
    int i = 0, j=0;

    // Desenhar a base
    float auxX = -x;
    float auxZ = -x;

    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
    		glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1); 
            glVertex3f(auxX, 0, auxZ);
            glVertex3f(auxX + aux, 0, auxZ + aux);
            glVertex3f(auxX + aux, 0, auxZ);
    		glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1); 
            glVertex3f(auxX + aux, 0, auxZ + aux);
            glVertex3f(auxX, 0, auxZ);
            glVertex3f(auxX, 0, auxZ + aux);
			glEnd();
            auxZ += aux;
        }
        auxZ = -x;
        auxX += aux;
    }

}

void drawBox(float length, float divisions) {

    float x = length / 2;
    float camadaX = length / divisions;
    float camadaY = length / divisions;
    float camadaZ = length / divisions;
    int i = 0, j=0;

    // Desenhar a base
    float auxX = -x;
    float auxY = -x;
    float auxZ = -x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
			
			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX + camadaX, auxY, auxZ);
            glVertex3f(auxX + camadaX, auxY, auxZ + camadaZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX + camadaX, auxY, auxZ + camadaZ);
            glVertex3f(auxX, auxY, auxZ + camadaZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();

            auxZ += camadaZ;
        }
        auxZ = -x;
        auxX += camadaX;
    }

    // Desenhar o teto
    auxX = -x;
    auxZ = -x;
    auxY = x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX + camadaX, auxY, auxZ + camadaZ);
            glVertex3f(auxX + camadaX, auxY, auxZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX, auxY, auxZ + camadaZ);
            glVertex3f(auxX + camadaX, auxY, auxZ + camadaZ);
			glEnd();

            auxZ += camadaZ;
        }
        auxZ = -x;
        auxX += camadaX;
    }

    // Desenhar o lado direito
    auxX = x;
    auxZ = x;
    auxY = x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ - camadaZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY - camadaY, auxZ - camadaZ);
            glVertex3f(auxX, auxY, auxZ - camadaZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();
			
            auxZ -= camadaZ;
        }
        auxZ = x;
        auxY -= camadaY;
    }

    // Desenhar o lado esquerdo
    auxX = -x;
    auxZ = -x;
    auxY = x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255);
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ + camadaZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY - camadaY, auxZ + camadaZ);
            glVertex3f(auxX, auxY, auxZ + camadaZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();

            auxZ += camadaZ;
        }
        auxZ = -x;
        auxY -= camadaY;
    }

    // Desenhar frente
    auxX = -x;
    auxZ = x;
    auxY = x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ);
            glVertex3f(auxX + camadaX, auxY - camadaY, auxZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX + camadaX, auxY - camadaY, auxZ);
            glVertex3f(auxX + camadaX, auxY, auxZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();

            auxX += camadaX;
        }
        auxX = -x;
        auxY -= camadaY;
    }

    // Desenhar trás
    auxX = x;
    auxZ = -x;
    auxY = x;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX, auxY, auxZ);
            glVertex3f(auxX, auxY - camadaY, auxZ);
            glVertex3f(auxX - camadaX, auxY - camadaY, auxZ);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(rand() % 255, rand() % 255, rand() % 255); 
            glVertex3f(auxX - camadaX, auxY - camadaY, auxZ);
            glVertex3f(auxX - camadaX, auxY, auxZ);
            glVertex3f(auxX, auxY, auxZ);
			glEnd();

            auxX -= camadaX;
        }
        auxX = x;
        auxY -= camadaY;
    }
}

void drawSphere(float radius, int slices, int stacks) {

    float deltaPhi = M_PI / stacks;
    float deltaTheta = 2 * M_PI / slices;

    for (float i = -M_PI / 2; i <= M_PI / 2; i += deltaPhi) {

        float aux1 = i + deltaPhi;


        for (float j = 0; j <= 2 * M_PI; j += deltaTheta) {

            float aux2 = j + deltaTheta;

            glBegin(GL_LINE_LOOP);
			glColor3f(1,1,1); 
            glVertex3f(cos(aux1) * sin(j) * radius, sin(aux1) * radius, cos(aux1)* cos(j)* radius);
            glVertex3f(cos(i) * sin(j) * radius, sin(i) * radius, cos(i) * cos(j) * radius);
            glVertex3f(cos(i) * sin(aux2) * radius,sin(i) * radius, cos(i) * cos(aux2) * radius);
			glEnd();

            glBegin(GL_LINE_LOOP);
			glColor3f(1,1,0); 
            glVertex3f(cos(aux1) * sin(j) * radius, sin(aux1) * radius, cos(aux1)* cos(j)* radius);
            glVertex3f(cos(i) * sin(aux2) * radius, sin(i) * radius, cos(i)* cos(aux2)* radius);
            glVertex3f(cos(aux1) * sin(aux2) * radius, sin(aux1) * radius, cos(aux1)* cos(aux2)* radius);
			glEnd();
        }
    }
}


void drawCone(float radius, float height, int slices, int stacks) {

    float theta = 0;
    float nextTheta = 0;
    float delta = (2 * M_PI) / slices;
    float raio = radius / stacks;
    float alturas = height / stacks;
    int i, j;

    //fazer a circunferência da base
    for (i = 0; i < slices; i++) {

        nextTheta = theta + delta;

		glBegin(GL_TRIANGLES);
		glColor3f(1, i, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(radius * sin(nextTheta), 0, radius * cos(nextTheta));
        glVertex3f(radius * sin(theta), 0, cos(theta));
		glEnd();

        theta = nextTheta;
    }

    // Fazer as laterais
    float r1 = radius;
    float r2 = radius - raio;
    float alt1 = 0;
    float alt2 = alturas;
    theta = 0;
    nextTheta = 0;

    for (i = 0; i < slices; i++) {

        nextTheta += delta;

        for (j = 0; j < stacks; j++) {
			glBegin(GL_TRIANGLES);
			glColor3f(1, 1, 1);
            glVertex3f(r1 * sin(nextTheta), alt1, r1 * cos(nextTheta));
            glVertex3f(r2 * sin(nextTheta), alt2, r2 * cos(nextTheta));
            glVertex3f(r1 * sin(theta), alt1, r1 * cos(theta));
			glEnd();

			glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 1);
            glVertex3f(r2 * sin(nextTheta), alt2, r2 * cos(nextTheta));
            glVertex3f(r2 * sin(theta), alt2, r2 * cos(theta));
            glVertex3f(r1 * sin(theta), alt1, r1 * cos(theta));
			glEnd();

            r1 -= raio;
            r2 -= raio;
            alt1 += alturas;
            alt2 += alturas;
        }
        r1 = radius;
        r2 = radius - raio;
        alt1 = 0;
        alt2 = alturas;
        theta = nextTheta;
    }
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

    float camX = radiusCam * cos(betaCam) * sin(alphaCam);
    float camY = radiusCam * sin(betaCam);
    float camZ = radiusCam * cos(betaCam) * cos(alphaCam);
	
    gluLookAt(camX,camY,camZ,
		      0.0f,1.0f,0.0f,
			  0.0f,1.0f,0.0f); // altera aqui y

	//Eixo
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

	drawSphere(1,10,10);

	// End of frame
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here
	switch(key)
	{
		case GLUT_KEY_UP:
			betaCam += M_PI/8;
			break; 
		case GLUT_KEY_DOWN:
			betaCam -= M_PI/8; 
			break;
		case GLUT_KEY_LEFT:
			alphaCam += M_PI/8;
			break;
		case GLUT_KEY_RIGHT:
			alphaCam -= M_PI/8;
			break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Plane");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	//glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

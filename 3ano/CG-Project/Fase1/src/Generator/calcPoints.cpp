#define _USE_MATH_DEFINES
#include <cmath>

#include "calcPoints.hpp"

figure generate::calcPlane(float length, float divisions)
{
    figure plane;

    float len = length / 2;
    float aux = length / divisions;
    int i = 0, j=0;

    float auxX = -len;
    float auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            plane.addPoint(auxX, 0, auxZ);
            plane.addPoint(auxX + aux, 0, auxZ + aux);
            plane.addPoint(auxX + aux, 0, auxZ);

            plane.addPoint(auxX + aux, 0, auxZ + aux);
            plane.addPoint(auxX, 0, auxZ);
            plane.addPoint(auxX, 0, auxZ + aux);

            auxZ += aux;
        }
        auxZ = -len;
        auxX += aux;
    }

    return plane;
}

figure generate::calcBox(float length, float divisions)
{
    figure box;

    float len = length / 2;
    float camadaX = length / divisions;
    float camadaY = length / divisions;
    float camadaZ = length / divisions;
    int i = 0, j=0;

    // Desenhar a base
    float auxX = -len;
    float auxY = -len;
    float auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);

            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ);

            auxZ += camadaZ;
        }
        auxZ = -len;
        auxX += camadaX;
    }

    // Desenhar o teto
    auxX = -len;
    auxY = len;
    auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ);

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);
            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);

            auxZ += camadaZ;
        }
        auxZ = -len;
        auxX += camadaX;
    }

    // Desenhar o lado direito
    auxX = len;
    auxY = len;
    auxZ = len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ - camadaZ);

            box.addPoint(auxX, auxY - camadaY, auxZ - camadaZ);
            box.addPoint(auxX, auxY, auxZ - camadaZ);
            box.addPoint(auxX, auxY, auxZ);

            auxZ -= camadaZ;
        }
        auxZ = len;
        auxY -= camadaY;
    }

    // Desenhar o lado esquerdo
    auxX = -len;
    auxY = len;
    auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ + camadaZ);

            box.addPoint(auxX, auxY - camadaY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ);

            auxZ += camadaZ;
        }
        auxZ = -len;
        auxY -= camadaY;
    }

    // Desenhar frente
    auxX = -len;
    auxY = len;
    auxZ = len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX + camadaX, auxY - camadaY, auxZ);

            box.addPoint(auxX + camadaX, auxY - camadaY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ);

            auxX += camadaX;
        }
        auxX = -len;
        auxY -= camadaY;
    }

    // Desenhar trás
    auxX = len;
    auxY = len;
    auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX - camadaX, auxY - camadaY, auxZ);

            box.addPoint(auxX - camadaX, auxY - camadaY, auxZ);
            box.addPoint(auxX - camadaX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ);

            auxX -= camadaX;
        }
        auxX = len;
        auxY -= camadaY;
    }
    return box;
}

figure generate::calcSphere(float radius, int slices, int stacks)
{
    figure sphere;

    float deltaPhi = M_PI / stacks;
    float deltaTheta = 2 * M_PI / slices;

    for (int i = 0; i < stacks; i++) {

        float ii = - M_PI/2 + i * deltaPhi;
        float aux1 = ii + deltaPhi;


        for (int j = 0; j < slices; j++) {

            float jj = j * deltaTheta;
            float aux2 = jj + deltaTheta;

            //Triângulo 1
            sphere.addPoint(cos(aux1) * sin(jj) * radius, sin(aux1) * radius, cos(aux1)* cos(jj)* radius);
            sphere.addPoint(cos(ii) * sin(jj) * radius, sin(ii) * radius, cos(ii) * cos(jj) * radius);
            sphere.addPoint(cos(ii) * sin(aux2) * radius,sin(ii) * radius, cos(ii) * cos(aux2) * radius);

            //Triângulo 2
            sphere.addPoint(cos(aux1) * sin(jj) * radius, sin(aux1) * radius, cos(aux1)* cos(jj)* radius);
            sphere.addPoint(cos(ii) * sin(aux2) * radius, sin(ii) * radius, cos(ii)* cos(aux2)* radius);
            sphere.addPoint(cos(aux1) * sin(aux2) * radius, sin(aux1) * radius, cos(aux1)* cos(aux2)* radius);

        }
    }

    return sphere;
}

figure generate::calcCone(float radius, float height, int slices, int stacks)
{
    figure cone;

    float theta = 0;
    float nextTheta = 0;
    float delta = (2 * M_PI) / slices;
    float raio = radius / stacks;
    float alturas = height / stacks;
    int i, j;

    //fazer a circunferência da base
    for (i = 0; i < slices; i++) {

        nextTheta = theta + delta;

        cone.addPoint(0, 0, 0);
        cone.addPoint(radius * sin(nextTheta), 0, radius * cos(nextTheta));
        cone.addPoint(radius * sin(theta), 0, cos(theta));

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

            cone.addPoint(r1 * sin(nextTheta), alt1, r1 * cos(nextTheta));
            cone.addPoint(r2 * sin(nextTheta), alt2, r2 * cos(nextTheta));
            cone.addPoint(r1 * sin(theta), alt1, r1 * cos(theta));

            cone.addPoint(r2 * sin(nextTheta), alt2, r2 * cos(nextTheta));
            cone.addPoint(r2 * sin(theta), alt2, r2 * cos(theta));
            cone.addPoint(r1 * sin(theta), alt1, r1 * cos(theta));

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
    return cone;
}
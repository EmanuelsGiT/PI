#define _USE_MATH_DEFINES
#include <cmath>

#include "calcPoints.hpp"

figure generate::calcPlane(float length, float divisions)
{
    figure plane;

    float hor = 1.0f / 3.0f;
    float ver = 1.0f / 2.0f;

    float textH = hor / (float)divisions;
    float textV = ver / (float)divisions;
    int i, j;
    int indexCount = 0;
    
    float len = length / 2;
    float auxX = -len;
    float auxZ = -len;
    float tetoH = hor; 
    float tetoV = ver - textV;
    float tam = length / divisions;



    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            plane.addPoint(auxX + tam, 0, auxZ + tam);
            plane.addPoint(auxX + tam, 0, auxZ);
            plane.addPoint(auxX, 0, auxZ);
            plane.addPoint(auxX, 0, auxZ + tam);

            plane.addTexPoint(tetoH + textH, tetoV, 0);
            plane.addTexPoint(tetoH + textH, tetoV + textV, 0);
            plane.addTexPoint(tetoH, tetoV + textV, 0);
            plane.addTexPoint(tetoH, tetoV, 0);
            
            plane.addNormalPoint(0, 1, 0);
            plane.addNormalPoint(0, 1, 0);
            plane.addNormalPoint(0, 1, 0);
            plane.addNormalPoint(0, 1, 0);

            plane.indices.push_back(indexCount);
            plane.indices.push_back(indexCount + 1);
            plane.indices.push_back(indexCount + 2);

            
            plane.indices.push_back(indexCount + 2);
            plane.indices.push_back(indexCount + 3);
            plane.indices.push_back(indexCount);

            indexCount += 4;
            auxZ += tam;
            tetoV -= textV;
        }
        auxZ = -len;
        auxX += tam;
        
        tetoH += textH;
        tetoV = ver - textV;
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
    int i, j;
    int indexCount = 0;

    float hor = 1.0f / 3.0f;
    float ver = 1.0f / 2.0f;

    float textH = hor / (float)divisions;
    float textV = ver / (float)divisions;

    float baseH = 0;
    float baseV = 0;

    // Desenhar a base
    float auxX = -len;
    float auxY = -len;
    float auxZ = -len;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);

            box.addTexPoint(baseH, baseV, 0);
            box.addTexPoint(baseH + textH, baseV, 0);
            box.addTexPoint(baseH + textH, baseV + textV, 0);
            box.addTexPoint(baseH, baseV + textV, 0);
                   
            box.addNormalPoint(0, -1, 0);
            box.addNormalPoint(0, -1, 0);
            box.addNormalPoint(0, -1, 0);
            box.addNormalPoint(0, -1, 0);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount+1);
            box.indices.push_back(indexCount+2);

            box.indices.push_back(indexCount+2);
            box.indices.push_back(indexCount+3);
            box.indices.push_back(indexCount);

            indexCount += 4;
            auxZ += camadaZ;
            baseV += textV;
            
        }
        auxZ = -len;
        auxX += camadaX;
        baseH += textH;
        baseV = 0;
    }

    // Desenhar o teto
    auxX = -len;
    auxY = len;
    auxZ = -len;
    float tetoH = hor; 
    float tetoV = ver - textV;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {

            box.addPoint(auxX + camadaX, auxY, auxZ + camadaZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);

            box.addTexPoint(tetoH + textH, tetoV, 0);
            box.addTexPoint(tetoH + textH, tetoV + textV, 0);
            box.addTexPoint(tetoH, tetoV + textV, 0);
            box.addTexPoint(tetoH, tetoV, 0);
            
            box.addNormalPoint(0, 1, 0);
            box.addNormalPoint(0, 1, 0);
            box.addNormalPoint(0, 1, 0);
            box.addNormalPoint(0, 1, 0);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount + 1);
            box.indices.push_back(indexCount + 2);

            
            box.indices.push_back(indexCount + 2);
            box.indices.push_back(indexCount + 3);
            box.indices.push_back(indexCount);

            indexCount += 4;
            auxZ += camadaZ;
            tetoV -= textV;
        }
        auxZ = -len;
        auxX += camadaX;
        
        tetoH += textH;
        tetoV = ver - textV;
    }

    // Desenhar o lado direito
    auxX = len;
    auxY = len;
    auxZ = len;
    float dirH = hor*2;
    float dirV = ver - textV;;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ - camadaZ);
            box.addPoint(auxX, auxY, auxZ - camadaZ);

                    
            box.addTexPoint(dirH, dirV + textV, 0);
            box.addTexPoint(dirH, dirV, 0);
            box.addTexPoint(dirH + textH, dirV, 0);
            box.addTexPoint(dirH + textH, dirV + textV, 0);
            
            box.addNormalPoint(1, 0, 0);
            box.addNormalPoint(1, 0, 0);
            box.addNormalPoint(1, 0, 0);
            box.addNormalPoint(1, 0, 0);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount + 1);
            box.indices.push_back(indexCount + 2);                  

            box.indices.push_back(indexCount + 2);
            box.indices.push_back(indexCount + 3);
            box.indices.push_back(indexCount);


            indexCount += 4;
            auxZ -= camadaZ;
            dirH += textH;
        }
        auxZ = len;
        auxY -= camadaY;
        dirV -= textV;
        dirH = hor*2;
    }

    // Desenhar o lado esquerdo
    auxX = -len;
    auxY = len;
    auxZ = -len;
    float esqH = 0;
    float esqV = 1-textV;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ + camadaZ);
            box.addPoint(auxX, auxY, auxZ + camadaZ);

            box.addTexPoint(esqH, esqV + textV, 0);
            box.addTexPoint(esqH, esqV, 0);
            box.addTexPoint(esqH + textH, esqV, 0);
            box.addTexPoint(esqH + textH, esqV + textV, 0);
            
            box.addNormalPoint(-1, 0, 0);
            box.addNormalPoint(-1, 0, 0);
            box.addNormalPoint(-1, 0, 0);
            box.addNormalPoint(-1, 0, 0);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount + 1);
            box.indices.push_back(indexCount + 2);
                        

            box.indices.push_back(indexCount + 2);
            box.indices.push_back(indexCount + 3);
            box.indices.push_back(indexCount);

            
            
            indexCount += 4;
            auxZ += camadaZ;
            esqH += textH;
        }
        auxZ = -len;
        auxY -= camadaY;
        esqV -= textV;
        esqH = 0;
    }

    // Desenhar frente
    auxX = -len;
    auxY = len;
    auxZ = len;
    float frenteH = hor;
    float frenteV = 1-textV;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX + camadaX, auxY - camadaY, auxZ);
            box.addPoint(auxX + camadaX, auxY, auxZ);

            box.addTexPoint(frenteH, frenteV + textV, 0);
            box.addTexPoint(frenteH, frenteV, 0);
            box.addTexPoint(frenteH + textH, frenteV, 0);
            box.addTexPoint(frenteH + textH, frenteV + textV, 0);
            
            box.addNormalPoint(0, 0, 1);
            box.addNormalPoint(0, 0, 1);
            box.addNormalPoint(0, 0, 1);
            box.addNormalPoint(0, 0, 1);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount + 1);
            box.indices.push_back(indexCount + 2);            

            box.indices.push_back(indexCount + 2);
            box.indices.push_back(indexCount + 3);
            box.indices.push_back(indexCount);


            indexCount += 4;
            auxX += camadaX;
            frenteH += textH;
        }
        auxX = -len;
        auxY -= camadaY;
        frenteV -= textV;
        frenteH = hor;
    }

    // Desenhar trás
    auxX = len;
    auxY = len;
    auxZ = -len;
    float trasH = hor * 2;
    float trasV = 1-textV;
    for (i = 0; i < divisions; i++) {
        for (j = 0; j < divisions; j++) {
            box.addPoint(auxX, auxY, auxZ);
            box.addPoint(auxX, auxY - camadaY, auxZ);
            box.addPoint(auxX - camadaX, auxY - camadaY, auxZ);
            box.addPoint(auxX - camadaX, auxY, auxZ);

            box.addTexPoint(trasH, trasV + textV, 0);
            box.addTexPoint(trasH, trasV, 0);
            box.addTexPoint(trasH + textH, trasV, 0);
            box.addTexPoint(trasH + textH, trasV + textV, 0);

            box.addNormalPoint(0, 0, -1);
            box.addNormalPoint(0, 0, -1);
            box.addNormalPoint(0, 0, -1);
            box.addNormalPoint(0, 0, -1);

            box.indices.push_back(indexCount);
            box.indices.push_back(indexCount + 1);
            box.indices.push_back(indexCount + 2);            
            
            box.indices.push_back(indexCount + 2);
            box.indices.push_back(indexCount + 3);
            box.indices.push_back(indexCount);

            

            indexCount += 4;
            auxX -= camadaX;
            trasH += textH;
        }
        auxX = len;
        auxY -= camadaY;
        trasV -= textV;
        trasH = hor * 2;
    }
    return box;
}

figure generate::calcSphere(float radius, int slices, int stacks)
{
    figure sphere;

    float delta1 = (float)M_PI / stacks;
    float delta2 = 2 * (float)M_PI / slices;
    float theta1 = -(float)M_PI / 2;
    float theta2 = 0.0f;
    int indexCount = 0;
    float textH = 1.0f / (float)slices;
    float textV = 1.0f / (float)stacks;

    for (int i = 0; i < stacks; i++) {

        for (int j = 0; j < slices; j++) {
            theta2 = j * delta2;
            sphere.addPoint(cos(theta1 + delta1) * sin(theta2) * radius, sin(theta1 + delta1) * radius, cos(theta1 + delta1) * cos(theta2) * radius);
            sphere.addPoint(cos(theta1) * sin(theta2) * radius, sin(theta1) * radius, cos(theta1) * cos(theta2) * radius);
            sphere.addPoint(cos(theta1) * sin(theta2 + delta2) * radius, sin(theta1) * radius, cos(theta1) * cos(theta2 + delta2) * radius);
            sphere.addPoint(cos(theta1 + delta1) * sin(theta2 + delta2) * radius, sin(theta1 + delta1) * radius, cos(theta1 + delta1) * cos(theta2 + delta2) * radius);

            sphere.addNormalPoint(cos(theta1 + delta1) * sin(theta2), sin(theta1 + delta1), cos(theta1 + delta1) * cos(theta2));
            sphere.addNormalPoint(cos(theta1) * sin(theta2), sin(theta1), cos(theta1) * cos(theta2));
            sphere.addNormalPoint(cos(theta1) * sin(theta2 + delta2), sin(theta1), cos(theta1) * cos(theta2 + delta2));
            sphere.addNormalPoint(cos(theta1 + delta1) * sin(theta2 + delta2), sin(theta1 + delta1), cos(theta1 + delta1) * cos(theta2 + delta2));
            
            sphere.addTexPoint(j * textH, i * textV + textV, 0);
            sphere.addTexPoint(j * textH, i * textV, 0);
            sphere.addTexPoint(j * textH + textH, i * textV, 0);
            sphere.addTexPoint(j * textH + textH, i * textV + textV, 0);
            

            //Triângulo 1
            sphere.indices.push_back(indexCount);
            sphere.indices.push_back(indexCount + 1);
            sphere.indices.push_back(indexCount + 2);
                                 

            //Triângulo 2
            sphere.indices.push_back(indexCount );
            sphere.indices.push_back(indexCount + 2);
            sphere.indices.push_back(indexCount + 3);

            indexCount += 4;
        }
        theta1 += delta1;
    }

    return sphere;
}

figure generate::calcCone(float radius, float height, int slices, int stacks)
{
    figure cone;

    float theta = 0;
    float nextTheta = 0;
    float delta = (2 *(float) M_PI) / slices;
    float raio = radius / stacks;
    float alturas = height / stacks;
    int i, j;
    int indexCount = 0;

    float textH = 1.0f / slices;
    float textV = 1.0f / stacks;

    float var = (2 * radius * (float)M_PI) / slices;
    //fazer o circulo da base
    for (i = 0; i < slices; i++) {

        nextTheta = theta + delta;

        cone.addPoint(0, 0, 0);
        cone.addPoint(radius * sin(nextTheta), 0, radius * cos(nextTheta));
        cone.addPoint(radius * sin(theta), 0, radius * cos(theta));

        cone.indices.push_back(indexCount);
        cone.indices.push_back(indexCount + 1);
        cone.indices.push_back(indexCount + 2);

        cone.addNormalPoint(0, -1, 0);
        cone.addNormalPoint(0, -1, 0);
        cone.addNormalPoint(0, -1, 0);

        cone.addTexPoint(var / 2, 1, 0);
        cone.addTexPoint(i * var, 0, 0);
        cone.addTexPoint((i + 1) * var, 0, 0);
        

        theta = nextTheta;
        indexCount += 3;
    }

    // Fazer as laterais
    float r1 = radius;
    float r2 = radius - raio;
    float alt1 = 0;
    float alt2 = alturas;
    theta = 0;
    
    nextTheta = 0;

    float ny = cos(atan(height / radius));

    for (i = 0; i < slices; i++) {

        nextTheta += delta;

        for (j = 0; j < stacks; j++) {
            cone.addPoint(r1 * sin(nextTheta), alt1, r1 * cos(nextTheta));
            cone.addPoint(r2 * sin(nextTheta), alt2, r2 * cos(nextTheta));
            cone.addPoint(r1 * sin(theta), alt1, r1 * cos(theta));
            cone.addPoint(r2 * sin(theta), alt2, r2 * cos(theta));

            cone.addTexPoint((i + 1) * textH, j * textV, 0);
            cone.addTexPoint((i + 1) * textH, (j + 1) * textV, 0);
            cone.addTexPoint(i * textH, j * textV, 0);
            cone.addTexPoint(i * textH, (j + 1) * textV, 0);

            cone.addNormalPoint(sin(nextTheta), ny, cos(nextTheta));
            cone.addNormalPoint(sin(nextTheta), ny, cos(nextTheta));
            cone.addNormalPoint(sin(theta), ny, cos(theta));
            cone.addNormalPoint(sin(theta), ny, cos(theta));

            cone.indices.push_back(indexCount);
            cone.indices.push_back(indexCount + 1);
            cone.indices.push_back(indexCount + 2);

            cone.indices.push_back(indexCount + 1);
            cone.indices.push_back(indexCount + 3);
            cone.indices.push_back(indexCount + 2);


            r1 -= raio;
            r2 -= raio;
            alt1 += alturas;
            alt2 += alturas;
            indexCount+=4;
        }
        r1 = radius;
        r2 = radius - raio;
        alt1 = 0;
        alt2 = alturas;
        theta = nextTheta;
    }
    return cone;
}

figure generate::calcTorus(float radius_in, float radius_out, int slices, int stacks)
{
    figure torus;

    float delta1 = 2 *(float)M_PI / slices;
    float delta2 = 2 * (float)M_PI / stacks;
    float phi = 0;
    float theta = 0;
    int indexCount = 0;

    float textH = 1.0f / slices;
    float textV = 1.0f / stacks;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            torus.addPoint((radius_in + radius_out * cos(phi)) * cos(theta), (radius_in + radius_out * cos(phi)) * sin(theta), radius_out * sin(phi));
            torus.addPoint((radius_in + radius_out * cos(phi)) * cos(theta + delta1), (radius_in + radius_out * cos(phi)) * sin(theta + delta1), radius_out * sin(phi));
            torus.addPoint((radius_in + radius_out * cos(phi + delta2)) * cos(theta + delta1), (radius_in + radius_out * cos(phi + delta2)) * sin(theta + delta1), radius_out * sin(phi + delta2));
            torus.addPoint((radius_in + radius_out * cos(phi + delta2)) * cos(theta), (radius_in + radius_out * cos(phi + delta2)) * sin(theta), radius_out * sin(phi + delta2));
            
            torus.addTexPoint(i * textH, j * textV, 0);
            torus.addTexPoint((i + 1) * textH, j * textV, 0);
            torus.addTexPoint((i + 1) * textH, (j + 1) * textV, 0);
            torus.addTexPoint(i * textH, (j + 1) * textV, 0);
            
            torus.addNormalPoint(cos(phi) * cos(theta), cos(phi) * sin(theta), sin(phi));
            torus.addNormalPoint(cos(phi) * cos(theta + delta1), cos(phi) * sin(theta + delta1), sin(phi));
            torus.addNormalPoint(cos(phi + delta2) * cos(theta + delta1), cos(phi + delta2) * sin(theta + delta1), sin(phi + delta2));
            torus.addNormalPoint(cos(phi + delta2) * cos(theta), cos(phi + delta2) * sin(theta), sin(phi + delta2));
            
            torus.indices.push_back(indexCount);
            torus.indices.push_back(indexCount + 1);
            torus.indices.push_back(indexCount + 2);

            torus.indices.push_back(indexCount + 2);
            torus.indices.push_back(indexCount + 3);
            torus.indices.push_back(indexCount);


            indexCount += 4;
            phi = delta2 * (j + 1);
        }

        theta = delta1 * (i + 1);
    }


    return torus;
}

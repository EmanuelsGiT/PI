#include "../tinyXML/tinyxml.h"
#include "calcPoints.hpp"
#include "bezier.hpp"
#include <cstdio>

using namespace std;
using namespace generate;


int write3D(figure figure, char *namefile)
{
    fstream file;
    char path[30] = "../out/";
    strcat(path,namefile);

    // in out(write) mode
    // ios::out Open for output operations.
    file.open(path,ios::out);
    for(point p : figure.pontos){
        file << p.x << " ";
        file << p.y << " ";
        file << p.z << " ";
        file << "\n";
    }

    if(!file){
        printf("\n Error in creating file!!!\n");
        return -1;
    }
    printf("File created successfully.\n");
    file.close();
    return 0;
}

figure readBezier(char* namefile, int t) {
    fstream file;
    char path[30] = "../out/";
    strcat(path,namefile);
    file.open(path,ios::in);
    std::string line;      // String auxiliar que irá corresponder a uma 
    int nPatches = 0;
    size_t linhaNum = 0;
    std::string delimiter = ",";

    figure auxVertices;
    std::vector<size_t> auxIndices;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (linhaNum == 0) {
                nPatches = atoi(line.c_str());
                printf("numPatches: %d\n",nPatches);
            }
            if (linhaNum >= 1 && linhaNum <= nPatches) {
                std::string token;
                size_t pos = 0;
                std::istringstream tokenizer(line);
                for (size_t i = 0; i < 15; i++) {
                    std::getline(tokenizer, token, ',');
                    auxIndices.push_back(stof(token));
                }
                std::getline(tokenizer, token);
                auxIndices.push_back(stof(token));
            }
            if (linhaNum > nPatches + 1) {
                std::string token;
                size_t pos = 0;
                size_t i = 0;
                float coord[3];
                string tokens[3];
                std::istringstream tokenizer(line);

                std::getline(tokenizer, tokens[0], ','); // then get the tokens from it
                std::getline(tokenizer, tokens[1], ',');
                std::getline(tokenizer, tokens[2]);

                auxVertices.addPoint(stof(tokens[0]), stof(tokens[1]), stof(tokens[2]));
                
            }
            linhaNum++;
        }
    }
    else {
        printf("File not found\n");
        figure fig;
        return fig;
    }
    file.close();
    
    
    figure fig = bezier::generateBezierPatches(auxVertices, auxIndices, t);

    return fig;
}

int main(int argc, char* argv[])
{
    figure fig;

    if (argc<2 || argc>7) printf("Cuidado com os argumentos! Digite 'help' para ajuda.\n");
    else
    {
        //Gerar os vertices para o desenho do plano e transcrever para o ficheiro .3d
        if (strcmp(argv[1],"plane") == 0 && argc == 5)
        {
            float length = atof(argv[2]);
            float divisions = atof(argv[3]);
            fig = calcPlane(length, divisions);
            if (write3D(fig,argv[4])) 
                printf("Plane writen successfuly!\n");

        }
        //Gerar os vértices para o desenho da caixa e transcrever para o ficheiro .3d
        else if (strcmp(argv[1],"box") == 0 && argc == 5)
        {
            float length = atof(argv[2]);
            float divisions = atof(argv[3]);
            fig = calcBox(length, divisions);
            if (write3D(fig,argv[4])) 
                printf("Box writen successfuly!\n");

        }
        //Gerar os vértices para o desenho da caixa e transcrever para o ficheiro .3d
        else if (strcmp(argv[1],"sphere") == 0 && argc == 6)
        {
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int stacks = atoi(argv[4]);
            fig = calcSphere(radius, slices, stacks);
            if (write3D(fig,argv[5])) 
                printf("Sphere writen successfuly!\n");
        }
        else if (strcmp(argv[1],"cone") == 0 && argc == 7)
        {
            float radius = atof(argv[2]);
            float height = atof(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            fig = calcCone(radius, height, slices, stacks);
            if (write3D(fig,argv[6])) 
                printf("Cone writen successfuly!\n");
        }
        else if (strcmp(argv[1],"bezier") == 0 && argc == 5)
        {
            int tecelation = atoi(argv[3]);
            fig = readBezier(argv[2], tecelation);
            if (write3D(fig,argv[4])) 
                printf("Bezier writen successfuly!\n");
        }
        else if (strcmp(argv[1],"help") == 0)
        {
            printf("Exemplos de Comandos Possíveis:\n");
            printf("- generator sphere 1(radius) 10(slices) 10(stacks) sphere.3d(file.3d)\n");
            printf("- generator box 2(length) 3(divisions) box.3d(file.3d)\n");
            printf("- generator cone 1(radius) 2(slices) 4(height) 3(stacks) cone.3d(file.3d)\n");
            printf("- generator plane 1(length) 3(divisions) plane.3d(file.3d)\n");
            printf("- generator bezier teapot.patch(patchfile) 2(tecelation) bezier.3d(file.3d)\n");
        }
    }
    return 0;
}
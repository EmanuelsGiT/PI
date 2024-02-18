#include "calcPoints.hpp"
#include "../tinyXML/tinyxml.h"

using namespace std;
using namespace generate;


int write3D(figure figure, char *namefile)
{
    fstream file;
    char path[100] = "../out/";
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
        cout<<"\n       Error in creating file!!!\n";
        return -1;
    }
    cout<<"File created successfully.\n";
    file.close();
    return 0;
}

int main(int argc, char* argv[])
{
    figure fig;

    if (argc<2) printf("Faltam argumentos! Digite 'help' para ajuda.\n");
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
        else if (strcmp(argv[1],"help") == 0)
        {
            printf("Exemplos de Comandos Possíveis:\n");
            printf("- generator sphere 1(radius) 10(slices) 10(stacks) sphere.3d(file.3d)\n");
            printf("- generator box 2(length) 3(divisions) box.3d(file.3d)\n");
            printf("- generator cone 1(radius) 2(slices) 4(height) 3(stacks) cone.3d(file.3d)\n");
            printf("- generator plane 1(length) 3(divisions) plane.3d(file.3d)\n");
        }
    }
    return 0;
}
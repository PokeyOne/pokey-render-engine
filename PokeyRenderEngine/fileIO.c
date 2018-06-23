//
//  fileIO.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-06-12.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "fileIO.h"

/*
 Loads scene from custom file. STIL IN PROGRESS AND NOT IN USE
 */
FileResult loadFile(char* filePath) {
    FILE *input = fopen(filePath, "r");
    
    char colourString[256];
    char vertexString[256];
    char triangleString[256];
    long colourAmo, vertexAmo, triangleAmo;
    int currentColourIndex = 0;
    int currentVertexIndex = 0;
    int currentTriangleIndex = 0;
    
    fscanf(input, "%s %s %s", colourString, vertexString, triangleString);
    //colourAmo = strtol(colourString);
    
    bool done = false;
    while(!done){
        char c = fgetc(input);
        switch (c) {
            case PKRNDR_COLOUR_COMMAND:
                {
                    char red[3];
                    char green[3];
                    char blue[3];
                    fscanf(input, "%s %s %s", red, green, blue);
                }
                break;
            case PKRNDR_VERTEX_COMMAND:
                //TODO
                break;
            case PKRNDR_TRIANGLE_COMMAND:
                //TODO
                break;
            default:
                break;
        }
    }
    
    return (FileResult){};
}

//
//  fileIO.h
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-06-12.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#ifndef fileIO_h
#define fileIO_h

#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"
#include "pkBoolean.h"

#define PKRNDR_COLOUR 0
#define PKRNDR_VERTEX 1
#define PKRNDR_TRIANGLE 2

#define PKRNDR_COLOUR_COMMAND 'c'
#define PKRNDR_VERTEX_COMMAND 'v'
#define PKRNDR_TRIANGLE_COMMAND 't'

typedef struct FileResult {
    size_t len;
    Triangle triangles[];
} FileResult;

FileResult loadFile(char* filePath);

#endif /* fileIO_h */

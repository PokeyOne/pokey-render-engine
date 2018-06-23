//
//  vectors.h
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-04-21.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#ifndef vectors_h
#define vectors_h

#include <stdio.h>
#include <math.h>
#include "pkmathutil.h"

typedef struct Colour {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Colour;

typedef struct PKPoint {
    double x;
    double y;
    double z;
} PKPoint;

typedef struct PKPoint Vec3D;

#define ZERO_VECTOR (Vec3D){0, 0, 0}

typedef struct Vec2D {
    double x;
    double y;
} Vec2D;

typedef struct Triangle {
    PKPoint points[3];
    Colour colour;
    Vec3D normal;
} Triangle;

typedef struct Object3D {
    size_t len;
    Triangle triangles[];
} Object3D;

PKPoint constructPKPoint(double x, double y, double z);
Vec3D constructVec3D(double x, double y, double z);
Triangle constructTriangle(PKPoint points[3]);
Vec3D getTriangleCentre(Triangle triangle);

double vectorMagnitude(Vec3D v);
double radAngleBetweenVectors(Vec3D a, Vec3D b);
Vec3D unitVector(Vec3D a);
Vec3D vectorNormalize(Vec3D a);
Vec3D vectorAbs(Vec3D a);
Vec3D vectorAdd(Vec3D a, Vec3D b);
Vec3D vectorSubtract(Vec3D a, Vec3D b);
Vec3D vectorDivide(Vec3D a, Vec3D b);
Vec3D vectorCrossProduct(Vec3D a, Vec3D b);
double vectorDotProduct(Vec3D a, Vec3D b);
Vec3D vectorDoubleMultiply(double a, Vec3D b);
Vec3D calculateTriangleNormal(Triangle triangle);

void printVector(Vec3D vec);

#endif /* vectors_h */

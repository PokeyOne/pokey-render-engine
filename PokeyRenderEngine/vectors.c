//
//  vectors.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-04-21.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "vectors.h"

PKPoint constructPKPoint(double x, double y, double z){
    PKPoint result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Vec3D getTriangleCentre(Triangle triangle) {
    double largestX = triangle.points[0].x, largestY = triangle.points[0].y, largestZ = triangle.points[0].z;
    double smallestX = triangle.points[0].x, smallestY = triangle.points[0].y, smallestZ = triangle.points[0].z;
    
    for(int i = 1; i < 3; i++){
        //curent point
        Vec3D *cp = &triangle.points[i];
        
        if(cp->x > largestX){
            largestX = cp->x;
        }
        if(cp->y > largestY){
            largestY = cp->y;
        }
        if(cp->z > largestZ){
            largestZ = cp->z;
        }
        
        if(cp->x < smallestX){
            smallestX = cp->x;
        }
        if(cp->y < smallestY){
            smallestY = cp->y;
        }
        if(cp->z < smallestZ){
            smallestZ = cp->z;
        }
    }
    
    return (Vec3D){(smallestX + largestX)/2, (smallestY + largestY)/2, (smallestZ + largestZ)/2};
}

double radAngleBetweenVectors(Vec3D a, Vec3D b) {
    return acos(vectorDotProduct(a, b)/(vectorMagnitude(a) * vectorMagnitude(b)));
}

double vectorMagnitude(Vec3D v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vec3D vectorNormalize(Vec3D a){
    Vec3D abs = vectorAbs(a);
    Vec3D result = {.x = 0.0, .y = 0.0, .z = 0.0};
    
    if(a.x != 0.0){
        result.x = a.x/abs.x;
    }
    
    if(a.y != 0.0){
        result.y = a.y/abs.y;
    }
    
    if(a.z != 0.0){
        result.z = a.z/abs.z;
    }
    
    return result;
}

Vec3D unitVector(Vec3D a){
    double denom = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
    return (Vec3D){.x = a.x/denom, .y = a.y/denom, .z = a.z/denom};
}

Triangle constructTriangle(PKPoint points[3]){
    Triangle result = {.points = *points};
    return result;
}

Vec3D vectorAbs(Vec3D a){
    return (Vec3D){.x = absd(a.x), .y = absd(a.y), .z = absd(a.z)};
}

Vec3D vectorSubtract(Vec3D a, Vec3D b){
    Vec3D result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    //printf("subtraction of (%f, %f, %f) and (%f, %f, %f) is (%f, %f, %f)\n", a.x, a.y, a.z, b.x, b.y, b.z, result.x, result.y, result.z);
    return result;
}

Vec3D vectorAdd(Vec3D a, Vec3D b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vec3D vectorDivide(Vec3D a, Vec3D b){
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

Vec3D vectorCrossProduct(Vec3D a, Vec3D b){
    Vec3D vector = {.x = a.y*b.z-a.z*b.y, .y = a.z*b.x-a.x*b.z, .z = a.x*b.y-a.y*b.x};
    //printf("cross product of (%f, %f, %f) and (%f, %f, %f) is (%f, %f, %f)\n", a.x, a.y, a.z, b.x, b.y, b.z, vector.x, vector.y, vector.z);
    return vector;
}

double vectorDotProduct(Vec3D a, Vec3D b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3D vectorDoubleMultiply(double a, Vec3D b) {
    b.x *= a;
    b.y *= a;
    b.z *= a;
    return b;
}

void printVector(Vec3D vec) {
    printf("x: %f, y: %f, z: %f", vec.x, vec.y, vec.z);
}

Vec3D calculateTriangleNormal(Triangle triangle){
    Vec3D v1 = vectorSubtract(triangle.points[1], triangle.points[0]);
    Vec3D v2 = vectorSubtract(triangle.points[2], triangle.points[0]);
    return vectorCrossProduct(v1, v2);
}


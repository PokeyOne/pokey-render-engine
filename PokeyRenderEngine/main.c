//
//  main.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-04-17.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "distance.h"
#include "vectors.h"
#include "pkBoolean.h"
#include "animation.h"
#include "lights.h"

#define IS_DEBUG 0
#define FULL_LIGHT 10.0

typedef struct RayResult {
    bool didHitAnything;
    double distance;
    Vec3D pointOfHit3D;
    Colour colour;
} RayResult;

RayResult calculateRay(Vec3D origin, Vec3D point, size_t len, Triangle triangles[], size_t lightLength, Light lights[]){
    
    bool hasHitSomething = false;
    double distanceOfShortestHit = 0;
    Vec3D pointOfHit3D = {};
    int indexOfTriangle = 0;
    
    for(int i = 0; i < len; i++){
        if(IS_DEBUG)
            printf("Processing triangle with points (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n", triangles[i].points[0].x, triangles[i].points[0].y, triangles[i].points[0].z, triangles[i].points[1].x, triangles[i].points[1].y, triangles[i].points[1].z, triangles[i].points[2].x, triangles[i].points[2].y, triangles[i].points[2].z);
        Vec3D direction = unitVector(vectorSubtract(point, origin));
        
        //Test if triangle is parallel
        if(vectorDotProduct(triangles[i].normal, direction) == 0){
            continue;
        }
        
        double d = vectorDotProduct(triangles[i].normal, triangles[i].points[0]);
        double t = (vectorDotProduct(triangles[i].normal, origin) + d)/(vectorDotProduct(triangles[i].normal, direction));
        Vec3D poi = vectorAdd(origin, vectorDoubleMultiply(t, direction));
        
        //printf("poi = %f, %f, %f; tri index = %i\n", poi.x, poi.y, poi.z, indexOfTriangle);
        
        //test if triangle is behind ray
        if(t <= 1){
            continue;
        }
        
        Vec3D edge0 = vectorSubtract(triangles[i].points[1], triangles[i].points[0]);
        Vec3D edge1 = vectorSubtract(triangles[i].points[2], triangles[i].points[1]);
        Vec3D edge2 = vectorSubtract(triangles[i].points[0], triangles[i].points[2]);
        
        Vec3D c0 = vectorCrossProduct(edge0, vectorSubtract(poi, triangles[i].points[0]));
        Vec3D c1 = vectorCrossProduct(edge1, vectorSubtract(poi, triangles[i].points[1]));
        Vec3D c2 = vectorCrossProduct(edge2, vectorSubtract(poi, triangles[i].points[2]));
        
        bool collide = !(vectorDotProduct(triangles[i].normal, c0) < 0 ||
                        vectorDotProduct(triangles[i].normal, c1) < 0 ||
                        vectorDotProduct(triangles[i].normal, c2) < 0);
        
        if(collide && (hasHitSomething == false || t < distanceOfShortestHit)){
            distanceOfShortestHit = t;
            hasHitSomething = true;
            pointOfHit3D = poi;
            indexOfTriangle = i;
        }
        
        //printf("vec2m1 = (%f, %f, %f)\nvec3m1 = (%f, %f, %f)\nunitvectorU & V = (%f, %f, %f) & (%f, %f, %f)\nTriangle = [(%f, %f), (%f, %f), (%f, %f)]\nintersection2D = %f, %f\n", vec2m1.x, vec2m1.y, vec2m1.z, vec3m1.x, vec3m1.y, vec3m1.z, unitVectorU.x, unitVectorU.y, unitVectorU.z, unitVectorV.x, unitVectorV.y, unitVectorV.z, tri2D[0].x, tri2D[0].y, tri2D[1].x, tri2D[1].y, tri2D[2].x, tri2D[2].y, intersection2D.x, intersection2D.y);
    }
    
    //TODO: calculate real colour
    Colour colour;
    if(hasHitSomething){
        colour = triangles[indexOfTriangle].colour;
        /* Removing lighting system because needs to be severely rethought
        double percentageLight = 0.0;
        for(int q = 0; q < lightLength; q++){
            percentageLight += lightLevel(lights[q], pointOfHit3D, triangles[indexOfTriangle]) / FULL_LIGHT;
        }
        if(percentageLight > 1.0){
            percentageLight = 1.0;
        }
        
        //printf("rgb = %i %i %i\n percentageLight = %f\n", colour.red, colour.green, colour.blue, percentageLight);
        colour.red *= percentageLight;
        colour.green *= percentageLight;
        colour.blue *= percentageLight;
        //printf("rgb2 = %i %i %i\n", colour.red, colour.green, colour.blue);
        */
        if(IS_DEBUG)
            printf("----pointOfHit3D = %f, %f, %f; tri index = %i\n", pointOfHit3D.x, pointOfHit3D.y, pointOfHit3D.z, indexOfTriangle);
    }else{
        colour = (Colour){0, 0, 0};
    }
    
    return (RayResult){.didHitAnything = hasHitSomething, .distance = distanceOfShortestHit, .pointOfHit3D = pointOfHit3D, .colour = colour};
}

int main(int argc, const char * argv[]) {
    Vec3D eyeLocation = {.x = 0, .y = 0, .z = 0};
    //double eyeRotation[3] = {0, 0, 0}; //TODO: inlcude eye rotation in calculations (tile camera or whole screen)
    double screenDistance = 2.0;
    int screenDimensions[2] = {400, 400};
    double pixelSize = 0.01;
    size_t triangleLen = 8;
    Triangle triangles[8] = {
        //FRONT
        {
            .points = {
                {.x = -5, .y = -5, .z = 15},
                {.x = -5, .y = 5, .z = 15},
                {.x = 5, .y = -5, .z = 15}
            },
            .colour = {0xFF, 0x00, 0x00}
        },
        {
            .points = {
                {.x = -5, .y = 5, .z = 15},
                {.x = 5, .y = 5, .z = 15},
                {.x = 5, .y = -5, .z = 15}
            },
            .colour = {0xFF, 0x00, 0x00}
        },
        
        //TOP
        {
            .points = {
                {.x = -5, .y = -5, .z = 15},
                {.x = -5, .y = -5, .z = 20},
                {.x = -5, .y = 5, .z = 20}
            },
            .colour = {0x00, 0xFF, 0x00}
        },
        
        {
            .points = {
                {.x = -5, .y = 5, .z = 15},
                {.x = -5, .y = -5, .z = 15},
                {.x = -5, .y = 5, .z = 20}
            },
            .colour = {0x00, 0xFF, 0x00}
        },
        
        //Bottom
        {
            .points = {
                {.x = 5, .y = -5, .z = 15},
                {.x = 5, .y = -5, .z = 20},
                {.x = 5, .y = 5, .z = 20}
            },
            .colour = {0x00, 0xFF, 0xFF}
        },
        
        {
            .points = {
                {.x = 5, .y = 5, .z = 15},
                {.x = 5, .y = -5, .z = 15},
                {.x = 5, .y = 5, .z = 20}
            },
            .colour = {0x00, 0xFF, 0xFF}
        },
        
        //BACK
        {
            .points = {
                {.x = -5, .y = 5, .z = 20},
                {.x = -5, .y = -5, .z = 20},
                {.x = 5, .y = -5, .z = 20}
            },
            .colour = {0x00, 0x00, 0xFF}
        },
        {
            .points = {
                {.x = -5, .y = 5, .z = 20},
                {.x = 5, .y = -5, .z = 20},
                {.x = 5, .y = 5, .z = 20}
            },
            .colour = {0x00, 0x00, 0xFF}
        },
    };
    
    //Precalculate triangle normals
    for(int tri = 0; tri < triangleLen; tri++){
        triangles[tri].normal = calculateTriangleNormal(triangles[tri]);
    }
    
    KeyFrame keyframes[10] = {
        {
            .translation = {-10, 0, 0},
            .frame = 0
        },
        {
            .translation = {10, 0, 0},
            .frame = 100
        },
        {
            .translation = {10, 10, 10},
            .frame = 117
        },
        {
            .translation = {-10, -10, 10},
            .frame = 130
        },
        {
            .translation = {0, 0, 10},
            .frame = 150
        },
        {
            .translation = {0, 0, 0},
            .frame = 160
        },
        {
            .translation = {0, 0, 10},
            .frame = 170
        },
        {
            .translation = {0, 0, 0},
            .frame = 180
        },
        {
            .translation = {0, 0, 10},
            .frame = 190
        },
        {
            .translation = {0, 0, 0},
            .frame = 200
        }
    };
    int frameEnd = 250;
    
    Light lights[1] = {
        {
            .lightType = PointLight,
            .strength = 10.0,
            .location = {0, 0, 0},
            .direction = {0, 0, 0}
        }
    };
    
    for(int frame = 0; frame <= frameEnd; frame++){
        
        printf("frame %03i\n", frame);
        
        Vec3D translation = calculateTranslation(sizeof(keyframes)/sizeof(keyframes[0]), keyframes, frame);
        
        RayResult pixels[screenDimensions[0]][screenDimensions[1]];
        
        Triangle trianglesCopy[triangleLen];
        for(int i = 0; i < triangleLen; i++){
            for(int j = 0; j < 3; j++){
                trianglesCopy[i].points[j] = vectorAdd(triangles[i].points[j], translation);
                trianglesCopy[i].colour = triangles[i].colour;
                trianglesCopy[i].normal = triangles[i].normal;
            }
        }
        
        for(int x = 0; x < screenDimensions[0]; x++){
            for(int y = 0; y < screenDimensions[1]; y++){
                Vec3D pixelLocation = {.x = pixelSize*(0-(screenDimensions[0]/2-x)), .y = pixelSize*(0-(screenDimensions[1]/2-y)), .z = screenDistance};
                pixels[x][y] = calculateRay(eyeLocation, pixelLocation, sizeof(trianglesCopy)/sizeof(trianglesCopy[0]), trianglesCopy, sizeof(lights)/sizeof(lights[0]), lights);
                //pixels[x][y] = calculateRayForTriangle(eyeLocation, pixelLocation, 1, 0, 5, -1, 0, 5, -1, 5, 10);
            }
        }
        
        char fileName[14];
        sprintf(fileName, "frame%04i.ppm", frame);
        FILE *fp = fopen(fileName, "wb");
        fprintf(fp, "P6 %i %i 255\n", screenDimensions[0], screenDimensions[1]);
        
        for(int x = 0; x < screenDimensions[0]; x++){
            for(int y = 0; y < screenDimensions[1]; y++){
                //printf("|%i", pixels[x][y].didHitAnything);
                fprintf(fp, "%c%c%c", pixels[x][y].colour.red, pixels[x][y].colour.green, pixels[x][y].colour.blue);
            }
            //printf("\n");
        }
        
        fclose(fp);
    }
    
    return 0;
}

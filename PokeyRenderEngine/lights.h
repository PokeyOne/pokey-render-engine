//
//  lights.h
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-05-12.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#ifndef lights_h
#define lights_h

#define LIGHT_DECAY_RATE 0.05

#include <stdio.h>
#include <math.h>
#include "vectors.h"
#include "distance.h"

typedef enum {
    PointLight
} LightType;

typedef struct Light {
    LightType lightType;
    double strength;
    Vec3D location;
    Vec3D direction;
} Light;

Light basicPointLight(Vec3D location);
double lightLevel(Light light, Vec3D intersectionPoint, Triangle triangle);

#endif /* lights_h */

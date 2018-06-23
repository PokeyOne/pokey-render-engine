//
//  lights.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-05-12.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "lights.h"

Light basicPointLight(Vec3D location) {
    return (Light){.lightType = PointLight, .strength = 1.0, .location = location, .direction = {0, 0, 1}};
}

double lightLevel(Light light, Vec3D intersectionPoint, Triangle triangle) {
    double distance = calculateDistance_p(light.location, intersectionPoint);
    double lightLevelAtIntersection = light.strength - (LIGHT_DECAY_RATE * distance);
    
    /*
    double rad = radAngleBetweenVectors(triangle.normal, vectorSubtract(light.location, getTriangleCentre(triangle)));
    //TODO calculate so percent is closeness from staight to parrallel
    
    if(lightLevelAtIntersection > 0){
        double per = 0;
        if(rad >= 0){
            if(rad <= 0.5){
                per = percentage(0.5, 0, rad);
            }else{
                per = percentage(0.5, 1, rad);
            }
        }else{
            if(rad >= -0.5){
                per = percentage(-0.5, 0, rad);
            }else{
                per = percentage(-0.5, -1, rad);
            }
        }
        return per * lightLevelAtIntersection;
    }else{
        return 0;
    }*/
    if(lightLevelAtIntersection > 0){
        return lightLevelAtIntersection;
    }else{
        return 0;
    }
}

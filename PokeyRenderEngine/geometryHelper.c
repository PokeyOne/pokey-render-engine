//
//  geometryHelper.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-05-18.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "geometryHelper.h"

Object3D makeCube(Vec3D size, Vec3D location){
    Vec3D points[8] = {
        {-0.5, 0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5}
    };
    
    for(int i = 0; i < 8; i++){
        points[i].x = size.x * points[i].x + location.x;
        points[i].y = size.y * points[i].y + location.y;
        points[i].z = size.z * points[i].z + location.z;
    }
    
    return (Object3D){};
}

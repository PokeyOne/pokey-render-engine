//
//  animation.h
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-05-09.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#ifndef animation_h
#define animation_h

#include <stdio.h>
#include "vectors.h"
#include "pkmathutil.h"

typedef struct KeyFrame {
    Vec3D translation;
    int frame;
} KeyFrame;

Vec3D calculateTranslation(size_t len, KeyFrame keyFrames[], int currentFrame);

#endif /* animation_h */

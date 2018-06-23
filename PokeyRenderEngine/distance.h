//
//  distance.h
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-04-17.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#ifndef distance_h
#define distance_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vectors.h"
#include "pkmathutil.h"

double square(double v);
double calculateDistance_c(double x1, double y1, double z1, double x2, double y2, double z2);
double calculateDistance_p(Vec3D a, Vec3D b);

#endif /* distance_h */

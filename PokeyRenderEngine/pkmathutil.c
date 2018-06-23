//
//  pkmathutil.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-04-25.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "pkmathutil.h"

/*
 Returns the absolute value of the double given. Equivelent to |original|
 */
double absd(double original) {
    if(original < 0.0){
        return original * -1.0;
    }else{
        return original;
    }
}

/*
 Returns the opposite of a percentage
 */
double percentageOpposite(double original){
    return 1.0 - original;
}

/*
 Used to get the percentage that point is between from and to
 */
double percentage(double from, double to, double point){
    return (point - from)/(to - from);
}

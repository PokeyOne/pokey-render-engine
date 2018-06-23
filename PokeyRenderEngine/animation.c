//
//  animation.c
//  PokeyRenderEngine
//
//  Created by Mateo Carreras on 2018-05-09.
//  Copyright © 2018 Mateo Carreras. All rights reserved.
//

#include "animation.h"

Vec3D calculateTranslation(size_t len, KeyFrame keyFrames[], int currentFrame){
    if(len == 0){
        return (Vec3D){0, 0, 0};
    }else if(len == 1){
        return keyFrames[0].translation;
    }
    
    int indexOfLastKeyFrameThatAheadOf = 0;
    for(int i = 1; i < len; i++){
        if(currentFrame >= keyFrames[i].frame){
            indexOfLastKeyFrameThatAheadOf = i;
        }
    }
    
    if(indexOfLastKeyFrameThatAheadOf == len-1){
        return keyFrames[len-1].translation;
    }else if(keyFrames[indexOfLastKeyFrameThatAheadOf].frame == currentFrame){
        return keyFrames[indexOfLastKeyFrameThatAheadOf].translation;
    }else{
        int lastKeyFrameFrame = keyFrames[indexOfLastKeyFrameThatAheadOf].frame;
        int nextKeyFrameFrame = keyFrames[indexOfLastKeyFrameThatAheadOf + 1].frame;
        double percentage = (double)(currentFrame - lastKeyFrameFrame)/(double)(nextKeyFrameFrame - lastKeyFrameFrame);
        return vectorAdd(vectorDoubleMultiply(percentageOpposite(percentage), keyFrames[indexOfLastKeyFrameThatAheadOf].translation), vectorDoubleMultiply(percentage, keyFrames[indexOfLastKeyFrameThatAheadOf + 1].translation));
    }
}

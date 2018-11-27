//
//  Ball.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Ball_h
#define Ball_h


#include <iostream>
#include <cmath>

#include "Vector3d.h"
#include "Sphere.h"
#include "Solid.h"
class Ball: public Sphere{
    //No encapsulado
public:
    Ball():Sphere(){};
    Ball(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double r):Sphere(p, v, c, f, m, r){};
    Ball(const Ball &e): Sphere(e){};
    spSolid clone();
    inline void update(double dt);
    inline int collision(spSolid s);
    inline int collisionPaddle(spSolid s);
    bool waitingForStart = true;
    
};

spSolid Ball::clone(){
    shared_ptr<Ball> e=make_shared<Ball>(*this);
    //return new Sphere(*this);
    return e;
}

void Ball::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    
    double ballX = pos.getX();
    
    //Checa colisiones conla parate superior
    if(-pos.getZ()>19.2){
        vel.setZ(-vel.getZ());
    } else if(pos.getY()<0){
        vel.setY(-vel.getY());
        pos.setY(0);
    } else if(ballX > 33 || ballX < -33){
        vel.setX(-vel.getX());
    }
    
    
    
}

//Colision con paletas y regreso al origen
int Ball::collision(spSolid solid){
    
    double ballX = pos.getX();
    double ballZ = pos.getZ();
    double solidX = solid->getPos().getX();
    double solidZ = solid->getPos().getZ();
    
    if ((ballZ-0.6 < solidZ + 1) && (ballZ+0.6 > solidZ-1) && (ballX+0.6 < solidX -2.5) && (ballX+0.6 > solidX -2.6) && (vel.getX() > 0)) {
        vel.setX(-vel.getX());
        return 1;
    }
    
    if ((ballZ-0.6 < solidZ + 1) && (ballZ+0.6 > solidZ-1) && (ballX-0.6 > solidX +2.5) && (ballX -0.6 < solidX +2.6) && (vel.getX() < 0)) {
        vel.setX(-vel.getX());
        return 1;
    }
    
    if ((ballX-0.6 < solidX+2.5) && (ballX+0.6 > solidX-2.5) && (ballZ+0.6 < solidZ - 1) && (ballZ+0.6 > solidZ - 1.1) && (vel.getZ() > 0)) {
        //vel.setX(vel.getX()*1);
        vel.setZ(-vel.getZ());
        return 1;
    }
    
    if ((ballX-0.6 < solidX+2.5) && (ballX+0.6 > solidX-2.5) && (ballZ-0.6 > solidZ + 1) && (ballZ-0.6 < solidZ + 1.1) && (vel.getZ() < 0)) {
        //vel.setX(vel.getX()*1);
        vel.setZ(-vel.getZ());
        return 1;
    }
    
    return 0;
}

//Colision con paletas y regreso al origen
int Ball::collisionPaddle(spSolid solid){
    
    double ballX = pos.getX();
    double ballZ = pos.getZ();
    double solidX = solid->getPos().getX();
    double solidZ = solid->getPos().getZ();
    
    if ((ballZ-0.6 < solidZ + 1) && (ballZ+0.6 > solidZ-1) && (ballX+0.6 < solidX -2.5) && (ballX+0.6 > solidX -2.6) && (vel.getX() > 0)) {
        vel.setX(-vel.getX());
        return 1;
    }
    
    if ((ballZ-0.6 < solidZ + 1) && (ballZ+0.6 > solidZ-1) && (ballX-0.6 > solidX +2.5) && (ballX -0.6 < solidX +2.6) && (vel.getX() < 0)) {
        vel.setX(-vel.getX());
        return 1;
    }
    
    if ((ballX-0.6 < solidX+2.5) && (ballX+0.6 > solidX-2.5) && (ballZ+0.6 < solidZ - 1) && (ballZ+0.6 > solidZ - 1.1) && (vel.getZ() > 0)) {
        //vel.setX(vel.getX()*1);
        vel.setZ(-vel.getZ());
        return 1;
    }
    
    if ((ballX-0.6 < solidX+2.5) && (ballX+0.6 > solidX-2.5) && (ballZ-0.6 > solidZ + 1) && (ballZ-0.6 < solidZ + 1.1) && (vel.getZ() < 0)) {
        //vel.setX(vel.getX()*1);
        vel.setZ(-vel.getZ());
        return 1;
    }
    
    if(pos.getZ()>19.2){
        solid->setVel(Vector3Dd(0,0,0));
        vel = Vector3Dd(0,0,0);
        pos = Vector3Dd(solidX,0, solidZ - 2);
        waitingForStart = true;
    }
    
    return 0;
}





#endif /* Ball_h */

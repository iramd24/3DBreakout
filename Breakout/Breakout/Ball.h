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

#include "Vector3D.h"
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
    inline int colision(spSolid s, bool derecha);
    
};

spSolid Ball::clone(){
    shared_ptr<Ball> e=make_shared<Ball>(*this);
    //return new Sphere(*this);
    return e;
}

void Ball::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    
    //Checa colisiones conla parate superior
    if(-pos.getZ()>19.2){
        vel.setZ(vel.getZ()*-1);
    }
    
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}

//Colision con paletas y regreso al origen
int Ball::colision(spSolid s, bool derecha){
    //cout<< "Sphere " << pos << endl;
    //cout << "paleta " << s->getPos() << endl;
    //cout << "pos " << pos << endl;
    //if(pos.getX()<s->getPos().getX()+2 && pos.getX()>s->getPos().getX()-2  && pos.getZ()==s->getPos().getZ()-3.5 && this->getVel().getZ() > 0)
    if(pos.getX()<s->getPos().getX()+2 && pos.getX()>s->getPos().getX()-2  && pos.getZ()<s->getPos().getZ()-3.30 && pos.getZ()>s->getPos().getZ()-3.65 && this->getVel().getZ() > 0){
        vel.setX(vel.getX()*1.2);
        vel.setZ(vel.getZ()*-1.2);
    } else if(pos.getX()<s->getPos().getX()+2 && pos.getX()>s->getPos().getX()-2  && pos.getZ()>s->getPos().getZ()+3.35 && pos.getZ()<s->getPos().getZ()+3.60 && this->getVel().getZ() < 0){
        vel.setX(vel.getX()*1.2);
        vel.setZ(vel.getZ()*-1.2);
    } else if(derecha && pos.getX()>28  && pos.getZ()>s->getPos().getZ()-3.5 && pos.getZ()<s->getPos().getZ()+3.5 && this->getVel().getX()>0){
        //cout << "entro" << endl;
        vel.setX(vel.getX()*-1.2);
        vel.setZ(vel.getZ()*1.2);
    } else if(!derecha && pos.getX()<-28  && pos.getZ()>s->getPos().getZ()-3.5 && pos.getZ()< s->getPos().getZ()+3.5 && this->getVel().getX()<0){
        //cout << "entro" << endl;
        vel.setX(vel.getX()*-1.2);
        vel.setZ(vel.getZ()*1.2);
    } else if(pos.getX()>33){
        vel = Vector3Dd(0,0,0);
        pos = Vector3Dd(0,0,0);
        return 1;
    } else if(pos.getX()<-33){
        vel = Vector3Dd(0,0,0);
        pos = Vector3Dd(0,0,0);
        return 2;
    }
    return 0;
}

#endif /* Ball_h */

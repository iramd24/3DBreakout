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
#include "Esfera.h"
#include "Solido.h"
class Pelota: public Esfera{
    //No encapsulado
public:
    Pelota():Esfera(){};
    Pelota(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double r):Esfera(p, v, c, f, m, r){};
    Pelota(const Pelota &e): Esfera(e){};
    spSolido clone();
    inline void update(double dt);
    inline int colision(spSolido s, bool derecha);
    
};

spSolido Pelota::clone(){
    shared_ptr<Pelota> e=make_shared<Pelota>(*this);
    //return new Esfera(*this);
    return e;
}

void Pelota::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    
    //Checa colisiones conla parate superior e inferior de la pantalla
    if(abs(pos.getZ())>19.2){
        vel.setZ(vel.getZ()*-1);
    }
    
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}

//Colision con paletas y regreso al origen
int Pelota::colision(spSolido s, bool derecha){
    //cout<< "Esfera " << pos << endl;
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

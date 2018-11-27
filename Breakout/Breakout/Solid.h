//
//  Solid.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Solid_h
#define Solid_h


#include "Vector3D.h"
class Solid;

using spSolid= shared_ptr<Solid>;

class Solid {
public:
    Solid();
    Solid(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m);
    Solid(const Solid &s);
    
    virtual spSolid clone()=0;
    
    inline Vector3Dd& getF();
    inline Vector3Dd& getPos();
    inline Vector3Dd& getVel();
    inline Vector3Dd& getCol();
    inline double getM();
    inline void setM(double m);
    virtual void render(){};
    inline void setF(Vector3Dd f);
    inline void setPos(Vector3Dd p);
    inline void setVel(Vector3Dd v);
    inline void setCol(Vector3Dd c);
    //inline void colision(spSolid s);
    virtual void update(double dt);
    friend ostream& operator<<(ostream &os, const Solid& s);
    
protected:
    Vector3Dd pos;
    Vector3Dd vel;
    Vector3Dd col;
    Vector3Dd f;
    double m;
    
};

Solid:: Solid(){
    this->pos = Vector3Dd(0,0,0);
    this->vel = Vector3Dd(0,0,0);
    this->col = Vector3Dd(0,0,0);
    this->f  = Vector3Dd(0,0,0);
    this->m = 1;
}

Solid:: Solid(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m){
    this->pos = p;
    this->vel = v;
    this->col = c;
    this->f  = f;
    this->m = m;
}

Solid:: Solid(const Solid &s){
    this->pos = s.pos;
    this->vel = s.vel;
    this->col = s.col;
    this->f  = s.f;
    this->m = s.m;
}

Vector3Dd& Solid::getF(){
    return f;
}

Vector3Dd& Solid::getVel(){
    return vel;
}
Vector3Dd& Solid::getPos(){
    return pos;
}
Vector3Dd& Solid::getCol(){
    return col;
}

double Solid::getM(){
    return m;
}


void Solid::setF(Vector3Dd f){
    this->f = f;
}

void Solid::setVel(Vector3Dd v){
    this->vel = v;
}
void Solid::setPos(Vector3Dd p){
    this->pos = p;
}
void Solid::setCol(Vector3Dd c){
    this->col = c;
}

void Solid::setM(double m){
    this->m = m;
}

void Solid::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}

/*void Solid::colision(spSolid s){
 
 }*/

inline ostream& operator<<(ostream &os, const Solid& s){
    os << s.pos << " "<< s.vel << " "<< s.col << " "<< s.f << " "<< s.m;
    return os;
}


#endif /* Solid_h */

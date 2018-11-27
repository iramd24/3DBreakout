//
//  Sphere.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include <iostream>
#include <cmath>

#include "Vector3d.h"
#include "Solid.h"
class Sphere: public Solid{
    //No encapsulado
public:
    Sphere();
    Sphere(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double r);
    Sphere(const Sphere &e);
    virtual spSolid clone();
    inline double getR();
    inline void setR(double r);
    inline void render();
    virtual void update(double dt);
    inline virtual int collision(spSolid s);
protected:
    //Encapsulado, necesita metodos de acceso
    double r;
};

Sphere:: Sphere(): Solid(){
    this->r = .5;
}

Sphere:: Sphere(Vector3Dd p, Vector3Dd v, Vector3Dd c, Vector3Dd f, double m, double r): Solid(p, v, c, f, m){
    this->r = r;
}

spSolid Sphere::clone(){
    shared_ptr<Sphere> e=make_shared<Sphere>(*this);
    //return new Sphere(*this);
    return e;
}

int Sphere::collision(spSolid s){
    return 0;
}

Sphere:: Sphere(const Sphere &e): Solid(e){
    this->r = e.r;
}

double Sphere::getR(){
    return r;
}

void Sphere::setR(double r){
    this->r = r;
}

void Sphere::render(){
    glPushMatrix();
    glColor3f(col.getX(),col.getY(),col.getZ());
    glTranslatef(pos.getX(),pos.getY(),pos.getZ());
    glutSolidSphere(r,10,10);
    glPopMatrix();
}

void Sphere::update(double dt){
    vel=vel+f/m*dt;
    pos=pos+vel*dt;
    
    
    if(pos.getY()<0){
        vel.setY(vel.getY()*-1);
        pos.setY(0);
    }
}

// checar


//double a = vel.getX();
//cout << a <<endl;
//double b = vel.getZ();
//cout << b << endl;
//vel =Vector3Dd(a*-1, 0, b);


#endif /* Sphere_h */

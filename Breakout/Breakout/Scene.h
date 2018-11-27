//
//  Scene.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include <vector>
#include "Vector3d.h"
#include "Cube.h"
#include "Sphere.h"
using namespace std;

class Scene {
    vector<spSolid> solids;
public:
    Scene();
    Scene(const Scene &e);
    virtual ~Scene();
    friend ostream& operator<<(ostream &os, const Scene& e);
    void render(){
        for(spSolid s:solids)
            s->render();
    }
    void update(double dt){
        /*
         //Uso de iteradores
         for (vector<Solid *>::iterator i = solids.begin();i < solids.end();i++) {
         Solid *s = *i;
         s->update(dt);
         }
         */
        for(spSolid s:solids)
            s->update(dt);
    }
    vector<spSolid> getSolids(){return solids;}
    void add(spSolid s){solids.push_back(s);}
};

Scene::Scene() {
    // TODO Auto-generated constructor stub
    
}

Scene::~Scene() {
    // TODO Auto-generated destructor stub
    /*for (spSolid s : solids){
     delete s;
     }*/
}

Scene::Scene(const Scene &e){
    for(spSolid s: e.solids){
        spSolid s0 = s->clone();
        this->solids.push_back(s0);
    }
}

inline ostream& operator<<(ostream &os, const Scene& e){
    
    for(spSolid s :e.solids)
        os << *s;
    return os;
}



#endif /* Scene_h */

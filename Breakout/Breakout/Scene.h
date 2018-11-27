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
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

using namespace std;

class Scene {
    //vector<spSolid> solids;
    vector<spSolid> bricks;
    vector<int> eraser;
    
public:
    spSolid ball;
    spSolid paddle;
    Scene();
    Scene(const Scene &e);
    virtual ~Scene();
    friend ostream& operator<<(ostream &os, const Scene& e);
    
    void render(){
        ball->render();
        paddle->render();
        for(spSolid brick:bricks)
            brick->render();
    }
    
    void update(double dt){
        if (bricks.size() == 0) {
            // todo
        }
        
        ball->collisionPaddle(paddle);
        int i = 0;
        
        eraser.clear();
        for(spSolid brick:bricks) {
            if (ball->collision(brick) == 1) {
                eraser.push_back(i);
            }
            i++;
        }
        for (int i=0; i<eraser.size(); i++) {
            bricks.erase(bricks.begin()+(eraser[i]-i));
        }
        
        
        
        ball->update(dt);
        paddle->update(dt);
        for(spSolid brick:bricks)
            brick->update(dt);
        
        
    }
    
    //vector<spSolid> getSolids(){return solids;}
    void add(spSolid s){bricks.push_back(s);}
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
//
//Scene::Scene(const Scene &e){
//    for(spSolid s: e.solids){
//        spSolid s0 = s->clone();
//        this->bric.push_back(s0);
//    }
//}


#endif /* Scene_h */

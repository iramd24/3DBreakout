//
//  Scene.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include <iostream>
#include <fstream>
#include <sstream>

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
        for(spSolid brick:bricks){
            brick->update(dt);
        }
    
    }
    
    void add(spSolid s){
        bricks.push_back(s);
    }
    
    void saveScene(){
        ofstream gameFile;
        gameFile.open ("game.txt");
        for(spSolid brick:bricks){
            gameFile << brick->getPos() << brick->getCol() << endl;
        }
        gameFile.close();
    }
    
    void loadScene() {
        //string brString = "(-30, 0, -17)(0.113725, 0.760784, 0.258824)";
        string line;
        ifstream gameFile ("game.txt");
        if (gameFile.is_open()) {
            bricks.clear();
            while (getline (gameFile,line)) {
                line.erase(std::remove(line.begin(), line.end(), ','), line.end());
                size_t pos1 = line.find('(');
                size_t pos2 = line.find(')');
                string pos = line.substr(pos1+1, pos2-1);
                
                string col = line.substr(pos2+2);
                col.pop_back();
                cout << "Pos:"<<pos << "Col:"<<col << '\n';
                
                std::stringstream posStream(pos);
                std::stringstream colStream(col);
                
                double p1, p2, p3, c1, c2, c3;
                posStream >> p1;
                posStream >> p2;
                posStream >> p3;
                
                colStream >> c1;
                colStream >> c2;
                colStream >> c3;
                shared_ptr<Brick> brick = make_shared<Brick> ();
                
                brick->setPos(Vector3Dd(p1, p2, p3));
                brick->setVel(Vector3Dd(0,0,0));
                brick->setCol(Vector3Dd(c1, c2, c3));
                brick->setS(1);
                
                bricks.push_back(brick);
                
            }
            gameFile.close();
        } else {
            cout << "Unable to open file";
        }
    }
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

//
//  Camera.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

double PI = 3.14159;

class Camera {
    Vector3D<double> pos;
    Vector3D<double> rot;
public:
    Camera();
    Camera(double x,double y,double z):pos(Vector3D<double>(x,y,z)){}
    virtual ~Camera();
    inline Vector3D<double> getPos() const {return pos;    }
    inline void setPos(Vector3D<double> pos) {this->pos = pos;}
    inline Vector3D<double> getRot() const {return rot;    }
    inline void setRot(Vector3D<double> rot) {this->rot = rot;}
    void render(){
        
        glRotatef(getRot().getX(), 1,0,0);
        glRotatef(getRot().getY(), 0,1,0);
        glRotatef(getRot().getZ(), 0,0,1);
        glTranslatef(-this->getPos().getX(),-this->getPos().getY(),-this->getPos().getZ());
    }
};


Camera::Camera() {
    // TODO Auto-generated constructor stub
    
}

Camera::~Camera() {
    // TODO Auto-generated destructor stub
}

#endif /* Camera_h */

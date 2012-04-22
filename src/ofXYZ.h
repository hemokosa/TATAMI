//
//  ofXYZ.h
//  emptyExample
//
//  Created by Takahiro Hirata on 12/04/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_ofXYZ_h
#define emptyExample_ofXYZ_h

#include "ofMain.h"

class ofXYZ {
  
private:
  float _length;
  ofVbo _vboX;
  ofVbo _vboY;
  ofVbo _vboZ;
  ofMesh _meshX;
  ofMesh _meshY;
  ofMesh _meshZ;
  float _width;
  
  float _transX, _transY;
  
public:
  
  ofXYZ(){
    _transX = 0;
    _transY = 0;
    /*
    _meshX.addVertex(ofVec3f(0, 0, 0));
    _meshX.addVertex(ofVec3f(1, 0, 0));
    _vboX.setMesh(_meshX, GL_STATIC_DRAW);

    _meshY.addVertex(ofVec3f(0, 0, 0));
    _meshY.addVertex(ofVec3f(0, 1, 0));
    _vboY.setMesh(_meshY, GL_STATIC_DRAW);

    _meshX.addVertex(ofVec3f(0, 0, 0));
    _meshX.addVertex(ofVec3f(0, 0, 1));
    _vboX.setMesh(_meshX, GL_STATIC_DRAW);
    */
  }
  
  void init(float length, float width){
    _length = length;
    _width = width;
    
    ofSetLineWidth(_width);
    
    _meshX.addVertex(ofVec3f(0, 0, 0));
    _meshX.addVertex(ofVec3f(_length, 0, 0));
    _meshX.addColor(ofFloatColor(1, 0, 0, 1));
    _meshX.addColor(ofFloatColor(1, 0, 0, 1));
    _vboX.setMesh(_meshX, GL_STATIC_DRAW);
    
    _meshY.addVertex(ofVec3f(0, 0, 0));
    _meshY.addVertex(ofVec3f(0, _length, 0));
    _meshY.addColor(ofFloatColor(0, 1, 0, 1));
    _meshY.addColor(ofFloatColor(0, 1, 0, 1));
    _vboY.setMesh(_meshY, GL_STATIC_DRAW);
    
    _meshZ.addVertex(ofVec3f(0, 0, 0));
    _meshZ.addVertex(ofVec3f(0, 0, _length));
    _meshZ.addColor(ofFloatColor(0, 0, 1, 1));
    _meshZ.addColor(ofFloatColor(0, 0, 1, 1));
    _vboZ.setMesh(_meshZ, GL_STATIC_DRAW);
  }
  
  void updateXYZ(float x, float y, float z){
    
    _transX = x;
    _transY = y;
  }
  
  void draw(){
    
    ofPushMatrix();
    
    ofTranslate(_transX, _transY);
    
    _vboX.draw(GL_LINES, 0, 2);
    _vboY.draw(GL_LINES, 0, 2);
    _vboZ.draw(GL_LINES, 0, 2);
    
    /*
    // X軸
    ofSetHexColor(0xff0000);
    ofLine(0.0, 0.0, 0.0,  _length, 0.0, 0.0);
    
    // Y軸
    ofSetHexColor(0x00ff00);
    ofLine(0.0, 0.0, 0.0, 0.0, _length, 0.0);
    
    // Z軸
    ofSetHexColor(0x0000ff);
    ofLine(0.0, 0.0, 0.0, 0.0, 0.0, _length);
    */
    glPopMatrix();      
  }
  
};

#endif

#pragma once

#include "ofMain.h"

#include "OrthoCamera.h"

#include "ofXYZ.h"
#include "Singleton.h"
#include "My3DObject.h"

#include "ofxControlPanel.h"
#include "ofxUI.h"

#define N_CAMERAS   4
#define VIEW_MAIN   0
#define VIEW_FRONT  1
#define VIEW_TOP    2
#define VIEW_EDIT   3



class testApp : public ofBaseApp{

public:
  void setup();
  void update();
  void draw();

  void keyPressed  (int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
  void exit();
  void guiEvent(ofxUIEventArgs &e);
  
  //デストラクタ
  ~testApp(){
    delete [] _vX;
    delete [] _vY;
  }
  
private:
  
  Singleton *_singleton;
  
  string  _strLog;
  
  ofLight   _light;
  ofXYZ     _XYZ;
  ofXYZ     _localXYZ;
  My3DObject _3d_object;

  bool					bCamParent;//cameras have parent?
	int						iMainCamera;  
  
  ofCamera*     _cameras[N_CAMERAS];  
 	ofEasyCam     _cam;
  OrthoCamera		_camTop;
  OrthoCamera		_camFront;
  OrthoCamera		_camEdit;  
  
  //viewports
  ofRectangle				viewMain;
	ofRectangle				viewGrid[N_CAMERAS];	  
  
  float         _menMax;
  float         _cX;
  float         _cY;
  float         *_vX;
  float         *_vY;
  int          _shapeMode;
  int          _waveCycle;
  float        _waveWidth;
  
  void setupViewports();  
  void drawScene(int iCameraDraw);	
  
  void updateObject();
  
  ofxControlPanel gui;

};

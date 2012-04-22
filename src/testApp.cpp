#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

  _singleton = Singleton::GetInstance();
  _singleton->init();
  _menMax = _singleton->getMenMax();
  
  _vX  = new float(_menMax);
  _vY  = new float(_menMax);

  ofSetFrameRate(30);
  
 	ofBackground(10, 10, 10);
  _XYZ.init(150.0, 3);
  _localXYZ.init(50, 1);
  
  _cam.setDistance(300);
  
  ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
  
	/////////////////////
	// SETUP CAMERAS
	/////////////////////	  
	iMainCamera = 0;
	bCamParent = false;
  
  _cameras[0] = &_cam;

	// edit
	_camEdit.scale = 150;
	_cameras[1] = &_camEdit;
  
	// top
	_camTop.scale = 150;
	_camTop.tilt(-90);
	_cameras[2] = &_camTop;

	// front
	_camFront.scale = 50;//値が大きいと小さく描画
	_cameras[3] = &_camFront;
	

	
	for (int i=0; i<N_CAMERAS; i++)
		_cameras[i]->cacheMatrices();
  
	/////////////////////
	// DEFINE VIEWPORTS
	/////////////////////	
	setupViewports();  
  
  
  _light.setDirectional();
  _light.setPosition(0, 500, 500);

  ofFloatColor ambi(0.5, 0.5, 0.5, 1.0);
  ofFloatColor diff(1.0, 1.0, 1.0);
  ofFloatColor spec(0.1, 0.1, 0.1);
  
  _light.setAmbientColor(ambi);
  _light.setDiffuseColor(diff);
  _light.setSpecularColor(spec);
  
  gui.setup("control panel", 10, 10, 275, ofGetHeight()*1/2);
  gui.addPanel("vertex settings", 1);
  gui.setOutlineColor(simpleColor(200, 200, 255, 255));
  gui.setWhichPanel(0);

  float min = -100.00;
  float max = 100.00;
  gui.addSlider("x0:", "X_0", -10, min, max, false);
  gui.addSlider("y0:", "Y_0", +20, min, max, false);
  gui.addSlider("x1:", "X_1", +10, min, max, false);
  gui.addSlider("y1:", "Y_1", +00, min, max, false);
  gui.addSlider("x2:", "X_2", -10, min, max, false);
  gui.addSlider("y2:", "Y_2", -20, min, max, false);
  
  gui.addSlider("center x:", "C_X", 50, 0, 350, false);
//  gui.addSlider("center y", "C_Y", 0, -20, 20, false);

  //shape mode settints
  gui.addPanel("shape settings", 1);
  gui.setWhichPanel(1);
	vector <string> names;
	names.push_back("normal");
	names.push_back("wave all");
	names.push_back("twist");
  names.push_back("spiral");
  names.push_back("sun");
  names.push_back("test");
  
	gui.addTextDropDown("shape mode:", "shape_mode", 0, names); 
  gui.addSlider("cycle:", "WAVE_CYCLE", 3, 0, 16, true);
  gui.addSlider("value:", "WAVE_WIDTH", 3, 0, 30, true);
  
  //export settints
  gui.addPanel("export settings", 1);
  gui.setWhichPanel(2);
  //gui.addSlider("scale:", "EXPORT_SCALE", 0.1, 0.1, 1.0, false);  
  vector <string> exportScalseNames;
  exportScalseNames.push_back("0.001");
  exportScalseNames.push_back("0.01");
  exportScalseNames.push_back("0.1");
  exportScalseNames.push_back("0.2");
  exportScalseNames.push_back("1.0");
  exportScalseNames.push_back("10.0");
  gui.addTextDropDown("export scale:", "export_scale", 3, exportScalseNames);   
  
  vector <string> exportAxisNames;
  exportAxisNames.push_back("NONE");
  exportAxisNames.push_back("Z->Y, Y->-Z");
  gui.addTextDropDown("export axis:", "export_axis", 1, exportAxisNames);   
 
  gui.loadSettings("controlPanelxml");  

  
  _shapeMode = 0;
  _waveCycle = 1;
  _waveWidth = 1;

  _cX = 90;
  _cY =  _shapeMode;
  _vX[0] = -10;
  _vY[0] =  20;
  _vX[1] =  10;
  _vY[1] =   0;
  _vX[2] = -10;
  _vY[2] = -20;
 
  updateObject();
  
}

void testApp::setupViewports()
{
	//call here whenever we resize the window

	/////////////////////
	// DEFINE VIEWPORTS
	/////////////////////	
	float xOffset = ofGetWidth()/3;
	float yOffset = ofGetHeight()/(N_CAMERAS-1);
	
	viewMain.x = xOffset;
	viewMain.y = 0;
	viewMain.width = xOffset * 2;
	viewMain.height = ofGetHeight();
	
	for (int i=1; i<N_CAMERAS; i++) {
		viewGrid[i].x = 0;
		viewGrid[i].y = yOffset * (i-1);
		viewGrid[i].width = xOffset;
		viewGrid[i].height = yOffset;
	}
//  gui.setup("control panel", 0, 0, ofGetWidth(), ofGetHeight()/4);

}

//--------------------------------------------------------------
void testApp::update(){
  gui.update();
  
}

void testApp::drawScene(int iCameraDraw){	
  
 	glEnable(GL_DEPTH_TEST);
  
  ofPushStyle();
  
  ofPushMatrix();
  
  _light.enable();
  
  float cX=0, cY=0;
  if (iCameraDraw==VIEW_EDIT) {
    ;
  } else {
    cX = _cX;
    cY = _cY;
    _3d_object.customDraw();
  }
  
  _XYZ.draw();
  
  //ローカル軸描画
  if (iCameraDraw!=VIEW_EDIT) {
    _localXYZ.draw();
  }

	glDisable(GL_DEPTH_TEST);
  //頂点丸描画
  glPushMatrix();
  //if (iCameraDraw==VIEW_TOP) {
  //  glRotated(90, 1, 0, 0);
  //}
  for (int i=0; i<_menMax; i++) {
    ofSetColor(0, 0, 255);
    ofCircle(_vX[i]+cX, _vY[i]+cY, 3);
    //ofSphere(_vX[i]+cX, _vY[i]+cY, 0, 5);
  }
  glPopMatrix();
  
  // 三角形のライン描画
  ofSetColor(255, 255, 0);
  glPushMatrix();
  for (int i=0; i<_menMax; i++) {
    if ( i< _menMax-1){
      ofLine(_vX[i]+cX, _vY[i]+cY, _vX[i+1]+cX, _vY[i+1]+cY);
    } else {
      ofLine(_vX[i]+cX, _vY[i]+cY, _vX[0]+cX, _vY[0]+cY);
    }
  }
  glPopMatrix();

  _light.disable();
  
  ofPopStyle();
  ofPopMatrix();  
}

//--------------------------------------------------------------
void testApp::draw(){
  
	//////////////////////////
	// DRAW ALL VIEWPORTS
	//////////////////////////
	
	//draw main viewport
	_cameras[iMainCamera]->begin(viewMain);
	drawScene(iMainCamera);
	_cameras[iMainCamera]->end();
	
	//draw side viewports
	for (int i=1; i<N_CAMERAS; i++)
	{
		_cameras[i]->begin(viewGrid[i]);
		drawScene(i);
		_cameras[i]->end();
	}

  _light.enable();
  
	ofPushStyle();
	glDepthFunc(GL_ALWAYS); // draw on top of everything
  	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(_strLog, viewMain.x + 20, 30);
  
	//draw outlines on views
	ofSetLineWidth(5);
	ofNoFill();
	ofSetColor(100, 100, 100);
     
	for (int i=1; i<N_CAMERAS; i++){
		ofRect(viewGrid[i]);
  }
	ofRect(viewMain);
	
	glDepthFunc(GL_LESS);
	ofPopStyle();  

  
	glDisable(GL_DEPTH_TEST);
	ofPushStyle();  
  gui.draw();
	ofPopStyle();  
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key == 'e' || key == 'E'){
    
    char *cwd ;
    cwd=getcwd(NULL, 0); ;
    printf("CWD:%s\n", cwd);
    //_strLog = cwd;
    free(cwd);
    
    
    FILE *fp;
    char filename[] = "/Users/Shared/out.stl";
    
    if((fp=fopen( filename, "w")) == NULL){
      LOG( "%sファイルが開けません\n", filename );
      //return -1;
    }    
    _3d_object.stlExport(fp);
    
    
    fclose( fp );
    
    printf( "%sファイル書き込みが終わりました\n", filename );
	}  
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

void testApp::updateObject(){
  
  _vX[0] = gui.getValueF("X_0");
  _vY[0] = gui.getValueF("Y_0");
  _vX[1] = gui.getValueF("X_1");
  _vY[1] = gui.getValueF("Y_1");
  _vX[2] = gui.getValueF("X_2");
  _vY[2] = gui.getValueF("Y_2");
  
  _cX = gui.getValueF("C_X");
  //_cY = gui.getValueF("C_Y");
  
  _localXYZ.updateXYZ(_cX, _cY, 0);
  
  _shapeMode = gui.getValueI("shape_mode");
  //LOG("_shapeMode:%d", _shapeMode);  
  
  _waveCycle = gui.getValueI("WAVE_CYCLE");
  _waveWidth = gui.getValueF("WAVE_WIDTH");
  
  _3d_object.init(_shapeMode,
                  _cX,
                  _cY,
                  _vX,
                  _vY,
                  _waveCycle,
                  _waveWidth
                  );
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
  
  LOG("button:%d", button);
  
  if (x<ofGetWidth()/3 || gui.dragging==TRUE) {
    _cam.disableMouseInput();
  } else {
    _cam.enableMouseInput();
  }
  gui.mouseDragged(x, y, button);
  updateObject();
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  gui.mousePressed(x, y, button);
  updateObject();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  gui.mouseReleased();
  updateObject();
  
  _3d_object.setExportAxis(gui.getValueI("export_axis"));
  _3d_object.setExportScale(gui.getValueI("export_scale"));
  
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	setupViewports();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::guiEvent(ofxUIEventArgs &e)
{

}

void testApp::exit()
{
 
}




//
//  My3DObject.h
//  emptyExample
//
//  Created by Takahiro Hirata on 12/04/14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_My3DObject_h
#define emptyExample_My3DObject_h

#include "ofMain.h"
#include "Singleton.h"

class My3DObject:public ofNode {
  
private:  
  int     _menMax;
  
	ofVbo   *_vbo;
	ofMesh  *_mesh;
  
  int     _vMax;
  int    _vMax2;
  double _vRadian;
  
  ofVec3f       **_vec3f;
  ofFloatColor  **_col;
  ofVec3f       **_nor3f;
  
  float _mode;
  
  float _exportScale;
  
  int _exportAxis;
  
public:
	My3DObject(){
    
    _menMax = V_MAX;
    _vbo  = new ofVbo[_menMax];
    _mesh  = new ofMesh[_menMax];
    
    _vMax   = 128+1;
#ifdef MOBIEL    
    _vMax   = 360*5+1;
#endif
#ifdef MOBIEL_TOP
    _vMax   = 360+1;
#endif    
    _vMax2   = _vMax*2;
    _vRadian = 360.0/(_vMax-1);// 一周まわすために-1
    
    _vec3f = new ofVec3f*[_menMax];
    _col   = new ofFloatColor*[_menMax];
    _nor3f = new ofVec3f*[_menMax];
    
    for(int i=0; i<_menMax; i++){//面の数分頂点数を追加
      _vec3f[i] = new ofVec3f[_vMax2];
      _col[i]   = new ofFloatColor[_vMax2];
      _nor3f[i] = new ofVec3f[_vMax2];
    }
    
    _mode = 0;
    
    _exportScale = 0.1;
    
    _exportAxis = EXPORT_AXIS_NONE;
	}

	//デストラクタ
  ~My3DObject(){
    delete[] _vbo;
    delete[] _mesh;
    
    for(int i=0; i<_menMax; i++){
      delete[] _vec3f[i];
      delete[] _col[i];
      delete[] _nor3f[i];
    }
    delete[] _vec3f;
    delete[] _col;
    delete[] _nor3f;
  }  

  //初期化
	void init(int mode,
            float cX, float cY,
            float *vX,
            float *vY,
            float cycle,
            float waveWidth
            )
  {
    //LOG("center(%f,%f), v(%f,%f)(%f,%f)(%f,%f)\n", cX, cY, vX[0], vY[0], vX[1], vY[1], vX[2], vY[2]);
    _mode = mode;
    float vD = -_vRadian / (180/PI);
    float vDRot = -_vRadian / (180/PI)*cycle;
    
    int planetTop[] = {0, 120, 240};
    int planet[] = {106, 358, 651, 826, 1039, 1253, 1434, 1765, 0};

    
    for(int meni=0; meni<_menMax; meni++){
      
      for (int i=0; i<_vMax2; i+=2){
        
        int ii = i/2;
        
        float X0, Y0, X1, Y1;
        if (meni<_menMax-1) {
          X0 = vX[meni];
          Y0 = vY[meni];
          X1 = vX[meni+1];
          Y1 = vY[meni+1];
        } else {//最後の頂点は最初への面にする
          X0 = vX[meni];
          Y0 = vY[meni];
          X1 = vX[0];
          Y1 = vY[0];
        }
        
        
        switch(mode){
          case 0:
          {
            float fookY = 0.0;
#ifdef MOBIEL_TOP    
            float tmpDeg = _vRadian * ii;
            //LOG("tmpDeg:%f\n", tmpDeg);
            for (int j=0; j<3; j++){
              if( planetTop[j] == tmpDeg){
                fookY = 5;
                LOG("planet[%d]:%d ", j, planet[j]);
              }
            }
#endif              
            _vec3f[meni][i]   = ofVec3f(//(センター + X0) * cos(...)
                                  (cX + X0) * cos(vD * ii),
                                  (cY + Y0 + fookY),
                                  (cX + X0) * sin(vD * ii)
                                  );
            _vec3f[meni][i+1] = ofVec3f(
                                  (cX + X1) * cos(vD * ii),
                                  (cY + Y1 + fookY),
                                  (cX + X1) * sin(vD * ii)
                                  );    
          }
          break;
          case 1://wave
          {
            _vec3f[meni][i]   = ofVec3f(
                                        (cX + X0) * cos(vD * ii),
                                        (cY + Y0) + cos(vD * ii*cycle)*waveWidth,
                                        (cX + X0) * sin(vD * ii)
                                        );
            _vec3f[meni][i+1] = ofVec3f(
                                        (cX + X1) * cos(vD * ii),
                                        (cY + Y1) + cos(vD * ii*cycle)*waveWidth,
                                        (cX + X1) * sin(vD * ii)
                                        );    
          }
          break;
          case 2://twist
          {
            //if (meni<1){//test用
              
              //LOG("ii:%d\n\n", ii);
              //LOG("0(%f,%f), 1(%f,%f)\n", X0, Y0, X1, Y1);
              double len0 = sqrt(pow(X0, 2) + pow(Y0, 2));
              double len1 = sqrt(pow(X1, 2) + pow(Y1, 2));              
              double radian0 = atan2(Y0, X0);
              double radian1 = atan2(Y1, X1);
              //LOG("radian0:%f\n", radian0);
              //LOG("radian1:%f\n", radian1);
              
              /*
              float degree0 = radian0 * (180.0/PI);
              float degree1 = radian1 * (180.0/PI);
              LOG("degree0:%f\n", degree0);  
              LOG("degree1:%f\n", degree1);  
               */
              
              _vec3f[meni][i]   = ofVec3f(
                                          (cX + len0*cos(radian0+vD*ii*cycle))  * cos(vD * ii),
                                          (cY + len0*sin(radian0+vD*ii*cycle)),
                                          (cX + len0*cos(radian0+vD*ii*cycle))  * sin(vD * ii)
                                          );
              _vec3f[meni][i+1] = ofVec3f(
                                          (cX + len1*cos(radian1+vD*ii*cycle))  * cos(vD * ii),
                                          (cY + len1*sin(radian1+vD*ii*cycle)),
                                          (cX + len1*cos(radian1+vD*ii*cycle))  * sin(vD * ii)
                                          );    
            //}
            
          }
          break;
          case MODE_SPIRAL://spiral
          {
            
            float fookY = 0.0;
#ifdef MOBIEL    
            float tmpDeg = _vRadian * cycle * ii;
            //LOG("tmpDeg:%f\n", tmpDeg);
            for (int j=0; j<9; j++){
              if( planet[j] == tmpDeg){
                fookY = -5;
                LOG("planet[%d]:%d ", j, planet[j]);
              }
            }            
#endif
            
            float pitchY = waveWidth*.2;
            float pitchW = waveWidth*.2;
            _vec3f[meni][i]   = ofVec3f(
                                        (cX + X0 + (pitchW*ii)) * cos(vDRot * ii),
                                        (cY + Y0 + (pitchY*ii)) + fookY,
                                        (cX + X0 + (pitchW*ii)) * sin(vDRot * ii)
                                        );
            _vec3f[meni][i+1] = ofVec3f(
                                        (cX + X1 + (pitchW*ii)) * cos(vDRot * ii),
                                        (cY + Y1 + (pitchY*ii)) + fookY,
                                        (cX + X1 + (pitchW*ii)) * sin(vDRot * ii)
                                        );               
          }
          break;
          case 4://sun
          {
            _vec3f[meni][i]   = ofVec3f(
                                        (cX + X0 + cos(vD * ii*cycle)*waveWidth) * cos(vD * ii),
                                        (cY + Y0),
                                        (cX + X0 + cos(vD * ii*cycle)*waveWidth) * sin(vD * ii)
                                        );
            _vec3f[meni][i+1] = ofVec3f(
                                        (cX + X1 + cos(vD * ii*cycle)*waveWidth) * cos(vD * ii),
                                        (cY + Y1),
                                        (cX + X1 + cos(vD * ii*cycle)*waveWidth) * sin(vD * ii)
                                        );               
          }
          break;
          case 5:
          //if (meni==0)//test
          {
            
            double len0 = sqrt(pow(X0, 2) + pow(Y0, 2));
            double len1 = sqrt(pow(X1, 2) + pow(Y1, 2));              
            double radian0 = atan2(Y0, X0);
            double radian1 = atan2(Y1, X1);  
            
            float len0_ = len0 + len0*0.5*sin(cycle * vD * ii);
            float len1_ = len1 + len1*0.5*sin(cycle * vD * ii);
            
            _vec3f[meni][i]   = ofVec3f(
                                        (cX + len0_*cos(radian0))  * cos(vD * ii),
                                        (cY + len0_*sin(radian0)),
                                        (cX + len0_*cos(radian0))  * sin(vD * ii)
                                        );
            _vec3f[meni][i+1] = ofVec3f(
                                        (cX + len1_*cos(radian1))  * cos(vD * ii),
                                        (cY + len1_*sin(radian1)),
                                        (cX + len1_*cos(radian1))  * sin(vD * ii)
                                        ); 
          }
          break;
        }
        _col[meni][i] =   ofFloatColor(1.0, 1.0, 1.0, 1.0);
        _col[meni][i+1] = ofFloatColor(1.0, 1.0, 1.0, 1.0);
      }
      

      // 法線計算
      float n0[3];
      float n1[3];
      float n2[3];
      
      for (int i=0; i<_vMax2; i+=2){
        //三角ポリゴン2面とも同じ法線とする
        if (i<_vMax2-2){ 
          n0[0] = _vec3f[meni][i].x;
          n0[1] = _vec3f[meni][i].y;
          n0[2] = _vec3f[meni][i].z;
          n1[0] = _vec3f[meni][i+1].x;
          n1[1] = _vec3f[meni][i+1].y;
          n1[2] = _vec3f[meni][i+1].z;
          n2[0] = _vec3f[meni][i+2].x;
          n2[1] = _vec3f[meni][i+2].y;
          n2[2] = _vec3f[meni][i+2].z;
        } else {
          LOG("i:%d\n", i);
          n0[0] = _vec3f[meni][i].x;
          n0[1] = _vec3f[meni][i].y;
          n0[2] = _vec3f[meni][i].z;
          n1[0] = _vec3f[meni][i+1].x;
          n1[1] = _vec3f[meni][i+1].y;
          n1[2] = _vec3f[meni][i+1].z;
          n2[0] = _vec3f[meni][0].x;
          n2[1] = _vec3f[meni][0].y;
          n2[2] = _vec3f[meni][0].z;
        }
        
        float nn[3];
         calcNormal(n0, n1, n2, nn);
        _nor3f[meni][i] = ofVec3f(nn[0], nn[1], nn[2]);
        _nor3f[meni][i+1] = ofVec3f(nn[0], nn[1], nn[2]);
      }
    
      _vbo[meni].setVertexData(_vec3f[meni], _vMax2, GL_DYNAMIC_DRAW);
      _vbo[meni].setColorData(_col[meni], _vMax2, GL_DYNAMIC_DRAW);
      _vbo[meni].setNormalData(_nor3f[meni], _vMax2, GL_DYNAMIC_DRAW);
      
      _vbo[meni].setMesh(_mesh[meni], GL_DYNAMIC_DRAW);
    }
  }
  
  
  int calcNormal( const float p1[3], const float p2[3], const float p3[3], float n[3])
  {
    float v1[3], v2[3], cross[3];
    for (int i = 0; i < 3; i++) { v1[i] = p1[i] - p2[i]; }
    for (int i = 0; i < 3; i++) { v2[i] = p3[i] - p2[i]; }
    for (int i = 0; i < 3; i++) { cross[i] = v2[(i+1)%3] * v1[(i+2)%3] - v2[(i+2)%3] * v1[(i+1)%3]; }
    
    float length = sqrt(cross[0] * cross[0] + cross[1] * cross[1] + cross[2] * cross[2]);
    
    if (length == 0.0f) { return 0; }
    
    for (int i = 0; i < 3; i++) { n[i] = cross[i] / length; }
    
    return 1;
  }   
  
	void customDraw()
  {
    for(int meni=0; meni<_menMax; meni++){
      
      _vbo[meni].draw(GL_TRIANGLE_STRIP, 0, _vMax2);

      // 法線表示
#if 0
      glLineWidth(1.0);
      for (int i=0; i<_vMax2; i++){
        float len = 10;
        ofLine(_vec3f[meni][i].x,                       _vec3f[meni][i].y,                       _vec3f[meni][i].z,
               _vec3f[meni][i].x+_nor3f[meni][i].x*len, _vec3f[meni][i].y+_nor3f[meni][i].y*len, _vec3f[meni][i].z+_nor3f[meni][i].z*len);
      }
#endif
    }
    //ofScale(1.05, 1.05, 1.05);
    //ofSetLineWidth(1.0);
    //_vbo.draw(GL_LINE_STRIP, 0, _vMax2);
	}

  bool stlExport(FILE *fp)
  {
    LOG("stlExport\n");
    
    // 再下点のy座標取得
    float bottomY = 9999;
    for(int meni=0; meni<_menMax; meni++){
      
      for (int i=0; i<_vMax2-4; i++){//3面の時だけかも
        if (_vec3f[meni][i].y<bottomY){
          bottomY = _vec3f[meni][i].y;
        }
      }
    }
    LOG("bottomY:%f\n", bottomY);
    float adjustY = -bottomY*_exportScale;
    LOG("adjustY:%f\n", adjustY);
    
    fputs( "solid tatami-ascii\n", fp );
    
    float nX, nY, nZ;
    float vX0, vY0, vZ0;
    float vX1, vY1, vZ1;
    float vX2, vY2, vZ2;
    
    for(int meni=0; meni<_menMax; meni++){
    
      for (int i=0; i<_vMax2-2; i++){//3面の時だけかも
       
        if (_exportAxis==EXPORT_AXIS_NONE) {
          nX =  _nor3f[meni][i].x; 
          nY =  _nor3f[meni][i].y; 
          nZ =  _nor3f[meni][i].z;
          
          vX0 = _vec3f[meni][i].x*_exportScale; 
          vY0 = _vec3f[meni][i].y*_exportScale + adjustY;
          vZ0 = _vec3f[meni][i].z*_exportScale;
          vX1 = _vec3f[meni][i+1].x*_exportScale; 
          vY1 = _vec3f[meni][i+1].y*_exportScale + adjustY;
          vZ1 = _vec3f[meni][i+1].z*_exportScale;
          vX2 = _vec3f[meni][i+2].x*_exportScale; 
          vY2 = _vec3f[meni][i+2].y*_exportScale + adjustY;
          vZ2 = _vec3f[meni][i+2].z*_exportScale;
        } else {
          nX =  _nor3f[meni][i].x;
          nY =  _nor3f[meni][i].z;
          nZ =  -_nor3f[meni][i].y;
          
          vX0 = _vec3f[meni][i].x*_exportScale; 
          vY0 = -_vec3f[meni][i].z*_exportScale;
          vZ0 = _vec3f[meni][i].y*_exportScale + adjustY;
          vX1 = _vec3f[meni][i+1].x*_exportScale; 
          vY1 = -_vec3f[meni][i+1].z*_exportScale;
          vZ1 = _vec3f[meni][i+1].y*_exportScale + adjustY;
          vX2 = _vec3f[meni][i+2].x*_exportScale; 
          vY2 = -_vec3f[meni][i+2].z*_exportScale; 
          vZ2 = _vec3f[meni][i+2].y*_exportScale + adjustY;         
        }
        

        
        // 法線
        fprintf(fp, "  facet normal  %f %f %f\n", nX, nY, nZ);
          // ポリゴン
          fputs( "    outer loop\n", fp );
            if(i%2==0){
              fprintf(fp, "      vertex  %f %f %f\n", vX0,    vY0,   vZ0);
              fprintf(fp, "      vertex  %f %f %f\n", vX1,    vY1,   vZ1);
              fprintf(fp, "      vertex  %f %f %f\n", vX2,    vY2,   vZ2);
            } else {
              fprintf(fp, "      vertex  %f %f %f\n", vX0,    vY0,   vZ0);
              fprintf(fp, "      vertex  %f %f %f\n", vX2,    vY2,   vZ2);
              fprintf(fp, "      vertex  %f %f %f\n", vX1,    vY1,   vZ1);
            }
          fputs( "    endloop\n", fp );
        fputs( "  endfacet\n", fp );
        
        if (_mode == MODE_SPIRAL){
          //始まりのふた
          if (_exportAxis==EXPORT_AXIS_NONE) {
            fprintf(fp, "  facet normal  %f %f %f\n", 0.0, 0.0, 1.0);
            fputs( "    outer loop\n", fp );
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[0][0].x*_exportScale,    _vec3f[0][0].y*_exportScale + adjustY,   _vec3f[0][0].z*_exportScale);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[2][0].x*_exportScale,    _vec3f[2][0].y*_exportScale + adjustY,   _vec3f[2][0].z*_exportScale);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[1][0].x*_exportScale,    _vec3f[1][0].y*_exportScale + adjustY,   _vec3f[1][0].z*_exportScale);
            fputs( "    endloop\n", fp );
            fputs( "  endfacet\n", fp );
          } else {
            fprintf(fp, "  facet normal  %f %f %f\n", 0.0, 1.0, 0.0);
            fputs( "    outer loop\n", fp );
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[0][0].x*_exportScale,    _vec3f[0][0].z*_exportScale,   _vec3f[0][0].y*_exportScale + adjustY);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[2][0].x*_exportScale,    _vec3f[2][0].z*_exportScale,   _vec3f[2][0].y*_exportScale + adjustY);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[1][0].x*_exportScale,    _vec3f[1][0].z*_exportScale,   _vec3f[1][0].y*_exportScale + adjustY);
            fputs( "    endloop\n", fp );
            fputs( "  endfacet\n", fp );
          }
          //終わりのふた
          if (_exportAxis==EXPORT_AXIS_NONE) {
            fprintf(fp, "  facet normal  %f %f %f\n", 0.0, 0.0, -1.0);
            fputs( "    outer loop\n", fp );
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[0][_vMax2-1].x*_exportScale,    _vec3f[0][_vMax2-1].y*_exportScale + adjustY,   _vec3f[0][_vMax2-1].z*_exportScale);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[1][_vMax2-1].x*_exportScale,    _vec3f[1][_vMax2-1].y*_exportScale + adjustY,   _vec3f[1][_vMax2-1].z*_exportScale);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[2][_vMax2-1].x*_exportScale,    _vec3f[2][_vMax2-1].y*_exportScale + adjustY,   _vec3f[2][_vMax2-1].z*_exportScale);
            fputs( "    endloop\n", fp );
            fputs( "  endfacet\n", fp );
          } else {
            fprintf(fp, "  facet normal  %f %f %f\n", 0.0, -1.0, 0.0);
            fputs( "    outer loop\n", fp );
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[0][_vMax2-1].x*_exportScale,    _vec3f[0][_vMax2-1].z*_exportScale,   _vec3f[0][_vMax2-1].y*_exportScale + adjustY);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[1][_vMax2-1].x*_exportScale,    _vec3f[1][_vMax2-1].z*_exportScale,   _vec3f[1][_vMax2-1].y*_exportScale + adjustY);
            fprintf(fp, "      vertex  %f %f %f\n", _vec3f[2][_vMax2-1].x*_exportScale,    _vec3f[2][_vMax2-1].z*_exportScale,   _vec3f[2][_vMax2-1].y*_exportScale + adjustY);
            fputs( "    endloop\n", fp );
            fputs( "  endfacet\n", fp );
          }
        }
        
      }
    }
    
    fputs( "endsolid\n", fp );
    
    return 1;
  }  
  
  void setExportAxis(int axis){
    _exportAxis = axis;
  }
  
  void setExportScale(int scaleID){
    
    switch (scaleID){
      case EXPORT_SCALE_000_001:
        _exportScale = 0.001;
        break;
      case EXPORT_SCALE_000_010:
        _exportScale = 0.01;
        break;
      case EXPORT_SCALE_000_100:
        _exportScale = 0.1;
        break;
      case EXPORT_SCALE_000_200:
        _exportScale = 0.2;
        break;
      case EXPORT_SCALE_001_000:
        _exportScale = 1.0;
        break;
      case EXPORT_SCALE_010_000:
        _exportScale = 10.0;
        break;
    }
  }
  
};












#endif

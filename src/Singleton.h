//
//  Singleton.h
//  emptyExample
//
//  Created by Takahiro Hirata on 12/04/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_Singleton_h
#define emptyExample_Singleton_h

#ifdef DEBUG 
//#define LOG(...) NSLog(__VA_ARGS__)
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) 
#endif

#define XYZ 3
#define XY 2
#define X_ID 0
#define Y_ID 1
#define Z_ID 2

#define V_MAX 3

#define EXPORT_AXIS_NONE 0
#define EXPORT_AXIS_ZTOY 1

#define EXPORT_SCALE_000_001 0
#define EXPORT_SCALE_000_010 1
#define EXPORT_SCALE_000_100 2
#define EXPORT_SCALE_000_200 3
#define EXPORT_SCALE_001_000 4
#define EXPORT_SCALE_010_000 5

#define MODE_SPIRAL 3

//#define MOBIEL
//#define MOBIEL_TOP

#include <iostream>


class Singleton{
  
public:
  // 唯一のアクセス経路
  static Singleton* GetInstance()
  {
    static Singleton instance;  // 唯一のインスタンス
    return &instance;
  }
  
  float _menMax;
  
  // あとは、このクラス自身が必要なメンバを定義する
  void init()
  {
    _menMax = V_MAX;
  }
  
  int getMenMax()
  {
    return _menMax;
  }
  
private:
  // 生成やコピーを禁止する
  Singleton(){}
  Singleton(const Singleton& rhs);
  Singleton& operator=(const Singleton& rhs);
};

#endif

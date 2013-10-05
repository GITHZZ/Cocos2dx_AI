//
//  DemoScene.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__DemoScene__
#define __Cocos2dx_AI__DemoScene__

#include "cocos2d.h"
#include "TileMap.h"
#include "AStar.h"
#include "Queue.h"
#include "Monster.h"
using namespace cocos2d;
class DemoScene : public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(DemoScene);
    
    //析构函数
    ~DemoScene();
private:
    TileMap* g_map;
};
#endif /* defined(__Cocos2dx_AI__DemoScene__) */

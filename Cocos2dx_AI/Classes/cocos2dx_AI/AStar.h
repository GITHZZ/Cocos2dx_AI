//
//  AStar.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__AStar__
#define __Cocos2dx_AI__AStar__

#include "cocos2d.h"
#include "TileMap.h"
using namespace cocos2d;
class AStar : public CCObject{
public:
    AStar();
    ~AStar();
    //运行AStar算法
    MapNode* doAStarSearch(CCPoint from,CCPoint to,TileMap* tileMap);
private:
    //方向
    CCPoint dir[8];
    //二分插入排序法
    void sortArrayUsingDichotomy(CCArray *arr);
};
#endif /* defined(__Cocos2dx_AI__AStar__) */

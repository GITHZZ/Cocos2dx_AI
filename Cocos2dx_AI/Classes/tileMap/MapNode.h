//
//  MapNode.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__MapNode__
#define __Cocos2dx_AI__MapNode__

#include "cocos2d.h"
using namespace cocos2d;
class MapNode : public CCObject{
public:
    MapNode();
private:
    CC_SYNTHESIZE(CCPoint, pos, Position);
    CC_SYNTHESIZE(int, f, F);
    CC_SYNTHESIZE(int, g, G);
    CC_SYNTHESIZE(int, h, H);
    CC_SYNTHESIZE(int, searchIndex, S_Index);
    CC_SYNTHESIZE(int, routeIndex, R_Index);
    CC_SYNTHESIZE(bool, isVisted, IsVisted);
    CC_SYNTHESIZE(MapNode*, parent, Parent);//使用链表存储
};
#endif /* defined(__Cocos2dx_AI__MapNode__) */

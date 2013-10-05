//
//  MapNode.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "MapNode.h"

MapNode::MapNode(){
    pos.x = pos.y = 0;
    f = g = h = 0;
    searchIndex = routeIndex = 0;
    isVisted = false;
    parent = NULL;
}
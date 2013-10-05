//
//  Queue.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__Queue__
#define __Cocos2dx_AI__Queue__

#include "cocos2d.h"
using namespace cocos2d;
class Queue : public CCObject{
public:
    Queue();
    ~Queue();
    void push(CCObject* obj);
    CCObject* pop();
    void clear();
private:
    CC_SYNTHESIZE_READONLY(CCArray*, data, Data);
    CC_SYNTHESIZE_READONLY(int, count, Count);
};

#endif /* defined(__Cocos2dx_AI__Queue__) */

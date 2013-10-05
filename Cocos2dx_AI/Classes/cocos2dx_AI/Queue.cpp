//
//  Queue.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "Queue.h"

Queue::Queue(){
    data = CCArray::create();
    count = 0;
}

Queue::~Queue(){
}

void Queue::push(CCObject* obj){
    data->addObject(obj);
    count = data->count();
}

CCObject* Queue::pop(){
    data->objectAtIndex(0);
    count = data->count();
    return data;
}

void Queue::clear(){
    data->removeAllObjects();
    count = 0;
}
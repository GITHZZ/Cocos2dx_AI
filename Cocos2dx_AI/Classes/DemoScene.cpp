//
//  DemoScene.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "DemoScene.h"

CCScene* DemoScene::scene(){
    CCScene* scene=CCScene::create();
    DemoScene* layer=DemoScene::create();
    scene->addChild(layer);
    return scene;
}

bool DemoScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    //加载tileMap的地图层
    g_map = new TileMap();
    g_map->initWithTileMap(1, this);
    
    //产生怪物
    Monster *monster = Monster::monsterWithFile("Monster.png");
    monster->setPosition(ccp(100,100));
    this->addChild(monster);
    monster->doMonsterMove(ccp(100, 100), ccp(200, 300), g_map);
    
    return true;
}

DemoScene::~DemoScene(){
    g_map->release();
}
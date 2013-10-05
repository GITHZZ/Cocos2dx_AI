//
//  TileMap.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "TileMap.h"

#define tilemap_tag 100
void TileMap::initWithTileMap(int index, cocos2d::CCLayer *layer){
    CCString *mapName = CCString::createWithFormat("gameMap%d.tmx",index);
    if (mapName) {
        CCLOG("[Info TileMap:13] you success to laoad Map gameMap%d.tmx",index);
    }
    CCTMXTiledMap *tileMap = CCTMXTiledMap::create(mapName->getCString());
    layer->addChild(tileMap,-1,tilemap_tag);
    
    //获取行列数
    ROWS = tileMap->getMapSize().height;
    COLS = tileMap->getMapSize().width;
    
    this->setLayer(layer);
}

CCTMXTiledMap* TileMap::getTileMap(){
    CCLayer *layer = this->getLayer();
    CCTMXTiledMap *tileMap = dynamic_cast<CCTMXTiledMap*>(layer->getChildByTag(tilemap_tag));
    return tileMap;
}

bool TileMap::canPassedXY(cocos2d::CCPoint pos){
    if (this->canPassedCOLROW(this->toRowCol(pos))) {
        return true;
    }
    return false;
}

bool TileMap::canPassedCOLROW(cocos2d::CCPoint pos){
    CCLayer *layer = this->getLayer();
    CCTMXTiledMap *tileMap = dynamic_cast<CCTMXTiledMap*>(layer->getChildByTag(tilemap_tag));
    //获得block层
    CCTMXLayer *block = tileMap->layerNamed("block");
    //获得砖块(根据某个位置)
    int tileGID = block->tileGIDAt(pos);
    if (tileGID) {
        CCDictionary *properties = tileMap->propertiesForGID(tileGID);
        if (properties) {
            const CCString *collion = properties->valueForKey("blockTiled");
            if (collion&&collion->compare("1")) {
                return true;
            }
        }
    }
    return true;
}

CCPoint TileMap::toRowCol(cocos2d::CCPoint pt){
    CCTMXTiledMap *tileMap = this->getTileMap();
    int x = pt.x/tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height)-pt.y)/
    tileMap->getTileSize().height;
    CCLOG("[INFO TileMap:32] XY TO ROWCOL (%d,%d)",x,y);
    return ccp(x,y);
}

CCPoint TileMap::toXY(cocos2d::CCPoint pt){
    CCTMXTiledMap *tileMap = this->getTileMap();
    CCPoint rt = ccp(pt.x*tileMap->getTileSize().width,
                     (tileMap->getMapSize().height*tileMap->getTileSize().height)-
                     (pt.y*tileMap->getTileSize().height));
    CCLOG("[INFO TileMap:32] ROWCOL TO XY (%f,%f)",rt.x,rt.y);
    return rt;
}

void TileMap::createMapNodes(){
    mapNodes = CCArray::create();
    for (int i = 0; i < ROWS*COLS; i++) {
        int x = i % COLS;
        int y = i / COLS;
        MapNode *mapNode = new MapNode();
        mapNode->setPosition(ccp(x,y));
        mapNodes->addObject(mapNode);
    }
}

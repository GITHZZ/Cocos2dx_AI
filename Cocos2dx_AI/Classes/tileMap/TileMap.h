//
//  TileMap.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__TileMap__
#define __Cocos2dx_AI__TileMap__

#include "cocos2d.h"
#include "MapNode.h"
using namespace cocos2d;
class TileMap : public CCObject{
public:
    void initWithTileMap(int index,CCLayer* layer);
    CCTMXTiledMap* getTileMap();
    CCPoint getGameObjInPos(CCString* objLayerName,CCString* objName);
    CCPoint toRowCol(CCPoint pt);
    CCPoint toXY(CCPoint pt);
    bool canPassedXY(CCPoint pos);
    bool canPassedCOLROW(CCPoint pos);
    //产生地图节点(寻路算法用)
    void createMapNodes();
private:
    //地图的行列数
    CC_SYNTHESIZE(int, COLS, COL);
    CC_SYNTHESIZE(int, ROWS, ROW);
    //存储节点的数组
    CC_SYNTHESIZE(CCArray*, mapNodes, MapNodes);
    
    CC_SYNTHESIZE(CCLayer*, layer, Layer);
    
};
#endif /* defined(__Cocos2dx_AI__TileMap__) */

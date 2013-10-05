//
//  AStar.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "AStar.h"

AStar::AStar(){
    dir[0] = ccp(1,0);
    dir[1] = ccp(1,1);
    dir[2] = ccp(0,-1);
    dir[3] = ccp(-1,-1);
    dir[4] = ccp(-1,0);
    dir[5] = ccp(-1,1);
    dir[6] = ccp(-1,-1);
    dir[7] = ccp(0,1);
}

AStar::~AStar(){
}

MapNode* AStar::doAStarSearch(cocos2d::CCPoint from, cocos2d::CCPoint to, TileMap *map){
    map->createMapNodes();
    
    CCArray *open = CCArray::create();//open列表作用是放入某点周围的8个节点进行比较
    CCArray *close = CCArray::create();//close列表是在open列表比较结束后放入close列表
    
    //将起始点到终点转换成tile坐标
    CCPoint fromCR = map->toRowCol(from);
    CCPoint toCR = map->toRowCol(to);
    
    CCArray *mapNodes = map->getMapNodes();
    //获取目标节点
    MapNode *end = dynamic_cast<MapNode*>(mapNodes->objectAtIndex(toCR.y*map->getCOL()+toCR.x));
    //获取起始节点
    MapNode *start = dynamic_cast<MapNode*>(mapNodes->objectAtIndex(fromCR.y*map->getCOL()+fromCR.x));
    //添加起始节点到open列表中
    open->addObject(start);
    //进入循环
    while (open != NULL) {
        sortArrayUsingDichotomy(open);
        //f中最小的节点
        static int minIndex = 0 ;
        MapNode *minNode = dynamic_cast<MapNode*>(open->objectAtIndex(minIndex));
        //CCLOG("(%f,%f)",minNode->getPosition().x,minNode->getPosition().y);
        //把最小的那个节点放入
        close->addObject(minNode);
        //判断是否为目标节点
        if (minNode->getPosition().x == end->getPosition().x&&
            minNode->getPosition().y == end->getPosition().y) {
            //成功寻找路径
            return minNode;
        }
        //移除open列表中的元素
        open->removeAllObjects();
        //循环判断该节点中周围8个节点的值
        for (int i = 0; i < 8; i++) {
            //遍历8个方向
            CCPoint nextPos = ccpAdd(minNode->getPosition(), dir[i]);
            //获取该点的节点
            MapNode *nextNode = dynamic_cast<MapNode*>(map->getMapNodes()->objectAtIndex(nextPos.y*map->getCOL()+nextPos.x));
            //节点是否可以访问
            if (map->canPassedCOLROW(nextNode->getPosition())&&
                !open->containsObject(nextNode)&&
                !close->containsObject(nextNode)&&
                !nextNode->getIsVisted()) {
                //计算权值
                if (dir[i].x != 0 && dir[i].y != 0) {
                    //斜边
                    nextNode->setG(minNode->getG()+14);
                }else{
                    nextNode->setG(minNode->getG()+10);
                }
                //计算h
                nextNode->setH(minNode->getH()+
                               (abs(toCR.x-nextPos.x)+abs(toCR.y-nextPos.y))*10);
                nextNode->setF(nextNode->getG() + nextNode->getH());
                //添加到open数组中
                open->addObject(nextNode);
                nextNode->setParent(minNode);//父节点
            }
            nextNode->setIsVisted(true);//代表已经访问过了
        }
    }
    
    //寻找路径失败
    return NULL;
}

void AStar::sortArrayUsingDichotomy(cocos2d::CCArray *arr){
    int j,low,high,mid;
    MapNode *node;
    for (int i = 1; i < arr->count(); i++) {
        //获取元素第二个元素
        node = dynamic_cast<MapNode*>(arr->objectAtIndex(i));
        int f = node->getF();
        low = 0; high = i - 1;//取得空间的最大和最小的序号值
        while (low <= high) {
            //取中间的位置
            mid = (low + high)/2;
            //获取中间的元素
            MapNode *node2 = dynamic_cast<MapNode*>(arr->objectAtIndex(mid));
            int f2 = node2->getF();
            //与中间的值比较
            if (f < f2) {//左边
                high = mid - 1;
            }else{//右边
                low = mid + 1;
            }
        }
        //记录后面移动
        for(j = i - 1;j >= high + 1 ;j--){
            MapNode *tempNode = dynamic_cast<MapNode*>(arr->objectAtIndex(j));
            int temp = j + 1;
            arr->replaceObjectAtIndex(temp,tempNode);
        }
        
        arr->replaceObjectAtIndex(high + 1, node);

    }
}
//
//  Monster.cpp
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#include "Monster.h"

Monster::Monster(){
    state = s_Stop;
    nodeArrayIndex = 0;
}

Monster::~Monster(){
}

Monster* Monster::monsterWithFile(const char *fileName){
    Monster *monster = new  Monster();
    if (monster->initWithMonster(fileName)) {
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Monster::initWithMonster(const char *fileName){
    //产生纹理
    CCSpriteBatchNode *partent = CCSpriteBatchNode::create(fileName, 100);
    CCTexture2D *m_spriteTexture = partent->getTexture();
    
    if (!partent) return false;
    
    this->initWithTexture(m_spriteTexture,CCRectMake(0, 0, 64, 64));
    
    if (this->initWithMonsterAnim(fileName)) {
        CCAnimate *forword = dynamic_cast<CCAnimate*>(monsterActions->objectAtIndex(m_up));
        this->runAction(CCRepeatForever::create(forword));
    }
    
    //进入循环
    this->schedule(schedule_selector(Monster::frameFunc), 1.0f/60.0f);
    
    return true;
}

bool Monster::initWithMonsterAnim(const char* fileName){
    //加载纹理
    CCTexture2D *texMonster = CCTextureCache::sharedTextureCache()->addImage(fileName);
    if (!texMonster) return false;
    //初始化monster动作
    monsterActions = CCArray::create();
    //存放每个动作的帧序列
    CCArray *animFrames = CCArray::create();
    for (int i = 0; i < 8; i++) {
        animFrames->removeAllObjects();
        for (int j = 0; j < 4; j++) {
            CCSpriteFrame *sprFrame = CCSpriteFrame::createWithTexture(texMonster,CCRectMake(j * 64, i * 64, 64, 64));
            CCAnimationFrame *frame = new CCAnimationFrame();
            frame->initWithSpriteFrame(sprFrame,0.5f,NULL);
            animFrames->addObject(frame);
            frame->release();
        }
        //使用帧序列创建动画
        CCAnimation *animation = CCAnimation::create(animFrames, 0.5f);
        CCAnimate *animate = CCAnimate::create(animation);
        monsterActions->addObject(animate);
    }
    return true;
}

void Monster::doMonsterMove(cocos2d::CCPoint start, cocos2d::CCPoint end,TileMap *map){
    //获取路径
    AStar *star = new AStar();
    MapNode *path = star->doAStarSearch(start, end, map);
    star->release();
    //回调链表并且存储到数组中
    nodes = CCArray::create();
    nodes->retain();
    
    MapNode *tempNode = path;
    while (tempNode) {
        //转换节点坐标
        tempNode->setPosition(map->toXY(tempNode->getPosition()));
        //添加到数组中
        nodes->addObject(tempNode);
        tempNode = tempNode->getParent();
    }
    //重新初始化monster坐标
    MapNode *startNode = dynamic_cast<MapNode*>(nodes->objectAtIndex(nodes->count()-1));
    CCPoint startPoint = startNode->getPosition();
    this->setPosition(startPoint);
    
    nodeArrayIndex = nodes->count()-2;
    
    //获取完了之后转换状态
    state = s_ReachTarget;
}

void Monster::frameFunc(cocos2d::CCTime dt){
    if (state == s_Stop) return;

    static CCPoint currentPos;

    switch (state) {
        case s_ReachTarget:{
            //代表已经到了目的点
            if (nodeArrayIndex < 0) {
                //释放数组
                nodes->release();
                //转换状态
                state = s_Stop;
                break;
            }
            //获取当前坐标
            MapNode *currentNode = dynamic_cast<MapNode*>(nodes->objectAtIndex(nodeArrayIndex));
            currentPos = currentNode->getPosition();
            //转换状态移动
            state = s_Chasing;
        }
            break;
        case s_MeetObstacle:
            break;
        case s_Chasing:{
            //计算向量
            CCPoint subPos = ccpSub(currentPos,this->getPosition());
            //移动monster
            this->setPosition(ccpAdd(this->getPosition(), ccpNormalize(subPos)));
            
            if (this->getPosition().x == currentPos.x&&
                this->getPosition().y == currentPos.y) {
                nodeArrayIndex--;
                state = s_ReachTarget;
            }
        }
            break;
        default:
            break;
    }
}
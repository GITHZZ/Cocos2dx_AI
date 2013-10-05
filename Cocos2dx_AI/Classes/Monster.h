//
//  Monster.h
//  Cocos2dx_AI
//
//  Created by 何遵祖 on 13-9-24.
//
//

#ifndef __Cocos2dx_AI__Monster__
#define __Cocos2dx_AI__Monster__

#include "cocos2d.h"
#include "MapNode.h"
#include "AStar.h"
using namespace cocos2d;
typedef enum{
    s_Stop,
    s_Chasing,
    s_ReachTarget,
    s_MeetObstacle
}MonsterState;
typedef enum{
    m_down = 0,
    m_left = 1,
    m_right = 2,
    m_up = 3,
    m_leftdown = 4,
    m_rightdown = 5,
    m_leftup = 6,
    m_rightup = 7
}ActionType;
class Monster : public CCSprite{
public:
    Monster();
    ~Monster();
    static Monster* monsterWithFile(const char* fileName);
    bool initWithMonster(const char* fileName);
    //移动Monster
    void doMonsterMove(CCPoint start,CCPoint end,TileMap *map);
private:
    CCArray *monsterActions;
    CCArray *nodes;
    int nodeArrayIndex;//用于显示数组序列号
    CC_SYNTHESIZE_READONLY(MonsterState, state, State);
    //初始化Monster动画
    bool initWithMonsterAnim(const char* fileName);
    //根据向量更新怪物方向
    void updateMonsterState();
    //循环移动
    void frameFunc(CCTime dt);
};
#endif /* defined(__Cocos2dx_AI__Monster__) */

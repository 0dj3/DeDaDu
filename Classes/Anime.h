#ifndef __ANIME_H__
#define __ANIME_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>


class Anime : public cocos2d::Sprite
{
public:
    Anime();

    int frame;
    char* pathPlist;

    void runAnimation();
    void idleAnimation();
    void dieAnimation();

private:
    
};

#endif // __ANIME_H__

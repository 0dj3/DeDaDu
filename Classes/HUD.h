#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "ui/CocosGUI.h"
#include "Unit.h"

USING_NS_CC;

class HUD : public Sprite
{
public:
    static HUD* create();
    ui::LoadingBar* healthBar;
    Sprite* hBBackground;
    Sprite* weaponSlot;
    Sprite* coinBar;
    Label* counter;
    
    void getHit(int damage, Unit* player);
    void updatePos(Unit* player);
    void setGold(int plus);
    Menu* menubutton;
    int gold = 0;
private:
    void Init();
    int health = 80;
    void GoToMenu(cocos2d::Ref* sender);
};

#endif // __HUD_H__

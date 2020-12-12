#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "ui/CocosGUI.h"
#include "Unit.h"
#include "Player.h"
#include <string>

USING_NS_CC;

class HUD : public Sprite
{
public:
    static HUD* create(Player* player);

    static void DisplayString(Vec2 position, std::string value, int fontSize, Color3B color);
    
    Sprite* hBBackground;
    ui::LoadingBar* healthBar;
    Sprite* coinBar;
    Label* counter;
    Sprite* weaponSprite;
    Sprite* weaponSlot;
    Label* damagestats;
    Label* delaystats;
    Player* playerHUD;
    
    void getHit(int damage, Unit* player);
    /*void updatePos(Unit* player);*/
    void setGold(int plus);
    Menu* menubutton;
private:
    void Init();
    int health = 80;
    void GoToMenu(cocos2d::Ref* sender);
    void update(float dt);
};

#endif // __HUD_H__

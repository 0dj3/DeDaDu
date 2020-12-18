#include "Portal.h"

Portal* Portal::create(){
	Portal* portal = new Portal();
	portal->init();
	return portal;
}

bool Portal::init(){
	auto portal = PortalSprite();
	this->addChild(portal);
	return true;
}

Sprite* Portal::PortalSprite() {
	portal = Sprite::create();
	//portal->setDisplayFrameWithAnimationName("portal/portalEnd.gif", 10);
	return portal;
}
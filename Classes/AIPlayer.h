#ifndef __AIPLAYER_H__
#define __AIPLAYER_H__

#include"cocos2d.h"
#include "Player.h"

class AIPlayer : public Player
{
	static AIPlayer* create();
	//ѡ�����ʵ���
	void findFitCard();
};

#endif

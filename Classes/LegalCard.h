#ifndef __LEGALCARD_H__
#define __LEGALCARD_H__

#include"cocos2d.h"
#include"Card.h"

class LegalCard
{
public:
	void addCard(Card* card);
	void eraseCard(Card* card);

private:
	cocos2d::Vector<Card*> _vCard;
};

#endif
#ifndef __CARD_H__
#define __CARD_H__

#include "cocos2d.h"
const double cardScale = 0.75;
const double cardSizeX = 129;
const double cardSizeY = 167;
//0������ƣ�1����С��
enum CardSize
{
	BIG_CARD,
	SMALL_CARD
};
//��ɫ0��1��2��
enum CardColor
{
	BLACK,
	RED,
	GOLD
};
//�Ƶ�ӵ����
enum CardOwner
{
	FARM,
	LANDLORD
};
//��ɫ 0���ģ�1���� 2���� 3÷�� 4��
enum CardFlower
{
	HEART,
	DIAMOND,
	SPADE,
	CLUB,
	NONE
};
enum CardBody
{
	BACKGROUND,
	NUMBER,
	FLOWER
};
class Card :public cocos2d::Sprite
{
public:
	Card::Card();
	static Card* createCard(CardSize size, int number, CardColor color,CardFlower flower, CardOwner owner);
	virtual bool init();
	bool initData(CardSize size, int number, CardColor color,CardFlower flower, CardOwner owner);
	
	int getCardNumber()const;
	void setCardSize(CardSize size);
	CardSize getCardSize()const;
	bool getCardTouched() const;
	void setCardTouched(bool touched);
private:
	//cocos2d::Sprite* _background;//���Ʊ���
	cocos2d::Sprite* _flower;//��ɫ
	cocos2d::Sprite* _number;//����
	CardColor _cardColor;//���ֺ�joker��ɫ
	CardFlower _cardFlower;//��ɫ
	CardSize _cardSize;  
	CardOwner _cardOwner;
	int _cardNumber;
	bool _touched;//�Ƿ񱻵��

};
#endif
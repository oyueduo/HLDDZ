#include"Card.h"

USING_NS_CC;

Card::Card()
{
	
}

Card* Card::createCard(CardSize size, int number, CardColor color,CardFlower flower, CardOwner owner)
{
	auto card = new Card();
	if (card && card->initWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_%dcard_f.png", (int)size)))
	{
		card->autorelease();
		card->initData( size, number,  color,flower,  owner);
		return card;
	}
	CC_SAFE_DELETE(card);
	return nullptr;
}

bool Card::init()
{
	if (Node::init())
		return true;
	
	return false;
}

bool Card::initData(CardSize size, int number, CardColor color,CardFlower flower, CardOwner owner)
{
	/* _background = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_%dcard_f.png", (int)size));
	 this->addChild(_background,0,CardBody::BACKGROUND);
	 this->setContentSize(_background->getContentSize());
*/
     _number = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_%d%d_%02d.png",(int)size,(int)color,number));
	 _number->setAnchorPoint(Vec2(0, 1));
	 _number->setPosition(Vec2(5, this/*_background*/->getContentSize().height-5));
	 this/*_background*/->addChild(_number,1,CardBody::NUMBER);

	 if (number <= 13)
	 {
		 _flower = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_%d%d.png",(int)size,(int) flower));
		 _flower->setAnchorPoint(Vec2(0, 1));
		 _flower->setPosition(Vec2(10, this/*_background*/->getContentSize().height-5 - _number->getContentSize().height));
		this/* _background*/->addChild(_flower,1,CardBody::FLOWER);
	 }
	 this->setScale(cardScale);
	 this->setContentSize(this->getContentSize()*cardScale);

	 _cardSize = size;
	 _cardNumber = number;
	 _cardFlower = flower;
	 _cardColor = color;
	 _cardOwner = owner;
	 _touched = false;
	return true;
}


int Card::getCardNumber() const
{
	return _cardNumber;
}

void Card::setCardSize(CardSize size)
{
	
	if (size != _cardSize)
	{
		this->removeAllChildrenWithCleanup(true);
		initData(size, _cardNumber, _cardColor, _cardFlower, _cardOwner);
	}
		_cardSize = size;
}

bool Card::getCardTouched() const
{
	return _touched;
}

void Card::setCardTouched(bool touched)
{
	_touched = touched;
}




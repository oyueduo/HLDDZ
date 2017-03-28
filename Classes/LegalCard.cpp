#include"LegalCard.h"

USING_NS_CC;

void LegalCard::addCard(Card * card)
{
	if (card != nullptr)
		_vCard.pushBack(card);
}

void LegalCard::eraseCard(Card * card)
{
	if (card != nullptr)
			_vCard.eraseObject(card, false);

}

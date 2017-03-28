#pragma once
#include"GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{
	_gameRule = new GameRule();
}

GameScene::~GameScene()
{
	delete _gameRule;
	_gameRule = nullptr;
}

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Common_BG2_2x.png");
	background->setScale(800.0 / 960.0f);
	background->setAnchorPoint(Vec2(0, 1));
	background->setPosition(0, visibleSize.height);
	this->addChild(background, 0);
	initData();

	newGame();
	//clock
	auto clockSprite = Clock::create();
	clockSprite->setScale(0.5f);
	clockSprite->setPosition(Vec2(visibleSize.width * 5 / 9 - 15, visibleSize.height * 2 / 5));
	this->addChild(clockSprite, 3, CLOCKSPRITE);
	clockSprite->setTime(30);

	//���2�Ʊ���
	auto _player2Card = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_0card_b.png"));
	_player2Card->setScale(0.5);
	_player2Card->setPosition(Vec2(650, 300));
	this->addChild(_player2Card);
	//���3�Ʊ���
	auto _player3Card = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_0card_b.png"));
	_player3Card->setScale(0.5);
	_player3Card->setPosition(Vec2(150, 300));
	this->addChild(_player3Card);
	//���2����
	_player2CardNumber = Label::createWithSystemFont(StringUtils::format("%d", _player2->getCardNumber()), "Arial", 30);
	_player2CardNumber->setColor(Color3B::BLACK);
	_player2CardNumber->setPosition(_player2Card->getContentSize().width / 2, _player2Card->getContentSize().height / 2);
	_player2Card->addChild(_player2CardNumber);
	//���3����
	_player3CardNumber = Label::createWithSystemFont(StringUtils::format("%d", _player3->getCardNumber()), "Arial", 30);
	_player3CardNumber->setColor(Color3B::BLACK);
	_player3CardNumber->setPosition(_player3Card->getContentSize().width / 2, _player3Card->getContentSize().height / 2);
	_player3Card->addChild(_player3CardNumber);

	auto jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��
	auto di = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��
	auto zhu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��
	auto jiao1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��1
	jiao1->setScale(0.9f);
	auto di1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��1
	di1->setScale(0.9f);
	auto zhu1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��1
	zhu1->setScale(0.9f);
	auto normalJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalJiaoBgR->runAction(FlipX::create(true));
	selectedJiaoBgR->runAction(FlipX::create(true));

	jiao->setPosition(Vec2(normalJiaoBgL->getContentSize().width / 2, normalJiaoBgL->getContentSize().height / 2));
	jiao1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width / 2, selectedJiaoBgL->getContentSize().height / 2));

	di->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 2 / 2, normalJiaoBgL->getContentSize().height / 2));
	di1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 2 / 2, selectedJiaoBgL->getContentSize().height / 2));

	zhu->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 3 / 2, normalJiaoBgL->getContentSize().height / 2));
	zhu1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 3 / 2, selectedJiaoBgL->getContentSize().height / 2));

	normalJiaoBgR->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 3 / 2, normalJiaoBgL->getContentSize().height / 2));
	selectedJiaoBgR->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 3 / 2, selectedJiaoBgL->getContentSize().height / 2));

	normalJiaoBgL->addChild(normalJiaoBgR);
	normalJiaoBgL->addChild(jiao);
	normalJiaoBgL->addChild(di);
	normalJiaoBgL->addChild(zhu);
	normalJiaoBgL->setScale(0.5);
	normalJiaoBgL->setContentSize(Size(normalJiaoBgL->getContentSize().width / 2, normalJiaoBgL->getContentSize().height / 2));

	selectedJiaoBgL->addChild(selectedJiaoBgR);
	selectedJiaoBgL->addChild(jiao1);
	selectedJiaoBgL->addChild(di1);
	selectedJiaoBgL->addChild(zhu1);
	selectedJiaoBgL->setScale(0.5);
	selectedJiaoBgL->setContentSize(Size(selectedJiaoBgL->getContentSize().width / 2, selectedJiaoBgL->getContentSize().height / 2));

	jiaoButton = MenuItemSprite::create(normalJiaoBgL, selectedJiaoBgL, CC_CALLBACK_0(GameScene::callLandlord, this));
	jiaoButton->setContentSize(Size(jiaoButton->getContentSize().width * 2, jiaoButton->getContentSize().height));

	auto qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��
	auto di2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��
	auto zhu2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��
	auto qiang1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��1
	qiang1->setScale(0.9f);
	auto di3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��1
	di3->setScale(0.9f);
	auto zhu3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��1
	zhu3->setScale(0.9f);
	auto normalQiangBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalQiangBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedQiangBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedQiangBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalQiangBgR->runAction(FlipX::create(true));
	selectedQiangBgR->runAction(FlipX::create(true));

	qiang->setPosition(Vec2(normalQiangBgL->getContentSize().width / 2, normalQiangBgL->getContentSize().height / 2));
	qiang1->setPosition(Vec2(selectedQiangBgL->getContentSize().width / 2, selectedQiangBgL->getContentSize().height / 2));

	di2->setPosition(Vec2(normalQiangBgL->getContentSize().width * 2 / 2, normalQiangBgL->getContentSize().height / 2));
	di3->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 2 / 2, selectedQiangBgL->getContentSize().height / 2));

	zhu2->setPosition(Vec2(normalQiangBgL->getContentSize().width * 3 / 2, normalQiangBgL->getContentSize().height / 2));
	zhu3->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 3 / 2, selectedQiangBgL->getContentSize().height / 2));

	normalQiangBgR->setPosition(Vec2(normalQiangBgL->getContentSize().width * 3 / 2, normalQiangBgL->getContentSize().height / 2));
	selectedQiangBgR->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 3 / 2, selectedQiangBgL->getContentSize().height / 2));

	normalQiangBgL->addChild(normalQiangBgR);
	normalQiangBgL->addChild(qiang);
	normalQiangBgL->addChild(di2);
	normalQiangBgL->addChild(zhu2);
	normalQiangBgL->setScale(0.5);
	normalQiangBgL->setContentSize(Size(normalQiangBgL->getContentSize().width / 2, normalQiangBgL->getContentSize().height / 2));

	selectedQiangBgL->addChild(selectedQiangBgR);
	selectedQiangBgL->addChild(qiang1);
	selectedQiangBgL->addChild(di3);
	selectedQiangBgL->addChild(zhu3);
	selectedQiangBgL->setScale(0.5);
	selectedQiangBgL->setContentSize(Size(selectedQiangBgL->getContentSize().width / 2, selectedQiangBgL->getContentSize().height / 2));

	qiangButton = MenuItemSprite::create(normalQiangBgL, selectedQiangBgL, CC_CALLBACK_0(GameScene::landlords, this));
	qiangButton->setContentSize(Size(qiangButton->getContentSize().width * 2, qiangButton->getContentSize().height));

	auto qiangSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��
	auto buSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
	auto qiangSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��1
	qiangSprite1->setScale(0.9f);
	auto buSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
	buSprite1->setScale(0.9f);
	auto normalBuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalBuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedBuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedBuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalBuBgR->runAction(FlipX::create(true));
	selectedBuBgR->runAction(FlipX::create(true));

	qiangSprite->setPosition(Vec2(normalBuBgL->getContentSize().width / 2, normalBuBgL->getContentSize().height / 2));
	qiangSprite1->setPosition(Vec2(selectedBuBgL->getContentSize().width / 2, selectedBuBgL->getContentSize().height / 2));

	buSprite->setPosition(Vec2(normalBuBgL->getContentSize().width * 2 / 2, normalBuBgL->getContentSize().height / 2));
	buSprite1->setPosition(Vec2(selectedBuBgL->getContentSize().width * 2 / 2, selectedBuBgL->getContentSize().height / 2));

	normalBuBgR->setPosition(Vec2(normalBuBgL->getContentSize().width * 3 / 2, normalBuBgL->getContentSize().height / 2));
	selectedBuBgR->setPosition(Vec2(selectedBuBgL->getContentSize().width * 3 / 2, selectedBuBgL->getContentSize().height / 2));

	normalBuBgL->addChild(normalBuBgR);
	normalBuBgL->addChild(qiangSprite);
	normalBuBgL->addChild(buSprite);
	normalBuBgL->setScale(0.5);
	normalBuBgL->setContentSize(Size(normalBuBgL->getContentSize().width / 2, normalBuBgL->getContentSize().height / 2));

	selectedBuBgL->addChild(selectedBuBgR);
	selectedBuBgL->addChild(qiangSprite1);
	selectedBuBgL->addChild(buSprite1);
	selectedBuBgL->setScale(0.5);
	selectedBuBgL->setContentSize(Size(selectedBuBgL->getContentSize().width / 2, selectedBuBgL->getContentSize().height / 2));

	buqiangButton = MenuItemSprite::create(normalBuBgL, selectedBuBgL, CC_CALLBACK_0(GameScene::notQiangLandlord, this));
	buqiangButton->setContentSize(Size(buqiangButton->getContentSize().width * 2, buqiangButton->getContentSize().height));

	auto jiaoSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��
	auto buSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
	auto jiaoSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��1
	jiaoSprite1->setScale(0.9f);
	auto buSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
	buSprite3->setScale(0.9f);
	auto normalBuJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalBuJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedBuJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedBuJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalBuJiaoBgR->runAction(FlipX::create(true));
	selectedBuJiaoBgR->runAction(FlipX::create(true));

	jiaoSprite->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width / 2, normalBuJiaoBgL->getContentSize().height / 2));
	jiaoSprite1->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width / 2, selectedBuJiaoBgL->getContentSize().height / 2));

	buSprite2->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width * 2 / 2, normalBuJiaoBgL->getContentSize().height / 2));
	buSprite3->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width * 2 / 2, selectedBuJiaoBgL->getContentSize().height / 2));

	normalBuJiaoBgR->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width * 3 / 2, normalBuJiaoBgL->getContentSize().height / 2));
	selectedBuJiaoBgR->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width * 3 / 2, selectedBuJiaoBgL->getContentSize().height / 2));

	normalBuJiaoBgL->addChild(normalBuJiaoBgR);
	normalBuJiaoBgL->addChild(jiaoSprite);
	normalBuJiaoBgL->addChild(buSprite2);
	normalBuJiaoBgL->setScale(0.5);
	normalBuJiaoBgL->setContentSize(Size(normalBuJiaoBgL->getContentSize().width / 2, normalBuJiaoBgL->getContentSize().height / 2));

	selectedBuJiaoBgL->addChild(selectedBuJiaoBgR);
	selectedBuJiaoBgL->addChild(jiaoSprite1);
	selectedBuJiaoBgL->addChild(buSprite3);
	selectedBuJiaoBgL->setScale(0.5);
	selectedBuJiaoBgL->setContentSize(Size(selectedBuJiaoBgL->getContentSize().width / 2, selectedBuJiaoBgL->getContentSize().height / 2));

	bujiaoButton = MenuItemSprite::create(normalBuJiaoBgL, selectedBuJiaoBgL, CC_CALLBACK_0(GameScene::notWantLandlord, this));
	bujiaoButton->setContentSize(Size(bujiaoButton->getContentSize().width * 2, bujiaoButton->getContentSize().height));

	auto chu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_193.png");//��
	auto pai = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_194.png");//��
	auto chu1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_193.png");//��1
	chu1->setScale(0.9f);
	auto pai1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_194.png");//��1
	pai1->setScale(0.9f);
	auto normalChuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_295.png");//�����󱳾�
	auto normalChuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_295.png");//�����ұ���
	auto selectedChuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_296.png");//�����󱳾�
	auto selectedChuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_296.png");//�����ұ���

	normalChuBgR->runAction(FlipX::create(true));
	selectedChuBgR->runAction(FlipX::create(true));

	chu->setPosition(Vec2(normalChuBgL->getContentSize().width / 2, normalChuBgL->getContentSize().height / 2));
	chu1->setPosition(Vec2(selectedChuBgL->getContentSize().width / 2, selectedChuBgL->getContentSize().height / 2));

	pai->setPosition(Vec2(normalChuBgL->getContentSize().width * 3 / 2, normalChuBgL->getContentSize().height / 2));
	pai1->setPosition(Vec2(selectedChuBgL->getContentSize().width * 3 / 2, selectedChuBgL->getContentSize().height / 2));

	normalChuBgR->setPosition(Vec2(normalChuBgL->getContentSize().width * 3 / 2, normalChuBgL->getContentSize().height / 2));
	selectedChuBgR->setPosition(Vec2(selectedChuBgL->getContentSize().width * 3 / 2, selectedChuBgL->getContentSize().height / 2));

	normalChuBgL->addChild(normalChuBgR);
	normalChuBgL->addChild(chu);
	normalChuBgL->addChild(pai);
	normalChuBgL->setScale(0.5);
	normalChuBgL->setContentSize(Size(normalChuBgL->getContentSize().width / 2, normalChuBgL->getContentSize().height / 2));

	selectedChuBgL->addChild(selectedChuBgR);
	selectedChuBgL->addChild(chu1);
	selectedChuBgL->addChild(pai1);
	selectedChuBgL->setScale(0.5);
	selectedChuBgL->setContentSize(Size(selectedChuBgL->getContentSize().width / 2, selectedChuBgL->getContentSize().height / 2));

	chuButton = MenuItemSprite::create(normalChuBgL, selectedChuBgL, CC_CALLBACK_0(GameScene::pushCard, this));
	chuButton->setContentSize(Size(chuButton->getContentSize().width * 2, chuButton->getContentSize().height));
	//����
	auto passSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
	auto passSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_168.png");//��
	auto passSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
	passSprite3->setScale(0.9f);
	auto passSprite4 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_168.png");//��1
	passSprite4->setScale(0.9f);
	auto normalPassBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalPassBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedPassBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedPassBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalPassBgR->runAction(FlipX::create(true));
	selectedPassBgR->runAction(FlipX::create(true));

	passSprite1->setPosition(Vec2(normalPassBgL->getContentSize().width / 2, normalPassBgL->getContentSize().height / 2));
	passSprite3->setPosition(Vec2(selectedPassBgL->getContentSize().width / 2, selectedPassBgL->getContentSize().height / 2));

	passSprite2->setPosition(Vec2(normalPassBgL->getContentSize().width * 3 / 2, normalPassBgL->getContentSize().height / 2));
	passSprite4->setPosition(Vec2(selectedPassBgL->getContentSize().width * 3 / 2, selectedPassBgL->getContentSize().height / 2));

	normalPassBgR->setPosition(Vec2(normalPassBgL->getContentSize().width * 3 / 2, normalPassBgL->getContentSize().height / 2));
	selectedPassBgR->setPosition(Vec2(selectedPassBgL->getContentSize().width * 3 / 2, selectedPassBgL->getContentSize().height / 2));

	normalPassBgL->addChild(normalPassBgR);
	normalPassBgL->addChild(passSprite1);
	normalPassBgL->addChild(passSprite2);
	normalPassBgL->setScale(0.5);
	normalPassBgL->setContentSize(Size(normalPassBgL->getContentSize().width / 2, normalPassBgL->getContentSize().height / 2));

	selectedPassBgL->addChild(selectedPassBgR);
	selectedPassBgL->addChild(passSprite3);
	selectedPassBgL->addChild(passSprite4);
	selectedPassBgL->setScale(0.5);
	selectedPassBgL->setContentSize(Size(selectedPassBgL->getContentSize().width / 2, selectedPassBgL->getContentSize().height / 2));
	passButton = MenuItemSprite::create(normalPassBgL, selectedPassBgL, CC_CALLBACK_0(GameScene::pass, this, _player1));
	passButton->setContentSize(Size(passButton->getContentSize().width * 2, passButton->getContentSize().height));
	//��ʾ
	auto hintSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_191.png");//��
	auto hintSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_192.png");//��
	auto hintSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_191.png");//1
	hintSprite3->setScale(0.9f);
	auto hintSprite4 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_192.png");//��1
	hintSprite4->setScale(0.9f);
	auto normalHintBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
	auto normalHintBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
	auto selectedHintBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
	auto selectedHintBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���

	normalHintBgR->runAction(FlipX::create(true));
	selectedHintBgR->runAction(FlipX::create(true));

	hintSprite1->setPosition(Vec2(normalHintBgL->getContentSize().width / 2, normalHintBgL->getContentSize().height / 2));
	hintSprite3->setPosition(Vec2(selectedHintBgL->getContentSize().width / 2, selectedHintBgL->getContentSize().height / 2));

	hintSprite2->setPosition(Vec2(normalHintBgL->getContentSize().width * 3 / 2, normalHintBgL->getContentSize().height / 2));
	hintSprite4->setPosition(Vec2(selectedHintBgL->getContentSize().width * 3 / 2, selectedHintBgL->getContentSize().height / 2));

	normalHintBgR->setPosition(Vec2(normalHintBgL->getContentSize().width * 3 / 2, normalHintBgL->getContentSize().height / 2));
	selectedHintBgR->setPosition(Vec2(selectedHintBgL->getContentSize().width * 3 / 2, selectedHintBgL->getContentSize().height / 2));

	normalHintBgL->addChild(normalHintBgR);
	normalHintBgL->addChild(hintSprite1);
	normalHintBgL->addChild(hintSprite2);
	normalHintBgL->setScale(0.5);
	normalHintBgL->setContentSize(Size(normalHintBgL->getContentSize().width / 2, normalHintBgL->getContentSize().height / 2));

	selectedHintBgL->addChild(selectedHintBgR);
	selectedHintBgL->addChild(hintSprite3);
	selectedHintBgL->addChild(hintSprite4);
	selectedHintBgL->setScale(0.5);
	selectedHintBgL->setContentSize(Size(selectedHintBgL->getContentSize().width / 2, selectedHintBgL->getContentSize().height / 2));
	hintButton = MenuItemSprite::create(normalHintBgL, selectedHintBgL, CC_CALLBACK_0(GameScene::hint, this, _player1));
	hintButton->setContentSize(Size(hintButton->getContentSize().width * 2, hintButton->getContentSize().height));
	//
	chuButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));
	passButton->setPosition(Vec2(visibleSize.width * 3 / 9 - 5, visibleSize.height * 2 / 5));
	hintButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));

	jiaoButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));
	qiangButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));
	buqiangButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));
	bujiaoButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));

	auto menu = Menu::create(chuButton, passButton, hintButton, NULL);
	auto qiangMenu = Menu::create(qiangButton, buqiangButton, NULL);
	auto jiaoMenu = Menu::create(jiaoButton, bujiaoButton, NULL);
	/*menu->alignItemsHorizontally();*/
	/*menu->setPosition(Vec2(visibleSize.width * 3 / 8, visibleSize.height *2/ 5));*/
	menu->setPosition(Vec2::ZERO);
	qiangMenu->setPosition(Vec2::ZERO);
	jiaoMenu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1, 10);//button tag =10
	this->addChild(jiaoMenu, 1, 10);
	this->addChild(qiangMenu, 1, 10);
	//chuButton->setEnabled(false);

	chuButton->setEnabled(false);
	passButton->setEnabled(false);
	hintButton->setEnabled(false);
	qiangButton->setEnabled(false);
	jiaoButton->setEnabled(false);
	bujiaoButton->setEnabled(false);
	buqiangButton->setEnabled(false);

	chuButton->setVisible(false);
	passButton->setVisible(false);
	hintButton->setVisible(false);
	qiangButton->setVisible(false);
	jiaoButton->setVisible(false);
	bujiaoButton->setVisible(false);
	buqiangButton->setVisible(false);

	//_currentPlayer = _player1;//���1�ȳ���

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	if (rand() % 3 == 0)                  //
	{
		jiaoButton->setEnabled(true);
		bujiaoButton->setEnabled(true);

		jiaoButton->setVisible(true);
		bujiaoButton->setVisible(true);

		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));

	}
	else if (rand() % 3 == 1)
	{
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));

		if (rand() % 10 > 5)
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));

	}
	else
	{
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));

		if (rand() % 10 > 5)
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));
	}

	return true;
}

bool GameScene::initData()
{
	//GameRul
	//_gameRule=
	//CardTypeArray cardArra
	//_cardTypeArray = &cardArray;

	_cardType = CardType::NOTYPE;
	_cardArrayNumber = 0;
	_cardLength = 0;
	_passTimes = 0;
	_isPass = false;

	_prePlayer1BuChu = NULL;
	_prePlayer2BuChu = NULL;
	_prePlayer3BuChu = NULL;

	_player1 = Player::create(playerType::PLAYER_1);
	_player2 = Player::create(playerType::PLAYER_2);
	_player3 = Player::create(playerType::PLAYER_3);

	_player1->setAI(false);
	_player2->setAI(true);
	_player3->setAI(true);

	this->addChild(_player1);
	this->addChild(_player2);
	this->addChild(_player3);
	_currentCard.clear();

	bujiaoTimes = 0;
	return true;
}
void GameScene::showCard()
{
	_player1->arrangeCard();
	_player2->arrangeCard();
	_player3->arrangeCard();
	_player1->showCard();
	_player2->showCard();
	_player3->showCard();
}
//����
void GameScene::sendCard()
{
	for (auto i = 0; i<51; i++)
	{
		if (i < 17)
			_player1->getCard(_vCard.at(i));
		else if (i >= 17 && i <= 33)
			_player2->getCard(_vCard.at(i));
		else
			_player3->getCard(_vCard.at(i));
	}
}
//ϴ��
void GameScene::shuffleCard()
{

	srand((unsigned int)time);
	for (int i = 53; i >0; i--)
	{
		int j = rand() % i;
		_vCard.swap(_vCard.at(i), _vCard.at(j));
	}
}

void GameScene::createCard()
{
	for (int i = 1; i <= 13; i++)
	{
		auto cardHeart = Card::createCard(CardSize::BIG_CARD, i, CardColor::RED, CardFlower::HEART, CardOwner::FARM);
		_vCard.pushBack(cardHeart);
		auto cartDiamond = Card::createCard(CardSize::BIG_CARD, i, CardColor::RED, CardFlower::DIAMOND, CardOwner::FARM);
		_vCard.pushBack(cartDiamond);
		auto cardSpade = Card::createCard(CardSize::BIG_CARD, i, CardColor::BLACK, CardFlower::SPADE, CardOwner::FARM);
		_vCard.pushBack(cardSpade);
		auto cardClub = Card::createCard(CardSize::BIG_CARD, i, CardColor::BLACK, CardFlower::CLUB, CardOwner::FARM);
		_vCard.pushBack(cardClub);
	}
	auto joker1 = Card::createCard(CardSize::BIG_CARD, 14, CardColor::BLACK, CardFlower::NONE, CardOwner::FARM);
	auto joker2 = Card::createCard(CardSize::BIG_CARD, 15, CardColor::RED, CardFlower::NONE, CardOwner::FARM);
	_vCard.pushBack(joker1);
	_vCard.pushBack(joker2);
}

void GameScene::newGame()
{
	createCard();
	shuffleCard();
	sendCard();
	showCard();
}

void GameScene::restartGame()
{
	this->removeAllChildrenWithCleanup(true);
	_vCard.clear();
	_player1 = NULL;
	_player2 = NULL;
	_player3 = NULL;
	//��һ�ֳ�����
	_prePlayer1Card.clear();
	_prePlayer2Card.clear();
	_prePlayer3Card.clear();
	//��һ�ֵĲ���
	_prePlayer1BuChu = NULL;
	_prePlayer2BuChu = NULL;
	_prePlayer3BuChu = NULL;
	////��ǰ������
	_currentCard.clear();
	//��ǰ���Ƶ���
	_currentPlayer = NULL;
	delete _gameRule;
	_gameRule = NULL;
	//��ǰ���Ƶ�����
	//��ǰ��������

	_player2CardNumber = NULL;
	_player3CardNumber = NULL;
	chuButton = NULL;
	passButton = NULL;
	hintButton = NULL;
	jiaoButton = NULL;
	qiangButton = NULL;
	buqiangButton = NULL;
	bujiaoButton = NULL;
	while (!wantLandlord.empty())
		wantLandlord.pop();
	_callLandlord = NULL;//�е������
	bujiaoTimes = 0;
	init();
}

void GameScene::pushCard()
{
	/*log("_currentCard.size 1= %d", _currentPlayer->getCurrentCard().size());*/
	if (_currentPlayer == _player1)                      //ɾ�����2��һ�ε���
	{
		if (_prePlayer2Card.size() != 0)
		{
			for (auto card : _prePlayer2Card)
			{
				card->runAction(RemoveSelf::create(true));
			}
			_prePlayer2Card.clear();
		}
		if (_prePlayer2BuChu != NULL)
		{
			_prePlayer2BuChu->removeFromParentAndCleanup(true);
			_prePlayer2BuChu = NULL;
		}
	}
	else if (_currentPlayer == _player2)                //ɾ�����3��һ�ε���
	{
		if (_prePlayer3Card.size() != 0)
		{
			for (auto card : _prePlayer3Card)
			{
				card->runAction(RemoveSelf::create(true));
			}
			_prePlayer3Card.clear();
		}
		if (_prePlayer3BuChu != NULL)
		{
			_prePlayer3BuChu->removeFromParentAndCleanup(true);
			_prePlayer3BuChu = NULL;
		}
	}
	else                                               //ɾ�����1��һ�ε���
	{
		if (_prePlayer1Card.size() != 0)
		{
			for (auto card : _prePlayer1Card)
			{
				card->runAction(RemoveSelf::create(true));
			}
			_prePlayer1Card.clear();
		}
		if (_prePlayer1BuChu != NULL)
		{
			_prePlayer1BuChu->removeFromParentAndCleanup(true);
			_prePlayer1BuChu = NULL;
		}
	}
	if (!_isPass)//û��
	{
		/*for (auto i = 0; i < _currentPlayer->getCurrentCard().size(); i++)
		log("%d", _currentPlayer->getCurrentCard().at(i)->getCardNumber());*/
		//    �Ʒ��Ϲ����ұȱ��˵Ĵ�
		
		if (_currentPlayer == _player1)
		{
			if (_gameRule->isLegal(_currentPlayer->getCurrentCard()) && _gameRule->isLargerCard(_cardLength, _cardType, _cardArrayNumber, _currentPlayer->getCurrentCard(), _gameRule->getCardType(), _gameRule->getCardArrayNumber()))
			{
				/*log("_currentCard.size 2= %d", _currentPlayer->getCurrentCard().size());*/
				/*std::sort(_currentPlayer->getCurrentCard().begin(), _currentPlayer->getCurrentCard().end(), GameRule::largerCard);*/
				_cardType = _gameRule->getCardType();
				_cardArrayNumber = _gameRule->getCardArrayNumber();
				_cardLength = _gameRule->getCardLength();
			}
			//�����Ʋ�����
			else   //�Ʋ�����
			{
				auto sp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_282.png");
				auto sp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_287.png");
				auto sp3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_283.png");
				sp2->setAnchorPoint(Vec2(0, 1.0 / 2));
				sp2->setPosition(Vec2(sp1->getContentSize().width, sp1->getContentSize().height / 2));
				sp1->addChild(sp2);
				sp3->setAnchorPoint(Vec2(0, 1.0 / 2));
				sp3->setPosition(Vec2(sp2->getContentSize().width, sp2->getContentSize().height / 2));
				sp2->addChild(sp3);
				this->addChild(sp1);
				sp1->setPosition(Vec2(200, 50));
				sp1->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), NULL));
				sp2->runAction(FadeOut::create(1.0f));
				sp3->runAction(FadeOut::create(1.0f));
				return;
			}
		}

		if (_currentPlayer != _player1)
		{
			_cardType = _currentPlayer->getGameRule->getCardType();
			_cardArrayNumber = _currentPlayer->getGameRule->getCardArrayNumber();
			_cardLength = _currentPlayer->getGameRule->getCardLength();
		}

		_currentCard.clear();
		//��ǰ������
		_currentCard = _currentPlayer->getCurrentCard();
		//��ӱ��γ�����
		if (_currentPlayer == _player1)
		{
			_prePlayer1Card = _currentCard;
			log("prePlayer1Card size:%d", _prePlayer1Card.size());
		}
		else if (_currentPlayer == _player2)
		{
			_prePlayer2Card = _currentCard;
			log("prePlayer2Card size:%d", _prePlayer2Card.size());
		}
		else
		{
			_prePlayer3Card = _currentCard;
			log("prePlayer3Card size:%d", _prePlayer3Card.size());
		}

		log("CurrentPlayer: %d pushCard ,Length: %d,CardType: %d ,CardArraynumber: %d", _currentPlayer->getPlayerType(), _gameRule->getCardLength(), _cardType, _cardArrayNumber);
		
		//���Ƶ�λ��
		double posStart = 0;
		if (_currentPlayer->getCurrentCard().size() <= 8)
			posStart = (cardSizeX*cardScale*0.4*0.33*((int)_currentPlayer->getCurrentCard().size() / 2));
		else
			posStart = (cardSizeX*cardScale*0.4*0.33*((int)(8) / 2));
		for (int i = 0; i < (_currentPlayer->getCurrentCard()).size(); i++)
		{
			(_currentPlayer->getCurrentCard()).at(i)->removeFromParentAndCleanup(false);
			this->addChild((_currentPlayer->getCurrentCard()).at(i));
		}
		for (int i = 0; i < (_currentPlayer->getCurrentCard()).size(); i++)
		{
			if (i < 8)
			{
				if (_currentPlayer == _player1)
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(370 - posStart + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 230)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));
				}/* CallFuncN::create([](Node*card) {	((Card*)card)->removeFromParent(); log("123%d",card->getCardNumber()); }), NULL)*/
				else  if (_currentPlayer == _player2)
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(550 - posStart + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));
				}
				else
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(230 + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));
				}
				//if (_currentPlayer->getCurrentCard().at(i)->getCardNumber() < 14)
				//	_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::FLOWER)->runAction(Sequence::create(FadeOut::create(0.5f),
				//		FadeIn::create(0.5),
				//		/*RemoveSelf::create(true),*/
				//		NULL));
				//_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::NUMBER)->runAction(Sequence::create(FadeOut::create(0.5f),
				//	FadeIn::create(0.5),
				//	///*RemoveSelf::create(true),*/
				//	NULL));
			}
			else
			{
				if (_currentPlayer == _player1)
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(370 - posStart + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 230 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height*0.4)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));/* CallFuncN::create([](Node*card) {	((Card*)card)->removeFromParent(); log("123%d",card->getCardNumber()); }), NULL)*/
				}
				else if (_currentPlayer == _player2)
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(550 - posStart + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));
				}
				else
				{
					((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
						ScaleTo::create(0.0f, 0.4f),
						MoveTo::create(0.3f, Vec2(230 + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height)),
						FadeIn::create(0.0f),
						/*RemoveSelf::create(true),*/
						NULL));
				}
				//if (_currentPlayer->getCurrentCard().at(i)->getCardNumber() < 14)
				//	_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::FLOWER)->runAction(Sequence::create(FadeOut::create(0.5f),
				//		FadeIn::create(0.5),
				//		/*RemoveSelf::create(true),*/
				//		NULL));
				//_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::NUMBER)->runAction(Sequence::create(FadeOut::create(0.5f),
				//	FadeIn::create(0.5),
				//	///*RemoveSelf::create(true),*/
				//	NULL));
			}
		}
		/*for (int i = 0; i < (_currentPlayer->getCurrentCard()).size(); i++)
		{
		_currentPlayer->getCurrentCard().at(i)->setScale(0.5f);
		if(i<8)
		_currentPlayer->getCurrentCard().at(i)->setPosition(Vec2(300 + i*1.0 / 6 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width,200));
		else
		_currentPlayer->getCurrentCard().at(i)->setPosition(Vec2(300 + (i-8)*1.0 / 6 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 200-1.0/2*_currentPlayer->getCurrentCard().at(i)->getContentSize().height));


		/*log("_currentCard.size 3= %d", _currentPlayer->getCurrentCard().size());*/
		_currentPlayer->pushCard();  //����

		if (_currentPlayer == _player2)           //������ʾ���Ƶ�����
		{
			_player2CardNumber->setString(StringUtils::format("%d", _player2->getVCard().size()));
		}
		else if (_currentPlayer == _player3)
		{
			_player3CardNumber->setString(StringUtils::format("%d", _player3->getVCard().size()));
		}

		//�����������
		if (_currentPlayer == _player1)
		{
			chuButton->setEnabled(false);
			passButton->setEnabled(false);
			hintButton->setEnabled(false);

			chuButton->setVisible(false);
			passButton->setVisible(false);
			hintButton->setVisible(false);

			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));

			log("LUNdao Player2");
			changePlayer(_player2);

			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (_player2->findFitCard(_cardType, _cardArrayNumber, _cardLength)) // �ܹ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					_passTimes = 0;
					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
					/*if (_currentPlayer == _player2)*/
					/*log("player2");*/
				}
				else // �ܲ���
				{
					_player2->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					pass(_player2);
				}

			}
			else    //֮ǰû���ϳ���
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				hint(_player2);
			}
		}
		else if (_currentPlayer == _player2)
		{
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));

			log("LUNdao Player3");
			log("lundao %d", _currentPlayer->getPlayerType());
			changePlayer(_player3);
			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (_player3->findFitCard(_cardType, _cardArrayNumber, _cardLength))// �ܹ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					_passTimes = 0;
					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
					log("lundao %d", _currentPlayer->getPlayerType());
				}
				else  // pass
				{
					_player3->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					pass(_player3);
				}
			}
			else
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				hint(_player3);
			}
		}
		else  //�ֵ����1
		{
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));

			chuButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
				[&]() { chuButton->setEnabled(true); chuButton->setVisible(true); }), NULL));
			passButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
				[&]() { passButton->setEnabled(true); passButton->setVisible(true); }), NULL));
			hintButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
				[&]() { hintButton->setEnabled(true); hintButton->setVisible(true); }), NULL));

			log("LUNdao Player1");
			changePlayer(_player1);
			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (!_player1->findFitCard(_cardType, _cardArrayNumber, _cardLength))// ���ܹ��ϣ���ʾû�д����ҵ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					auto cannotSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_249.png");
					cannotSprite->setPosition(Vec2(300, 100));
					this->addChild(cannotSprite);
					cannotSprite->setVisible(false);
					cannotSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/Show::create(), FadeOut::create(1.0f), RemoveSelf::create(true), NULL));
					//�����ư�ť��Ϊ����
				}
				else
				{
					_player1->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				}

			}
			else
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			}
		}
	}
	else//��
	{
		if (_currentPlayer == _player1)
		{
			_prePlayer1BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
			chuSprite->setPosition(Vec2(_prePlayer1BuChu->getContentSize().width, 0));
			chuSprite->setAnchorPoint(Vec2(0, 0));
			_prePlayer1BuChu->addChild(chuSprite);
			_prePlayer1BuChu->setPosition(400, 250);
			_prePlayer1BuChu->setScale(0.7f);
			this->addChild(_prePlayer1BuChu);
			//_prePlayer1BuChu->setVisible(false);
			//chuSprite->setVisible(false);
			//_prePlayer1BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(),  NULL));
		}
		else if (_currentPlayer == _player2)
		{
			_prePlayer2BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
			chuSprite->setPosition(Vec2(_prePlayer2BuChu->getContentSize().width, 0));
			chuSprite->setAnchorPoint(Vec2(0, 0));
			_prePlayer2BuChu->addChild(chuSprite);
			_prePlayer2BuChu->setPosition(540, 300);
			_prePlayer2BuChu->setScale(0.7f);
			this->addChild(_prePlayer2BuChu);
			//_prePlayer2BuChu->setVisible(false);
			//chuSprite->setVisible(false);
			//_prePlayer2BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(),/* FadeOut::create(1.0f), RemoveSelf::create(true),*/ NULL));
			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create()/*, FadeOut::create(1.0f), RemoveSelf::create(true)*/, NULL));
		}
		else
		{
			_prePlayer3BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
			chuSprite->setPosition(Vec2(_prePlayer3BuChu->getContentSize().width, 0));
			chuSprite->setAnchorPoint(Vec2(0, 0));
			_prePlayer3BuChu->addChild(chuSprite);
			_prePlayer3BuChu->setPosition(230, 300);
			_prePlayer3BuChu->setScale(0.7f);
			this->addChild(_prePlayer3BuChu);
			//_prePlayer3BuChu->setVisible(false);
			//chuSprite->setVisible(false);
			//_prePlayer3BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
		}
		_isPass = false;
		if (_passTimes == 2)
		{
			_cardType = CardType::NOTYPE;
			_cardArrayNumber = 0;
			_cardLength = 0;
			_passTimes = 0;
		}
		//�����������
		if (_currentPlayer == _player1)
		{
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));

			chuButton->setEnabled(false);
			passButton->setEnabled(false);
			hintButton->setEnabled(false);

			chuButton->setVisible(false);
			passButton->setVisible(false);
			hintButton->setVisible(false);

			log("LUNdao p  Player2");
			changePlayer(_player2);
			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (_player2->findFitCard(_cardType, _cardArrayNumber, _cardLength)) // �ܹ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					_passTimes = 0;
					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
				}
				else // �ܲ���
				{
					_player2->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					pass(_player2);
				}
			}
			else
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				hint(_player2);
			}
		}
		else if (_currentPlayer == _player2)
		{
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
			log("LUNdao p  Player3");
			changePlayer(_player3);
			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (_player3->findFitCard(_cardType, _cardArrayNumber, _cardLength))// �ܹ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					_passTimes = 0;
					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
				}
				else  // pass
				{
					_player3->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					pass(_player3);
				}
			}
			else
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				hint(_player3);
			}
		}
		else
		{
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));

			chuButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
				[&]() { chuButton->setEnabled(true); chuButton->setVisible(true); }), NULL));
			passButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
				[&]() { passButton->setEnabled(true); passButton->setVisible(true); }), NULL));
			hintButton->runAction(Sequence::create(/*DelayTime::create(2.0f), */CallFunc::create(
				[&]() { hintButton->setEnabled(true); hintButton->setVisible(true); }), NULL));

			log("LUNdao p  Player1");
			changePlayer(_player1);
			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
			{
				if (!_player1->findFitCard(_cardType, _cardArrayNumber, _cardLength))// ���ܹ��ϣ���ʾû�д����ҵ���
				{
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
					auto cannotSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_249.png");
					cannotSprite->setPosition(Vec2(300, 100));
					this->addChild(cannotSprite);
					cannotSprite->setVisible(false);
					cannotSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/Show::create(), FadeOut::create(1.0f), RemoveSelf::create(true), NULL));
					//�����ư�ť��Ϊ����
				}
				else
				{
					_player1->getCurrentCard().clear();
					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
				}
			}
			else
			{
				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.2f));
			}
		}
	}
}

//void GameScene::pushSchedule(float dt)
//{
//	if (_currentPlayer == _player3)
//		log("is player3");
//	pushCard();
//}

void GameScene::pass(Player* currentPlayer)
{
	_isPass = true;
	_passTimes++;
	if (currentPlayer != _player1)//�������1 
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
	else
	{
		pushCard();
	}
}

void GameScene::hint(Player* _player1)
{
	if (_player1->getVCard().size() == 20 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 20))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 16 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 16))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 12))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 8))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 18 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 18))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 15 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 15))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 12))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 9 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 9))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 6))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() == 20 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 20))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 18 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 18))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 16 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 16))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 14 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 14))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 12))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 10 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 10))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 8))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 6))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE, 0, 12))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 11 && _player1->findFitCard(CardType::SEQUENCE, 0, 11))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 10 && _player1->findFitCard(CardType::SEQUENCE, 0, 10))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 9 && _player1->findFitCard(CardType::SEQUENCE, 0, 9))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE, 0, 8))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 7 && _player1->findFitCard(CardType::SEQUENCE, 0, 7))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE, 0, 6))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 5 && _player1->findFitCard(CardType::SEQUENCE, 0, 5))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 5 && _player1->findFitCard(CardType::TRIPLET_WITH_ATTACHED_PAIRS, 0, 5))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 4 && _player1->findFitCard(CardType::TRIPLET_WITH_ATTACHED_CARDS, 0, 4))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 1 && _player1->findFitCard(CardType::SINGLE, 0, 1))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
	else if (_player1->getVCard().size() >= 2 && _player1->findFitCard(CardType::PAIR, 0, 2))
	{
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));

	}
}

void GameScene::changePlayer(Player *player)
{
	_currentPlayer = player;
	//if (player == _player1)
	//{
	//	//((Menu*)this->getChildByTag(10))->setEnable
	//}
	//else
	//{
	//	//_currentPlayer->findFitCard();
	//}
}

void GameScene::selectLandlord(Player *player)
{
	player->setLandlord(true);
}

void GameScene::callLandlord()      //�е���
{
	if (_currentPlayer == _player1)
	{
		_callLandlord = _player1;
		wantLandlord.push(_player1);
		changePlayer(_player2);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		jiaoButton->setEnabled(false);
		bujiaoButton->setEnabled(false);

		jiaoButton->setVisible(false);
		bujiaoButton->setVisible(false);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����

	}
	else if (_currentPlayer == _player2)
	{
		_callLandlord = _player2;
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		wantLandlord.push(_player2);
		changePlayer(_player3);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
	}
	else
	{
		_callLandlord = _player3;
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		qiangButton->setEnabled(true);
		buqiangButton->setEnabled(true);

		qiangButton->setVisible(true);
		buqiangButton->setVisible(true);
		wantLandlord.push(_player3);
		changePlayer(_player1);

	}
}

void GameScene::landlords()        //������
{
	if (_currentPlayer == _player1)
	{
		if (wantLandlord.front() == _player1)
		{
			selectLandlord(_player1);         //ѡ��player1 Ϊ����
			addLandlordCard();                //��ӵ�����

			qiangButton->setEnabled(false);      //������������ť
			buqiangButton->setEnabled(false);

			qiangButton->setVisible(false);
			buqiangButton->setVisible(false);

			chuButton->setEnabled(true);         //���ó��ư�ť
			passButton->setEnabled(true);
			hintButton->setEnabled(true);

			chuButton->setVisible(true);
			passButton->setVisible(true);
			hintButton->setVisible(true);

			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));         //����ʱ��λ��
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			_currentPlayer = _player1;
			return;
		}
		wantLandlord.push(_player1);
		changePlayer(_player2);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		qiangButton->setEnabled(false);
		buqiangButton->setEnabled(false);

		qiangButton->setVisible(false);
		buqiangButton->setVisible(false);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����

	}
	else if (_currentPlayer == _player2)
	{
		if (wantLandlord.front() == _player2)
		{
			selectLandlord(_player2);          //ѡ��player2Ϊ����
			addLandlordCard();                //��ӵ�����
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			_currentPlayer = _player2;
			hint(_player2);   //��ʾ����
			return;
		}
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		wantLandlord.push(_player2);
		changePlayer(_player3);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
	}
	else
	{
		if (wantLandlord.front() == _player3)
		{
			selectLandlord(_player3);          //ѡ��player3Ϊ����
			addLandlordCard();                //��ӵ�����
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			_currentPlayer = _player3;
			hint(_player3);   //��ʾ����
			return;

		}
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		qiangButton->setEnabled(true);
		buqiangButton->setEnabled(true);

		qiangButton->setVisible(true);
		buqiangButton->setVisible(true);
		wantLandlord.push(_player3);
		changePlayer(_player1);
	}
}

void GameScene::notWantLandlord()   //����
{
	if (_currentPlayer == _player1)
	{
		_player1->setIsWantLandlord(false);//��Ϊ��Ҫ����
		bujiaoTimes++;
		if (bujiaoTimes == 3)
		{
			restartGame();          //���¿�ʼ
		}
		changePlayer(_player2);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		jiaoButton->setEnabled(false);
		bujiaoButton->setEnabled(false);

		jiaoButton->setVisible(false);
		bujiaoButton->setVisible(false);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));       //�е���
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));   //����

	}
	else if (_currentPlayer == _player2)
	{
		_player2->setIsWantLandlord(false);//��Ϊ��Ҫ����
		bujiaoTimes++;
		if (bujiaoTimes == 3)
			restartGame();//���¿�ʼ
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		changePlayer(_player3);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));       //�е���
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
	}
	else
	{
		_player3->setIsWantLandlord(false);//��Ϊ��Ҫ����
		bujiaoTimes++;
		if (bujiaoTimes == 3)
			restartGame();//���¿�ʼ
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		jiaoButton->setEnabled(true);
		bujiaoButton->setEnabled(true);

		jiaoButton->setVisible(true);
		bujiaoButton->setVisible(true);
		changePlayer(_player1);

	}
}

void GameScene::notQiangLandlord()  //����
{
	if (_currentPlayer == _player1)
	{
		notWantLandlordTimes++;
		if (wantLandlord.front() == _player1 || notWantLandlordTimes == 2)
		{
			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
			addLandlordCard();                //��ӵ�����
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
			if (wantLandlord.back() == _player2)
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
				_currentPlayer = _player2;
				hint(_player2);
				//��������
			}
			else
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
				_currentPlayer = _player3;
				hint(_player3);
				//��������
			}
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			return;
		}
		changePlayer(_player2);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		qiangButton->setEnabled(false);
		buqiangButton->setEnabled(false);

		qiangButton->setVisible(false);
		buqiangButton->setVisible(false);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����

	}
	else if (_currentPlayer == _player2)
	{
		notWantLandlordTimes++;
		if (wantLandlord.front() == _player2 || notWantLandlordTimes == 2)
		{
			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
			addLandlordCard();                //��ӵ�����
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
			if (wantLandlord.back() == _player3)
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
				_currentPlayer = _player3;
				hint(_player3);
				//��������
			}
			else
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
				_currentPlayer = _player1;
				//�������ư�ť
			}
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			return;
		}
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		changePlayer(_player3);
		if (rand() % 10 > 5)                //���2
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
		else
			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
	}
	else
	{
		notWantLandlordTimes++;
		if (wantLandlord.front() == _player3 || notWantLandlordTimes == 2)
		{
			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
			addLandlordCard();                //��ӵ�����
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
			if (wantLandlord.back() == _player2)
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
				_currentPlayer = _player2;
				hint(_player2);
				//��������
			}
			else
			{
				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
				_currentPlayer = _player1;
				//�������ư�ť
			}
			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
			return;
		}
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
		qiangButton->setEnabled(true);
		buqiangButton->setEnabled(true);

		qiangButton->setVisible(true);
		buqiangButton->setVisible(true);
		changePlayer(_player1);
	}
}


void GameScene::addLandlordCard()
{
	if (_player1->getLandlord())
	{
		_player1->getCard(_vCard.at(51));
		_player1->getCard(_vCard.at(52));
		_player1->getCard(_vCard.at(53));
		_player1->arrangeCard();

		_vCard.at(51)->setPosition(_vCard.at(51)->getPosition() + Vec2(0, 20));
		_vCard.at(51)->runAction(MoveBy::create(0.5, Vec2(0, -20)));
		_vCard.at(52)->setPosition(_vCard.at(52)->getPosition() + Vec2(0, 20));
		_vCard.at(52)->runAction(MoveBy::create(0.5, Vec2(0, -20)));
		_vCard.at(53)->setPosition(_vCard.at(53)->getPosition() + Vec2(0, 20));
		_vCard.at(53)->runAction(MoveBy::create(0.5, Vec2(0, -20)));


	}
	else if (_player2->getLandlord())
	{
		_player2->getCard(_vCard.at(51));
		_player2->getCard(_vCard.at(52));
		_player2->getCard(_vCard.at(53));
	}
	else
	{
		_player3->getCard(_vCard.at(51));
		_player3->getCard(_vCard.at(52));
		_player3->getCard(_vCard.at(53));
	}
}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
{
	if (_player1->getCurrentCard().size()>0)
		log("0 player1 current size %d,%d", _player1->getCurrentCard().size(), _player1->getCurrentCard().at(0)->getCardNumber());
	_startTouchedID = -1;
	auto pos = touch->getLocation();
	for (int i = (int)_player1->getVCard().size() - 1; i >= 0; i--)
	{
		auto card = _player1->getVCard().at(i);
		auto cardPos = card->getPosition() - pos;
		/*if (i != (int)_player1->getVCard().size() - 1)
		{*/
		if (cardPos.x >(-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
		{
			if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
			{
				_startTouchedID = i;
				_endTouchedID = i;
				auto card = _player1->getVCard().at(i);
				card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
				break;
			}
		}
		/*}
		else
		{
		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
		{
		if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
		{
		_startTouchedID = i;
		_endTouchedID = i;
		auto card = _player1->getVCard().at(i);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
		break;
		}
		}
		}*/
	}
	if (_startTouchedID == -1)
		return false;
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
{
	auto pos = touch->getLocation();
	for (int i = (int)_player1->getVCard().size() - 1; i >= 0; i--)
	{
		auto card = _player1->getVCard().at(i);
		auto cardPos = card->getPosition() - pos;
		/*if (i != (int)_player1->getVCard().size() - 1)
		{*/
		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
		{
			if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
			{

				_endTouchedID = i;
				if (_endTouchedID > _startTouchedID)
				{
					for (auto j = _startTouchedID; j <= _endTouchedID; j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
					}
					for (auto j = 0; j < _startTouchedID; j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
					}
					for (auto j = _endTouchedID + 1; j < _player1->getVCard().size(); j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
					}
				}
				else
				{
					for (auto j = _endTouchedID; j <= _startTouchedID; j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
					}
					for (auto j = 0; j < _endTouchedID; j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
					}
					for (auto j = _startTouchedID + 1; j < _player1->getVCard().size(); j++)
					{
						auto card = _player1->getVCard().at(j);
						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
					}
				}
				break;

			}
		}
		/*}
		else
		{
		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
		{
		if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
		{
		_endTouchedID = i;
		if (_endTouchedID >_startTouchedID)
		{
		for (auto j = _startTouchedID; j <= _endTouchedID; j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
		}
		for (auto j = 0; j < _startTouchedID; j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
		}
		for (auto j = _endTouchedID+1; j < _player1->getVCard().size(); j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
		}
		}
		else
		{
		for (auto j = _endTouchedID; j <= _startTouchedID; j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
		}
		for (auto j = 0; j < _endTouchedID; j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
		}
		for (auto j = _startTouchedID+1; j < _player1->getVCard().size(); j++)
		{
		auto card = _player1->getVCard().at(j);
		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
		}
		}
		break;
		}*/
	}
}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
{
	log("1 player1 current size %d", _player1->getCurrentCard().size());
	log("startTouchedID = %d,endTouchedID = %d", _startTouchedID, _endTouchedID);
	/*log("%d  %d", touch->getLocation().x, touch->getLocation().y);*/
	auto pos = touch->getLocation();
	if (_endTouchedID > _startTouchedID)
	{
		for (auto i = _startTouchedID; i <= _endTouchedID; i++)
		{
			auto card = _player1->getVCard().at(i);
			card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
			if (card->getCardTouched())
			{
				/*log("s-%d", card->getCardNumber());*/
				card->setPosition(card->getPosition() + Vec2(0, -20));
				card->setCardTouched(false);

				_player1->getCurrentCard().eraseObject(card);
			}
			else
			{
				card->setPosition(card->getPosition() + Vec2(0, 20));
				card->setCardTouched(true);
				_player1->getCurrentCard().pushBack(card);
			}
		}
	}
	else
	{
		log("2 player1 current size %d", _player1->getCurrentCard().size());
		for (auto i = _endTouchedID; i <= _startTouchedID; i++)
		{
			auto card = _player1->getVCard().at(i);
			card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
			if (card->getCardTouched())
			{
				log("s-%d", card->getCardNumber());
				card->setPosition(card->getPosition() + Vec2(0, -20));
				card->setCardTouched(false);

				_player1->getCurrentCard().eraseObject(card);
				log("%d", _player1->getCurrentCard().size());
			}
			else
			{
				log("d-%d", card->getCardNumber());
				card->setPosition(card->getPosition() + Vec2(0, 20));
				card->setCardTouched(true);
				_player1->getCurrentCard().pushBack(card);
				log("%d", _player1->getCurrentCard().size());
			}
		}
		log("3 player1 current size %d", _player1->getCurrentCard().size());
	}

}



//#include"GameScene.h"
//
//USING_NS_CC;
//
//GameScene::GameScene()
//{
//	_gameRule = new GameRule();
//}
//
//GameScene::~GameScene()
//{
//	delete _gameRule;
//	_gameRule = nullptr;
//}
//
//Scene * GameScene::createScene()
//{
//	auto scene = Scene::create();
//	auto layer = GameScene::create();
//	scene->addChild(layer);
//	return scene;
//}
//
//bool GameScene::init()
//{
//	if (!Layer::init())
//		return false;
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//
//	auto background = Sprite::create("Common_BG2_2x.png");
//	background->setScale(800.0 / 960.0f);
//	background->setAnchorPoint(Vec2(0, 1));
//	background->setPosition(0, visibleSize.height);
//	this->addChild(background, 0);
//	initData();
//
//	newGame();
//	//clock
//	auto clockSprite = Clock::create();
//	clockSprite->setScale(0.5f);
//	clockSprite->setPosition(Vec2(visibleSize.width * 5 / 9 - 15, visibleSize.height * 2 / 5));
//	this->addChild(clockSprite, 3, CLOCKSPRITE);
//	clockSprite->setTime(30);
//
//	Sprite* temp1;
//	Sprite* temp2;
//	//����
//	_player1BuQiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1->setPosition(Vec2(_player1BuQiang->getContentSize().width * 3 / 2, _player1BuQiang->getContentSize().height / 2));
//	_player1BuQiang->addChild(temp1);
//	_player1BuQiang->setScale(0.7);
//	_player1BuQiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player1BuQiang, 1);
//
//	_player2BuQiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1->setPosition(Vec2(_player2BuQiang->getContentSize().width * 3 / 2, _player2BuQiang->getContentSize().height / 2));
//	_player2BuQiang->addChild(temp1);
//	_player2BuQiang->setScale(0.7);
//	_player2BuQiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player2BuQiang, 1);
//
//	_player3BuQiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1->setPosition(Vec2(_player3BuQiang->getContentSize().width * 3 / 2, _player3BuQiang->getContentSize().height / 2));
//	_player3BuQiang->addChild(temp1);
//	_player3BuQiang->setScale(0.7);
//	_player3BuQiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player3BuQiang, 1);
//	//������
//
//	_player1Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player1Qiang->getContentSize().width * 3 / 2, _player1Qiang->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player1Qiang->getContentSize().width * 5 / 2, _player1Qiang->getContentSize().height / 2));
//	_player1Qiang->addChild(temp1);
//	_player1Qiang->addChild(temp2);
//	_player1Qiang->setScale(0.7);
//	_player1Qiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player1Qiang, 1);
//
//	_player2Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player2Qiang->getContentSize().width * 3 / 2, _player2Qiang->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player2Qiang->getContentSize().width * 5 / 2, _player2Qiang->getContentSize().height / 2));
//	_player2Qiang->addChild(temp1);
//	_player2Qiang->addChild(temp2);
//	_player2Qiang->setScale(0.7);
//	_player2Qiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player2Qiang, 1);
//
//	_player3Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player3Qiang->getContentSize().width * 3 / 2, _player3Qiang->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player3Qiang->getContentSize().width * 5 / 2, _player3Qiang->getContentSize().height / 2));
//	_player3Qiang->addChild(temp1);
//	_player3Qiang->addChild(temp2);
//	_player3Qiang->setScale(0.7);
//	_player3Qiang->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player3Qiang, 1);
//
//	//����
//
//	_player1BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1->setPosition(Vec2(_player1BuJiao->getContentSize().width * 3 / 2, _player1BuJiao->getContentSize().height / 2));
//	_player1BuJiao->addChild(temp1);
//	_player1BuJiao->setScale(0.7);
//	_player1BuJiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player1BuJiao, 1);
//
//	_player2BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1->setPosition(Vec2(_player2BuJiao->getContentSize().width * 3 / 2, _player2BuJiao->getContentSize().height / 2));
//	_player2BuJiao->addChild(temp1);
//	_player2BuJiao->setScale(0.7);
//	_player2BuJiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player2BuJiao, 1);
//
//	_player3BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1->setPosition(Vec2(_player3BuJiao->getContentSize().width * 3 / 2, _player3BuJiao->getContentSize().height / 2));
//	_player3BuJiao->addChild(temp1);
//	_player3BuJiao->setScale(0.7);
//	_player3BuJiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player3BuJiao, 1);
//	//�е���
//
//	_player1Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player1Jiao->getContentSize().width * 3 / 2, _player1Jiao->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player1Jiao->getContentSize().width * 5 / 2, _player1Jiao->getContentSize().height / 2));
//	_player1Jiao->addChild(temp1);
//	_player1Jiao->addChild(temp2);
//	_player1Jiao->setScale(0.7);
//	_player1Jiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player1Jiao, 1);
//
//	_player2Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player2Jiao->getContentSize().width * 3 / 2, _player2Jiao->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player2Jiao->getContentSize().width * 5 / 2, _player2Jiao->getContentSize().height / 2));
//	_player2Jiao->addChild(temp1);
//	_player2Jiao->addChild(temp2);
//	_player2Jiao->setScale(0.7);
//	_player2Jiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player2Jiao, 1);
//
//	_player3Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//	temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//	temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//	temp1->setPosition(Vec2(_player3Jiao->getContentSize().width * 3 / 2, _player3Jiao->getContentSize().height / 2));
//	temp2->setPosition(Vec2(_player3Jiao->getContentSize().width * 5 / 2, _player3Jiao->getContentSize().height / 2));
//	_player3Jiao->addChild(temp1);
//	_player3Jiao->addChild(temp2);
//	_player3Jiao->setScale(0.7);
//	_player3Jiao->setPosition(Vec2(visibleSize.width / 2, -visibleSize.height / 2));
//	this->addChild(_player3Jiao, 1);
//	////���2�Ʊ���
//	auto _player2Card = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_0card_b.png"));
//	_player2Card->setScale(0.5);
//	_player2Card->setPosition(Vec2(650, 300));
//	this->addChild(_player2Card);
//	//���3�Ʊ���
//	auto _player3Card = Sprite::createWithSpriteFrameName(StringUtils::format("HLDDZ_MainGame0_2x_0card_b.png"));
//	_player3Card->setScale(0.5);
//	_player3Card->setPosition(Vec2(150, 300));
//	this->addChild(_player3Card);
//	//���2����
//	_player2CardNumber = Label::createWithSystemFont(StringUtils::format("%d", _player2->getCardNumber()), "Arial", 30);
//	_player2CardNumber->setColor(Color3B::BLACK);
//	_player2CardNumber->setPosition(_player2Card->getContentSize().width / 2, _player2Card->getContentSize().height / 2);
//	_player2Card->addChild(_player2CardNumber);
//	//���3����
//	_player3CardNumber = Label::createWithSystemFont(StringUtils::format("%d", _player3->getCardNumber()), "Arial", 30);
//	_player3CardNumber->setColor(Color3B::BLACK);
//	_player3CardNumber->setPosition(_player3Card->getContentSize().width / 2, _player3Card->getContentSize().height / 2);
//	_player3Card->addChild(_player3CardNumber);
//
//	auto jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��
//	auto di = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��
//	auto zhu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��
//	auto jiao1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��1
//	jiao1->setScale(0.9f);
//	auto di1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��1
//	di1->setScale(0.9f);
//	auto zhu1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��1
//	zhu1->setScale(0.9f);
//	auto normalJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalJiaoBgR->runAction(FlipX::create(true));
//	selectedJiaoBgR->runAction(FlipX::create(true));
//
//	jiao->setPosition(Vec2(normalJiaoBgL->getContentSize().width / 2, normalJiaoBgL->getContentSize().height / 2));
//	jiao1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width / 2, selectedJiaoBgL->getContentSize().height / 2));
//
//	di->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 2 / 2, normalJiaoBgL->getContentSize().height / 2));
//	di1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 2 / 2, selectedJiaoBgL->getContentSize().height / 2));
//
//	zhu->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 3 / 2, normalJiaoBgL->getContentSize().height / 2));
//	zhu1->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 3 / 2, selectedJiaoBgL->getContentSize().height / 2));
//
//	normalJiaoBgR->setPosition(Vec2(normalJiaoBgL->getContentSize().width * 3 / 2, normalJiaoBgL->getContentSize().height / 2));
//	selectedJiaoBgR->setPosition(Vec2(selectedJiaoBgL->getContentSize().width * 3 / 2, selectedJiaoBgL->getContentSize().height / 2));
//
//	normalJiaoBgL->addChild(normalJiaoBgR);
//	normalJiaoBgL->addChild(jiao);
//	normalJiaoBgL->addChild(di);
//	normalJiaoBgL->addChild(zhu);
//	normalJiaoBgL->setScale(0.5);
//	normalJiaoBgL->setContentSize(Size(normalJiaoBgL->getContentSize().width / 2, normalJiaoBgL->getContentSize().height / 2));
//
//	selectedJiaoBgL->addChild(selectedJiaoBgR);
//	selectedJiaoBgL->addChild(jiao1);
//	selectedJiaoBgL->addChild(di1);
//	selectedJiaoBgL->addChild(zhu1);
//	selectedJiaoBgL->setScale(0.5);
//	selectedJiaoBgL->setContentSize(Size(selectedJiaoBgL->getContentSize().width / 2, selectedJiaoBgL->getContentSize().height / 2));
//
//	jiaoButton = MenuItemSprite::create(normalJiaoBgL, selectedJiaoBgL, CC_CALLBACK_0(GameScene::callLandlord, this));
//	jiaoButton->setContentSize(Size(jiaoButton->getContentSize().width * 2, jiaoButton->getContentSize().height));
//
//	auto qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��
//	auto di2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��
//	auto zhu2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��
//	auto qiang1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��1
//	qiang1->setScale(0.9f);
//	auto di3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_171.png");//��1
//	di3->setScale(0.9f);
//	auto zhu3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_172.png");//��1
//	zhu3->setScale(0.9f);
//	auto normalQiangBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalQiangBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedQiangBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedQiangBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalQiangBgR->runAction(FlipX::create(true));
//	selectedQiangBgR->runAction(FlipX::create(true));
//
//	qiang->setPosition(Vec2(normalQiangBgL->getContentSize().width / 2, normalQiangBgL->getContentSize().height / 2));
//	qiang1->setPosition(Vec2(selectedQiangBgL->getContentSize().width / 2, selectedQiangBgL->getContentSize().height / 2));
//
//	di2->setPosition(Vec2(normalQiangBgL->getContentSize().width * 2 / 2, normalQiangBgL->getContentSize().height / 2));
//	di3->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 2 / 2, selectedQiangBgL->getContentSize().height / 2));
//
//	zhu2->setPosition(Vec2(normalQiangBgL->getContentSize().width * 3 / 2, normalQiangBgL->getContentSize().height / 2));
//	zhu3->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 3 / 2, selectedQiangBgL->getContentSize().height / 2));
//
//	normalQiangBgR->setPosition(Vec2(normalQiangBgL->getContentSize().width * 3 / 2, normalQiangBgL->getContentSize().height / 2));
//	selectedQiangBgR->setPosition(Vec2(selectedQiangBgL->getContentSize().width * 3 / 2, selectedQiangBgL->getContentSize().height / 2));
//
//	normalQiangBgL->addChild(normalQiangBgR);
//	normalQiangBgL->addChild(qiang);
//	normalQiangBgL->addChild(di2);
//	normalQiangBgL->addChild(zhu2);
//	normalQiangBgL->setScale(0.5);
//	normalQiangBgL->setContentSize(Size(normalQiangBgL->getContentSize().width / 2, normalQiangBgL->getContentSize().height / 2));
//
//	selectedQiangBgL->addChild(selectedQiangBgR);
//	selectedQiangBgL->addChild(qiang1);
//	selectedQiangBgL->addChild(di3);
//	selectedQiangBgL->addChild(zhu3);
//	selectedQiangBgL->setScale(0.5);
//	selectedQiangBgL->setContentSize(Size(selectedQiangBgL->getContentSize().width / 2, selectedQiangBgL->getContentSize().height / 2));
//
//	qiangButton = MenuItemSprite::create(normalQiangBgL, selectedQiangBgL, CC_CALLBACK_0(GameScene::landlords, this));
//	qiangButton->setContentSize(Size(qiangButton->getContentSize().width * 2, qiangButton->getContentSize().height));
//
//	auto qiangSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
//	auto buSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_177.png");//��
//	auto qiangSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
//	qiangSprite1->setScale(0.9f);
//	auto buSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_170.png");//��1
//	buSprite1->setScale(0.9f);
//	auto normalBuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalBuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedBuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedBuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalBuBgR->runAction(FlipX::create(true));
//	selectedBuBgR->runAction(FlipX::create(true));
//
//	qiangSprite->setPosition(Vec2(normalBuBgL->getContentSize().width / 2, normalBuBgL->getContentSize().height / 2));
//	qiangSprite1->setPosition(Vec2(selectedBuBgL->getContentSize().width / 2, selectedBuBgL->getContentSize().height / 2));
//
//	buSprite->setPosition(Vec2(normalBuBgL->getContentSize().width * 2 / 2, normalBuBgL->getContentSize().height / 2));
//	buSprite1->setPosition(Vec2(selectedBuBgL->getContentSize().width * 2 / 2, selectedBuBgL->getContentSize().height / 2));
//
//	normalBuBgR->setPosition(Vec2(normalBuBgL->getContentSize().width * 3 / 2, normalBuBgL->getContentSize().height / 2));
//	selectedBuBgR->setPosition(Vec2(selectedBuBgL->getContentSize().width * 3 / 2, selectedBuBgL->getContentSize().height / 2));
//
//	normalBuBgL->addChild(normalBuBgR);
//	normalBuBgL->addChild(qiangSprite);
//	normalBuBgL->addChild(buSprite);
//	normalBuBgL->setScale(0.5);
//	normalBuBgL->setContentSize(Size(normalBuBgL->getContentSize().width / 2, normalBuBgL->getContentSize().height / 2));
//
//	selectedBuBgL->addChild(selectedBuBgR);
//	selectedBuBgL->addChild(qiangSprite1);
//	selectedBuBgL->addChild(buSprite1);
//	selectedBuBgL->setScale(0.5);
//	selectedBuBgL->setContentSize(Size(selectedBuBgL->getContentSize().width / 2, selectedBuBgL->getContentSize().height / 2));
//
//	buqiangButton = MenuItemSprite::create(normalBuBgL, selectedBuBgL, CC_CALLBACK_0(GameScene::notQiangLandlord, this));
//	buqiangButton->setContentSize(Size(buqiangButton->getContentSize().width * 2, buqiangButton->getContentSize().height));
//
//	auto jiaoSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��
//	auto buSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
//	auto jiaoSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_169.png");//��1
//	jiaoSprite1->setScale(0.9f);
//	auto buSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
//	buSprite3->setScale(0.9f);
//	auto normalBuJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalBuJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedBuJiaoBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedBuJiaoBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalBuJiaoBgR->runAction(FlipX::create(true));
//	selectedBuJiaoBgR->runAction(FlipX::create(true));
//
//	jiaoSprite->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width / 2, normalBuJiaoBgL->getContentSize().height / 2));
//	jiaoSprite1->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width / 2, selectedBuJiaoBgL->getContentSize().height / 2));
//
//	buSprite2->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width * 2 / 2, normalBuJiaoBgL->getContentSize().height / 2));
//	buSprite3->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width * 2 / 2, selectedBuJiaoBgL->getContentSize().height / 2));
//
//	normalBuJiaoBgR->setPosition(Vec2(normalBuJiaoBgL->getContentSize().width * 3 / 2, normalBuJiaoBgL->getContentSize().height / 2));
//	selectedBuJiaoBgR->setPosition(Vec2(selectedBuJiaoBgL->getContentSize().width * 3 / 2, selectedBuJiaoBgL->getContentSize().height / 2));
//
//	normalBuJiaoBgL->addChild(normalBuJiaoBgR);
//	normalBuJiaoBgL->addChild(jiaoSprite);
//	normalBuJiaoBgL->addChild(buSprite2);
//	normalBuJiaoBgL->setScale(0.5);
//	normalBuJiaoBgL->setContentSize(Size(normalBuJiaoBgL->getContentSize().width / 2, normalBuJiaoBgL->getContentSize().height / 2));
//
//	selectedBuJiaoBgL->addChild(selectedBuJiaoBgR);
//	selectedBuJiaoBgL->addChild(jiaoSprite1);
//	selectedBuJiaoBgL->addChild(buSprite3);
//	selectedBuJiaoBgL->setScale(0.5);
//	selectedBuJiaoBgL->setContentSize(Size(selectedBuJiaoBgL->getContentSize().width / 2, selectedBuJiaoBgL->getContentSize().height / 2));
//
//	bujiaoButton = MenuItemSprite::create(normalBuJiaoBgL, selectedBuJiaoBgL, CC_CALLBACK_0(GameScene::notWantLandlord, this));
//	bujiaoButton->setContentSize(Size(bujiaoButton->getContentSize().width * 2, bujiaoButton->getContentSize().height));
//
//	auto chu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_193.png");//��
//	auto pai = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_194.png");//��
//	auto chu1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_193.png");//��1
//	chu1->setScale(0.9f);
//	auto pai1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_194.png");//��1
//	pai1->setScale(0.9f);
//	auto normalChuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_295.png");//�����󱳾�
//	auto normalChuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_295.png");//�����ұ���
//	auto selectedChuBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_296.png");//�����󱳾�
//	auto selectedChuBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_296.png");//�����ұ���
//
//	normalChuBgR->runAction(FlipX::create(true));
//	selectedChuBgR->runAction(FlipX::create(true));
//
//	chu->setPosition(Vec2(normalChuBgL->getContentSize().width / 2, normalChuBgL->getContentSize().height / 2));
//	chu1->setPosition(Vec2(selectedChuBgL->getContentSize().width / 2, selectedChuBgL->getContentSize().height / 2));
//
//	pai->setPosition(Vec2(normalChuBgL->getContentSize().width * 3 / 2, normalChuBgL->getContentSize().height / 2));
//	pai1->setPosition(Vec2(selectedChuBgL->getContentSize().width * 3 / 2, selectedChuBgL->getContentSize().height / 2));
//
//	normalChuBgR->setPosition(Vec2(normalChuBgL->getContentSize().width * 3 / 2, normalChuBgL->getContentSize().height / 2));
//	selectedChuBgR->setPosition(Vec2(selectedChuBgL->getContentSize().width * 3 / 2, selectedChuBgL->getContentSize().height / 2));
//
//	normalChuBgL->addChild(normalChuBgR);
//	normalChuBgL->addChild(chu);
//	normalChuBgL->addChild(pai);
//	normalChuBgL->setScale(0.5);
//	normalChuBgL->setContentSize(Size(normalChuBgL->getContentSize().width / 2, normalChuBgL->getContentSize().height / 2));
//
//	selectedChuBgL->addChild(selectedChuBgR);
//	selectedChuBgL->addChild(chu1);
//	selectedChuBgL->addChild(pai1);
//	selectedChuBgL->setScale(0.5);
//	selectedChuBgL->setContentSize(Size(selectedChuBgL->getContentSize().width / 2, selectedChuBgL->getContentSize().height / 2));
//
//	chuButton = MenuItemSprite::create(normalChuBgL, selectedChuBgL, CC_CALLBACK_0(GameScene::pushCard, this));
//	chuButton->setContentSize(Size(chuButton->getContentSize().width * 2, chuButton->getContentSize().height));
//	//����
//	auto passSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��
//	auto passSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_168.png");//��
//	auto passSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_167.png");//��1
//	passSprite3->setScale(0.9f);
//	auto passSprite4 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_168.png");//��1
//	passSprite4->setScale(0.9f);
//	auto normalPassBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalPassBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedPassBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedPassBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalPassBgR->runAction(FlipX::create(true));
//	selectedPassBgR->runAction(FlipX::create(true));
//
//	passSprite1->setPosition(Vec2(normalPassBgL->getContentSize().width / 2, normalPassBgL->getContentSize().height / 2));
//	passSprite3->setPosition(Vec2(selectedPassBgL->getContentSize().width / 2, selectedPassBgL->getContentSize().height / 2));
//
//	passSprite2->setPosition(Vec2(normalPassBgL->getContentSize().width * 3 / 2, normalPassBgL->getContentSize().height / 2));
//	passSprite4->setPosition(Vec2(selectedPassBgL->getContentSize().width * 3 / 2, selectedPassBgL->getContentSize().height / 2));
//
//	normalPassBgR->setPosition(Vec2(normalPassBgL->getContentSize().width * 3 / 2, normalPassBgL->getContentSize().height / 2));
//	selectedPassBgR->setPosition(Vec2(selectedPassBgL->getContentSize().width * 3 / 2, selectedPassBgL->getContentSize().height / 2));
//
//	normalPassBgL->addChild(normalPassBgR);
//	normalPassBgL->addChild(passSprite1);
//	normalPassBgL->addChild(passSprite2);
//	normalPassBgL->setScale(0.5);
//	normalPassBgL->setContentSize(Size(normalPassBgL->getContentSize().width / 2, normalPassBgL->getContentSize().height / 2));
//
//	selectedPassBgL->addChild(selectedPassBgR);
//	selectedPassBgL->addChild(passSprite3);
//	selectedPassBgL->addChild(passSprite4);
//	selectedPassBgL->setScale(0.5);
//	selectedPassBgL->setContentSize(Size(selectedPassBgL->getContentSize().width / 2, selectedPassBgL->getContentSize().height / 2));
//	passButton = MenuItemSprite::create(normalPassBgL, selectedPassBgL, CC_CALLBACK_0(GameScene::pass, this, _player1));
//	passButton->setContentSize(Size(passButton->getContentSize().width * 2, passButton->getContentSize().height));
//	//��ʾ
//	auto hintSprite1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_191.png");//��
//	auto hintSprite2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_192.png");//��
//	auto hintSprite3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_191.png");//1
//	hintSprite3->setScale(0.9f);
//	auto hintSprite4 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_192.png");//��1
//	hintSprite4->setScale(0.9f);
//	auto normalHintBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����󱳾�
//	auto normalHintBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_285.png");//�����ұ���
//	auto selectedHintBgL = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����󱳾�
//	auto selectedHintBgR = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_286.png");//�����ұ���
//
//	normalHintBgR->runAction(FlipX::create(true));
//	selectedHintBgR->runAction(FlipX::create(true));
//
//	hintSprite1->setPosition(Vec2(normalHintBgL->getContentSize().width / 2, normalHintBgL->getContentSize().height / 2));
//	hintSprite3->setPosition(Vec2(selectedHintBgL->getContentSize().width / 2, selectedHintBgL->getContentSize().height / 2));
//
//	hintSprite2->setPosition(Vec2(normalHintBgL->getContentSize().width * 3 / 2, normalHintBgL->getContentSize().height / 2));
//	hintSprite4->setPosition(Vec2(selectedHintBgL->getContentSize().width * 3 / 2, selectedHintBgL->getContentSize().height / 2));
//
//	normalHintBgR->setPosition(Vec2(normalHintBgL->getContentSize().width * 3 / 2, normalHintBgL->getContentSize().height / 2));
//	selectedHintBgR->setPosition(Vec2(selectedHintBgL->getContentSize().width * 3 / 2, selectedHintBgL->getContentSize().height / 2));
//
//	normalHintBgL->addChild(normalHintBgR);
//	normalHintBgL->addChild(hintSprite1);
//	normalHintBgL->addChild(hintSprite2);
//	normalHintBgL->setScale(0.5);
//	normalHintBgL->setContentSize(Size(normalHintBgL->getContentSize().width / 2, normalHintBgL->getContentSize().height / 2));
//
//	selectedHintBgL->addChild(selectedHintBgR);
//	selectedHintBgL->addChild(hintSprite3);
//	selectedHintBgL->addChild(hintSprite4);
//	selectedHintBgL->setScale(0.5);
//	selectedHintBgL->setContentSize(Size(selectedHintBgL->getContentSize().width / 2, selectedHintBgL->getContentSize().height / 2));
//	hintButton = MenuItemSprite::create(normalHintBgL, selectedHintBgL, CC_CALLBACK_0(GameScene::hint, this, _player1));
//	hintButton->setContentSize(Size(hintButton->getContentSize().width * 2, hintButton->getContentSize().height));
//	//
//	chuButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));
//	passButton->setPosition(Vec2(visibleSize.width * 3 / 9 - 5, visibleSize.height * 2 / 5));
//	hintButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));
//
//	jiaoButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));
//	qiangButton->setPosition(Vec2(visibleSize.width * 4 / 9 + 3, visibleSize.height * 2 / 5));
//	buqiangButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));
//	bujiaoButton->setPosition(Vec2(visibleSize.width * 6 / 9 - 36, visibleSize.height * 2 / 5));
//
//	auto menu = Menu::create(chuButton, passButton, hintButton, NULL);
//	auto qiangMenu = Menu::create(qiangButton, buqiangButton, NULL);
//	auto jiaoMenu = Menu::create(jiaoButton, bujiaoButton, NULL);
//	/*menu->alignItemsHorizontally();*/
//	/*menu->setPosition(Vec2(visibleSize.width * 3 / 8, visibleSize.height *2/ 5));*/
//	menu->setPosition(Vec2::ZERO);
//	qiangMenu->setPosition(Vec2::ZERO);
//	jiaoMenu->setPosition(Vec2::ZERO);
//	this->addChild(menu, 1, 10);//button tag =10
//	this->addChild(jiaoMenu, 1, 10);
//	this->addChild(qiangMenu, 1, 10);
//	//chuButton->setEnabled(false);
//
//	chuButton->setEnabled(false);
//	passButton->setEnabled(false);
//	hintButton->setEnabled(false);
//	qiangButton->setEnabled(false);
//	jiaoButton->setEnabled(false);
//	bujiaoButton->setEnabled(false);
//	buqiangButton->setEnabled(false);
//
//	chuButton->setVisible(false);
//	passButton->setVisible(false);
//	hintButton->setVisible(false);
//	qiangButton->setVisible(false);
//	jiaoButton->setVisible(false);
//	bujiaoButton->setVisible(false);
//	buqiangButton->setVisible(false);
//
//	//_currentPlayer = _player1;//���1�ȳ���
//
//	auto listener = EventListenerTouchOneByOne::create();
//	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
//	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
//	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//
//	if (rand() % 3 == 0)                  //
//	{
//		jiaoButton->setEnabled(true);
//		bujiaoButton->setEnabled(true);
//
//		jiaoButton->setVisible(true);
//		bujiaoButton->setVisible(true);
//		_currentPlayer = _player1;
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//	}
//	else if (rand() % 3 == 1)
//	{
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		_currentPlayer = _player2;
//		if (rand() % 10 > 5)
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));
//
//	}
//	else
//	{
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		_currentPlayer = _player3;
//		if (rand() % 10 > 5)
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));
//	}
//
//	return true;
//}
//
//bool GameScene::initData()
//{
//	//GameRul
//	//_gameRule=
//	//CardTypeArray cardArra
//	//_cardTypeArray = &cardArray;
//
//	_cardType = CardType::NOTYPE;
//	_cardArrayNumber = 0;
//	_cardLength = 0;
//	_passTimes = 0;
//	_isPass = false;
//
//	_prePlayer1BuChu = NULL;
//	_prePlayer2BuChu = NULL;
//	_prePlayer3BuChu = NULL;
//
//	_player1 = Player::create(playerType::PLAYER_1);
//	_player2 = Player::create(playerType::PLAYER_2);
//	_player3 = Player::create(playerType::PLAYER_3);
//
//	_player1->setAI(false);
//	_player2->setAI(true);
//	_player3->setAI(true);
//
//	this->addChild(_player1);
//	this->addChild(_player2);
//	this->addChild(_player3);
//	_currentCard.clear();
//
//	bujiaoTimes = 0;
//	return true;
//}
//void GameScene::showCard()
//{
//	_player1->arrangeCard();
//	_player2->arrangeCard();
//	_player3->arrangeCard();
//	_player1->showCard();
//	_player2->showCard();
//	_player3->showCard();
//}
////����
//void GameScene::sendCard()
//{
//	for (auto i = 0; i<51; i++)
//	{
//		if (i < 17)
//			_player1->getCard(_vCard.at(i));
//		else if (i >= 17 && i <= 33)
//			_player2->getCard(_vCard.at(i));
//		else
//			_player3->getCard(_vCard.at(i));
//	}
//}
////ϴ��
//void GameScene::shuffleCard()
//{
//
//	srand((unsigned int)time);
//	for (int i = 53; i >0; i--)
//	{
//		int j = rand() % i;
//		_vCard.swap(_vCard.at(i), _vCard.at(j));
//	}
//}
//
//void GameScene::createCard()
//{
//	for (int i = 1; i <= 13; i++)
//	{
//		auto cardHeart = Card::createCard(CardSize::BIG_CARD, i, CardColor::RED, CardFlower::HEART, CardOwner::FARM);
//		_vCard.pushBack(cardHeart);
//		auto cartDiamond = Card::createCard(CardSize::BIG_CARD, i, CardColor::RED, CardFlower::DIAMOND, CardOwner::FARM);
//		_vCard.pushBack(cartDiamond);
//		auto cardSpade = Card::createCard(CardSize::BIG_CARD, i, CardColor::BLACK, CardFlower::SPADE, CardOwner::FARM);
//		_vCard.pushBack(cardSpade);
//		auto cardClub = Card::createCard(CardSize::BIG_CARD, i, CardColor::BLACK, CardFlower::CLUB, CardOwner::FARM);
//		_vCard.pushBack(cardClub);
//	}
//	auto joker1 = Card::createCard(CardSize::BIG_CARD, 14, CardColor::BLACK, CardFlower::NONE, CardOwner::FARM);
//	auto joker2 = Card::createCard(CardSize::BIG_CARD, 15, CardColor::RED, CardFlower::NONE, CardOwner::FARM);
//	_vCard.pushBack(joker1);
//	_vCard.pushBack(joker2);
//}
//
//void GameScene::newGame()
//{
//	createCard();
//	shuffleCard();
//	sendCard();
//	showCard();
//}
//
//void GameScene::restartGame()
//{
//	this->removeAllChildrenWithCleanup(true);
//	_vCard.clear();
//	_player1 = NULL;
//	_player2 = NULL;
//	_player3 = NULL;
//	//��һ�ֳ�����
//	_prePlayer1Card.clear();
//	_prePlayer2Card.clear();
//	_prePlayer3Card.clear();
//	//��һ�ֵĲ���
//	_prePlayer1BuChu = NULL;
//	_prePlayer2BuChu = NULL;
//	_prePlayer3BuChu = NULL;
//	////��ǰ������
//	_currentCard.clear();
//	//��ǰ���Ƶ���
//	_currentPlayer = NULL;
//	delete _gameRule;
//	_gameRule = NULL;
//	//��ǰ���Ƶ�����
//	//��ǰ��������
//
//	_player2CardNumber = NULL;
//	_player3CardNumber = NULL;
//	chuButton = NULL;
//	passButton = NULL;
//	hintButton = NULL;
//	jiaoButton = NULL;
//	qiangButton = NULL;
//	buqiangButton = NULL;
//	bujiaoButton = NULL;
//	while (!wantLandlord.empty())
//		wantLandlord.pop();
//	_callLandlord = NULL;//�е������
//	bujiaoTimes = 0;
//	init();
//}
//
//void GameScene::pushCard()
//{
//	/*log("_currentCard.size 1= %d", _currentPlayer->getCurrentCard().size());*/
//	if (_currentPlayer == _player1)                      //ɾ�����2��һ�ε���
//	{
//		if (_prePlayer2Card.size() != 0)
//		{
//			for (auto card : _prePlayer2Card)
//			{
//				card->runAction(RemoveSelf::create(true));
//			}
//			_prePlayer2Card.clear();
//		}
//		if (_prePlayer2BuChu != NULL)                         //ɾ�����2��һ�εĲ���
//		{
//			_prePlayer2BuChu->removeFromParentAndCleanup(true);
//			_prePlayer2BuChu = NULL;
//		}
//	}
//	else if (_currentPlayer == _player2)                //ɾ�����3��һ�ε���
//	{
//		if (_prePlayer3Card.size() != 0)
//		{
//			for (auto card : _prePlayer3Card)
//			{
//				card->runAction(RemoveSelf::create(true));
//			}
//			_prePlayer3Card.clear();
//		}
//		if (_prePlayer3BuChu != NULL)                //ɾ�����3��һ�εĲ���
//		{
//			_prePlayer3BuChu->removeFromParentAndCleanup(true);
//			_prePlayer3BuChu = NULL;
//		}
//	}
//	else                                               //ɾ�����1��һ�ε���
//	{
//		if (_prePlayer1Card.size() != 0)
//		{
//			for (auto card : _prePlayer1Card)
//			{
//				card->runAction(RemoveSelf::create(true));
//			}
//			_prePlayer1Card.clear();
//		}
//		if (_prePlayer1BuChu != NULL)                   //ɾ�����1��һ�εĲ���
//		{
//			_prePlayer1BuChu->removeFromParentAndCleanup(true);
//			_prePlayer1BuChu = NULL;
//		}
//	}
//	if (!_isPass)//û��
//	{
//		/*for (auto i = 0; i < _currentPlayer->getCurrentCard().size(); i++)
//		log("%d", _currentPlayer->getCurrentCard().at(i)->getCardNumber());*/
//		//    �Ʒ��Ϲ����ұȱ��˵Ĵ�
//		if (_gameRule->isLegal(_currentPlayer->getCurrentCard()) && _gameRule->isLargerCard(_cardLength, _cardType, _cardArrayNumber, _currentPlayer->getCurrentCard(), _gameRule->getCardType(), _gameRule->getCardArrayNumber()))
//		{
//			/*log("_currentCard.size 2= %d", _currentPlayer->getCurrentCard().size());*/
//			/*std::sort(_currentPlayer->getCurrentCard().begin(), _currentPlayer->getCurrentCard().end(), GameRule::largerCard);*/
//			_cardType = _gameRule->getCardType();                    //���µ�ǰ���ͣ���С������
//			_cardArrayNumber = _gameRule->getCardArrayNumber();
//			_cardLength = _gameRule->getCardLength();
//
//
//			_currentCard.clear();
//			//��ǰ������
//			_currentCard = _currentPlayer->getCurrentCard();
//			//��ӱ��γ�����
//			if (_currentPlayer == _player1)
//			{
//				_prePlayer1Card = _currentCard;
//				log("prePlayer1Card size:%d", _prePlayer1Card.size());
//			}
//			else if (_currentPlayer == _player2)
//			{
//				_prePlayer2Card = _currentCard;
//				log("prePlayer2Card size:%d", _prePlayer2Card.size());
//			}
//			else
//			{
//				_prePlayer3Card = _currentCard;
//				log("prePlayer3Card size:%d", _prePlayer3Card.size());
//			}
//
//			log("CurrentPlayer: %d pushCard ,Length: %d,CardType: %d ,CardArraynumber: %d", _currentPlayer->getPlayerType(), _gameRule->getCardLength(), _cardType, _cardArrayNumber);
//			/*if (_currentPlayer != _player1)
//			{
//			for (int i = 0; i < _currentPlayer->getCurrentCard().size(); i++)
//			{
//			this->addChild(_currentPlayer->getCurrentCard().at(i));
//			}
//			}*/
//			//���Ƶ�λ��
//			double posStart = 0;
//			if (_currentPlayer->getCurrentCard().size() <= 8)
//				posStart = (cardSizeX*cardScale*0.4*0.33*((int)_currentPlayer->getCurrentCard().size() / 2));
//			else
//				posStart = (cardSizeX*cardScale*0.4*0.33*((int)(8) / 2));
//			for (int i = 0; i < (_currentPlayer->getCurrentCard()).size(); i++)/*auto card : _currentPlayer->getCurrentCard()*/
//			{
//				if (i < 8)
//				{
//					if (_currentPlayer == _player1)
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(370 - posStart + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 230)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));
//					}/* CallFuncN::create([](Node*card) {	((Card*)card)->removeFromParent(); log("123%d",card->getCardNumber()); }), NULL)*/
//					else  if (_currentPlayer == _player2)
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(550 - posStart + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));
//					}
//					else
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(230 + i*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));
//					}
//					//if (_currentPlayer->getCurrentCard().at(i)->getCardNumber() < 14)
//					//	_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::FLOWER)->runAction(Sequence::create(FadeOut::create(0.5f),
//					//		FadeIn::create(0.5),
//					//		/*RemoveSelf::create(true),*/
//					//		NULL));
//					//_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::NUMBER)->runAction(Sequence::create(FadeOut::create(0.5f),
//					//	FadeIn::create(0.5),
//					//	///*RemoveSelf::create(true),*/
//					//	NULL));
//				}
//				else
//				{
//					if (_currentPlayer == _player1)
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(370 - posStart + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 230 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height*0.4)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));/* CallFuncN::create([](Node*card) {	((Card*)card)->removeFromParent(); log("123%d",card->getCardNumber()); }), NULL)*/
//					}
//					else if (_currentPlayer == _player2)
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(550 - posStart + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));
//					}
//					else
//					{
//						((_currentPlayer->getCurrentCard()).at(i))->runAction(Sequence::create(Show::create(), FadeOut::create(0.0f),
//							ScaleTo::create(0.0f, 0.4f),
//							MoveTo::create(0.3f, Vec2(230 + (i - 8)*1.0 / 5 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 300 - 1.0 / 2 * _currentPlayer->getCurrentCard().at(i)->getContentSize().height)),
//							FadeIn::create(0.0f),
//							/*RemoveSelf::create(true),*/
//							NULL));
//					}
//					//if (_currentPlayer->getCurrentCard().at(i)->getCardNumber() < 14)
//					//	_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::FLOWER)->runAction(Sequence::create(FadeOut::create(0.5f),
//					//		FadeIn::create(0.5),
//					//		/*RemoveSelf::create(true),*/
//					//		NULL));
//					//_currentPlayer->getCurrentCard().at(i)->getChildByTag(CardBody::NUMBER)->runAction(Sequence::create(FadeOut::create(0.5f),
//					//	FadeIn::create(0.5),
//					//	///*RemoveSelf::create(true),*/
//					//	NULL));
//				}
//			}
//			/*for (int i = 0; i < (_currentPlayer->getCurrentCard()).size(); i++)
//			{
//			_currentPlayer->getCurrentCard().at(i)->setScale(0.5f);
//			if(i<8)
//			_currentPlayer->getCurrentCard().at(i)->setPosition(Vec2(300 + i*1.0 / 6 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width,200));
//			else
//			_currentPlayer->getCurrentCard().at(i)->setPosition(Vec2(300 + (i-8)*1.0 / 6 * _currentPlayer->getCurrentCard().at(i)->getContentSize().width, 200-1.0/2*_currentPlayer->getCurrentCard().at(i)->getContentSize().height));
//
//
//			/*log("_currentCard.size 3= %d", _currentPlayer->getCurrentCard().size());*/
//			_currentPlayer->pushCard();  //����
//
//			if (_currentPlayer == _player2)           //������ʾ���Ƶ�����
//			{
//				_player2CardNumber->setString(StringUtils::format("%d", _player2->getVCard().size()));
//			}
//			else if (_currentPlayer == _player3)
//			{
//				_player3CardNumber->setString(StringUtils::format("%d", _player3->getVCard().size()));
//			}
//
//			//�����������
//			if (_currentPlayer == _player1)
//			{
//				chuButton->setEnabled(false);
//				passButton->setEnabled(false);
//				hintButton->setEnabled(false);
//
//				chuButton->setVisible(false);
//				passButton->setVisible(false);
//				hintButton->setVisible(false);
//
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//
//				log("LUNdao Player2");
//				changePlayer(_player2);
//
//				if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//				{
//					if (_player2->findFitCard(_cardType, _cardArrayNumber, _cardLength)) // �ܹ���
//					{
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//						_passTimes = 0;
//						this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//						/*if (_currentPlayer == _player2)*/
//						/*log("player2");*/
//					}
//					else // �ܲ���
//					{
//						_player2->getCurrentCard().clear();
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//						pass(_player2);
//					}
//
//				}
//				else    //֮ǰû���ϳ���
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					hint(_player2);
//				}
//			}
//			else if (_currentPlayer == _player2)
//			{
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//
//				log("LUNdao Player3");
//				log("lundao %d", _currentPlayer->getPlayerType());
//				changePlayer(_player3);
//				if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//				{
//					if (_player3->findFitCard(_cardType, _cardArrayNumber, _cardLength))// �ܹ���
//					{
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//						_passTimes = 0;
//						this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//						log("lundao %d", _currentPlayer->getPlayerType());
//					}
//					else  // pass
//					{
//						_player3->getCurrentCard().clear();
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//						pass(_player3);
//					}
//				}
//				else
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					hint(_player3);
//				}
//			}
//			else  //�ֵ����1
//			{
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//
//				chuButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
//					[&]() { chuButton->setEnabled(true); chuButton->setVisible(true); }), NULL));
//				passButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
//					[&]() { passButton->setEnabled(true); passButton->setVisible(true); }), NULL));
//				hintButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
//					[&]() { hintButton->setEnabled(true); hintButton->setVisible(true); }), NULL));
//
//				log("LUNdao Player1");
//				changePlayer(_player1);
//				if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//				{
//					if (!_player1->findFitCard(_cardType, _cardArrayNumber, _cardLength))// ���ܹ��ϣ���ʾû�д����ҵ���
//					{
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//						auto cannotSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_249.png");
//						cannotSprite->setPosition(Vec2(300, 100));
//						this->addChild(cannotSprite);
//						cannotSprite->setVisible(false);
//						cannotSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/Show::create(), FadeOut::create(1.0f), RemoveSelf::create(true), NULL));
//						//�����ư�ť��Ϊ����
//					}
//					else
//					{
//						_player1->getCurrentCard().clear();
//						((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//						this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					}
//
//				}
//				else
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//				}
//			}
//		}
//		//�����Ʋ�����
//		else if (_currentPlayer == _player1)  //�Ʋ�����
//		{
//			auto sp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_282.png");
//			auto sp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_287.png");
//			auto sp3 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_283.png");
//			sp2->setAnchorPoint(Vec2(0, 1.0 / 2));
//			sp2->setPosition(Vec2(sp1->getContentSize().width, sp1->getContentSize().height / 2));
//			sp1->addChild(sp2);
//			sp3->setAnchorPoint(Vec2(0, 1.0 / 2));
//			sp3->setPosition(Vec2(sp2->getContentSize().width, sp2->getContentSize().height / 2));
//			sp2->addChild(sp3);
//			this->addChild(sp1);
//			sp1->setPosition(Vec2(200, 50));
//			sp1->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), NULL));
//			sp2->runAction(FadeOut::create(1.0f));
//			sp3->runAction(FadeOut::create(1.0f));
//		}
//	}
//	else//��
//	{
//		if (_currentPlayer == _player1)
//		{
//			_prePlayer1BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
//			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
//			chuSprite->setPosition(Vec2(_prePlayer1BuChu->getContentSize().width, 0));
//			chuSprite->setAnchorPoint(Vec2(0, 0));
//			_prePlayer1BuChu->addChild(chuSprite);
//			_prePlayer1BuChu->setPosition(400, 250);
//			_prePlayer1BuChu->setScale(0.7f);
//			this->addChild(_prePlayer1BuChu);
//			//_prePlayer1BuChu->setVisible(false);
//			//chuSprite->setVisible(false);
//			//_prePlayer1BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
//			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(),  NULL));
//		}
//		else if (_currentPlayer == _player2)
//		{
//			_prePlayer2BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
//			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
//			chuSprite->setPosition(Vec2(_prePlayer2BuChu->getContentSize().width, 0));
//			chuSprite->setAnchorPoint(Vec2(0, 0));
//			_prePlayer2BuChu->addChild(chuSprite);
//			_prePlayer2BuChu->setPosition(540, 300);
//			_prePlayer2BuChu->setScale(0.7f);
//			this->addChild(_prePlayer2BuChu);
//			//_prePlayer2BuChu->setVisible(false);
//			//chuSprite->setVisible(false);
//			//_prePlayer2BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(),/* FadeOut::create(1.0f), RemoveSelf::create(true),*/ NULL));
//			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create()/*, FadeOut::create(1.0f), RemoveSelf::create(true)*/, NULL));
//		}
//		else
//		{
//			_prePlayer3BuChu = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");
//			auto chuSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_02.png");
//			chuSprite->setPosition(Vec2(_prePlayer3BuChu->getContentSize().width, 0));
//			chuSprite->setAnchorPoint(Vec2(0, 0));
//			_prePlayer3BuChu->addChild(chuSprite);
//			_prePlayer3BuChu->setPosition(230, 300);
//			_prePlayer3BuChu->setScale(0.7f);
//			this->addChild(_prePlayer3BuChu);
//			//_prePlayer3BuChu->setVisible(false);
//			//chuSprite->setVisible(false);
//			//_prePlayer3BuChu->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
//			//chuSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ Show::create(), NULL));
//		}
//		_isPass = false;
//		if (_passTimes == 2)
//		{
//			_cardType = CardType::NOTYPE;
//			_cardArrayNumber = 0;
//			_cardLength = 0;
//			_passTimes = 0;
//		}
//		//�����������
//		if (_currentPlayer == _player1)
//		{
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//
//			chuButton->setEnabled(false);
//			passButton->setEnabled(false);
//			hintButton->setEnabled(false);
//
//			chuButton->setVisible(false);
//			passButton->setVisible(false);
//			hintButton->setVisible(false);
//
//			log("LUNdao p  Player2");
//			changePlayer(_player2);
//			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//			{
//				if (_player2->findFitCard(_cardType, _cardArrayNumber, _cardLength)) // �ܹ���
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					_passTimes = 0;
//					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//				}
//				else // �ܲ���
//				{
//					_player2->getCurrentCard().clear();
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					pass(_player2);
//				}
//			}
//			else
//			{
//				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//				hint(_player2);
//			}
//		}
//		else if (_currentPlayer == _player2)
//		{
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//			log("LUNdao p  Player3");
//			changePlayer(_player3);
//			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//			{
//				if (_player3->findFitCard(_cardType, _cardArrayNumber, _cardLength))// �ܹ���
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					_passTimes = 0;
//					this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//				}
//				else  // pass
//				{
//					_player3->getCurrentCard().clear();
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					pass(_player3);
//				}
//			}
//			else
//			{
//				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//				hint(_player3);
//			}
//		}
//		else
//		{
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//
//			chuButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
//				[&]() { chuButton->setEnabled(true); chuButton->setVisible(true); }), NULL));
//			passButton->runAction(Sequence::create(/*DelayTime::create(2.0f),*/ CallFunc::create(
//				[&]() { passButton->setEnabled(true); passButton->setVisible(true); }), NULL));
//			hintButton->runAction(Sequence::create(/*DelayTime::create(2.0f), */CallFunc::create(
//				[&]() { hintButton->setEnabled(true); hintButton->setVisible(true); }), NULL));
//
//			log("LUNdao p  Player1");
//			changePlayer(_player1);
//			if (_cardType != CardType::NOTYPE)// ֮ǰ���˳���
//			{
//				if (!_player1->findFitCard(_cardType, _cardArrayNumber, _cardLength))// ���ܹ��ϣ���ʾû�д����ҵ���
//				{
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(10);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//					auto cannotSprite = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_249.png");
//					cannotSprite->setPosition(Vec2(300, 100));
//					this->addChild(cannotSprite);
//					cannotSprite->setVisible(false);
//					cannotSprite->runAction(Sequence::create(/*DelayTime::create(2.0f),*/Show::create(), FadeOut::create(1.0f), RemoveSelf::create(true), NULL));
//					//�����ư�ť��Ϊ����
//				}
//				else
//				{
//					_player1->getCurrentCard().clear();
//					((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//					this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//				}
//			}
//			else
//			{
//				((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//				this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.2f));
//			}
//		}
//	}
//}
//
////void GameScene::pushSchedule(float dt)
////{
////	if (_currentPlayer == _player3)
////		log("is player3");
////	pushCard();
////}
//
//void GameScene::pass(Player* currentPlayer)
//{
//	_isPass = true;
//	_passTimes++;
//	if (currentPlayer != _player1)//�������1 
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//	else
//	{
//		pushCard();
//	}
//}
//
//void GameScene::hint(Player* _player1)
//{
//	if (_player1->getVCard().size() == 20 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 20))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 16 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 16))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 12))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS_WITH_ATTACHED_CARDS, 0, 8))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 18 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 18))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 15 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 15))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 12))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 9 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 9))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE_OF_TRIPLETS, 0, 6))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() == 20 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 20))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 18 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 18))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 16 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 16))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 14 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 14))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 12))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 10 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 10))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 8))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE_OF_PAIRS, 0, 6))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 12 && _player1->findFitCard(CardType::SEQUENCE, 0, 12))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 11 && _player1->findFitCard(CardType::SEQUENCE, 0, 11))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 10 && _player1->findFitCard(CardType::SEQUENCE, 0, 10))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 9 && _player1->findFitCard(CardType::SEQUENCE, 0, 9))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 8 && _player1->findFitCard(CardType::SEQUENCE, 0, 8))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 7 && _player1->findFitCard(CardType::SEQUENCE, 0, 7))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 6 && _player1->findFitCard(CardType::SEQUENCE, 0, 6))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 5 && _player1->findFitCard(CardType::SEQUENCE, 0, 5))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 5 && _player1->findFitCard(CardType::TRIPLET_WITH_ATTACHED_PAIRS, 0, 5))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 4 && _player1->findFitCard(CardType::TRIPLET_WITH_ATTACHED_CARDS, 0, 4))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 1 && _player1->findFitCard(CardType::SINGLE, 0, 1))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//	else if (_player1->getVCard().size() >= 2 && _player1->findFitCard(CardType::PAIR, 0, 2))
//	{
//		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::pushCard, this)), NULL));
//
//	}
//}
//
//void GameScene::changePlayer(Player *player)
//{
//	_currentPlayer = player;
//	//if (player == _player1)
//	//{
//	//	//((Menu*)this->getChildByTag(10))->setEnable
//	//}
//	//else
//	//{
//	//	//_currentPlayer->findFitCard();
//	//}
//}
//
//void GameScene::selectLandlord(Player *player)
//{
//	player->setLandlord(true);
//}
//
//void GameScene::callLandlord()      //�е���
//{
//	Sprite* temp1;
//	Sprite* temp2;
//	if (_currentPlayer == _player1)
//	{
//		_player1Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player1Jiao->getContentSize().width * 3 / 2, _player1Jiao->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player1Jiao->getContentSize().width * 5 / 2, _player1Jiao->getContentSize().height / 2));
//		_player1Jiao->addChild(temp1);
//		_player1Jiao->addChild(temp2);
//		_player1Jiao->setScale(0.7);
//		_player1Jiao->setPosition(Vec2(400, 250));
//		this->addChild(_player1Jiao, 1);
//
//		if (bujiaoTimes == 2)
//		{
//			_player1Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1Jiao->removeFromParentAndCleanup(true);
//			}), NULL));
//
//			_player2BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //��������˵Ĳ���
//				_player2BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));
//			_player3BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player3BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));
//
//			selectLandlord(_player1);         //ѡ��player1 Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			jiaoButton->setEnabled(false);      //������������ť
//			bujiaoButton->setEnabled(false);
//
//			jiaoButton->setVisible(false);
//			bujiaoButton->setVisible(false);
//
//			chuButton->setEnabled(true);         //���ó��ư�ť
//			passButton->setEnabled(true);
//			hintButton->setEnabled(true);
//
//			chuButton->setVisible(true);
//			passButton->setVisible(true);
//			hintButton->setVisible(true);
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));         //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player1;
//			return;
//		}
//		_callLandlord = _player1;
//		wantLandlord.push(_player1);//���1�������
//		changePlayer(_player2);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));           //����ʱ��
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//		jiaoButton->setEnabled(false);            //���ýе�����ť
//		bujiaoButton->setEnabled(false);
//
//		jiaoButton->setVisible(false);
//		bujiaoButton->setVisible(false);
//		if (rand() % 10 > 5)                //���2
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//
//	}
//	else if (_currentPlayer == _player2)
//	{
//		_player2Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player2Jiao->getContentSize().width * 3 / 2, _player2Jiao->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player2Jiao->getContentSize().width * 5 / 2, _player2Jiao->getContentSize().height / 2));
//		_player2Jiao->addChild(temp1);
//		_player2Jiao->addChild(temp2);
//		_player2Jiao->setScale(0.7);
//		_player2Jiao->setPosition(Vec2(540, 300));
//		this->addChild(_player2Jiao, 1);
//
//		if (bujiaoTimes == 2)
//		{
//			_player2Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1Jiao->removeFromParentAndCleanup(true);
//			}), NULL));
//			_player1BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));
//			_player3BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player3BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));//��������˵Ĳ���
//
//			selectLandlord(_player2);         //ѡ��player2 Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));         //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player2;
//			hint(_player2);
//			return;
//		}
//		_callLandlord = _player2;
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		wantLandlord.push(_player2);
//		changePlayer(_player3);
//		if (rand() % 10 > 5)                //���3
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//	}
//	else
//	{
//		_player3Jiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player3Jiao->getContentSize().width * 3 / 2, _player3Jiao->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player3Jiao->getContentSize().width * 5 / 2, _player3Jiao->getContentSize().height / 2));
//		_player3Jiao->addChild(temp1);
//		_player3Jiao->addChild(temp2);
//		_player3Jiao->setScale(0.7);
//		_player3Jiao->setPosition(Vec2(230, 300));
//		this->addChild(_player3Jiao, 1);
//
//		if (bujiaoTimes == 2)
//		{
//			_player3Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1Jiao->removeFromParentAndCleanup(true);
//			}), NULL));
//			_player1BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));
//			_player2BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player2BuJiao->removeFromParentAndCleanup(true);
//			}), NULL));//��������˵Ĳ���
//
//			selectLandlord(_player3);         //ѡ��player3 Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));         //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player3;
//			hint(_player3);                    //��Ϸ��ʼ
//			return;
//		}
//		_callLandlord = _player3;
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//		qiangButton->setEnabled(true);   //������������ť
//		buqiangButton->setEnabled(true);
//
//		qiangButton->setVisible(true);
//		buqiangButton->setVisible(true);
//
//		wantLandlord.push(_player3);
//		changePlayer(_player1);
//
//	}
//}
//
//void GameScene::landlords()        //������
//{
//	Sprite* temp1;
//	Sprite* temp2;
//	if (_currentPlayer == _player1)
//	{
//		if (_player1BuJiao != NULL)
//		{
//			_player1BuJiao->removeFromParentAndCleanup(true);       //�������
//		}
//		if (_player1Jiao != NULL)                                   //����е���
//		{
//			_player1Jiao->removeFromParentAndCleanup(true);
//		}
//		_player1Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player1Qiang->getContentSize().width * 3 / 2, _player1Qiang->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player1Qiang->getContentSize().width * 5 / 2, _player1Qiang->getContentSize().height / 2));
//		_player1Qiang->addChild(temp1);
//		_player1Qiang->addChild(temp2);
//		_player1Qiang->setScale(0.7);
//		_player1Qiang->setPosition(Vec2(400, 250));
//		this->addChild(_player1Qiang, 1);
//
//		if (wantLandlord.front() == _player1)
//		{
//			_player1Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1Qiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player2Qiang != NULL)
//			{
//				_player2Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player2Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2BuQiang != NULL)
//			{
//				_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player2BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Qiang != NULL)
//			{
//				_player3Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player3Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3BuQiang != NULL)
//			{
//				_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player3BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(_player1);         //ѡ��player1 Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			qiangButton->setEnabled(false);      //������������ť
//			buqiangButton->setEnabled(false);
//
//			qiangButton->setVisible(false);
//			buqiangButton->setVisible(false);
//
//			chuButton->setEnabled(true);         //���ó��ư�ť
//			passButton->setEnabled(true);
//			hintButton->setEnabled(true);
//
//			chuButton->setVisible(true);
//			passButton->setVisible(true);
//			hintButton->setVisible(true);
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));         //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player1;
//			return;
//		}
//		if (_player2->getIsWantLandlord() == false)//player2û�У�player3���ˣ�
//		{
//			changePlayer(_player3);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//		}
//		else
//		{
//			changePlayer(_player2);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//		}
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//		qiangButton->setEnabled(false);
//		buqiangButton->setEnabled(false);
//
//		qiangButton->setVisible(false);
//		buqiangButton->setVisible(false);
//
//		if (rand() % 10 > 5)                //���2��3
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//		wantLandlord.push(_player1);
//	}
//	else if (_currentPlayer == _player2)
//	{
//		if (_player2BuJiao != NULL)
//		{
//			_player2BuJiao->removeFromParentAndCleanup(true);   //�������
//		}
//		if (_player2Jiao != NULL)                                   //����е���
//		{
//			_player2Jiao->removeFromParentAndCleanup(true);
//		}
//
//		_player2Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player2Qiang->getContentSize().width * 3 / 2, _player2Qiang->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player2Qiang->getContentSize().width * 5 / 2, _player2Qiang->getContentSize().height / 2));
//		_player2Qiang->addChild(temp1);
//		_player2Qiang->addChild(temp2);
//		_player2Qiang->setScale(0.7);
//		_player2Qiang->setPosition(Vec2(540, 300));
//		this->addChild(_player2Qiang, 1);
//
//		if (wantLandlord.front() == _player2)
//		{
//			_player2Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player2Qiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player1Qiang != NULL)
//			{
//				_player1Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player1Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1BuQiang != NULL)
//			{
//				_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player1BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Qiang != NULL)
//			{
//				_player3Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player3Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3BuQiang != NULL)
//			{
//				_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player3BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//
//			selectLandlord(_player2);          //ѡ��player2Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player2;
//			hint(_player2);   //��ʾ����
//			return;
//		}
//		if (_player2->getIsWantLandlord() == false)//player3û�У�player1���ˣ�
//		{
//			changePlayer(_player1);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//			qiangButton->setEnabled(true);      //������������ť
//			buqiangButton->setEnabled(true);
//
//			qiangButton->setVisible(true);
//			buqiangButton->setVisible(true);
//		}
//		else
//		{
//			changePlayer(_player3);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//
//			if (rand() % 10 > 5)                //���3
//				this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//			else
//				this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//		}
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		wantLandlord.push(_player2);
//	}
//	else
//	{
//		if (_player3BuJiao != NULL)
//		{
//			_player3BuJiao->removeFromParentAndCleanup(true);  //�������
//		}
//		if (_player3Jiao != NULL)                                   //����е���
//		{
//			_player3Jiao->removeFromParentAndCleanup(true);
//		}
//
//		_player3Qiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_07.png");//��
//		temp2 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_08.png");//��
//		temp1->setPosition(Vec2(_player3Qiang->getContentSize().width * 3 / 2, _player3Qiang->getContentSize().height / 2));
//		temp2->setPosition(Vec2(_player3Qiang->getContentSize().width * 5 / 2, _player3Qiang->getContentSize().height / 2));
//		_player3Qiang->addChild(temp1);
//		_player3Qiang->addChild(temp2);
//		_player3Qiang->setScale(0.7);
//		_player3Qiang->setPosition(Vec2(230, 300));
//		this->addChild(_player3Qiang, 1);
//
//		if (wantLandlord.front() == _player3)
//		{
//			_player3Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player3Qiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player1Qiang != NULL)
//			{
//				_player1Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player1Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1BuQiang != NULL)
//			{
//				_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player1BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2Qiang != NULL)
//			{
//				_player2Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�����
//					_player2Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2BuQiang != NULL)
//			{
//				_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //�������
//					_player2BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//
//			selectLandlord(_player3);          //ѡ��player3Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player3;
//			hint(_player3);   //��ʾ����
//			return;
//		}
//		if (_player1->getIsWantLandlord() == false)//player1û�У�player2���ˣ�
//		{
//			changePlayer(_player2);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			if (rand() % 10 > 5)                //���2
//				this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//			else
//				this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//		}
//		else                      //���1
//		{
//			changePlayer(_player1);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//			qiangButton->setEnabled(true);          //����������
//			buqiangButton->setEnabled(true);
//
//			qiangButton->setVisible(true);
//			buqiangButton->setVisible(true);
//		}
//		wantLandlord.push(_player3);
//	}
//}
//
//void GameScene::notWantLandlord()   //����
//{
//	Sprite* temp1;
//	if (_currentPlayer == _player1)
//	{
//		_player1BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1->setPosition(Vec2(_player1BuJiao->getContentSize().width * 3 / 2, _player1BuJiao->getContentSize().height / 2));
//		_player1BuJiao->addChild(temp1);
//		_player1BuJiao->setScale(0.7);
//		_player1BuJiao->setPosition(Vec2(400, 250));
//		this->addChild(_player1BuJiao, 1);
//
//		_player1->setIsWantLandlord(false);//��Ϊ��Ҫ����
//		bujiaoTimes++;
//		if (bujiaoTimes == 3)
//		{
//			restartGame();          //���¿�ʼ
//			return;
//		}
//		changePlayer(_player2);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		jiaoButton->setEnabled(false);     //���ýе���
//		bujiaoButton->setEnabled(false);
//
//		jiaoButton->setVisible(false);
//		bujiaoButton->setVisible(false);
//		if (rand() % 10 > 5)                //���2
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));       //�е���
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));   //����
//
//	}
//	else if (_currentPlayer == _player2)
//	{
//		_player2BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1->setPosition(Vec2(_player2BuJiao->getContentSize().width * 3 / 2, _player2BuJiao->getContentSize().height / 2));
//		_player2BuJiao->addChild(temp1);
//		_player2BuJiao->setScale(0.7);
//		_player2BuJiao->setPosition(Vec2(540, 300));
//		this->addChild(_player2BuJiao, 1);
//
//		_player2->setIsWantLandlord(false);//��Ϊ��Ҫ����
//		bujiaoTimes++;
//		if (bujiaoTimes == 3)
//		{
//			restartGame();//���¿�ʼ
//			return;
//		}
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		changePlayer(_player3);
//		if (rand() % 10 > 5)                //���3
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::callLandlord, this)), NULL));       //�е���
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notWantLandlord, this)), NULL));   //����
//	}
//	else
//	{
//		_player3BuJiao = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_04.png");//��
//		temp1->setPosition(Vec2(_player3BuJiao->getContentSize().width * 3 / 2, _player3BuJiao->getContentSize().height / 2));
//		_player3BuJiao->addChild(temp1);
//		_player3BuJiao->setScale(0.7);
//		_player3BuJiao->setPosition(Vec2(230, 300));
//		this->addChild(_player3BuJiao, 1);
//
//		_player3->setIsWantLandlord(false);//��Ϊ��Ҫ����
//		bujiaoTimes++;
//
//		if (bujiaoTimes == 3)
//		{
//			restartGame();//���¿�ʼ
//			return;
//		}
//
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//		jiaoButton->setEnabled(true);           //���ýе���
//		bujiaoButton->setEnabled(true);
//
//		jiaoButton->setVisible(true);
//		bujiaoButton->setVisible(true);
//
//		changePlayer(_player1);
//	}
//}
//
//void GameScene::notQiangLandlord()  //����
//{
//	Sprite*temp1;
//	if (_currentPlayer == _player1)
//	{
//		if (_player1Jiao != NULL)                      //����е���
//		{
//			_player1Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1Jiao->removeFromParentAndCleanup(true);
//				_player1Jiao = NULL;
//			}), NULL));
//		}
//		_player1BuQiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//		temp1->setPosition(Vec2(_player1BuQiang->getContentSize().width * 3 / 2, _player1BuQiang->getContentSize().height / 2));
//		_player1BuQiang->addChild(temp1);
//		_player1BuQiang->setScale(0.7);
//		_player1BuQiang->setPosition(Vec2(400, 250));
//		this->addChild(_player1BuQiang, 1);
//
//		qiangButton->setEnabled(false);                  //������������ť
//		buqiangButton->setEnabled(false);
//
//		qiangButton->setVisible(false);
//		buqiangButton->setVisible(false);
//		notWantLandlordTimes++;
//		if (_player2->getIsWantLandlord() == false)//��һ��player2��û�е������ڶ����˽���
//		{
//			_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player1BuQiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player2BuJiao != NULL)
//			{
//				_player2BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2����
//					_player2BuJiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Jiao != NULL)
//			{
//				_player3Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3��
//					_player3Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(_player3);          //ѡ��player3Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//			_currentPlayer = _player3;
//			hint(_player3);   //��ʾ����
//			return;
//		}
//		if (wantLandlord.front() == _player1 || notWantLandlordTimes == 2)//�ٴ��ֵ�player1���������������˲���
//		{
//			if (_player1BuQiang != NULL)                      //���1����
//			{
//				_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//					_player1BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2Jiao != NULL)
//			{
//				_player2Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2��
//					_player2Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2BuQiang != NULL)
//			{
//				_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2����
//					_player2BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2Qiang != NULL)
//			{
//				_player2Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2��
//					_player2Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3BuQiang != NULL)
//			{
//				_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3����
//					_player3BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Qiang != NULL)
//			{
//				_player3Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3��
//					_player3Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			if (wantLandlord.back() == _player2)
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//				_currentPlayer = _player2;
//				hint(_player2);
//			}
//			else
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//				_currentPlayer = _player3;
//				hint(_player3);
//			}
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			return;
//		}
//		changePlayer(_player2);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//
//		if (rand() % 10 > 5)                //���2
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//
//	}
//	else if (_currentPlayer == _player2)
//	{
//		if (_player2Jiao != NULL)                      //����е���
//		{
//			_player2Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player2Jiao->removeFromParentAndCleanup(true);
//				_player2Jiao = NULL;
//			}), NULL));
//		}
//
//		_player2BuQiang = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_01.png");//��
//		temp1 = Sprite::createWithSpriteFrameName("HLDDZ_MainGame0_2x_42_03.png");//��
//		temp1->setPosition(Vec2(_player2BuQiang->getContentSize().width * 3 / 2, _player2BuQiang->getContentSize().height / 2));
//		_player2BuQiang->addChild(temp1);
//		_player2BuQiang->setScale(0.7);
//		_player2BuQiang->setPosition(Vec2(540, 300));
//		this->addChild(_player2BuQiang, 1);
//
//		notWantLandlordTimes++;
//		if (_player3->getIsWantLandlord() == false)//��һ��player3��û�е�����player1�˽���
//		{
//			_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player2BuQiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player3BuJiao != NULL)
//			{
//				_player3BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3����
//					_player3BuJiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1Jiao != NULL)
//			{
//				_player1Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1��
//					_player1Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(_player1);          //ѡ��player1Ϊ����
//			addLandlordCard();                //��ӵ�����
//
//			chuButton->setEnabled(true);         //���ó��ư�ť
//			passButton->setEnabled(true);
//			hintButton->setEnabled(true);
//
//			chuButton->setVisible(true);
//			passButton->setVisible(true);
//			hintButton->setVisible(true);
//
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player1;
//			return;
//		}
//		if (wantLandlord.front() == _player2 || notWantLandlordTimes == 2)//�ٴ��ֵ�player2���������������˲���
//		{
//			if (_player2BuQiang != NULL)                      //���2����
//			{
//				_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//					_player2BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Jiao != NULL)
//			{
//				_player3Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3��
//					_player3Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1BuQiang != NULL)
//			{
//				_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1����
//					_player1BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1Qiang != NULL)
//			{
//				_player1Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1��
//					_player1Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3BuQiang != NULL)
//			{
//				_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3����
//					_player3BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player3Qiang != NULL)
//			{
//				_player3Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���3��
//					_player3Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			if (wantLandlord.back() == _player3)
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//				_currentPlayer = _player3;
//				hint(_player3);
//			}
//			else
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//				_currentPlayer = _player1;
//				chuButton->setEnabled(true);         //���ó��ư�ť
//				passButton->setEnabled(true);
//				hintButton->setEnabled(true);
//
//				chuButton->setVisible(true);
//				passButton->setVisible(true);
//				hintButton->setVisible(true);
//			}
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			return;
//		}
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER3X, PLAYER3Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		changePlayer(_player3);
//		if (rand() % 10 > 5)                //���3
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::landlords, this)), NULL));       //������
//		else
//			this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(GameScene::notQiangLandlord, this)), NULL));   //����
//	}
//	else
//	{
//		if (_player3Jiao != NULL)                      //����е���
//		{
//			_player3Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player3Jiao->removeFromParentAndCleanup(true);
//				_player3Jiao = NULL;
//			}), NULL));
//		}
//		notWantLandlordTimes++;
//		if (_player1->getIsWantLandlord() == false)//��һ��player1��û�е�����player2����
//		{
//			_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//				_player3BuQiang->removeFromParentAndCleanup(true);
//			}), NULL));
//			if (_player1BuJiao != NULL)
//			{
//				_player1BuJiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1����
//					_player1BuJiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2Jiao != NULL)
//			{
//				_player2Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2��
//					_player2Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(_player2);          //ѡ��player2Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			_currentPlayer = _player2;
//			hint(_player2);   //��ʾ����
//			return;
//		}
//		if (wantLandlord.front() == _player3 || notWantLandlordTimes == 2)//�ٴ��ֵ�player3���������������˲���
//		{
//			if (_player3BuQiang != NULL)                      //���3����
//			{
//				_player3BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {
//					_player3BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1Jiao != NULL)
//			{
//				_player1Jiao->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1��
//					_player1Jiao->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1BuQiang != NULL)
//			{
//				_player1BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1����
//					_player1BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player1Qiang != NULL)
//			{
//				_player1Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���1��
//					_player1Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2BuQiang != NULL)
//			{
//				_player2BuQiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2����
//					_player2BuQiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			if (_player2Qiang != NULL)
//			{
//				_player2Qiang->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() {     //���2��
//					_player2Qiang->removeFromParentAndCleanup(true);
//				}), NULL));
//			}
//			selectLandlord(wantLandlord.back());          //ѡ�����һ����������Ϊ����
//			addLandlordCard();                //��ӵ�����
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));     //����ʱ��λ��
//			if (wantLandlord.back() == _player2)
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER2X, PLAYER2Y));
//				_currentPlayer = _player2;
//				hint(_player2);
//			}
//			else
//			{
//				this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X2, PLAYER1Y2));
//				_currentPlayer = _player1;
//				chuButton->setEnabled(true);         //���ó��ư�ť
//				passButton->setEnabled(true);
//				hintButton->setEnabled(true);
//
//				chuButton->setVisible(true);
//				passButton->setVisible(true);
//				hintButton->setVisible(true);
//			}
//			((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(30);
//			this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//			return;
//		}
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeOut::create(0.1f));
//		this->getChildByTag(CLOCKSPRITE)->setPosition(Vec2(PLAYER1X, PLAYER1Y));
//		((Clock*)this->getChildByTag(CLOCKSPRITE))->setTime(15);
//		this->getChildByTag(CLOCKSPRITE)->runAction(FadeIn::create(0.1f));
//		qiangButton->setEnabled(true);
//		buqiangButton->setEnabled(true);
//
//		qiangButton->setVisible(true);
//		buqiangButton->setVisible(true);
//		changePlayer(_player1);
//	}
//}
//
//
//void GameScene::addLandlordCard()
//{
//	if (_player1->getLandlord())
//	{
//		for (int i = 0; i < _player1->getVCard().size(); ++i)
//		{
//			_player1->getVCard().at(i)->removeFromParent();
//		}
//		_player1->getCard(_vCard.at(51));
//		_player1->getCard(_vCard.at(52));
//		_player1->getCard(_vCard.at(53));
//		_player1->arrangeCard();
//		_player1->showCard();
//
//		_vCard.at(51)->setPosition(_vCard.at(51)->getPosition() + Vec2(0, 20));
//		_vCard.at(51)->runAction(MoveBy::create(0.5, Vec2(0, -20)));
//		_vCard.at(52)->setPosition(_vCard.at(52)->getPosition() + Vec2(0, 20));
//		_vCard.at(52)->runAction(MoveBy::create(0.5, Vec2(0, -20)));
//		_vCard.at(53)->setPosition(_vCard.at(53)->getPosition() + Vec2(0, 20));
//		_vCard.at(53)->runAction(MoveBy::create(0.5, Vec2(0, -20)));
//	}
//	else if (_player2->getLandlord())
//	{
//		for (int i = 0; i < _player2->getVCard().size(); ++i)
//		{
//			_player2->getVCard().at(i)->removeFromParent();
//		}
//		_player2->getCard(_vCard.at(51));
//		_player2->getCard(_vCard.at(52));
//		_player2->getCard(_vCard.at(53));
//		_player2->arrangeCard();
//		_player2->showCard();
//		_player2CardNumber->setString(StringUtils::format("%d", _player2->getVCard().size()));
//	}
//	else
//	{
//		for (int i = 0; i < _player3->getVCard().size(); ++i)
//		{
//			_player3->getVCard().at(i)->removeFromParent();
//		}
//		_player3->getCard(_vCard.at(51));
//		_player3->getCard(_vCard.at(52));
//		_player3->getCard(_vCard.at(53));
//		_player3->arrangeCard();
//		_player3->showCard();
//		_player3CardNumber->setString(StringUtils::format("%d", _player3->getVCard().size()));
//	}
//}
//
//bool GameScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
//{
//	if (_player1->getCurrentCard().size()>0)
//		log("0 player1 current size %d,%d", _player1->getCurrentCard().size(), _player1->getCurrentCard().at(0)->getCardNumber());
//	_startTouchedID = -1;
//	auto pos = touch->getLocation();
//	for (int i = (int)_player1->getVCard().size() - 1; i >= 0; i--)
//	{
//		auto card = _player1->getVCard().at(i);
//		auto cardPos = card->getPosition() - pos;
//		/*if (i != (int)_player1->getVCard().size() - 1)
//		{*/
//		if (cardPos.x >(-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
//		{
//			if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
//			{
//				_startTouchedID = i;
//				_endTouchedID = i;
//				auto card = _player1->getVCard().at(i);
//				card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
//				break;
//			}
//		}
//		/*}
//		else
//		{
//		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
//		{
//		if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
//		{
//		_startTouchedID = i;
//		_endTouchedID = i;
//		auto card = _player1->getVCard().at(i);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
//		break;
//		}
//		}
//		}*/
//	}
//	if (_startTouchedID == -1)
//		return false;
//	return true;
//}
//
//void GameScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
//{
//	auto pos = touch->getLocation();
//	for (int i = (int)_player1->getVCard().size() - 1; i >= 0; i--)
//	{
//		auto card = _player1->getVCard().at(i);
//		auto cardPos = card->getPosition() - pos;
//		/*if (i != (int)_player1->getVCard().size() - 1)
//		{*/
//		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
//		{
//			if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
//			{
//
//				_endTouchedID = i;
//				if (_endTouchedID > _startTouchedID)
//				{
//					for (auto j = _startTouchedID; j <= _endTouchedID; j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
//					}
//					for (auto j = 0; j < _startTouchedID; j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//					}
//					for (auto j = _endTouchedID + 1; j < _player1->getVCard().size(); j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//					}
//				}
//				else
//				{
//					for (auto j = _endTouchedID; j <= _startTouchedID; j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(196, 196, 196));
//					}
//					for (auto j = 0; j < _endTouchedID; j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//					}
//					for (auto j = _startTouchedID + 1; j < _player1->getVCard().size(); j++)
//					{
//						auto card = _player1->getVCard().at(j);
//						card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//					}
//				}
//				break;
//
//			}
//		}
//		/*}
//		else
//		{
//		if (cardPos.x > (-1.0 / 2 * card->getContentSize().width) && cardPos.x < (1.0 / 2 * card->getContentSize().width))
//		{
//		if (cardPos.y<(1.0 / 2 * card->getContentSize().height) && cardPos.y>(-1.0 / 2 * card->getContentSize().height))
//		{
//		_endTouchedID = i;
//		if (_endTouchedID >_startTouchedID)
//		{
//		for (auto j = _startTouchedID; j <= _endTouchedID; j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
//		}
//		for (auto j = 0; j < _startTouchedID; j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
//		}
//		for (auto j = _endTouchedID+1; j < _player1->getVCard().size(); j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
//		}
//		}
//		else
//		{
//		for (auto j = _endTouchedID; j <= _startTouchedID; j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(196, 196, 196));
//		}
//		for (auto j = 0; j < _endTouchedID; j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
//		}
//		for (auto j = _startTouchedID+1; j < _player1->getVCard().size(); j++)
//		{
//		auto card = _player1->getVCard().at(j);
//		card->getChildByTag(CardBody::BACKGROUND)->setColor(Color3B(255, 255, 255));
//		}
//		}
//		break;
//		}*/
//	}
//}
//
//void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unusedEvent)
//{
//	log("1 player1 current size %d", _player1->getCurrentCard().size());
//	log("startTouchedID = %d,endTouchedID = %d", _startTouchedID, _endTouchedID);
//	/*log("%d  %d", touch->getLocation().x, touch->getLocation().y);*/
//	auto pos = touch->getLocation();
//	if (_endTouchedID > _startTouchedID)
//	{
//		for (auto i = _startTouchedID; i <= _endTouchedID; i++)
//		{
//			auto card = _player1->getVCard().at(i);
//			card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//			if (card->getCardTouched())
//			{
//				/*log("s-%d", card->getCardNumber());*/
//				card->setPosition(card->getPosition() + Vec2(0, -20));
//				card->setCardTouched(false);
//
//				_player1->getCurrentCard().eraseObject(card);
//			}
//			else
//			{
//				card->setPosition(card->getPosition() + Vec2(0, 20));
//				card->setCardTouched(true);
//				_player1->getCurrentCard().pushBack(card);
//			}
//		}
//	}
//	else
//	{
//		log("2 player1 current size %d", _player1->getCurrentCard().size());
//		for (auto i = _endTouchedID; i <= _startTouchedID; i++)
//		{
//			auto card = _player1->getVCard().at(i);
//			card/*->getChildByTag(CardBody::BACKGROUND)*/->setColor(Color3B(255, 255, 255));
//			if (card->getCardTouched())
//			{
//				log("s-%d", card->getCardNumber());
//				card->setPosition(card->getPosition() + Vec2(0, -20));
//				card->setCardTouched(false);
//
//				_player1->getCurrentCard().eraseObject(card);
//				log("%d", _player1->getCurrentCard().size());
//			}
//			else
//			{
//				log("d-%d", card->getCardNumber());
//				card->setPosition(card->getPosition() + Vec2(0, 20));
//				card->setCardTouched(true);
//				_player1->getCurrentCard().pushBack(card);
//				log("%d", _player1->getCurrentCard().size());
//			}
//		}
//		log("3 player1 current size %d", _player1->getCurrentCard().size());
//	}
//
//}
//

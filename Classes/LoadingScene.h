#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class Loading : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void loadingCallback();//加载后的回调函数。
    // implement the "static create()" method manually
    CREATE_FUNC(Loading);
};

#endif // __HELLOWORLD_SCENE_H__

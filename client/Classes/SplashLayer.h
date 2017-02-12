//
//  SplashLayer.h
//  Quoridor
//
//  Created by shiyi on 2016/11/8.
//
//

#ifndef SplashLayer_H
#define SplashLayer_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class SplashLayer : public Layer
{
public:
	SplashLayer(){}
	~SplashLayer(){}

    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(SplashLayer);
        
private:
    //初始化用户数据
    void initUserData();
    //加载音乐
    void loadingAudio();
    //加载图片
    void loadingImage();
    //图片异步加载回调函数
    void loadingImageCallBack(Texture2D* texture, std::string name);
    //图片加载结束回调函数
    void loadingEndCallBack(Texture2D* texture, std::string name);
    //切换场景
    void changeScane(float dt);

    //音乐加载线程
    std::thread* td_logingAudio;
};

#endif /* SplashLayer_H */

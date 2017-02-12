//
//  SplashLayer.cpp
//  Quoridor
//
//  Created by shiyi on 2016/11/8.
//
//

#include "SplashLayer.h"
#include "GlobalDefine.h"
#include <thread>
#include "HelloWorldScene.h"
#include "ChoosePlayLayer.h"
#include "SettingLayer.h"
#include "GameLayer.h"
#include "GameWithCmpLayer.h"
#include "LoginLayer.h"
#include "client.h"

Scene* SplashLayer::createScene()
{
    auto layer = SplashLayer::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    return scene;
}


bool SplashLayer::init()
{
    if( !Layer::init() )
    {
        return false;
    }
    
    client::get();
    
//    ParticleSystem* particle = ParticleSystemQuad::create("particle.plist");
//    particle->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
//    addChild(particle, 0);
    
//    ParticleSystem* particle1 = ParticleSystemQuad::create("particle_texture.plist");
//    particle1->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
//    addChild(particle1, 1);
    
    //初始化logo精灵
    Sprite* logoSprite = Sprite::create("image/bg_splash.png");
    logoSprite->setPosition(ORIGIN.x + VISIBLESIZE.width/2, ORIGIN.y + VISIBLESIZE.height/2);
    this->addChild(logoSprite);

    //首次运行初始化用户数据
    if(!getBoolFromXML(IS_EXISTED))
    {
        initUserData();
        log("init UserData");
    }
    
    //图片和声音的异步加载
    td_logingAudio = new std::thread(&SplashLayer::loadingAudio, this);
    
    loadingImage();
    
    return true;
}

void SplashLayer::loadingImage()
{
    log("loadImage");
    
//    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/ChoosePlayScene.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "pnglist/ChoosePlayScene.plist"));
//    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/common_buttons.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "pnglist/common_buttons.plist"));
//    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/Dialog.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "pnglist/Dialog.plist"));
//    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/settingImage.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "pnglist/settingImage.plist"));
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/userHead.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "pnglist/userHead.plist"));
    
    Director::getInstance()->getTextureCache()->addImageAsync("image/Setting_mask.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/Setting_mask.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/bg_login.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/bg_login.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/vbar.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/vbar.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/hbar.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/hbar.png"));
//    Director::getInstance()->getTextureCache()->addImageAsync("image/thbar.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/thbar.png"));
//    Director::getInstance()->getTextureCache()->addImageAsync("image/tvbar.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/tvbar.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/black.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/black.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/white.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/white.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/blue.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/blue.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/yellow.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/yellow.png"));
    Director::getInstance()->getTextureCache()->addImageAsync("image/whiteblock.png", CC_CALLBACK_1(SplashLayer::loadingImageCallBack, this, "image/whiteblock.png"));
    
    
    Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", CC_CALLBACK_1(SplashLayer::loadingEndCallBack, this, "HelloWorld.png"));
    
}

void SplashLayer::loadingEndCallBack(Texture2D* texture, std::string name)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name, texture);
    log("loadImageEnd");
    
    //合并并销毁线程
    td_logingAudio->join();
    CC_SAFE_FREE(td_logingAudio);
    
    //切换场景
    changeScane(1.0f);
}

void SplashLayer::loadingImageCallBack(Texture2D* texture, std::string name)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name, texture);
}

void SplashLayer::loadingAudio()
{
    log("loadAudio");
    //初始化音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/gameBGM.wav");
    //初始化音效
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/failure.wav");
    log("loadAudioEnd");
}

void SplashLayer::changeScane(float dt)
{
    auto scene = LoginLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(dt, scene));
}

void SplashLayer::initUserData()
{
    setBoolToXML(SOUNDKEY, true);           //声音开关
    setBoolToXML(SHOCKKEY, false);          //震动开关
    setFloatToXML(EFFECTVOL, 0.80f);        //音效大小
    setFloatToXML(MUSICVOL, 0.35f);         //音乐大小
    setBoolToXML(IS_EXISTED, true);         //设置初始化标志
    UserDefault::getInstance()->flush();    //刷新
}

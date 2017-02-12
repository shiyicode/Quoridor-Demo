//
//  GlobalDefine.h
//  Quoridor
//
//  Created by shiyi on 2016/11/8.
//
//

#ifndef GlobalDefine_H
#define GlobalDefine_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const std::string NUM[] = {"", "一", "二", "三", "四", "五",
    "六", "七", "八", "九", "十"};
#define CHESSNUM 9
#define UNIT 13

#define WIDTH 640
#define HEIGHT 1024

#define VISIBLESIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#define audioEngine CocosDenshion::SimpleAudioEngine::getInstance()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey

#define IS_EXISTED      "isExisted"
#define EFFECTVOL       "effectVolume"
#define MUSICVOL        "musicVolume"
#define SOUNDKEY        "soundKey"
#define SHOCKKEY        "shockKey"


#endif /* GlobalDefine_H */

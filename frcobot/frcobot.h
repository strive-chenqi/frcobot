#pragma once
#include "ifrcobot.h"
#include "glo_def.h"

//具体状态类
class ManualMode : public IRobotMode {
public:
    void specificOperation()  {
        // 手动模式的具体操作
    }

    void init(IFrcoBot* ifcrbot) {

        if (ifcrbot->connectRobot() != 0) {
            printf("连接失败，请检查网络设置\n");
            return;
        }
        
        printf("连接成功\n");

        char ip[64] = "";
        char version[64] = "";
        uint8_t state;

        //测试
        ifcrbot->robot_.GetSDKVersion(version);
        printf("SDK version:%s\n", version);
        ifcrbot->robot_.GetControllerIP(ip);
        printf("controller ip:%s\n", ip);

        ifcrbot->robot_.Mode(1);
        sleep(1);

    }
};

class AutoMode : public IRobotMode {
public:
    void specificOperation()  {
        
    }

    void init(IFrcoBot* ifcrbot)  {

        ifcrbot->connectRobot();

        char ip[64] = "";
        char version[64] = "";
        uint8_t state;

        ifcrbot->robot_.GetSDKVersion(version);
        printf("SDK version:%s\n", version);
        ifcrbot->robot_.GetControllerIP(ip);
        printf("controller ip:%s\n", ip);

        ifcrbot->robot_.Mode(1);
        sleep(1);
    }
};


//两种状态改为使用状态模式，而不是两个子类

//class FrcobotManualMod : public IFrcoBot<FrcobotManualMod>
//{
//    friend class IFrcoBot<FrcobotManualMod>;
//
//public:
//    virtual void init();
//    
//    int jogMove(uint8_t ref, uint8_t nb, uint8_t dir, float vel, float acc, float max_dis);
//
//private:
//    FrcobotManualMod();
//    
//    
//
//private:
//    
//};
//
//class FrcobotAutoMod : public IFrcoBot<FrcobotManualMod>
//{
//    friend class IFrcoBot<FrcobotManualMod>;
//
//public:
//    virtual void init();
//
//private:
//    FrcobotAutoMod();
//    
//
//private:
//    
//};
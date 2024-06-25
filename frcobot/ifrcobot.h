#pragma once
#include "network_interface.h"
#include "robot.h"

class ManualMode; // ǰ������
class AutoMode;   // ǰ������
class IFrcoBot;

//״̬ģʽ��ÿһ������ʵ��һ����Context(IRobotMode)��һ��״̬��ص���Ϊ��Ҳ�����ԼӸ��ģ�ÿ������ʵ��ͬһ�ַ�������ʵ�ַ�ʽ��һ��
class IRobotMode {
public:
	virtual ~IRobotMode() = default;
	virtual void specificOperation() = 0; // �����������
	virtual void init(IFrcoBot* ifcrbot) = 0; // ��ʼ������
};


//template<typename T>
class IFrcoBot
{
	friend class ManualMode; //����Ϊ��Ԫ�෽�����robot_��
	friend class AutoMode;

public:
	//static T& GetInstance() {
	//	static T instance; 
	//	
	//	return instance;
	//}
	
	//����ģʽ��״̬ģʽ���
	static IFrcoBot& GetInstance(IRobotMode* mode) {
		static IFrcoBot instance;

		instance.setMode(mode);  

		return instance;
	}


private:
	IFrcoBot() : current_mode_(nullptr) {};
	virtual ~IFrcoBot();

	void setMode(IRobotMode* mode);
	int connectRobot();

//protected:
//	IFrcoBot() : current_mode_(nullptr){};
//	virtual ~IFrcoBot();

	

private:
	FRRobot robot_;                    //ʵ���������˶���

	IRobotMode* current_mode_; // ��ǰģʽ

};
#ifndef THEVENT_H
#define THEVENT_H

#include "stdafx.h"
#include "RenderObject.h"
#include <vector>
using namespace std;


#define EVENT_CREATION           1


#define CONDITION_FRAME          1
#define CONDITION_X              2
#define CONDITION_Y              3

#define RELATION_AND             1
#define RELATION_OR              2

#define COMPARISON_BIGGER        1
#define COMPARISON_EQUAL         2
#define COMPARISON_SMALLER       3

#define ATTRIBUTE_LIFE                                             1               //����
#define ATTRIBUTE_TYPE                                             2              //����
#define ATTRIBUTE_WIDTH_RATIO                                      3              //���
#define ATTRIBUTE_HEIGHT_RATIO                                     4              //�߱�
#define ATTRIBUTE_R                                                5              //R
#define ATTRIBUTE_G                                                6              //G
#define ATTRIBUTE_B                                                7              //B
#define ATTRIBUTE_ALPHA                                            8              //��͸����
#define ATTRIBUTE_FACE_DIRECTION                                   9              //����
#define ATTRIBUTE_SPEED                                            10             //�ٶ�
#define ATTRIBUTE_SPEED_DIRECTION                                  11            //�ٶȷ���
#define ATTRIBUTE_ACSPEED                                          12            //���ٶ�
#define ATTRIBUTE_ACSPEED_DIRECTION                                13           //���ٶȷ���
#define ATTRIBUTE_HORZ_RATIO                                       14            //���
#define ATTRIBUTE_VERT_RATIO                                       15            //�ݱ�
#define ATTRIBUTE_FOG                                              16            //��Ч��
#define ATTRIBUTE_DELETE                                           17           //����Ч��
#define ATTRIBUTE_HIGHLIGHT                                        18            //�߹�Ч��
#define ATTRIBUTE_SHADE                                            19           //��ӰЧ��
#define ATTRIBUTE_DELETE_OUT_OF_SCREEN                             20            //��������
#define ATTRIBUTE_DETERMINATION                                    21            //�޵�״̬

#define CHANGETYPE_CHANGETO      1
#define CHANGETYPE_INCREASE      2
#define CHANGETYPE_DECREASE      3

#define CHANGEMANNER_LINEAR     1                 //����
#define CHANGEMANNER_FIXED        2                 //�̶�
#define CHANGEMANNER_SIN           3                 //����

class THEvent{
public:
	UINT nOccurFrame;
	UINT nEventType;
public:
	THEvent(){}
	virtual ~THEvent(){}
	virtual void onEvent() = 0;
	bool operator >(THEvent* e){ return this->nOccurFrame > e->nOccurFrame; }
};

class EventCreation :public THEvent{
public:
	RenderObject *m_obj;
public:
	EventCreation() :m_obj(NULL){ nEventType = EVENT_CREATION; }
	EventCreation(RenderObject *obj) :m_obj(obj){ nEventType = EVENT_CREATION; }
	virtual ~EventCreation();
	virtual void onEvent();
};

class BulletEventCondition{
public:
	BYTE type;
	BYTE comparison;
	int dest;
};

class THBulletEvent{
public:
	int firstOccurFrame;
	BYTE attributeType;
	BYTE changeType;
	int value;
	BYTE changeManner;
	int changeTime;
	int repeatTime;               //�ظ���������
	int repeatFrameInterval;      //�ظ����  
public:
	THBulletEvent();
	bool IsOccuring(int frame);
};

#endif
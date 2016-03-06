#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "stdafx.h"

#define UPDATETYPE_V_ANGLE             1
#define UPDATETYPE_XY                  2
#define UPDATETYPE_CS                  3


#define DRAW_CENTERED                  1
#define DRAW_LEFTTOP                   2

class Engine;

class RenderObject{
protected:
	float x, y;
	float angle;
	float anglespeed;
	int xmin, xmax, ymin, ymax;    //���귶Χ�������˷�Χ��ɾ���ö���
	float velocity;             //�ٶ�
	float vx, vy;
	float av;                    //���ٶ� 
	float acangle;            //���ٶȷ���
	float ax, ay;                   //���ٶ�
	float vmax, vmin;               //����ٶȺ���С�ٶ�
	float anglemax, anglemin;       //���ǶȺ���С�Ƕ�
	float vxmin, vxmax, vymin, vymax; //����ٶ�
	float xdir, ydir;               //��������
	float x_step, y_step;         //ÿ֡λ����
	int texture;
	RECT imgRect;
	int imgWidth;
	int imgHeight;
	float alpha;                //͸����
	bool bAutoDelete;           //�Ƿ������Զ�ɾ��
	bool bNeedDelete;           //�Ƿ���Ҫɾ��
	BYTE updatetype;            //���·�ʽ��XY���귽ʽ���ٶ�-�Ƕȷ�ʽ��
public:
	RenderObject();
	virtual ~RenderObject();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void CommonUpdate(){
		Update();
	}
	virtual void CommonDraw(){
		Draw();
	}
	void DrawImg(float x, float y, int z, DWORD dwFlag, int r = 255, int g = 255, int b = 255);
	void SetRange(int xmin, int xmax, int ymin, int ymax);
	inline void EnableAutoDelete(){ bAutoDelete = true; }
	inline void DisableAutoDelete(){ bAutoDelete = false; }
	void SetTexture(int tex);
	inline int GetTexture();
	void SetDirection(int xdir, int ydir);
	void SetVelocity(float velocity);
	inline void SetVelocity_XY(float vx, float vy){
		this->vx = vx;
		this->vy = vy;
	}
	void SetPosition(float x, float y);
	void SetImgRect(int l, int t, int r, int b);
	void SetRotation(float x, float y, float angle);
	void SetScale(float x, float y, float sx, float sy);
	void SetReversalX(float x);
	void SetReversalY(float y);
	inline void SetAngle(float angle){ this->angle = angle; }
	inline void SetAngleSpeed(float anglespeed){ this->anglespeed = anglespeed; }
	inline void SetAlpha(float alpha){ this->alpha = alpha; }
	inline void SetAcceleration(float a){ this->av = a; }
	inline void SetAcAngle(float acangle){ this->acangle = acangle; }
	inline void SetAcceleration_XY(float ax, float ay){ this->ax = ax; this->ay = ay; }
	inline void SetVelocityRange(float vmin, float vmax){
		this->vmin = vmin;
		this->vmax = vmax;
	}
	inline void SetVelocityRange_XY(float vxmin, float vxmax, float vymin, float vymax){
		this->vxmin = vxmin;
		this->vxmax = vxmax;
		this->vymin = vymin;
		this->vymax = vymax;
	}
	void SetUpdateType(BYTE type);
	inline float GetX(){ return x; }
	inline float GetY(){ return y; }
	void ClearTransform();
	void MoveTo(float xdest, float ydest);
	void CalStep();
	void UpdatePosition();
	bool NeedAutoDelete();
	inline void MarkDelete(){ bNeedDelete = true; }

	friend class Engine;
};

#endif
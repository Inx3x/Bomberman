#pragma once
#include "Headers.h"

class Object
{
protected:
	OBJECT Key;
	Transform TransInfo;
	char* Texture[3];
	int Color;
	bool Active;
	ULONGLONG Time;

	int ItemList;
	int Explosion_Power_Cnt;
	int Explosion_Direction;
	int Explosion_Weight;
	bool Boss_Explosion;
public:
	Object();
	virtual ~Object();

	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	void SetPosition(const float& _x, const float& _y) { TransInfo.Position.x = _x; TransInfo.Position.y = _y; }
	void setActive(const bool& _Active) { Active = _Active; }
	void setTime(const ULONGLONG& _Time) { Time = _Time; }
	void setColor(const int _Color) { Color = _Color; }
	void setExplosionPowerZero() { Explosion_Power_Cnt = 0; }
	void setExplosionDirection(const int& _Explosion_Direction) { Explosion_Direction = _Explosion_Direction; }
	void setExplosion_Weight(const int& _ItemList){
		if (_ItemList == BOMBPOWERUP)	Explosion_Weight++;
		else if (Explosion_Weight > 1)	Explosion_Weight--;
	}
	void setBossExplosion(const int& _Boss_Explosion) { Boss_Explosion = _Boss_Explosion; }
	
	OBJECT GetKey() { return Key; }
	int getItemList() { return ItemList; }
	bool getActive() { return Active; }
	ULONGLONG gettTime() { return Time; }
	Vector3 GetPosition() const { return TransInfo.Position; }
	Vector3 GetScale() const { return TransInfo.Scale; }
	Transform GetTransform() const { return TransInfo; }
};


#include "Bullet_Main.h"


Bullet_SAlien::Bullet_SAlien() {

	for (int i = 0; i < Bullet_Main_Point_NUM; i++)
	{
		_Points[i].y = _Points[i].y * -1.0f;
	}
	CreateBufferObject();

};
Bullet_SAlien::~Bullet_SAlien() {};


void Bullet_SAlien::AutoTranslate_Bullet() {

	_y -= 0.0035;
	BulletTrans = Translate(_x, _y, 0.0);
	SetTRSMatrix(BulletTrans);


}
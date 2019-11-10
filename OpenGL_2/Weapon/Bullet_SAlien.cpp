#include "Bullet_Main.h"


Bullet_SAlien::Bullet_SAlien() {};
Bullet_SAlien::~Bullet_SAlien() {};


void Bullet_SAlien::AutoTranslate_Bullet() {

	_y -= 0.003;
	BulletTrans = Translate(_x, _y, 0.0);
	SetTRSMatrix(BulletTrans);


}
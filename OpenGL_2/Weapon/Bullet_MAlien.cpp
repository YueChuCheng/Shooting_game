#include "Bullet_Main.h"


Bullet_MAlien::Bullet_MAlien() {

	for (int i = 0; i < Bullet_Main_Point_NUM; i++)
	{
		_Points[i].y = _Points[i].y * -1.0f;
	}
	CreateBufferObject();

};
Bullet_MAlien::~Bullet_MAlien() {};


void Bullet_MAlien::AutoTranslate_Bullet() {

	
	_x += (MainRoleDis_x * 0.0035f ) ;
	_y += (MainRoleDis_y * 0.0035f );
	
	BulletTrans = Translate(_x , _y , 0.0);
	_mxMainRoleRotate = RotateZ(atan(MainRoleDis_x / MainRoleDis_y)*-50.0f);
	SetTRSMatrix(BulletTrans * _mxMainRoleRotate);

}
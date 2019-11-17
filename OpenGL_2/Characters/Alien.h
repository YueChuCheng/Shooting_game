#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int Alien_Point_NUM = 6; //最大點子總數


class Alien
{
public:
	Alien() {};
	~Alien() {};

	bool used = false;//空間是否被利用

	GLfloat _x = 0.0f;
	GLfloat _y = -3.0f; //一開始不得出現於螢幕上
	bool alife = true; //一開始為活著的狀態
	float alphea = 1.0;

	virtual void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	virtual GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	virtual void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColorx, GLfloat vColory, GLfloat vColorz, GLfloat vColorw); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color

	virtual virtual void Draw() = 0; //宣告為虛擬類別，於各自類別中設計
	virtual virtual void DrawW() = 0;//宣告為虛擬類別，於各自類別中設計

	//移動矩陣
	mat4 mxTran_Alien;
	mat4 mxRotate_Alien;
	//自動移動函式
	virtual void AutomaticMotion() {};
	virtual void AutomaticMotion(GLfloat MainRole_x, GLfloat MainRole_y) {};
	virtual void AutomaticMotion(float timer) {};

	//自動發射飛彈函式
	virtual void AutomaticFire(mat4 Alien_mxTran) = 0;

	//自動檢查是否有受傷、死亡函式
	virtual void AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien) = 0;


	float dis_x = 0; //相差多少寬
	float dis_y = 0; //相差多少高




	private:

	vec4 _Points[Alien_Point_NUM];
	vec4 _Colors[Alien_Point_NUM];

	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;



	void CreateBufferObject();

	protected:
		// 紀錄是否有矩陣的更新
		bool  _bUpdateMV;
		bool  _bUpdateProj;
		bool if_first_alien = true; //第一次發出Alien
		
};



//Small Alien 
class Small_Alien : public Alien
{
public:
	Small_Alien() ;
	~Small_Alien();
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	virtual void SetTRSMatrix(mat4& mat);
	GLuint GetShaderHandle() { return _Program; }
	void Draw();

	void DrawW();

	void AutomaticMotion();
	
	//自動發射飛彈函式
	 void AutomaticFire(mat4 Alien_mxTran) ;

	//自動檢查是否有受傷、死亡函式
	 void AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y,float MAX_X, float MAX_Y, bool *HurtAlien);

	 const double MAX_X = 0.2; //最長寬
	 const double MAX_Y = 0.35; //最高點
	
	 


private:


	vec4 _Points[Alien_Point_NUM];
	vec4 _Colors[Alien_Point_NUM];

	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;



	void CreateBufferObject();



	const int Blood_original = 2;
	int Blood = Blood_original;
	

	


};






//Middle Alien 
class Middle_Alien : public Alien
{
public:
	Middle_Alien();
	~Middle_Alien();
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	virtual void SetTRSMatrix(mat4& mat);
	GLuint GetShaderHandle() { return _Program; }
	void Draw();

	void DrawW();

	void AutomaticMotion(GLfloat MainRole_x , GLfloat MainRole_y);

	//自動發射飛彈函式
	void AutomaticFire(mat4 Alien_mxTran);

	//自動檢查是否有受傷、死亡函式
	void AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien);


	const double MAX_X = 0.3; //最長寬
	const double MAX_Y = 0.35; //最高點

	


private:




	vec4 _Points[Alien_Point_NUM];
	vec4 _Colors[Alien_Point_NUM];

	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;



	void CreateBufferObject();



	const int Blood_original = 4;
	int Blood = Blood_original;



};



const int rectangle_BAlien = 6;
const int BAlien_Point_NUM = (rectangle_BAlien * 5 ); //最大點子總數

//BOSS_Alien 
class BOSS_Alien : public Alien
{
public:
	BOSS_Alien();
	~BOSS_Alien();
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	virtual void SetTRSMatrix(mat4& mat);
	GLuint GetShaderHandle() { return _Program; }
	void Draw();

	void DrawW();

	void AutomaticMotion(float timer);

	bool first_direction_x = true;
	bool first_direction_y = true;

	//自動發射飛彈函式
	void AutomaticFire(mat4 Alien_mxTran);

	//自動檢查是否有受傷、死亡函式
	void AutoCheckHurtDie(GLfloat Bullet_x, GLfloat Bullet_y, float MAX_X, float MAX_Y, bool* HurtAlien);

	const double MAX_X = 0.95; //最長寬
	const double MAX_Y = 0.6; //最高點



private:



	vec4 _Points[BAlien_Point_NUM];
	vec4 _Colors[BAlien_Point_NUM];

	// VAO
	GLuint _VAO;
	// VBO
	GLuint _VBO;
	//  for Shader
	GLuint _Program;
	// Vertex Position Attribute
	GLuint _ModelView, _Projection;
	// Matrix 
	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;



	void CreateBufferObject();



	const int Blood_original = 30;
	int Blood = Blood_original;

};




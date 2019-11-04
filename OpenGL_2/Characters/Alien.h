#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int Alien_Point_NUM = 6; //最大點子總數


class Alien
{
public:
	Alien() {
	
	
	
	
	};
	~Alien() {};

	GLfloat _x = 0;
	GLfloat _y = 0;

	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color

	virtual void Draw() = 0; //宣告為虛擬類別，於各自類別中設計
	virtual void DrawW() = 0;//宣告為虛擬類別，於各自類別中設計

	//移動矩陣
	mat4 mxTran_Alien;

	//自動移動函式
	virtual void AutomaticMotion() = 0;

	//自動發射飛彈函式
	virtual void AutomaticFire(mat4 Alien_mxTran) = 0;

	//自動檢查是否有受傷、死亡函式
	virtual void AutoCheckHurtDie() = 0;



	protected:

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

	// 紀錄是否有矩陣的更新
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();
};



//Small Alien 
class Small_Alien : public Alien
{
public:
	Small_Alien();
	~Small_Alien();
	void Draw();

	void DrawW();

	 void AutomaticMotion();

	//自動發射飛彈函式
	 void AutomaticFire(mat4 Alien_mxTran) ;

	//自動檢查是否有受傷、死亡函式
	 void AutoCheckHurtDie();

private:

	


};






//Middle Alien 
class Middle_Alien : public Alien
{
public:
	Middle_Alien();
	~Middle_Alien();
	void Draw();

	void DrawW();

	void AutomaticMotion();

	//自動發射飛彈函式
	void AutomaticFire(mat4 Alien_mxTran);

	//自動檢查是否有受傷、死亡函式
	void AutoCheckHurtDie();

private:




};



//BOSS_Alien 
class BOSS_Alien : public Alien
{
public:
	BOSS_Alien();
	~BOSS_Alien();
	void Draw();

	void DrawW();

	void AutomaticMotion();

	//自動發射飛彈函式
	void AutomaticFire(mat4 Alien_mxTran);

	//自動檢查是否有受傷、死亡函式
	void AutoCheckHurtDie();

private:




};



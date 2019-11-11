#include "../Header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4; 

const int Bullet_Main_Head = 80;
const int Bullet_Main_Button = 6;

const int Bullet_Main_Point_NUM = Bullet_Main_Head + Bullet_Main_Button;



class Bullet_Main
{
public:
	Bullet_Main();
	~Bullet_Main();
	GLfloat _x = 0.0f;
	GLfloat _y = 0.0f;
	int Bullet_UseSpace; //�p��ϥέ��Ӱ}�C
	GLfloat _scale = 1.0f;
	GLfloat _speed = 0.0f;
	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	void Draw();
	void DrawW();
	GLuint GetShaderHandle() { return _Program; }

	mat4 BulletTrans;


	const float MAX_X = 0.045f; //�̪��e
	const float MAX_Y = 0.8f; //�̰��I



	//�۰ʲ��ʪ���
	virtual void AutoTranslate_Bullet();

	bool HurtAlien =false ;  //�O�_����Alien

protected:
	vec4 _Points[Bullet_Main_Point_NUM];
	vec4 _Colors[Bullet_Main_Point_NUM];

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

	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();
};








class Bullet_SAlien :public Bullet_Main
{
public:
	Bullet_SAlien ();
	~Bullet_SAlien ();

	//void CreateBullet_SmallAlien();

	void AutoTranslate_Bullet();
private:

};




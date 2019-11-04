#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int Alien_Point_NUM = 6; //�̤j�I�l�`��


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

	virtual void Draw() = 0; //�ŧi���������O�A��U�����O���]�p
	virtual void DrawW() = 0;//�ŧi���������O�A��U�����O���]�p

	//���ʯx�}
	mat4 mxTran_Alien;

	//�۰ʲ��ʨ禡
	virtual void AutomaticMotion() = 0;

	//�۰ʵo�g���u�禡
	virtual void AutomaticFire(mat4 Alien_mxTran) = 0;

	//�۰��ˬd�O�_�����ˡB���`�禡
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

	// �����O�_���x�}����s
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

	//�۰ʵo�g���u�禡
	 void AutomaticFire(mat4 Alien_mxTran) ;

	//�۰��ˬd�O�_�����ˡB���`�禡
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

	//�۰ʵo�g���u�禡
	void AutomaticFire(mat4 Alien_mxTran);

	//�۰��ˬd�O�_�����ˡB���`�禡
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

	//�۰ʵo�g���u�禡
	void AutomaticFire(mat4 Alien_mxTran);

	//�۰��ˬd�O�_�����ˡB���`�禡
	void AutoCheckHurtDie();

private:




};


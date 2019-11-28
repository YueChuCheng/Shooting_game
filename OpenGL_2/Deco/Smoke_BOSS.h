#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int Smoke_circle = 50;

const int Smoke_Point_NUM = Smoke_circle * 16; //�̤j�I�l�`��


class Smoke
{
public:
	Smoke();
	~Smoke() {};

	bool used = false;//�Ŷ��O�_�Q�Q��

	GLfloat _x = 0.0f;
	GLfloat _y = -3.0f; //�@�}�l���o�X�{��ù��W


	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);

	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color


	void Draw(); //�ŧi���������O�A��U�����O���]�p

	float timer_smoke = 0;

	//���ʯx�}
	mat4 mxTran_Smoke;
	//�۰ʲ��ʨ禡
	void AutomaticMotion(float boss_x, float boss_y,float delta);

	void SetAlpha(GLfloat alpha);
	GLfloat alphea_Smoke = 1.0f;


	float dis_x = 0; //�ۮt�h�ּe
	float dis_y = 0; //�ۮt�h�ְ�




private:

	vec4 _Points[Smoke_Point_NUM];
	vec4 _Colors[Smoke_Point_NUM];

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

	// �����O�_���x�}����s
	bool  _bUpdateMV;
	bool  _bUpdateProj;
	bool if_first_alien = true; //�Ĥ@���o�XSmoke

};
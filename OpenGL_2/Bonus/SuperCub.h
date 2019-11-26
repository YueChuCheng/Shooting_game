#include "../header/Angel.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int SuperCube_triangle = 3;
const int SuperCube_circle = 50;
const int SuperCube_Point_NUM = SuperCube_circle + SuperCube_triangle * 2; //�̤j�I�l�`��

enum Cube_style
{
	HIT = 0 , TWO_GUN = 1
};


class SuperCube
{
public:
	SuperCube();
	~SuperCube() {};

	int cubeStyle; //cube �����A
	
	bool used = false;//�Ŷ��O�_�Q�Q��
	bool if_first_cube = false;


	GLfloat _x = 0.0f;
	GLfloat _y = 3.0f; //�@�}�l���o�X�{��ù��W


	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);

	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color
	void Draw(); //�ŧi���������O�A��U�����O���]�p
	
	void CheackMainRole(GLfloat x, GLfloat y, float Max_X, float MAX_Y); //�ˬd�O�_�Qmain role�I��


	//���ʯx�}
	mat4 mxTran_SuperCube;
	mat4 mxRotate_SuperCube;

	//�۰ʲ��ʨ禡
	void AutomaticMotion(float mainrole_x, float mainrole_y);

	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	
	
	float MAX_X = 0.5f; //�̪��e
	float MAX_Y = 0.5f; //�̰��I


private:

	float theta = 0.0f; //�������ਤ��
	
	vec4 _Points[SuperCube_Point_NUM];
	vec4 _Colors[SuperCube_Point_NUM];

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
	bool if_first_alien = true; //�Ĥ@���o�XSuperCube

	


};

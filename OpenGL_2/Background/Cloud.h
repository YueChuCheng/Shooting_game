#include "../Header/Angel.h"

typedef Angel::vec4 color4;
typedef Angel::vec4 point4;


const int Cloud_circle = 200;
const int Cloud_rectangle = 6;
const int Cloud_Point_NUM = ( Cloud_circle * 4 ) + (Cloud_rectangle *2);



class Cloud
{
public:
	Cloud();
	~Cloud();
	GLfloat _x = 0;
	GLfloat _y = 0;
	GLfloat _scale = 1;

	GLfloat _xLoc , _yLoc , _scaleLoc; //雲朵位置


	void SetShader(mat4& mxModelView, mat4& mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _Program; }
	void SetViewMatrix(mat4& mat);
	void SetProjectionMatrix(mat4& mat);
	void SetTRSMatrix(mat4& mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color

	void Draw();
	void DrawW();

	//API 位置(X、Y) 、大小
	void SetXYScale(float fx, float fy, float fscale);
	
	//自動移動背景
	void AutoTranslate_Background();
private:
	
	vec4 _Points[Cloud_Point_NUM];
	vec4 _Colors[Cloud_Point_NUM];

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


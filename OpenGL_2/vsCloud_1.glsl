#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;


uniform float fx ;
uniform float fy;
uniform float fscale;



void main()
{
	
	mat4 mxTranslate = mat4(
		
		fscale,0,0,0,
		0,fscale,0,0,
		0,0,1,0,
		fx,fy,0,1
	
	);
	
	


		




    gl_Position =  Projection *  ModelView  * mxTranslate  * vPosition ;
	color = vColor;
}

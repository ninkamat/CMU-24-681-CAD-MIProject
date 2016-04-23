#define YSGLSL_TEX_TYPE_NONE                0
#define YSGLSL_TEX_TYPE_TILING              1
#define YSGLSL_TEX_TYPE_BILLBOARD           2
#define YSGLSL_TEX_TYPE_3DTILING            3
#define YSGLSL_TEX_TYPE_ATTRIBUTE           4
#define YSGLSL_TEX_BILLBOARD_PERS           0
#define YSGLSL_TEX_BILLBOARD_ORTHO          1
#define YSGLSL_TEX_WRAP_CUTOFF              0
#define YSGLSL_TEX_WRAP_REPEAT              1
#define YSGLSL_BILLBOARD_CLIPPING_NONE      0
#define YSGLSL_BILLBOARD_CLIPPING_CIRCLE    1
#define YSGLSL_POINTSPRITE_CLIPPING_NONE      0
#define YSGLSL_POINTSPRITE_CLIPPING_CIRCLE    1
#define YSGLSL_MARKER_TYPE_PLAIN            0
#define YSGLSL_MARKER_TYPE_CIRCLE           1
#define YSGLSL_MARKER_TYPE_RECT             2
#define YSGLSL_MARKER_TYPE_STAR             3
#define YSGLSL_MARKER_TYPE_EMPTY_RECT       4
#define YSGLSL_MARKER_TYPE_EMPTY_CIRCLE     5
#define YSGLSL_MARKER_TYPE_EMPTY_STAR       6
#define YSGLSL_MAX_NUM_LIGHT                8
#define YSGLSL_POINTSPRITE_SIZE_IN_PIXEL    0
#define YSGLSL_POINTSPRITE_SIZE_IN_3DSPACE  1
#define YSGLSL_RENDERER_TYPE_NONE           0
#define YSGLSL_RENDERER_TYPE_PLAIN2D        1
#define YSGLSL_RENDERER_TYPE_MARKER2D       2
#define YSGLSL_RENDERER_TYPE_POINTSPRITE2D  3
#define YSGLSL_RENDERER_TYPE_PLAIN3D        10
#define YSGLSL_RENDERER_TYPE_SHADED3D       11
#define YSGLSL_RENDERER_TYPE_FLASH          12
#define YSGLSL_RENDERER_TYPE_MARKER3D       13
#define YSGLSL_RENDERER_TYPE_POINTSPRITE3D  14
#define YSGLSL_SHADOWMAP_NONE               0
#define YSGLSL_SHADOWMAP_USE                1
#define YSGLSL_SHADOWMAP_DEBUG              2

#ifdef GL_ES
	#define LOWP lowp
	#define MIDP mediump
	#define HIGHP highp
#else
	#define LOWP
	#define MIDP
	#define HIGHP
#endif


uniform  HIGHP  mat4  projection;
uniform  HIGHP  mat4  modelView;
uniform  MIDP  float viewportWid,viewportHei;
uniform int viewportOrigin;

uniform int markerType;
uniform  MIDP  float dimension;

attribute  HIGHP  vec3 vertex;
attribute  MIDP  vec2 pixelOffset;
attribute  LOWP  vec4 colorIn;

varying  MIDP  vec2 offsetOut;
varying  LOWP  vec4 color;

// Variables for fog
uniform bool fogEnabled;
uniform  MIDP  float fogDensity;
uniform  LOWP  vec4 fogColor;
varying  HIGHP  float zInViewCoord;

// Variables for z-offset
uniform bool useZOffset;
uniform  MIDP  float zOffset;


void main()
{
	 HIGHP  vec4 vertexInView=modelView*vec4(vertex,1.0);

	if(false!=fogEnabled)
	{
		zInViewCoord=-vertexInView.z;
	}
	else
	{
		zInViewCoord=0.0;
	}

	gl_Position=projection*vertexInView;

	if(true==useZOffset)
	{
		gl_Position.z+=zOffset*gl_Position[3];
	}

	float xOffset=((2.0*pixelOffset.x)/viewportWid)*gl_Position[3];
	float yOffset=((2.0*pixelOffset.y)/viewportHei)*gl_Position[3];
	gl_Position.x+=xOffset;
	gl_Position.y+=yOffset;
	offsetOut=pixelOffset;
	color=colorIn;
}

uniform sampler2D hImage;
uniform float time;
uniform float wind;
varying vec2 coords;
varying vec4 offset;
float pi=3.14;
void main(){
	gl_TexCoord[0]=gl_MultiTexCoord0;
	float mscale=1.0;
	offset=vec4(0,0,0,0);
	coords=gl_TexCoord[0].st;
	offset.y=cos(time+(gl_Vertex.x)*(wind/5.0*pi))*0.05;
	gl_Position=gl_ModelViewProjectionMatrix*(gl_Vertex+offset);

}
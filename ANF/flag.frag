uniform sampler2D hImage;
varying vec2 coords;
varying vec4 offset;
void main(){
	gl_FragColor=texture2D(hImage,coords)*0.4+offset.y*0.6+gl_Color;
}
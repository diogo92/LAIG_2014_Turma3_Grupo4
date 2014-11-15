uniform sampler2D hImage;
varying vec2 coords;
void main(){
	gl_FragColor=texture2D(hImage,coords);
}
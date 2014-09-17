#ifndef _DATAHOLDERS_H_
#define _DATAHOLDERS_H_

struct global_data {
	unsigned char drawMode; // 0 = fill; 1 = line; 2 = point;
	unsigned char drawShading; // 0 = flat; 1 = gouraud;
	float drawBackground[4]; // values range [0,1]
	unsigned char cullingFace; // 0 = none; 1 = back; 2 = front; 3 = both;
	unsigned char cullingOrder; // 0 = ccw; 1 = cw;
} ;

#endif
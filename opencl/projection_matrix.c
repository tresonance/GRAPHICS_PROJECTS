#include "header.h"

void		init_ortho(float l, float r, float t, float b, float n, float f, float m[16])
{
	//float		*m;

	//if(!(m = (float*)malloc(sizeof(float) * 16)))
	//	exit(1);
	memset(&m[0], 0.0f, sizeof(float) * 16);
	m[0] = 2.0f/(r - l);
	m[3] = -(r + l)/((float)(r - l));

	m[5] = 2.0f/(float)(t - b);
	m[7] = -(t + b)/((float)(t - b));

	m[10] = 2.0f/(f - n);
	m[11] = -(f + n)/((float)(f - n));

	m[15] = 1.0f;

	//return (m);
}

void		init_perspective(float fov, float aspect_ratio, float f, float n, float m[16])
{
	//float		*m;
	float			d;

	//if(!(m = (float*)malloc(sizeof(float) * 16)))
	//	exit(1);
	d = 1.0/(float)tan((fov/2) * PI/180.0);
	memset(&m[0], 0.0f, sizeof(float)*16);
	m[0] = d/(float)aspect_ratio;
	m[5] = d;
	m[10] = -(f + n) / ((float)(f - n));
	m[11] = -2.0*f*n / ((float)(f - n));
	m[14] = -1.0f;
	//return (m);
}

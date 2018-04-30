#include "opencl.h"

float3				matrix_vector_multily(float *m1, float4 vec)
{
	t_vector		v;;
	
	v.s[0] = m1->s[0] * vec.s[0] + m1->s[4]* vec.s[1] +  m1->s[8]*vex.s[2] +  m1->s[12]*vex.s[3];
	v.s[1] = m1->s[1] * vec.s[0] + m1->s[5]* vec.s[1] +  m1->s[9]*vex.s[2] +  m1->s[13]*vex.s[3];
	v.s[2] = m1->s[2] * vec.s[0] + m1->s[6]* vec.s[1] +  m1->s[10]*vex.s[2] +  m1->s[14]*vex.s[3];
	v.s[2] = m1->s[3] * vec.s[0] + m1->s[7]* vec.s[1] +  m1->s[11]*vex.s[2] +  m1->s[15]*vex.s[3];
	return (v);
}

void		gl_lookat(float3 eye, float3 lookat, float3 up, __global float16 *m)
{
	flaot16 m1;
	flaot16 m2;
	flaot16 m2;
	float4 u, v w;
	float value;
	m1 = (float16)(1.0, 0.0, 0.0,-eye.s[0], 
					      0.0, 1.0, 0.0, -eye.s[1], 
						  0.0, 0.0, 1.0, -eye.s[2],
						  0.0, 0.0,0.0,1.0 );
	w = normalize(eye - lookat);
	u = normalize(cross(up, w));
	v = cross(w, u);
	m2 = (float16)(u.s[0], u.s[1], u.s[2], 0.0,
					v.s[0], v.s[1],v.s[2], 0.0,
					w.s[0], w.s[1],w.s[2], 0.0,
					0.0, 0.0, 0.0, 1.0);
	for(int m=0; m < 4; m++)
	{
		for(n= 0; n < 4; n++)
		{
			value = 0;
			for (k=0; k < 4; k++)
				value += m1[k*4 + m] + m2[k*n + k];
			m[4*n + m] = value;
		}
	}
	return (m);
}

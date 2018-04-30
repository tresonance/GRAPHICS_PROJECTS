#include "opencl.h"

	__kernel void init_sphere(__global t_camera *cam, __global float16 *m){
	flaot16 m1;
	flaot16 m2;
	float4 u, v w;
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
	int tx = get_global_id(0); 
	int ty = get_global_id(1);
 
	float value = 0;
	for (int k = 0; k < wA; ++k)
	{
		float elementA = m2[ty * wA + k];
		float elementB = m1[k * wB + tx];
		value += elementA * elementB;
	}
	m[ty * wA + tx] = value;
}

__kernel void main(__global float4 *dst, __global t_scene *snene, __global t_camera *camera  __global uint width, uint height, __global float *lookatMatrix, __global float *projectionMatrix)
{
	unsigned int gid = get_global_id(0);
	t_ray ray;

	scene->sphere.pos = matrix_vector_multiply(lookatMatrix, ray->pos);
	ray->pos = camera->pos;
	dest[gid] = raytrace(scene, 

}

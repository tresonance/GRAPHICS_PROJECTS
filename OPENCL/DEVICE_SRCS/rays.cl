#include "cl_header.h"

float3					reflection_ray(float3 raydir, flaot3 normal, flaot3 inter_pos)
{
	t_ray				refl;

	refl.dir = (raydir - 2.0f * normal * (dot(raydir, normal));
	refl.dir = normalize(refl.dir);
	refl.pos = inter_pos + BIAS * raydir;
}


t_ray					refraction_ray(flaot3 raydir, float3 normal, float refr_index, float3 inter_pos)
{
	float cos_incidence;
	float cos_trans_square;
	t_ray				refr;

	cos_incidence = -dot( normal, raydir );
	cos_trans_square = 1.0f - refr_index * refr_index * (1.0f - cos_incidence * cos_incidence);
	refr.dir = (refr_index * raydir) + (refr_index * cos_incidence - sqrt( cos_trans_square )) * normal;
	refr.pos = inetr_pos + BIAS * raydir;
	refr.dir = normalize(refr.dir);
	return (refr);
}

t_ray					shadow_ray(float3 inetr_pos, t_light l, float3  raydir, float *light_dist)
{
	t_ray				shadow_ray;

	shadow_ray.pos = inetr_pos + BIAS * raydir;
	if(l.light_type <= 0)
	{
		shadow_ray.dir = l.pos - shadow_ray.pos;
		*light_dist = length(shadow_ray);
	}
	else 
	{
		shadow_ray.dir = l.pos - shadow_ray.pos;
		*light_dist = length(shadow_ray);
		shadow_ray.dir = l.dir;
	}
	shadow_ray.dir = normalize(shadow_ray);
	return (shadow_ray);
}

float3					matrix_mul(__global float *matrix, float3 *vect)
{
	float3				result;

	result.x = matrix[0]*((*vect).x) + matrix[4]*((*vect).y) + matrix[8]*((*vect).z) + matrix[12];
	result.y = matrix[1]*((*vect).x) + matrix[5]*((*vect).y) + matrix[9]*((*vect).z) + matrix[13];
	result.z = matrix[2]*((*vect).x) + matrix[6]*((*vect).y) + matrix[10]*((*vect).z) + matrix[14];
	return (result);
}

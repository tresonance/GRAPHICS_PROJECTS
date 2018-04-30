#include "opencl.h"

float					inter(t_scene *scene, t_ray *ray, void **hit,  int *hit_type)
{
	float				minT;
	int					i;
	float				t;

	minT = kMaxRenderDist;
	for(i = 0; i < scene->num_sphere; i++)
	{
		if (ray_sphere_inter(scene->sphere[i], ray, &t))
		{
			minT = t;
			*hit = scene->sphere[i];
			*hit_type = 1;
		}
	}
	for(i = 0; i < scene->num_plane; i++)
	{
		if (ray_plane_inter(scene->plane[i], ray, &t))
		{
			minT = t;
			*hit = scene->plane[i];
			*hit_type = 2;
		}
	}
	return (minT);
}

float4				raytrace(t_scene *scene, t_ray *ray)
{
	void			*hit_obj;
	int				hit_type;
	float			t;
	float4			color;
	float3			normal;
	float3			hit_point;
	float3			m;

	hit_obj = NULL;
	hit_type = 0;
	t = inter(scene, ray, &hit_obj, &hit_type);
	color = (float4)(0.0, 0.0, 0.0,0.0);
	if (t < kMaxRenderDist)
	{
		hit_point = ray->pos + t * ray->dir;
		if (hit_type == 1)
		{
			normal = (float3)(hit_point - ((t_sphere*)hit_obj)->pos);
			m = ((t_sphere*)hit_obj)->material;
		}
		else if(hit_type == 2)
		{
			normal = ((t_plane*)hit_obj)->normal;
			m = ((t_plane*)hit_obj)->material;
		}
		else
		{
			m.color = (float4)(1.0, 1.0, 1.0, 1.0);
		}
	}
	return (clamp(m.color, 0, 1));
}

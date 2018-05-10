#include "cl_header.h"

float4						raytrace(__global t_scene *s, t_ray *ray, int depth)
{
	float4					color;
	int						hit_type;
	void					*hit_obj;
	float					t;
	float3					normal;
	float3					hit_point;
	float					material;
	float4					diffuse_color;


	hit_obj = NULL;
	hit_type = -1;
	color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	material = scene->standard_material;
	t = intersection_obj(s, ray, &hit_obj, &hit_type); 
	if(NULL != hit_obj)
	{
		hit_point = ray->pos + (t * ray->dir);
		if(hit_type = SPHERE)
		{
			normal = hit_point - ((t_sphere*)hit_obj)->pos;
			material = ((t_sphere*)hit_obj)->m;
		}
		else if (hit_type == PLANE)
		{
			normal = ((t_plane)hit_obj)->normal;
			material = ((t_sphere*)hit_obj)->m;
		}

		if(material.color_type == 1)
		{
			if(((int)(hit_point.x / 5.0)) % 2 == 0 )
			{
				if(((int)(hit_point.z / 5.0)) % 2 == 0 )
				{
					diffuse_color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
				}
			}
		}
		else
		{
			if(((int)(hit_point.z / 5.0)) % 2 != 0 )
			{
				diffuse_color = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		if(depth < MAXDEPTH && m->reflective > 0)
		{
			t_ray	refl = reflection_ray(ray->dir, normal, hit_point);
			diffuse_color += m->reflective * raytrace(s, &refl, depth + 1);
		}
		if(depth < MAXDEPTH && m->refractive > 0)
		{
			t_ray	refr = refraction_ray(ray->dir, normal, m.refractive, hit_point);			
			diffuse_color += m->refractive * raytrace(s, &refr, depth + 1);
		}
		int		i = -1;
		t_ray	shadow_r;
		float	light_dist;

		while(++i < s->light_num)
		{
			hit_obj = NULL;
			hit_type = -1;
			shadow_r = shadow_ray(hit_point, s->light[i], ray->dir, &light_dist);
			t = intersection_obj(s, &shadow_r, &hit_obj, &hit_type); 
			if(t > light_dist)
				color += diffuse_color * s->light[i].color * max(0.0f, dot(normal, ray->dir));
		}
	}
	return (clamp(color, 0.0f, 1.0f);
}

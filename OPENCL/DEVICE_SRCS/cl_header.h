#ifndef CL_HEADER_H
#define CL_HEADER_H

#define WIDTH 600
#define HEIGHT 450

#define BIAS 0.001f
#define MAXDIST 8000.0f
#define TOLERANCE 0.0001f

#define MAXDEPTH 2
#define ANTI_ALIASING 2
#define FOC 1.0

#define SPHERE_NUMBER_MAXI 15
#define CYLINDER_NUMBER_MAXI 15
#define CONE_NUMBER_MAXI 15
#define PLANE_NUMBER_MAXI 15
#define BOX_NUMBER_MAXI 15
#define LIGHT_NUMBER_MAXI 15

#define TRUE 1
#define FALSE 0

typedef enum {
	SPHERE, PLANE, CYLINDER, CONE, BOX
}						e_type;


typedef struct			s_cam
{
	float3				pos;
	float3				lookat;
	float3				dir;
	float3				up;
	float3				right;
}						t_cam;

typedef struct			s_material
{
	int					color_type;
	float4				color;
	float				reflective;
	float				refractive;
}						t_material;

typedef struct			s_sphere
{
	float3				pos;
	float				radius;
	float3				color;
	t_material			m;
}						t_sphere;

typedef struct			s_cylinder
{
	float3				pos;
	float				radius;
	float3				dir;
	int					is_cut;
	float3				cut_axe;
	float				cut_length;
	t_material			m;
}						t_cylinder, t_cone;

typedef struct			s_plane
{
	float3				pos;
	float3				normal;
	t_material			m;
}						t_plane;

typedef struct			s_box
{
	float3				bottom_left;
	float3				top_right;
	t_material			m;
}						t_box;

typedef struct			s_ray
{
	float3				pos;
	float3				dir;
}						t_ray;

typedef struct			s_light
{
	float3				pos;
	int					light_type;
	float3				dir;
	float4				color;
	float				light_dist;
}						t_light;

typedef struct			s_scene
{
	t_sphere			spheres[SPHERE_NUMBER_MAXI];
	int					num_sphere;
	t_cylinder			cylinders[CYLINDER_NUMBER_MAXI];
	int					num_cylinder;
	t_cone				cones[CONE_NUMBER_MAXI];
	int					num_cone;
	t_plane				planes[PLANE_NUMBER_MAXI];
	int					num_plane;
	t_box				boxs[BOX_NUMBER_MAXI];
	int					num_box;
	t_light				lights[LIGHT_NUMBER_MAXI];
	int					num_light;
	t_material			standart_material;
}						t_scene;

/*
 * ray_cl
 */

t_ray					reflection_ray(float3 raydir, float3 normal, float3 inter_pos);
t_ray					refraction_ray(float3 raydir, float3 normal, float refr_index, float3 inter_pos);
t_ray					shadow_ray(float3 inter_pos, t_light l, float3 raydir, float *light_dist);
float3					matrix_mul(__global float *matrix, float3 *vect);
/*
 * inter.cl 
 */

//int						ray_sphere_inter(t_sphere *s, t_ray *ray, float *t);
//int						ray_plane_inter(t_plane *s, t_ray *ray, float *t);
//float					intersection_obj(__global t_scene *s, t_ray *ray, void **obj, int *type);
/*
 * raytrace
 */
//float4					raytrace(__global t_scene *s, t_ray *ray, int depth);
#endif

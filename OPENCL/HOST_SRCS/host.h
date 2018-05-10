#ifndef __HOST_H__
#define __HOST_H__

#include "../libft/libft.h"
#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif
//#include <OpenCL/cl.h>

#define WIDTH 600
#define HEIGHT 450

#define TRUE 1
#define FALSE 0

#define SPHERE_NUMBER_MAXI 15
#define CYLINDER_NUMBER_MAXI 15
#define CONE_NUMBER_MAXI 15
#define PLANE_NUMBER_MAXI 15
#define BOX_NUMBER_MAXI 15
#define LIGHT_NUMBER_MAXI 15

typedef struct		s_host_opencl
{
	cl_platform_id		platform_id;
	cl_uint				num_platform;
	cl_device_id		device_id;
	cl_uint				num_device;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*kernel_src;
	cl_program			program;
	cl_kernel			kernel[2];
	cl_int				err; //FOR ERRORi
	size_t				global_work_size;
	cl_uint				kwidth;
	cl_uint				kheight;
}					t_host_opencl;

typedef enum {
	PLANE, SPHERE, CYLINDER, CONE, CUBOID
}						e_type;


typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			lookat;
	cl_float3			dir;
	cl_float3			up;
	cl_float3			right;
}						t_cam;

typedef struct			s_material
{
	int					color_type;
	cl_float4			color;
	float				reflective;
	float				refractive;

}						t_material;

typedef struct			s_sphere
{
	cl_float3			pos;
	float				radius;
	cl_float3			color;
	t_material			m;
}						t_sphere;

typedef struct			s_cylinder
{
	cl_float3			pos;
	float				radius;
	cl_float3			dir;
	int					is_cut;
	cl_float3			cut_axe;
	float				cut_length;
	t_material			m;
}						t_cylinder, t_cone;

typedef struct			s_plane
{
	cl_float3			pos;
	cl_float3			normal;
	t_material			m;
}						t_plane;

typedef struct			s_box
{
	cl_float3			bottom_left;
	cl_float3			top_right;
	t_material			m;
}						t_box;

typedef struct			s_ray
{
	cl_float3			pos;
	cl_float3			dir;
}						t_ray;

typedef struct			s_light
{
	cl_float3			pos;
	int					light_type;
	cl_float3			dir;
	cl_float4			color;
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
 * utils.c
 */
void					err_exit(char *str);
int						error_at_line(char *str, int line, char **scene_tab, int total_line);
char					*kernel_src(char *filename);
int						load_data_from_file(char *file, t_scene *s, t_cam *cam, int display_flag);
/*
 * init_opencl.c
 */
void					init_opencl_context(t_host_opencl *p, int display_host_data);
void					program_failed_info(t_host_opencl p);
void					init_opencl_program(t_host_opencl *p, char *kernel_file_name);
void					compile_kernel(t_host_opencl *p, t_scene *s, t_cam *cam, int display_device_data);
//void					compile_kernel(t_host_opencl *p, t_scene *s, t_cam *cam, cl_uint  width, cl_uint height , cl_float *wordTocam, cl_float *wordTransform);

/*
 * cameara_data.c
 */
int						check_param_number(char *str, int line, int param_number);
//void					set_vector(cl_float3  *pos, char *str, int *i);
//void					set_color(cl_float4  *color, char *str, int *i);
int						parse_camera(t_cam *cam, char **str, int *index, int total_line);
/*
 * light_data.c
 */
int						parse_light(t_scene *s, int *light_num, char **str, int *index, int total_line);

/*
 * plane_data.c
 */
int						check_material_color_param(char *str, int line, int param_number);
void					set_material_color(cl_float4  *color, char *str, int *i);
int						get_plane_material(t_scene *s, char **str, int *plane_num, int *index, int *i, int total_line);
int						parse_plane(t_scene *s, int *plane_num, char **str, int *index, int total_line);
int						error(char *str, int line, int position, char **file_tab, int total_line);
/*
 * sphere_data.c
 */
int						radius_checker(char *str);
int						get_sphere_material(t_scene *s, char **str, int *sphere_num, int *index, int *i, int total_line);
int						parse_sphere(t_scene *s, int *sphere_num, char **str, int *index, int total_line);

/*
 * cylinder_data.c
 */
int						parse_cylinder(t_scene *s, int *cylinder_num, char **str, int *index, int total_line);
int						get_cylinder_material(t_scene *s, char **str, int *cylinder_num, int *index, int *i, int total_line);
/*
 * cone_data.c
 */
int						parse_cone(t_scene *s, int *cone_num, char **str, int *index, int total_line);
int						get_cone_material(t_scene *s, char **str, int *cone_num, int *index, int *i, int total_line);
/*
 * box_data.c
 */
int						parse_box(t_scene *s, int *box_num, char **str, int *index, int total_line);
int						get_box_material(t_scene *s, char **str, int *box_num, int *index, int *i, int total_line);

/*
 * read_scene_file.c
 */
char					**get_scene(char *scene_file, int *num_line);

/*
 * destroyer.c
 */
void					free_scene_string(char **src, int num_line);

/*
 * display_data.c
 */
void					display_scene_data(t_scene *scene, t_cam *cam);
void					display_scene_data_on_device(t_scene *scene, t_cam *cam);

/*
 *ft_atof.c
 */
double					ft_atof(char *nb, int *i);
#endif

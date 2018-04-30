#include "header.h"

t_material				init_material(float r, float g, float b, float w)
{
	t_material			m;

	m.color_type = 0;
	m.color.s[0] = r;
	m.color.s[1] = g;
	m.color.s[2] = b;
	m.color.s[3] = w;
	m.reflectivity = 0;
	m.refractivity = 0;
	return (m);
}

t_sphere				init_sphere(void)
{
	t_sphere			sphere;
	t_material			m;

	sphere.material = init_material(1.0, 0.0, 0.0,0.0);
	sphere.pos.s[0] = 0.0;
	sphere.pos.s[1] = 0.0;
	sphere.pos.s[2] = 10.0;
	sphere.pos.s[3] = 1.0;
	
	sphere.radius = 7.0;
	return (sphere);
}

t_cylinder				init_cylinder(void)
{
	t_cylinder			cylinder;
	t_material			m;

	cylinder.material = init_material(0.0,1.0,0.0,0.0);
	cylinder.pos.s[0] = 0.0;
	cylinder.pos.s[1] = 0.0;
	cylinder.pos.s[2] = -10.0;
	cylinder.pos.s[3] = 1.0;
	
	cylinder.normal.s[0] = 0.0;
	cylinder.normal.s[1] = 1.0;
	cylinder.normal.s[2] = 0.0;
	cylinder.normal.s[3] = 0.0;

	return (cylinder);
}

t_plane				init_plane(void)
{
	t_plane			plane;
	t_material		m;

	plane.material = init_material(0.0,0.0,1.0,0.0);
	plane.pos.s[0] = 0.0;
	plane.pos.s[1] = 0.0;
	plane.pos.s[2] = -40.0;
	plane.pos.s[3] = 1.0;

	plane.normal.s[0] = 0.0;
	plane.normal.s[1] = 0.0;
	plane.normal.s[2] = 1.0;
	plane.normal.s[3] = 0.0;
	return (plane);
}

t_cone				init_cone(void)
{
	t_cone			cone;
	t_material		m;

	cone.material = init_material(1.0,0.5,0.0,0.0);
	cone.pos.s[0] = 0.0;
	cone.pos.s[1] = 10.0;
	cone.pos.s[2] = 0.0;
	cone.pos.s[3] = 1.0;

	cone.normal.s[0] = 0.0;
	cone.normal.s[1] = 1.0;
	cone.normal.s[2] = 0.0;
	cone.normal.s[3] = 0.0;
	return (cone);
}

t_cube				init_cube(void)
{
	t_cube			cube;
	t_material		m;

	cube.material = init_material(1.0,0.0,0.7,0.0);
	cube.pos_min.s[0] = -2.0;
	cube.pos_min.s[1] = 0.0;
	cube.pos_min.s[2] = 0.0;
	cube.pos_min.s[3] = 1.0;

	cube.pos_max.s[0] = 0.0;
	cube.pos_max.s[1] = 30.0;
	cube.pos_max.s[2] = 0.0;
	cube.pos_max.s[3] = 1.0;
	return (cube);
}

t_light				init_light(void)
{
	t_light			light;
	t_material		m;

	light.pos.s[0] = 0.0;
	light.pos.s[1] = 30.0;
	light.pos.s[2] = 0.0;
	light.pos.s[3] = 1.0;

	light.color.s[0] = 1.0;
	light.color.s[1] = 1.0;
	light.color.s[2] = 1.0;
	light.color.s[3] = 1.0;
	return (light);
}

t_camera			init_camera(void)
{
	t_camera		camera;

	camera.pos.s[0] = 0.0;
	camera.pos.s[1] = 0.0;
	camera.pos.s[2] = -1.0;
	camera.pos.s[3] = 1.0;

	camera.lookat.s[0] = 0.0;
	camera.lookat.s[1] = 0.0;
	camera.lookat.s[2] = 0.0;
	camera.lookat.s[3] = 1.0;
	return (camera);
}

t_scene				init_scene(void)
{
	t_scene			scene;

	scene.sphere = init_sphere();
	scene.num_sphere = 1;
	scene.cylinder = init_cylinder();
	scene.num_cylinder = 0;
	scene.plane = init_plane();
	scene.num_plane = 1;
	scene.cone = init_cone();
	scene.num_cone = 0;
	scene.cube = init_cube();
	scene.num_cube = 0;
	scene.light = init_light();
	scene.num_light = 1;
	scene.material = init_material(1.0,1.0,1.0,1.0);
	return (scene);


}

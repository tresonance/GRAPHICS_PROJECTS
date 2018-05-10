#include "host.h"

int				main(int argc, char **argv)
{
	t_host_opencl p;
	
	t_scene		scene;
	t_cam		cam;
	int			display_host_data = 0;
	int			display_device_data = 0;
	cl_uint			width = (cl_uint)WIDTH;
	cl_uint		height= (cl_uint)HEIGHT;

	if(argc == 3)
	{
		float camt[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		float wort[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		
		load_data_from_file(argv[1], &scene, &cam, display_host_data);
		
		init_opencl_context(&p, 0);
		init_opencl_program(&p, argv[2]);
		//compile_kernel(&p, &scene, &cam, width, height, camt,  wort);
		compile_kernel(&p, &scene, &cam, display_device_data);

	}
	return (0);
}

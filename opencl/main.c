#include "header.h"

int				main()
{
	t_opencl p;

	init_opencl(&p);
	compile_opencl_program(&p);
	release_opencl(&p);
	return(0);

	return (0);
}

#include "host.h"

void				free_scene_string(char **src, int num_line)
{
	int				i;

	if(src && *src)
	{
		i = -1;
		while(++i < num_line)
		{
			if(src[i])
				ft_strdel(&src[i]);
		}
		ft_memdel((void **)src);
	}
}

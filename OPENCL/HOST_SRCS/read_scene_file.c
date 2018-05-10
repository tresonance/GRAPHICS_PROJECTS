#include "host.h"

static int					number_line(char *scene_file)
{
	int				fd;
	char			*line;
	int				line_num;

	if(0 > (fd = open(scene_file, O_RDONLY)))
		err_exit("Could not open scne file");
	line_num = 0;
	while(get_next_line(fd, &line) > 0)
	{
		line_num++;
		ft_strdel(&line);
	}
	close(fd);
	return (line_num);
}


char				**get_scene(char *scene_file, int *num_line)
{
	char			**src;
	int				fd;
	char			*line;
	int				i;

	*num_line = number_line(scene_file);
	if(NULL == (src = (char**)malloc((*num_line) * sizeof(char*))))
		err_exit("Unable to allocate scene string");
	if(0 > (fd = open(scene_file, O_RDONLY)))
		err_exit("Could not open scne file");
	i = 0;
	while(get_next_line(fd, &line) > 0)
	{
		src[i++] = line;
	}
	close(fd);
	return (src);
}



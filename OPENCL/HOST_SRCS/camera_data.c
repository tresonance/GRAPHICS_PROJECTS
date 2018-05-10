#include "host.h"

int					check_param_number(char *str, int line, int param_number)
{
	int				i;
	int				num_space;
	char			*trim;

	i = -1;
	num_space = 0;
	while(str[++i])
	{
		if(!ft_isdigit(str[i]))
		{
			if(str[i] == ' ')
				num_space++;
			else if(str[i] != '-' && str[i] != '.')
				return(1);
		}
	}
	return (!(num_space + 1  == param_number));
}

/*void				set_vector(cl_float3 *pos, char *str, int *i)
{
	pos->x = (cl_float)ft_atof(str, i);
	pos->y = (cl_float)ft_atof(str, i);
	pos->z = (cl_float)ft_atof(str, i);
}*/

/*void				set_color(cl_float3 *color, char *str, int *i)
{
	color->s[0] = (float)ft_atof(str, i);
	color->s[1] = (float)ft_atof(str, i);
	color->s[2] = (float)ft_atof(str, i);
	color->s[3] = (float)ft_atof(str, i);
}*/

int					parse_camera(t_cam *cam, char **str, int *index, int total_line)
{
	int				i;

	if(0 == ft_strcmp("camera{", str[*index]))
	{
		if(0 == ft_strncmp("pos:", str[++(*index)], 4))
		{
			i = 5;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				cam->pos.x = (cl_float)ft_atof(str[*index], &i);
				cam->pos.y = (cl_float)ft_atof(str[*index], &i);
				cam->pos.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&cam->pos, str[*index], &i);
			}
			else
				return (error_at_line("Error line:", *index, str,total_line));
		}
		else
			return(error_at_line("Error line:", *index, str,total_line));
		if(0 == ft_strncmp("lookat:", str[++(*index)], 7))
		{
			i = 8;
			if(0 == check_param_number(&str[*index][i], *index, 3))
			{
				cam->lookat.x = (cl_float)ft_atof(str[*index], &i);
				cam->lookat.y = (cl_float)ft_atof(str[*index], &i);
				cam->lookat.z = (cl_float)ft_atof(str[*index], &i);
				//set_vector(&cam->lookat, str[*index], &i);
			}
			else
				return (error_at_line("Error line:", *index, str,total_line));
		}
		else
			return(error_at_line("Error line:", *index, str, total_line));
		if(0 == ft_strcmp("}", str[++(*index)]))
		{
			*index += 2;
			cam->up.x = 0.0f;
			cam->up.y = 1.0f;
			cam->up.z = 0.0f;
			return (0);
		}
		return (1);
	}
	return (error_at_line("Error line:", *index, str, total_line));
}

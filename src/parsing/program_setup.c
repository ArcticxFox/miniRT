#include "minirt.h"

int	load_scene_info(char *filename, t_data *minirt)
{
	int		fd;
	char	*res;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	res = get_next_line(fd);
	printf("%s\n", res);
	while (res)
	{
		if (res[0] == '\0')
		{
			free(res);
			res = get_next_line(fd);
		}
		else if (parse_line(res, minirt))
		{
			free(res);
			res = get_next_line(fd);
			if (res)
				printf("%s\n", res);
		}
	}
	close(fd);
	return (0);
}

int	file_name_check(char *filename)
{
	char	*str;
	int		len;

	if (ft_strlen(filename) <= ft_strlen(".rt"))
		return (1);
	str = ft_strchr(filename, '.');
	if (!str)
		return (1);
	len = ft_strlen(str);
	if (ft_strncmp(str, ".rt", len) != 0)
		return (1);
	return (0);
}

int	input_parsing(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (file_name_check(av[1]))
		return (1);
	return (0);
}

void	print_everything(t_data *minirt)
{
	char c;

	c = 0;
	printf("RATIO = %f\n", minirt->ambient_light->ratio);
	for (int i = 0; i != 3; i++){
		switch (i)
		{
		case 0:
			c = 'R';
			break;
		case 1:
			c = 'G';
			break;
		case 2:
			c = 'B';
			break;
		default:
			break;
		}
		printf("%c = %d\n", c, minirt->ambient_light->RGB[i]);
	}
	c = 0;
	for (int i = 0; i != 3; i++){
		switch (i)
		{
		case 0:
			c = 'x';
			break;
		case 1:
			c = 'y';
			break;
		case 2:
			c = 'z';
			break;
		default:
			break;
		}
		printf("viewpoint %c = %f\n", c, minirt->camera->viewpoint[i]);
	}
	c = 0;
	for (int i = 0; i != 3; i++){
		switch (i)
		{
		case 0:
			c = '3';
			break;
		case 1:
			c = 'd';
			break;
		case 2:
			c = 'n';
			break;
		default:
			break;
		}
		printf("NOV %c = %f\n", c, minirt->camera->threed_NOV[i]);
	}
	return ;
}

int	program_setup(int ac, char **av, t_data *minirt)
{
	int	err_num;

	minirt = ft_calloc(1, sizeof(t_data));
	if (!minirt)
		return (1);
	err_num = input_parsing(ac, av);
	if (err_num)
	{
		return (err_num);
	}
	err_num = load_scene_info(av[1], minirt);
	if (err_num)
	{
		return (err_num);
	}
	print_everything(minirt);
	return (0);
}

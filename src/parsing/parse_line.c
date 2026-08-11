#include "minirt.h"

//checks that the input is valid for the given identifier. if no identifier, throws an error
static int	check_type(char **split, int *marker)
{
	// int	i;
	int	type;

	*marker = 0;
	while (split[*marker] && split[*marker][0] == '\0')
		(*marker)++;
	if (!check_alpha(split[*marker]))
		return (0);
	type = find_input_type(split[*marker]);
	*marker += 1;
	return (type);
}

//turns all whitespace into spaces to use ft_split
static void	norm_whitespace(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] >= 7 && line[i] <= 13)
			line[i] = 32;
		i++;
	}
	return ;
}

static int parse_by_type(char **split, t_data *minirt, int	type)
{
	int	res;

	res = 0;
	if (type == 10)
		res = amb_parse(split, minirt);
	if (type == 20)
		res = cam_parse(split, minirt);
	if (type == 30)
		res = amb_parse(split, minirt);
	if (type == 40)
		res = amb_parse(split, minirt);
	if (type == 50)
		res = amb_parse(split, minirt);
	if (type == 60)
		res = amb_parse(split, minirt);
	if (res)
	{
		printf("fuck\n");
		return (res);
	}
	return (res);
}

//parses the line
int parse_line(char *line, t_data *minirt)
{
	char	**split;
	int		type;
	int		marker;

	if (!line)
		return (1);
	norm_whitespace(line);
	split = ft_split(line, ' ');
	if (!split)
		return (1);
	int j = 0;
	while (split[j])
	{
		printf("%s\n", split[j]);
		j++;
	}
	type = check_type(split, &marker);
	if (!type)
	{
		ft_free_array(split);
		return (1);
	}
	parse_by_type(split + marker, minirt, type);
	ft_free_array(split);
	return (1);
}

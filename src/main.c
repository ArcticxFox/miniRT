#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	minirt;
	// (void) ac;
	// (void) av;
	// char *in = "-50.0,,10,A";

	// int len = ft_strlen(in);
	// if (in[0] == ',' || in[len - 1] == ',')
	// {
	// 	printf("idea works\n");
	// 	return (0);
	// }
	// char **out = ft_split(in, ',');
	// int i = 0;
	// while (out[i])
	// 	printf("%s\n", out[i++]);
	// printf("%d\n", i);
	// ft_free_array(out);
	// return (0);
	if (program_setup(ac, av, &minirt))
	{
		printf("shitfucked\n");
		return (1);
	}
	printf("%s is a good name!\n", av[1]);
	return (0);
}

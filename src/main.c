#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	minirt;

	if (program_setup(ac, av, &minirt))
	{
		printf("shitfucked\n");
		return (1);
	}
	printf("%s is a good name!\n", av[1]);
	return (0);
}

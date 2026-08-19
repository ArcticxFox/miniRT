#include "minirt.h"

void	free_all(t_data *minirt)
{
	if (minirt->cylinder)
		free(minirt->cylinder);
	if (minirt->sphere)
		free(minirt->sphere);
	if (minirt->plane)
		free(minirt->plane);
}

int	main(int ac, char **av)
{
	t_data	minirt;

	if (program_setup(ac, av, &minirt))
	{
		printf("shitfucked\n");
		return (1);
	}
	printf("%s is a good name!\n", av[1]);
	free_all(&minirt);
	return (0);
}

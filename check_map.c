
#define ERROR 1
#define SUCCESS 0
//pourrait stocker toutes les variables a check aussi...contourner la norminette
typedef struct	map
{
	char	**map;
	int		map_nb_lines;
	char	player_orientation;
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;

} t_map;


// Proto
int	check_map_ext(char *argv);
//----------------------------------------------------------------------------------------

// check l'extension .cub
int		check_map_ext(char *argv)
{
	int	i;

	i = 0;
	while (*argv)
		i++;
	if ((argv[i - 1] == 'b') && (argv[i - 2] == 'u') && (argv[i - 3] == 'c'))
		return (SUCCESS);
	else
		return (ERROR);
}

//compte le nombre de ligne, pour savoir la bonne taille de tableau->map.cub
//ignore les lignes vides
int	map_count_line(char *argv)
{
	int		fd;
	int		count;
	char	*gnl_return;
	char	*tmp;

	count = 0;
	fd = open(argv, O_RDONLY);
	gnl_return = get_next_line(fd);
	while (gnl_return)
	{
		tmp = gnl_return;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0') // Vérifie si la ligne n'est pas juste un retour à la ligne ou vide
			count++;
		free(gnl_return);
		gnl_return = get_next_line(fd);
		
	}
	if (count < 3 || gnl_return == "\0")
	{
		error_handler("empty map", 1);
	}
	close (fd);
	return (count);
}

// récupère la map et la met dans un tableau
char	**map_harvest(char *map_sample, int line_map)
{
	int		fd;
	char	**tableau_stock;
	char	*line;
	int		i;

	i = 0;
	fd = open(map_sample, O_RDONLY);
	tableau_stock = malloc(sizeof(char *) * (line_map + 1));
	if (!tableau_stock)
		return (NULL);
	while (i < line_map)
	{
		line = get_next_line(fd);
		tmp = line;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0')
			tableau_stock[i] = ft_strdup(line);
		free (line);
		i++;
	}
	close (fd);
	return (tableau_stock);
}


// récupère le contenu de la map et rempli tableau
void	init_map_cub(char *argv, t_map *map)
{
	map->map_nb_lines = map_count_line(argv);
	mlx->map = map_harvest(argv, map->map_nb_lines);
	
}


/*
big mama
note:
- Appel de fonction en main?
- nb: init "t_map" qq part
- appel de fonction:
	if (!parsing_map(argc,argv)
		return(exit_game)

But:
- stocke la map->struct
- check extension
- présence d'une map 
*/

int	parsing_map(int argc, char **argv, t_map *map)
{
	
	int check_extension;

	check_extension = check_map_ext(argv[1]); //au lieu d'une foret de if, stocke dans une variable
	if (argc != 2)
		return(ERROR);
	init_map_cub(argv[1]);
	
	if (check_extension &&)
		return(ERROR);
}
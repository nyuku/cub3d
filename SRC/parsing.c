#include "parsing.h"
# include "cube.h"
# include "struct.h"


// Proto
void	check_map_ext(char *argv);
int		set_texture(char *str, t_map *map);
int		map_count_line(char *argv);
char	**map_harvest(char *map_sample, int line_map);
void	init_map_cub(char *argv, t_map *map);
char	*skip_space(char *str);
void	check_texture(t_map *map);
void	free_split(char **split_str);
int		*set_color(char *str, t_map *map, t_color *up_or_down, char *letter);
int		parsing_cub(int argc, char **argv, t_map *map);
int		set_texture(char *str, t_map *map);
//----------------------------------------------------------------------------------------

// check l'extension .cub
void		check_map_ext(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if ((argv[i - 1] != 'b') && (argv[i - 2] != 'u') && (argv[i - 3] != 'c'))
		error_handler("Error: wrong files extensions", 1);
}

//compte le nombre de ligne, pour savoir la bonne taille de tableau->map.cub
//ignore les lignes vides
//test: is okay
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
		char *tmp = gnl_return;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0') // Vérifie si la ligne n'est pas juste un retour à la ligne ou vide
			count++;
		free(gnl_return);
		gnl_return = get_next_line(fd);
		
	}
	if (count == 0)// flagada a verirfie
	{
		error_handler("empty map", 1);
	}
	close (fd);
	printf("valeur de ligne: %d\n", count);
	return (count);
}

// récupère la map et la met dans un tableau
//test: is okay
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
	line = get_next_line(fd);
	while (i < line_map)
	{
		char *tmp = line;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0')
		{
			tableau_stock[i] = ft_strdup(line);
			i++;
		}
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (tableau_stock);
}


// récupère le contenu de la map et rempli tableau
void	init_map_cub(char *argv, t_map *map)
{
	map->map_nb_lines = map_count_line(argv);
	map->map = map_harvest(argv, map->map_nb_lines);
//	int i = 0;
//	while (map->map && i < map->map_nb_lines)
//	{
//		printf("%s\n", map->map[i]);
//		i++;
//	}
	
}


char	*skip_space(char *str)
{
    while (*str == ' ')
        str++;
    return (str);
}

// lis la map receuilli et check si les elements de textures sont correct


void check_texture(t_map *map)
{
	int	e;
	int	count;

	e = 0;
	count = 0;
	char **map_tab = map->map;
	while( map_tab && (count < 6))
	{
		
		if (!set_texture(map_tab[e], map))
			count++;
		else
			error_handler("wrong texture\n",1);
		e++;
	}
}
//attaque tout de suite apres les espaces... appelé pour analyser si , on sait deja quel lettre c'est
//F ....220,100,0
//on passe d'une strin "200,100,0" a remplir dans une structure
// na faut convertir en int... pour verifier la valeur
//split puis atoi
void free_split(char **split_str) 
{ 
	int	j;
	
	j = 0;
    while (split_str[j]) 
	{
        free(split_str[j]);
        j++;
    }
    free(split_str);
	error_handler("Error: Invalid color format\n",1);
}

//recupere la str de couleur, converti en int, vérifie s que chiffre et dans bon scope
//verifie bien 3 chiffre
//remet dans un int * le contenu
int	*set_color(char *str, t_map *map, t_color *up_or_down, char *letter)
{
	int	i;
	char **split_str;
	int rgb[3];
	
	i = 0;
	str = skip_space(str);
	split_str = ft_split(str, ",");
	//checker si que int
	while (split_str[i] != NULL)
		i++;
	if (i != 3) 
	{
		free_split(split_str);
		return;
	}

	while (split_str[i] != NULL && i < 3) 
	{
        if (ft_isdigit(split_str[i])) 
		{
            free_split(split_str);
			break;
		}
		rgb[i] = ft_atoi(split_str[i]);
		if (rgb[i] < 0 || rgb[i] > 255) 
		{
            free_split(split_str);
            break;
        }
		i++;
	}
	return (rgb);
}

// skip potentielle espace avant indice, puis re skip pour avoir le path
// check que ce soit que ce qu'on cherche
// test: is okay
//ajouter traitement pour le sol et le plafond
int	set_texture(char *str, t_map *map)
{
	str = skip_space(str);
	if (ft_strncmp(str, "NO ", 3) == 0)// avant "NO " 3
	{
		map->texture_north = ft_strdup(skip_space(str + 3));
		printf("its a NO\n");
	}
    else if (ft_strncmp(str, "SO ", 3) == 0)
	{
		map->texture_south = ft_strdup(skip_space(str + 3));
		printf("its a SO\n");
	}
    else if (ft_strncmp(str, "WE ", 3) == 0)
	{
		map->texture_west = ft_strdup(skip_space(str + 3));
		printf("its a WE\n");
	}
    else if (ft_strncmp(str, "EA ", 3) == 0)
	{
		map->texture_east = ft_strdup(skip_space(str + 3));
		printf("its a EA\n");
	}
    else if (ft_strncmp(str, "F ", 2) == 0)
	{
//		map->floor_color = ft_strdup(skip_space(str + 2));
		//on a la string skip_space(str + 2)
		set_color(str, map, "F");
		printf("its a F\n");
	}
    else if (ft_strncmp(str, "C ", 2) == 0)
	{
		//map->ceiling_color = ft_strdup(skip_space(str + 2));
		//on a la string skip_space(str + 2)
		set_color(str, map, "C");
		printf("its a C\n");
	}
	else
	{
		return(ERROR);
	}
	return(SUCCESS);

}

//int check_map(char **map)
//{
//	printf("plop\n");
//}

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
- présence des élements de structures
- vérifiér viabilité
!
*/
int	parsing_cub(int argc, char **argv, t_map *map)
{
	if (argc != 2)
		error_handler("Pas le bon nbre d'arguments\n",1);
	check_map_ext(argv[1]);
	init_map_cub(argv[1], map);
//	//free map si soucis
	check_texture(map);
	//check_map(map->map);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_map *map = malloc(sizeof(t_map));
    if (map == NULL)
        return (printf("beurk\n"));

	printf("plop\n");
	parsing_cub(argc,argv, map);

	printf("Voici le path de North: %s\n", map->texture_north);
	printf("Voici le path de South: %s\n", map->texture_south);
	printf("Voici le path de West: %s\n", map->texture_west);
	printf("Voici le path de East: %s\n", map->texture_east);
//	printf("Voici les coordonnés de Floor %s\n", map->floor_color);
//	printf("Voici les coordonnés de Ceiling %s\n", map->ceiling_color);

	return (0);
}
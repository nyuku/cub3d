
#include<stdio.h>
#define ERROR 1
#define SUCCESS 0

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
# define BUFFER_SIZE 10

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((s1[i] && s2[i]) && (s1[i] == s2[i]))
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int     ft_strlen(char *str)
{
    int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char    *ft_strjoin(char *remains, char *buffer)
{
    char *array;
    unsigned int size;
    int i;
    int j;

    if (!remains && !buffer)
        return (NULL);
    size = ft_strlen(remains) + ft_strlen(buffer);
    if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
        return (NULL);
    i = 0;
    j = 0;
    if (remains)
    {
        while (remains[i])
            array[j++] = remains[i++];
        i = 0;
    }
    while (buffer[i])
        array[j++] = buffer[i++];
    array[size] = '\0';
    free((void *)remains);
    return (array);
}

char    *push_line(char *remains)
{
    int i;
    char *array;

    i = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (remains[i] == '\n')
		i++;
    if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (remains[i] && remains[i] != '\n')
    {
        array[i] = remains[i];
        i++;
    }
	if (remains[i] == '\n')
	{
		array[i] = '\n';
		array[i + 1] = '\0';
		return (array);
	}
    array[i] = '\0';
    return (array);
}

char    *cut_next_line(char *remains)
{
    int i;
    int j;
    char *array;

    i = 0;
    j = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (!remains[i])
    {
        free(remains);
        return (NULL);
    }
    if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains) - i + 1))))
        return (NULL);
    i++;
    while (remains[i])
    {
        array[j] = remains[i];
        i++;
        j++;
    }
    array[j] = '\0';
    free(remains);
    return (array);
}

bool ft_strchr(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] == '\n')
			return (true);
		i += 1;
	}
	return (false);
}

char     *get_next_line(int fd)
{
    if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    char buffer[BUFFER_SIZE + 1];
    buffer[0] = '\0';
    static char *remains;
	char *line;
    int count;

    count = 1;
    while (!ft_strchr(buffer) && count != 0)
    {
        if ((count = read(fd, buffer, BUFFER_SIZE)) == (-1))
            return (NULL);
        buffer[count] = '\0';
        remains = ft_strjoin(remains, buffer);
    }
    line = push_line(remains);
    remains = cut_next_line(remains);
	if (line[0] == '\0') 
    {
        free(line);
        return (NULL);
    }
    return (line);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		i;
	char	*str;

	i = 0;
	str = (char *) src;
	dup = (char *) malloc(sizeof (char) * (ft_strlen(str) + 1));
	if (!dup)
		return (0);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
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
	char 	*floor_color;
	char 	*ceiling_color;

} t_map;

void	error_handler(char *txt, int code)
{
	printf("%s\n", txt);
	exit(code);
}
// Proto
void	check_map_ext(char *argv);
int	check_element(char *str, t_map *map);
//----------------------------------------------------------------------------------------

// check l'extension .cub
void		check_map_ext(char *argv)
{
	int	i;

	i = 0;
	while (*argv)
		i++;
	if ((argv[i - 1] == 'b') && (argv[i - 2] == 'u') && (argv[i - 3] == 'c'))
		printf("bonne extension!\n");//return (SUCCESS);
	else
		error_handler("Error: wrong files extensions", 1);
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
		char *tmp = gnl_return;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp != '\n' && *tmp != '\0') // Vérifie si la ligne n'est pas juste un retour à la ligne ou vide
			count++;
		free(gnl_return);
		gnl_return = get_next_line(fd);
		
	}
	if (gnl_return == NULL)// flagada a verirfie
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
		char *tmp = line;
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
	map->map = map_harvest(argv, map->map_nb_lines);
	
}

// int skip_space(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while(str[i] == " ")
// 		i++;
// 	return (i);
// }

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
	while( map_tab && (count <= 6))
	{
		
		if (!check_element(map_tab[e], map))
			count++;
		else
			error_handler("wrong texture\n",1);
		e++;
	}
}


// skip potentielle espace avant indice, puis re skip pour avoir le path
// check que ce soit que ce qu'on cherche
int	check_element(char *str, t_map *map)
{
	str = skip_space(str); 
	if (ft_strncmp(str, "NO ", 3) == 0)
        map->texture_north = ft_strdup(skip_space(str + 3));
    else if (ft_strncmp(str, "SO ", 3) == 0)
        map->texture_south = ft_strdup(skip_space(str + 3));
    else if (ft_strncmp(str, "WE ", 3) == 0)
        map->texture_west = ft_strdup(skip_space(str + 3));
    else if (ft_strncmp(str, "EA ", 3) == 0)
        map->texture_east = ft_strdup(skip_space(str + 3));
    else if (ft_strncmp(str, "F ", 2) == 0)
        map->floor_color = ft_strdup(skip_space(str + 2));
    else if (ft_strncmp(str, "C ", 2) == 0)
        map->ceiling_color = ft_strdup(skip_space(str + 2));
	else
		return(ERROR);
	return (SUCCESS);
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
!
*/

int	parsing_map(int argc, char **argv, t_map *map)
{
	
	check_map_ext(argv[1]);
	if (argc != 2)
		return(ERROR);
	init_map_cub(argv[1], map);
	//free map si soucis
	check_texture(map);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	t_map *map;
	parsing_map(argc,argv, map);

	printf("Voici le path de North: %s\n", map->texture_north);
	printf("Voici le path de South: %s\n", map->texture_south);
	printf("Voici le path de West: %s\n", map->texture_west);
	printf("Voici le path de East: %s\n", map->texture_east);

	return (0);
}
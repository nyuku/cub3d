
#include "parsing.h"

int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
					i++;
			word++;
		}
		while (s[i] == c)
			i++;
	}
	return (word);
}

void	ft_free(char **tab, int j)
{
	if (tab[j] == NULL)
	{
		while (j-- > 0)
			free(tab[j]);
		free(tab);
		tab = NULL;
		return ;
	}
}

void	ft_second_floor(char const *s, char c, char **tab, int i)
{
	int	j;
	int	k;
	int	count;

	j = 0;
	while (j < (ft_word_count(s, c)))
	{
		count = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
		tab[j] = malloc(sizeof(char) * (count + 1));
		ft_free(tab, j);
		i -= count;
		k = 0;
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
	tab[j][k] = '\0';
	j++;
	}
	tab[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab[ft_word_count(s, c)] = 0;
	ft_second_floor(s, c, tab, i);
	return (tab);
}

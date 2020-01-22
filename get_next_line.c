/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:57:47 by antmarti          #+#    #+#             */
/*   Updated: 2020/01/22 19:45:53 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_strlen(const char *s)
{
	int len;

	len = 0;
	if (!s[len])
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2 || !(str = malloc((sizeof(char) *
	(ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*str;
	int		i;

	if (!s || !(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	if ((start >= (ft_strlen(s))))
		return (ft_strdup(""));
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (((char *)s) + i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return (((char *)s) + i);
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		*buffer;
	static char	*file;
	char		*acc;
	int			i;
	char		*temp;

	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))) || line == NULL)
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (file == NULL)
			file = ft_strdup(buffer);
		else
		{
			acc = ft_strjoin(file, buffer);
			free(file);
			file = acc;
		}
		if (ft_strchr(file, '\n'))
			break ;
	}
	free(buffer);
	i = 0;
	if (ret == 0 && !file)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (ret == -1)
		return (-1);
	else
	{
		while (file[i] && file[i] != '\n')
		i++;
		if (file[i] == '\n')
		{
			*line = ft_substr(file, 0, i);
			temp = ft_strdup(&((file)[i + 1]));
			free(file);
			file = temp;
		}
		else
		{
			*line = ft_strdup(file);
			free(file);
			file = 0;
			return (0);
		}
	}
	return (1);
}

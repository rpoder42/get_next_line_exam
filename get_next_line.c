#define BUFFER_SIZE 3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while(str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*dst;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 && !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1 && s1[j])
	{
		dst[i] = s1[j];
		i++;
		j++;
	}
	if (s1)
		free(s1);
	while (s2 && s2[k])
	{
		dst[i] = s2[k];
		i++;
		k++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*trim_line(char *str)
{
	int		len;
	int		i;
	char	*dst;

	len = 0;
	i = 0;
	while(str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*trim_rest(char *str)
{
	int		len;
	int		i;
	char	*dst;

	len = 0;
	i = 0;
	while(str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	dst = malloc(sizeof(char) * (ft_strlen(str + len) + 1));
	if (!dst)
		return (NULL);
	while (str[len])
	{
		dst[i] = str[len];
		i++;
		len++;
	}
	dst[i] = '\0';
	return (dst);
}

bool	ft_strrchr(char *str, char c)
{
	int	i;

	i = 0;
	while(str && str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*read_line(int fd, char *rest)
{
	char	*buf;
	char	*dst;
	int		ret;

	ret = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (ret > 0 && !ft_strrchr(rest, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
		{
			if (rest)
				free(rest);
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		rest = ft_strjoin(rest, buf);
		if (!rest)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffed_line;
	static char	*rest = NULL;

	if (fd < 0)
		return (NULL);
	buffed_line = read_line(fd, rest);
	if (!buffed_line)
	{
		free(buffed_line);
		return (NULL);
	}
	line = trim_line(buffed_line);
	if (!line)
		return (NULL);
	rest = trim_rest(buffed_line);
	if (!rest)
		return (NULL);
	free(buffed_line);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 05:06:20 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/02 05:07:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"


char    *line_content(char *line)
{
	int idx;

	idx = 2;

	while (line[++idx])
	{
		if (!ft_isspace(line[idx]))
			break;
	}
	return (ft_substr(line, idx, ft_strlen(line) - idx));
}

int read_file(char *file, t_cube_data *cube_data)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Can't read the file\n"), 1);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
//		ft_printf("%s", line);
		if (line[0] == '\n' || line[0] == '\0')
			continue;
		parse_line(line, cube_data);
		free(line);
	}
//	free(line);
	close(fd);
	return (0);
}

void replace_tabs_with_spaces(char ***map)
{
	int idx;
	int idx2;
	char *new_line;
	char *tmp;
	char *to_append;

	idx = -1;
	while ((*map)[++idx])
	{
		new_line = ft_strdup("");
		idx2 = -1;
		while ((*map)[idx][++idx2])
		{
			if ((*map)[idx][idx2] == '\t')
				to_append = ft_strdup("    ");
			else
				to_append = ft_sprintf("%c", (*map)[idx][idx2]);
			tmp = ft_strdup(new_line);
			free(new_line);
			new_line = ft_sprintf("%s%s", tmp, to_append);
			free(tmp);
			free(to_append);
		}
		free((*map)[idx]);
		(*map)[idx] = new_line;
	}
}


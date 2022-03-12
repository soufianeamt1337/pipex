/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_au.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:57:57 by samajat           #+#    #+#             */
/*   Updated: 2022/03/12 18:32:25 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void close_all (int a, int fd[a][2])
{
    close (fd[0][0]);
	close (fd[0][1]);
	close (fd[1][0]);
	close (fd[1][1]);
	close (fd[2][0]);
	close (fd[2][1]);
}

char *extract_paths (char **env)
{
	int		i;
	char	*line;
	int		path_length;

	i = 0;
	while (env[i])
	{
		line = ft_substr (env[i], 0, 4);
		path_length = ft_strlen (env[i]);
		if (!ft_memcmp (line, "PATH", 4))
		{
			free (line);
			return (ft_substr(env[i], 5, path_length));
		}
		free (line);
		i++;
	}
	return (NULL);
}

void generate_paths(t_data *data, char **env)
{
	data->path = extract_paths (env);
	data->all_paths = ft_split (data->path, ':');
}


void	exec_cmd (t_data *data, char **env)
{
	int	i;

	i = 0;
	while (data->all_paths[i])
	{
		data->all_paths[i] = ft_strjoin (data->all_paths[i], "/");
		data->mypath = ft_strjoin (data->all_paths[i], data->cmd[0]);
		execve (data->mypath, data->cmd , env);
		i++;
	}
}

int main (int argc, char **argv, char **env)
{
	t_data  data;
	int fd[3][2];
	int i;
	int	l;

	l = -1;
	i = -1;
	while (++i < 3)
		if (pipe(fd[i]) < 0)
				return (2);
	data.id = fork();
	if (!data.id)
	{
		dup2 (fd[0][1], 1);
        close_all (3 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[1], ' ');
		exec_cmd (&data, env);
	}
	data.id = fork();
	if (!data.id)
	{
		dup2 (fd[0][0], 0);
		dup2 (fd[1][1], 1);
        close_all (3 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[2], ' ');
		exec_cmd (&data, env);
	}
	data.id = fork();
	if (!data.id)
	{
		dup2 (fd[1][0], 0);
        dup2 (fd[2][1], 1);
        close_all (3 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[3], ' ');
		exec_cmd (&data, env);
	}
	data.id = fork();
	if (!data.id)
	{
		dup2 (fd[2][0], 0);
        close_all (3 , fd);
		generate_paths(&data, env);
		data.cmd = ft_split (argv[4], ' ');
		exec_cmd (&data, env);
	}
	wait (NULL);
}
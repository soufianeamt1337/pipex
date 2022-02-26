/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:29:48 by samajat           #+#    #+#             */
/*   Updated: 2022/02/26 22:38:49 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../includes/pipex.h"
//int execve(const char *path, char *const argv[], char *envp[]);


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

int main(int argc, char **argv, char **env) {
	int id;
	int	fd[2];

	// if (pipe(fd) < 0)
	// 	return (2);
	id = fork();
	if (id < 0)
		return (2);
	if (id == 0)
	{
		//child process
		int	i;
		char *line;
		char **paths;
		char *mypath;
		char **cmd;
		int file = open (argv[1], O_CREAT | O_RDWR, 0777);
		dup2 (file, 1);
		line = extract_paths (env);
		paths = ft_split (line, ':');
		cmd = ft_split (argv[2], ' ');
		while (paths[i])
		{
			paths[i] = ft_strjoin (paths[i], "/");
			mypath = ft_strjoin (paths[i], cmd[0]);
			execve (mypath, cmd , env);
			i++;
		}
	}
	else 
	{
		//parent process
		wait (NULL);
		printf ("The cmd execution is successfull.");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:46:05 by samajat           #+#    #+#             */
/*   Updated: 2022/03/25 15:28:37 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Headers
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../srcs/get_next_line/get_next_line.h"

//data
typedef struct s_data
{
	int		id;
	int		**pipes;
	char	*path;
	char	**all_paths;
	char	*mypath;
	char	**cmd;
	int		last_pipe;
	int		pipes_nbr;
	int		infile;
	int		outfile;
	char	**argv;
	char	**env;
	int		argc;
	int		is_here_doc;
	int		pipe_arr_included;
}	t_data;

//utils
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	t_free(int	**pipes, int i);
int		generate_pipes(t_data *data);
int		**allocate_arr(int argc);
void	print_error(char *message);

//main functions
char	*extract_paths(char **env);
void	generate_paths(t_data *data, char **env);
void	exec_cmd(t_data *data, char *command);
void	close_all(t_data *data);
int		check_syntax(t_data *data);
void	collect_data(t_data *data, int argc, char **argv, char **env);
void	write_addresses(t_data *data);
void	free_all_paths(t_data *data);
void	free_arr(char **arr);
void	here_doc(t_data *data);
void	add_slash_to_paths(t_data *data);
void	free_pipe_arr(t_data *data, int j);
void	free_all_data(t_data *data, int pipe_incuded);
int		add_here_doc(t_data *data);

#endif
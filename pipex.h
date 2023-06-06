/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:27:47 by gcapa-pe          #+#    #+#             */
/*   Updated: 2023/05/25 14:06:21 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	char	**paths;
	char	*command;
}			t_pipex;

void		ft_pipex(char *argv[], char *envp[], t_pipex *pipex);
void		command_1(char *argv[], char *envp[], t_pipex *pipex);
void		command_2(char *argv[], char *envp[], t_pipex *pipex);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(char *s);
char		*triple_strjoin(char *s1, char *s2, char *s3);
char		*path_and_check(char *envp[], char *command, t_pipex *pipex);
char		**ft_split(char *str, char ch);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_second_child(char *argv[], char *envp[], t_pipex *pipex);
void		ft_free_all(char **path);

#endif
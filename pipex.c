/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:03:13 by gcapa-pe          #+#    #+#             */
/*   Updated: 2023/05/24 17:33:53 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_1(char *argv[], char *envp[], t_pipex *pipex)
{
	char	*full_path;
	char	**command_split;

	command_split = ft_split(argv[2], ' ');
	full_path = path_and_check(envp, command_split[0], pipex);
	if (full_path == NULL)
	{	
		close(pipex->infile);
		close(pipex->outfile);
		perror("Invalid command -> 1");
		exit(1);
	}
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->infile);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	execve(full_path, command_split, envp);
	close(pipex->infile);
	close(pipex->outfile);
	ft_free_all(command_split);
	perror("Execution error on first command ");
	exit(1);
}

void	command_2(char *argv[], char *envp[], t_pipex *pipex)
{
	char	*full_path;
	char	**command_split;

	command_split = ft_split(argv[3], ' ');
	full_path = path_and_check(envp, command_split[0], pipex);
	if (full_path == NULL)
	{	
		close(pipex->infile);
		close(pipex->outfile);
		perror("Invalid command -> 2");
		exit(1);
	}
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close(pipex->pipe_fd[1]);
	execve(full_path, command_split, envp);
	close(pipex->infile);
	close(pipex->outfile);
	ft_free_all(command_split);
	perror("Execution error on second command");
	exit(1);
}

void	ft_pipex(char *argv[], char *envp[], t_pipex *pipex)
{
	int	child1_pid;

	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("Error piping process");
		exit(1);
	}
	child1_pid = fork();
	if (child1_pid == -1)
	{
		perror("Error forking first child");
		exit(1);
	}
	else if (child1_pid == 0)
	{
		close(pipex->pipe_fd[0]);
		command_1(argv, envp, pipex);
	}
	ft_second_child(argv, envp, pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

void	ft_second_child(char *argv[], char *envp[], t_pipex *pipex)
{
	int	child2_pid;

	child2_pid = fork();
	if (child2_pid == -1)
	{
		perror("Error forking second child");
		exit(1);
	}
	else if (child2_pid == 0)
	{
		close(pipex->pipe_fd[1]);
		command_2(argv, envp, pipex);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		pipex;

	if (argc == 5)
	{
		pipex.infile = open(argv[1], O_RDONLY);
		pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_pipex(argv, envp, &pipex);
		close(pipex.infile);
		close(pipex.outfile);
	}
	else
	{
		perror("Error wrong number of arguments");
		exit(1);
	}
}

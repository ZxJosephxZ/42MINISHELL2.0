

#include "../inc/minishell.h"

extern int g_status;

void	child_builtin(t_prompt *prompt, t_mini *mini, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(mini) && mini->full_cmd)
		execve(mini->full_path, mini->full_cmd, prompt->envp);
	else if (mini->full_cmd && !ft_strncmp(*mini->full_cmd, "pwd", l) \
			&& l == 3)
			g_status = mini_pwd();
	else if (is_builtin(mini) && mini->full_cmd && \
			!ft_strncmp(*mini->full_cmd, "echo", l) && l == 4)
			g_status = mini_echo(cmd);
	else if (is_builtin(mini) && mini->full_cmd && \
			!ft_strncmp(*mini->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_status = 0;
	}
}

static	void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;

	node = cmd->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*mini;
	int		l;

	mini = cmd->content;
	l = 0;
	if (mini->full_cmd)
		l = ft_strlen(*mini->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(prompt, mini, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmd, fd);
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini *mini;
	DIR		*dir;

	mini = cmd->content;
	dir = NULL;
	if (mini->full_cmd)
		dir = opendir(*mini->full_cmd);
	if (mini->infile == -1 || mini->outfile == -1)
		return (NULL);
	if ((mini->full_path && access(mini->full_path, X_OK) == 0) || is_builtin(mini))
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(mini) && ((mini->full_path && \
			!access(mini->full_path, F_OK)) || dir))
			g_status = 126;
	else if (!is_builtin(mini) && mini->full_cmd)
			g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/inc/libft.h"
#include "get_next_line.h"
#include "color.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

typedef struct s_prompt
{
    t_list *cmds;
    char    **envp;
    pid_t   pid;
} t_prompt;

typedef struct s_mini
{
    char **full_cmd;
    char *full_path;
    int infile;
    int outfile;
}t_mini;

enum e_mini_error
{
    QUOTE =1,
    NDIR = 2,
    NPERM = 3,
    NCMD = 6,
    DUPERR = 7,
    FORKERR = 8,
    PIPERR = 9,
    PIPENDERR = 10,
    MEM = 11,
    IS_DIR = 12,
    NOT_DIR = 13
};

char	*mini_readline(t_prompt *prompt, char *str);
void	*mini_here_fd(int fd[2]);
int		builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int		is_builtin(t_mini *n);
int		mini_cd(t_prompt *prompt);
void	cd_error(char **str[2]);
int		mini_pwd(void);
int		mini_echo(t_list *cmd);
int		mini_export(t_prompt *prompt);
int		mini_unset(t_prompt *prompt);
int		mini_exit(t_list *cmd, int *is_exit);
void	*check_args(char *out, t_prompt *p);
char	**ft_cmdtrim(char const *s, char *set);
char	**ft_cmdsubsplit(char const *s, char *set);
char	*ft_strtrim_all(char const *s1, int squote, int dquote);
t_list	*fill_nodes(char **args, int i);
int		get_fd(int oldfd, char *path, int flags[2]);
t_mini	*get_outfile1(t_mini *node, char **args, int *i);
t_mini	*get_outfile2(t_mini *node, char **args, int *i);
t_mini	*get_infile1(t_mini *node, char **args, int *i);
t_mini	*get_infile2(t_mini *node, char **args, int *i);
void	*exec_cmd(t_prompt *prompt, t_list *cmd);
void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2]);
void	child_builtin(t_prompt *prompt, t_mini *n, int l, t_list *cmd);
void	exec_custom(char ***out, char *full, char *args, char **envp);
int		exec_builtin(t_prompt *prompt, int (*func)(t_prompt *));
void	get_cmd(t_prompt *prompt, t_list *start, char **split_path, char *path);
char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);
char	*expand_path(char *str, int i, int quotes[2], char *var);
int		get_here_doc(char *str[2], char *aux[2]);
void	*mini_perror(int err_type, char *param, int err);
char	*mini_getenv(char	*var, char **envp, int n);
char	**mini_setenv(char *var, char *value, char **envp, int n);
char	*mini_getprompt(t_prompt prompt);
void	free_content(void *content);
void	handle_sigint(int sig);
void	handle_sigint_child(int sig);

int	ft_between_chars(char *s, char *set, char char1, char char2);
char	*ft_chartostr(char c);
char	**ft_dup_matrix(char **m);
char	**ft_extend_matrix(char **in, char *newstr);
void	ft_free_matrix(char ***m);
int	ft_isspace(char c);
char	**ft_lsttomatrix(t_list *lst);
char	**ft_matrix_replace_in(char ***big, char **small, int n);
int	ft_matrixlen(char **m);
t_list	*ft_matrixtolst(char **matrix);
int	ft_nbrlen(long n, int base);
int	ft_putmatrix_fd(char **m, int nl, int fd);
int	ft_putnbr_base_fd(long n, char *base, int fd);
int	ft_putnchar_fd(char c, int fd, int n);
int	ft_putstrn_fd(char *s, int fd, int n);
int	ft_recursive_power(int nb, int power);
int	ft_sqrt(int nb);
int	ft_strchr_i(const char *s, int c);
char	*ft_strenlarge(char *s1, char *s2);
int	ft_strrncmp(const char *s1, const char *s2, size_t n);
char	**ft_subsplit(char const *s, char *needle);
char	*ft_uitoa(unsigned int n);
int	ft_countchar(char *s, char c);
int	ft_strchars_i(const char *s, char *set);
char	*expand_path(char *str, int i, int quotes[2], char *var);
char	*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);
int	ft_putendl_fd_2(char *s, int fd);
int	ft_putstr_fd_2(char *s, int fd);
int	ft_putchar_fd_2(char c, int fd);

#endif
#ifndef MINISHELL_H
#define MINISHELL_H

#include "/libft/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

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
    char **full_path;
    int infile;
    int outfile;
}t_mini

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

#endif
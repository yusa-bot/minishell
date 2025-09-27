/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:23:17 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/27 19:20:58 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>
#include <sys/stat.h>

# include "../libft/libft.h"

# include "../include/builtins.h"
# include "../include/tokenizer.h"
# include "../include/parser.h"
# include "struct.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_BUILTIN_MISUSE 2
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_EXEC 126
# define EXIT_OUT_OF_RANGE 255

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int g_sig;

//ft_error.c
void malloc_error();
void	syntax_error(char *unexpected_token, t_token **token_lst, t_env **env_lst);

void	setup_signals_interactive(void);
void	sigint_handler(int sig);

void setup_signals_interactive(void);
char	*search_external_path(const char *cmd, t_env **env_lst);
int run_pipe(t_cmd *cmd, t_env **env_lst, t_shell *shell);
int apply_redirect(const t_cmd *cmd, t_shell *shell);

void setup_signals_child(void);
void	sigint_handler(int signo);
void setup_signals_interactive(void);

int is_builtin_parent(char **args);
int is_builtin_child(char **args);
int run_builtin(char **args, t_env **env_lst, t_shell *shell);

int run_child(t_cmd *cmd, t_env **env_lst, t_shell *shell);
int	exec_child(t_cmd *cmd, t_env **env_lst, t_shell *shell);
int run_parent(t_cmd *cmd, t_env **env_lst, t_shell *shell);

void continue_free(t_token **token_lst, t_cmd **cmd_lst);
void ft_cmd_clear(t_cmd **cmd_lst);
void	ft_token_clear(t_token **token_lst);

int ft_echo(char **argv, int fd);
int ft_exit(char **argv, t_shell *shell);
void free_split(char **arr);

int prepare_heredoc_for_cmd(t_cmd *cmd, void *env);

#endif

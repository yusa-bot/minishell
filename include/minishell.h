/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:03:13 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/31 16:11:00 by rinka            ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libft/libft.h"
# include <sys/errno.h>
# include <dirent.h>

# include "builtins.h"
# include "tokenizer.h"
# include "parser.h"
# include "struct.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_BUILTIN_MISUSE 2
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NO_EXEC 126
# define EXIT_OUT_OF_RANGE 255

# define STDERR 2

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t g_sig;

//ft_error.c
void	malloc_error(t_shell *sh, t_token **single_token_lst);
void	*syntax_error(t_shell *sh, char *unexpected_token);
void	perror_exit(char *msg);
void	err_wrt(int fd, char *str1, char *str2);

void	setup_signals_interactive(void);
void	sigint_handler(int sig);

void	setup_signals_interactive(void);
char	*search_external_path(const char *cmd, t_env **env_lst);
int		exec_pipe(t_shell *sh);
int		apply_redirect(t_shell *sh);

void	setup_signals_child(void);
void	sigint_handler(int signo);
void	setup_signals_interactive(void);

int		is_builtin_parent(char **args);
int		is_builtin_child(char **args);
int		run_builtin(t_shell *sh, char **args);

int		exec_child_handler(t_shell *sh);
int		exec_child(t_shell *sh);
int		exec_parent(t_shell *sh);

void	continue_free(t_shell *sh);
void	ft_cmd_clear(t_cmd **cmd_lst);
void	ft_token_clear(t_token **token_lst);

int		ft_echo(char **argv, int fd);
int		ft_exit(char **argv, t_shell *shell);

int		prepare_heredocs(t_cmd *cmd_lst);

// minishell_util
int		read_prompt(t_shell *sh);
void	minishell_init(t_shell *sh, char **envp);
void	after_oneloop_cleanup(t_shell *sh);
void	after_minishell(t_shell *sh);

void ft_handle_unclosed_quote(t_shell *sh);

void	exec_cmd_handler(t_shell *sh);

#endif

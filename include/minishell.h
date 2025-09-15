/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:23:17 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 22:16:31 by ayusa            ###   ########.fr       */
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

# include "../libft/lst/lst.h"
# include "../libft/libft.h"

# include "../include/builtins.h"
# include "../include/tokenizer.h"
# include "../include/parser.h"

extern int g_sig;
typedef struct s_shell {
    t_env   *env;
    int     status;
} t_shell;

//ft_error.c
void malloc_error();
void	syntax_error(char *unexpected_token, t_token **token_lst, t_env **env_lst);

void	setup_signals_interactive(void);
void	sigint_handler(int sig);

void setup_signals_interactive(void);
char	*search_external_path(const char *cmd, t_env **env);
void run_pipe(t_cmd *cmd, t_env **env, t_shell shell);
int apply_redirect(const t_cmd *cmd);

void setup_signals_child(void);
void	sigint_handler(int signo);
void setup_signals_interactive(void);

int is_parent(char **args);
int run_builtin(char **args, t_env **env, t_shell shell);
int run_child(t_cmd *cmd, t_env **env, t_shell shell);
int run_parent(t_cmd *cmd, t_env **env, t_shell shell);

int ft_echo(char **argv, int fd, t_shell shell);

#endif

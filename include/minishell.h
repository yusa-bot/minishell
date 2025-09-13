/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:23:17 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/13 22:07:55 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# include "../include/builtins.h"
# include "../include/tokenizer.h"
# include "../include/parser.h"
# include "../include/signal.h"

int g_sig;

//pipe
typedef struct s_pipeline {

} t_pipeline;

//ft_utils.c
int	is_delimiter(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
char *ft_strjoin_safe(char *s1, char *s2);
void	ft_free_str_array(char **arr);

//ft_error.c
void malloc_error();
void	syntax_error(char *unexpected_token, t_token **token_lst, t_env **env_lst);

t_env *set_env(char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:04:36 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 17:09:24 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "minishell.h"

t_cmd	*ft_parser(t_token *token_lst, t_env *env_lst, char ***tmpfiles, t_shell *shell);

t_token	*join_expanded_tokens(t_token **cmd_start, t_token **token_lst, t_env *env_lst, t_shell *shell);

//ft_parser_utils.c
t_token	*ft_tokenlst_dup(t_token *lst);
void	*ambiguous_redirect_error(char *original, t_token *token_lst, t_token *single_token_lst, t_env *env_lst);

//ft_cmdlst_utils.c
t_cmd	*ft_cmdlst_init(void);
t_cmd	*ft_cmdlst_new(char **cmd_args, char **env_vars, t_redirect *infile, t_redirect *outfile);
void	ft_cmdlst_delone(t_cmd *lst);
void	ft_cmdlst_clear(t_cmd **lst);
t_cmd	*ft_cmdlst_last(t_cmd *lst);
void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new);

//ft_redirectlst
t_redirect	*ft_redirectlst_init(void);
t_redirect	*ft_redirectlst_new(char *expanded_argi, char *original_arg, t_token_type token_type);
void		ft_redirectlst_clear(t_redirect **lst);
t_redirect	*ft_redirectlst_last(t_redirect *lst);
void		ft_redirectlst_add_back(t_redirect **lst, t_redirect *new);

//ft_globbing..c
t_token	*glob_single_token(char *pattern);
void	ft_globbing(t_token **token_list_ptr, int *arg_count);

char	*ft_heredoc(char *eof, t_cmd *cmd_lst, t_env *env_lst, char ***tmpfiles);

#endif

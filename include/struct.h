
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:23:17 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/28 13:43:11 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_env {
	char		*key;
	char		*value;
	int			is_export;
	struct s_env	*next;
} t_env;

typedef enum e_token_type
{
	PIPE,
	VARIABLE,
	REDIRECT_IN,// <
	REDIRECT_OUT,// >
	APPEND,// >>
	HEREDOC,// <<
	FILENAME,
	INFILE,//リダイレクトのファイル名（確定）
	WORD,
	VARIABLE_ASSIGNMENT,
}	t_token_type;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote_type;

typedef struct s_token
{
	char			*str;
	char			*original_str;
	t_token_type	token_type;
	t_quote_type	quote_type;
	int				is_joined_with_next;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	char				*original_arg;//用途を限定せず汎用的に
	char				*expanded_arg;
	t_token_type		token_type;//<, >, >>, <<
	struct s_redirect	*next;//複数リダイレクト用
} t_redirect;

typedef struct s_cmd
{
	char			**cmd_args;
	t_env		*tmp_env;//一時的な環境変数
	t_redirect		*infile;
	t_redirect		*outfile;
	struct s_cmd	*next;//pipeline用
}	t_cmd;

typedef struct s_shell{
	int		status;
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;
	char	*line; //prompt
	char	**tmpfiles;
} t_shell;

#endif

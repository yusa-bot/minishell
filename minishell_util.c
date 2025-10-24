/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:18:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/24 17:02:39 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_init(t_shell *sh, char **envp, char ***tmpfiles)
{
	sh->env = NULL;
	sh->env = ft_set_env(envp);
	sh->token = NULL;
	sh->cmd = NULL;
	sh->status = 0;
	sh->line = NULL;
	tmpfiles = NULL;
}

void	after_oneloop(t_shell *sh, char	**tmpfiles)
{
	int i;

	i = 0;
	while (tmpfiles &&  tmpfiles[i])
	{
		if (unlink(tmpfiles[i++]) == -1)
			perror("minishell: unlink");//unlink失敗時
	}
	ft_free_str_array(tmpfiles);

	continue_free(sh); // before:ft_parser()直後だった after:ここで良いかな？(yusa)
	free(sh->line); //ここで解放しないと、どこかの内部(忘れた)でまだline使っててセグフォになる。
	sh->line = NULL;
}

after_minishell(t_shell *sh)
{
	cear_history();
	if (sh->line)
		free(sh->line);
	continue_free(&sh);
	ft_lst_clear(&sh->env);
	sh->env = NULL;
}

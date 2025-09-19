/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:11:30 by rtakayam          #+#    #+#             */
/*   Updated: 2025/09/19 16:44:54 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "struct.h"

t_token	*tokenize_line(char *line);

//ft_tokenlst_utils.c
void	ft_tokenlst_delone(t_token *lst);
void	ft_tokenlst_clear(t_token **lst);
t_token	*ft_tokenlst_last(t_token *lst);
void	ft_tokenlst_add_back(t_token **lst, t_token *new);
void	ft_tokenlst_add_front(t_token **lst, t_token *new);
t_token	*ft_tokenlst_new(char *str, t_token_type token_type,
			t_quote_type quote_type, int is_joined_with_next);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:23:05 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/13 21:25:20 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

#include <signal.h>
#include <sys/types.h>
# include "libft.h"
# include "builtins.h"
# include "tokenizer.h"
# include "parser.h"

void	setup_signals_interactive(void);
void	sigint_handler(int sig);

#endif
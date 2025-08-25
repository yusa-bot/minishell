
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "builtins.h"
# include "tokenizer.h"


//ft_utils.c
int	is_delimiter(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s, size_t n);
char *ft_strjoin_safe(char *s1, char *s2);

//ft_error.c
void malloc_error();
void	syntax_error(char *unexpected_token, t_token **token_lst);


#endif
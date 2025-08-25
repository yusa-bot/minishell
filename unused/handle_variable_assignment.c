// #include "minishell.h"

// char *handle_variable_assignment(t_env **env_lst, char *line)
// {
// 	char *rest_of_line;
// 	char *assignment_value;
// 	int	i;
// 	int tmp;

// 	i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	tmp = i;
// 	if (!is_digit(line[i]))
// 	{
// 		while (is_digit(line[i]) || is_alpha(line[i]) || line[i] == '_')
// 			i++;
// 		if (tmp != i && line[i] == '=')
// 		{
// 			while (line[i] != ' ' && line[i] != '\t')
// 				i++;
// 			assignment = ft_strndup(&line[tmp], i - tmp);
// 			ft_add_env(env_lst, assignment, 0);//is_export = 0
// 			rest_of_line = ft_strdup(&line[i]);
// 			free(line);
// 			return (rest_of_line);
// 		}
// 	}
// 		rest_of_line = ft_strdup(line);
// 		free(line);
// 		return (rest_of_line);
// }

/*
exportにも対応？？なら先にリスト作ったほうが処理しやすいかも
↑
export無しの変数代入だけを特別な構文としてenv_lstへのデータ格納前に処理することにした（exportはコマンドの実行だから）
*/
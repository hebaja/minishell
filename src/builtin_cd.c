#include "../include/minishell.h"

/* TODO DEBUG purpose */
t_token	*build_token()
{
	t_token *tokens_head;
	t_token *token;
	char	*path = "src";

	tokens_head = token_build("cd", 2);
	token = token_build(path, ft_strlen(path));
	token_lst_add_back(&tokens_head, token);
	return tokens_head;
}

void	builtin_cd()
{
	t_token	*token_lst;
	char	buf[100];
	char	*env;

	token_lst = build_token();
	getcwd(buf, 100);
	ft_printf("%s\n", buf);
	print_tokens(token_lst);
	if (chdir(token_lst->next->value) == -1)
		perror("chdir");
	getcwd(buf, 100);
	ft_printf("%s\n", buf);
}

/* TODO DEBUG purpose */
int	main()
{
	builtin_cd();
	return (0);
}

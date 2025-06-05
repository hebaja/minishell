#ifndef MINISHELL_TEST_H
# define MINISHELL_TEST_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "../include/minishell.h"
# include "criterion-2.4.2/include/criterion/assert.h"
# include "criterion-2.4.2/include/criterion/criterion.h"
# include "criterion-2.4.2/include/criterion/redirect.h"

extern t_token	*token_lst;
extern t_cmd	*cmd_lst;
extern t_env	*env_lst;
extern size_t	size;
extern char		**values;
extern char		**types;
extern char		**paths;
extern int		res;
extern int		cmd_res;
extern int		i;

void	clean_values(char **values);
void	redirect_all_stdout(void);
void	redirect_stdout(void);
void	redirect_stderr(void);
char    *fetch_token_type(t_token_type type);
char	**fetch_tokens_type_list(t_token *token_lst);
void	unquoted_value_test(t_token *token_lst, char *value, char quote);
void	redirect_stdout_err(void);
void	test_token_lst(t_token *token_lst, char *value, char *type);
void	usual_flow(t_token **token_lst, t_env *env_lst);
void	test_lst(t_token *token_lst, char **values, char **types);
char	**split_token_lst(t_token *token_lst);
char	**populate_values(int size, ...);
char	*multi_str_join(int size, ...);
t_env	*build_envp(void);
void	clean_envp(void);
void	setup(void);
void	clean(void);
void	setup_redirect_err(void);

#endif

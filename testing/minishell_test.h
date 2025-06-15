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

extern size_t	size;
extern char		**values;
extern char		**types;
extern char		**paths;
extern t_ms		*ms;
extern int		res;
extern int		cmd_res;
extern int		i;

void	init_test(void);
void	init_test_redirect_stderr(void);
void	init_test_redirect_stdout(void);
void	init_test_alloc_mem(void);
void	clean_values(char **values);
void	redirect_all_stdout(void);
void	redirect_stdout(void);
void	redirect_stderr(void);
char    *fetch_token_type(t_token_type type);
char	**fetch_tokens_type_list(t_token *token_lst);
void	unquoted_value_test(t_token *token_lst, char *value, char quote);
void	redirect_stdout_err(void);
void	test_token_lst(t_token *token_lst, char *value, char *type);
void	usual_flow(t_ms *ms);
void	test_lst(t_token *token_lst, char **values, char **types);
char	**split_token_lst(t_token *token_lst);
char	**populate_values(int size, ...);
char	*multi_str_join(int size, ...);
t_env	*build_envp(void);
void	clean_envp(void);
void	clean_test(void);
void	setup(void);
void	clean(void);
void	setup_redirect_err(void);
void	clean_split_path(char **paths);
char	**split_path_test(t_env *env_lst);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/24 02:19:05 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include  <dirent.h>
# include "../src/exec/libf/libft.h"

/* general */
typedef enum e_boolean {FALSE, TRUE, ZAB}	t_bool;

/* signals */
int			capture_signals(void);
t_bool		is_execution_running(t_bool *execution_is_running);

/* tokenizer */
// ' ', '\n', '\'', '"', '\\', '$', '|', '<', '>', '<<', '>>', 
enum e_type {
	WSPACE,
	NEW_LINE,
	QUOTE,
	DQUOTE,
	ESCAPE,
	VAR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	WORD
};

enum e_state {
	QUOTED,
	DOUBLE_QUOTED,
	NORMAL
};

typedef struct s_token
{
	char			*content;
	enum e_state	state;
	enum e_type		type;
	t_bool			expand_heredoc;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;
void		tokenize(char **line, t_token **tokens, enum e_state *state);
void		special_character_handler(char **line, t_token **tokens,
				enum e_state *state, enum e_type type);
void		variable_handler(char **line, t_token **tokens,
				enum e_state *state);
void		normal_character_handler(char **line, t_token **tokens,
				enum e_state *state);
int			input_output_characters_handler(char **line, t_token **tokens,
				enum e_state *state);
void		new_node(t_token **tokens, t_token *new_token);
/* syntax checker */
t_bool		syntax_check(t_token *tokens);
t_bool		is_redirection(enum e_type type);

/* environment */
typedef struct s_env
{
	char			*property;
	char			*value;
	struct s_env	*next;
}	t_env;
t_env		**get_env(void);

void		fetch_env(t_env **env, char **environment);
char		*get_var(char *property);

/* expander */
void		expand(t_token **tokens);
void		replace_vars(t_token *tokens);
void		replace_var(t_token *tokens);
void		gather_strings(t_token *tokens);
void		remove_quotes(t_token **tokens, enum e_type type);
void		remove_first_quotes(t_token **tokens, enum e_type type);
void		empty_strings_checker(t_token *tokens, enum e_type type);

/* parser */
typedef struct s_command
{
	char				**elements;
	int					input_fd;
	int					output_fd;
	t_bool				append;
	struct s_command	*next;
	struct s_command	*prev;
}					t_command;
t_command	*parse(t_token *tokens, t_bool *fail);

/* redirections */
void		handle_redir_out(t_token *tokens, int *fd, t_bool *fail,
				t_bool *append);
void		handle_redir_in(t_token *tokens, int *fd, t_bool *fail);
int			handle_heredoc(t_token *tokens, int *fd, t_bool *fail);

/* lib */
size_t		_strlen(char *s);
void		*_malloc(size_t size);
char		*_strdup(char *s);
int			_strcmp(char *s1, char *s2);
char		*_strjoin(char *s1, char *s2);
void		free_tokens(t_token *tokens);
void		free_commands(t_command *commands);

/* execution */
int			exec_all(t_command *commands, t_env *env);
char		**get_env_array(t_env *env);
char		*get_env_var(char *property, t_env *env);
void		set_env_var(char *property, char *value, t_env *env, int i);
void		do_all(t_command *commands, t_env *env, int *pip, int *pip1);
void		dups(t_command *commands, int *pip, int *pip1);
int			wait_and_getstatus(int pid);
char		*join_path_cmd(char *path, char *cmd);
int			check_dir_and_access(char *cmd);
void		print_not_found(char *cmd);
void		get_paths(char ***paths);
int			check_exist(char **paths, char *cmd, int red);
int			check_executable(char **paths, char *cmd);
int			just_cd(t_env *env);
int			print_env(t_env *env);
void		my_new_node(t_env *env, char *value, char *property);
void		print_if_no_red(char *cmd, int red);
void		without_value(char *arg, t_env *env);
int			is_dir(char *cmd);

/*builtins*/
int			ft_pwd(void);
int			ft_echo(char **args);
void		ft_exit(char **args);
int			ft_cd(char **args, t_env *env);
int			ft_munset(char **value, t_env **env);
int			ft_export(char **args, t_env *env);
int			ft_env(t_env *env);
#endif
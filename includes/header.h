/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/12 17:11:53 by bel-amri         ###   ########.fr       */
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

/* general */
typedef enum e_boolean {FALSE, TRUE}	t_bool;

/* signals */
void		capture_signals(void);

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
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

void		tokenize(char **line, t_token **tokens, enum e_state *state);

/* syntax checker */
t_bool		syntax_check(t_token *tokens);
t_bool		is_redirection(enum e_type type);

/* expander */
void		expand(t_token **tokens);

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

/* lib */
size_t		_strlen(char *s);
void		*_malloc(size_t size);
char		*_strdup(char *s);
int			_strcmp(char *s1, char *s2);
char		*_strjoin(char *s1, char *s2);
void		free_tokens(t_token *tokens);
void		free_commands(t_command *commands);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkafmagh <kkafmagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:31 by tdenis            #+#    #+#             */
/*   Updated: 2025/07/28 19:21:40 by kkafmagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

extern int	g_signal;

typedef enum e_token
{
	DOUBLE_QUOTE,
	SIMPLE_QUOTE,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	SPACES,
	PARENTHESIS,
}		t_token;

typedef struct s_vars
{
	char	**envi;
	int		*pid;
	int		watatus;
	int		last_code;
	char	*current_path;
	int		pipe1[2];
	int		pipe2[2];
	int		fd[3];
}	t_vars;

typedef struct s_list
{
	char			*com;
	char			**arguments;
	char			**infile;
	char			**outfile;
	int				fd_in;
	int				fd_out;
	struct s_list	*prev;
	struct s_list	*next;
}		t_list;

// Command name
// Array of strings (arguments)
// Array of strings (input file paths)
// Array of strings (output file paths)
// Open file descriptor (infile)
// Open file descriptor (outfile)
// Previous command in list
// Next command in list

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- free/close/print/debug

int		ft_free(void *str);
void    lst_close(t_list *lst);
int		free_tab(char **tab);
int		print_tab(char **arg_lst);
void	free_cmds(char ***commands);
void	close_fd(t_vars *va);
void	free_lst(t_list *lst);
int     ft_findstr(const char *str, const char *src, int len);
void	free_end(t_vars *va, t_list *lst);
void    file_close(int *file);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- pipex

void    exe(t_vars *va, t_list *lst);
int		pipex(t_vars *va, t_list *lst);
int     path_checker(t_vars *va, t_list *lst);
void    loop(t_vars *va, t_list *lst);
void    onecom(t_vars *va, t_list *lst);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- dup pipex

void	restore_fd(t_vars *va);
int     dir_checker(t_vars *va, char *cmd);
int     dup_maker(t_vars *va, t_list *lst);
int     in_util(t_vars *va, t_list *lst);
int     out_util(t_vars *va, t_list *lst);
int     input_access_checker(t_vars *va, char *content);
int     output_access_checker(t_vars *va, char *content);
int     in_checker(t_vars *va, char **in2);
int     out_checker(t_vars *va, char **out2);
int     file_opener(t_vars *va, t_list *lst);
int     in_opener(t_vars *va, t_list *lst);
int     out_opener(t_list *lst);
int		heredoc(t_vars *va, t_list *lst, char *file);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- set_list

int		count_in(char *str);
int		count_out(char *str);
char	*catch_word(char *str);
t_list	*new_node(t_list *lst);
t_list	*prev_node(t_list *lst);
t_list	*next_node(t_list *lst);
t_list	*set_lst(t_vars *va, t_list *lst, char *str);
int		fill_lst(t_vars *va, t_list *lst, char *str);
int		set_infile(t_vars *va, t_list *lst, char *str);
int		set_outfile(t_vars *va, t_list *lst, char *str);
int		set_evar(t_vars *va, t_list *lst, char *str);
int		set_arg(t_vars *va, t_list *lst, char *str);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- built in

int     builts_in(t_vars *va, t_list *lst);
char    **export_util1(t_vars *va, char **args, char **env);
char    **ft_export_1a(t_vars *va, int i, char **args, char **res);
char    **export_util2(char *va, char *ag, char **env);
char    *getvar(t_vars *va, char *var);
char	**ft_unset(char **ag, char **env);
int		ft_cd(t_vars *va, char **arguments);
int     ft_echo(t_vars *va, char **args);
int		ft_exit(t_vars *va, t_list *lst);
int		ft_pwd(t_vars *va);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- random

int		still_alphanum(char *str);
int		ft_printf(int fd, const char *s, ...);
char    *getfile(char *str);
char	*ft_trim(char *str);
int     lst_count(t_list *lst);
int		tab_len(char **tab);
void	tab_cmds(t_vars *va, char *str);
void	clean_ter(char **env);
int		print_hex(t_vars *va);
char	**cpy_tab(char **tab);
void	handle(int s);
int		ft_strcmp(char *src, char *dest);
char	**set_env(t_vars *va, char **env);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  signaux

void    sig_handler(int s);
void    file_end(char *str, t_vars *va);
void	end_heredoc(int signal);
void    handle(int s);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  parsing

int     syntaxer(char *in);
int     quote_checker(char *in);
int     piperror(char *in);
int     chevron_err(char *in);
int     chevron_err2(char *in);
char    **wrdsplit(char *in);
char    **cmdsplit(char *in);
char    *chevronspacer(char *in);
int     quote_skip(char *in);
t_list  *node_init(char *cmd);
void    chevrons(char **in, char **res, int *i, int *j);
char    *filecpy(char *s1, char *s2);
char    *killquote(t_vars *va, char *str);
void    new_lst(t_vars *va, char *in, char **supersplit, t_list **curr);
void    infilecpy(t_list **node, int *i);
void    outfilecpy(t_list **node, int *i);
void    file_clr(t_vars *va, t_list **node);
void    arg_clr(t_list **node);
char    *str_clr(t_vars *va, char *str);
int     wrd_split_count(char *in);
char    *wrdmalloc(char const *str, int start, int end);

#endif

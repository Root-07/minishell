/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:50 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 15:09:56 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include <readline/readline.h>
# include <readline/history.h>

// defines to help `conv_to_cd` function.
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

// defines to help the parser
# define RDR_IN 1
# define RDR_OUT 2
# define RDR_APPEND 3
# define RDR_HERDOC 4
# define NONE 0

// struct used to helpe `conv_to_cd` function.
typedef struct s_conv
{
	int	start;
	int	end;
	int	check;
	int	quotes;
}	t_conv;

typedef struct s_cmd
{
	char			**args;
	int				ifd;
	int				ofd;
	int				inred;
	int				outred;
	int				herdoc;
	int				first_rdr;
	int				cmd_len;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exe
{
	int		i;
	t_cmd	*env;
	char	*check;
	int		i_tmp[2];
	int		len;
}	t_exe;

typedef struct s_global
{
	int		status;
	int		herdoc;
	int		cmd;
	int		parent;
	int		is_fork;
	t_list	**lst_env;
	t_list	*lst_export;
	t_exe	exe;
}	t_global;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

t_global	g_global;

// split and get token from command
void	split_cmd(char *input, t_list **list);
void	ft_del(void *data);
void	ft_free_split(char **split);
void	no_free(void *ptr);
void	ft_free_env(void *data);

// analyze the command
int		check_node(t_list *list);
int		check_rdr(char *data);
int		check_pipe(char *data, int first);
char	*check_cmd(char *old_cmd);

/* parser */
t_cmd	*parser(t_list *list);
void	ft_free_cmd(t_cmd *cmd);
int		check_quotes(char *input);
int		check_if_quotes(char *str, int i, int *quotes);
int		find_quotes(char *str, int i, int *quotes);
void	quotes_error(int type);
int		get_cmd_line(t_list *list);
void	get_arrgs_supp(t_list *node, t_cmd *cmd, int len, int cmd_len);
t_cmd	get_args(t_list *lst, int cmd_len);
char	*get_herdoc(int fd);
int		check_onbiges(char *file);
void	redirections_in(t_cmd **lst, char *file);
int		redirections_out(t_cmd **lst, char *file);
int		redirections_append(t_cmd **lst, char *file);
void	redirections_herdoc(t_cmd **lst);
int		redirections(t_cmd *cmd, char *str, int rdr);
void	herdoc_supp(char *herdoc, int fd, int expand);
int		herdoc(char *file, int expand);
int		read_herdocs(t_list *lst);
void	write_expantion(char *herdoc, int fd);
int		syntax_error_supp(t_list *node);
int		syntax_error(t_list *node);
int		check_pipe(char *data, int first);
int		rdr_error(char *data);
int		check_rdr(char *data);
int		check_node(t_list *list);
void	check_quotes_supp(char *input, int *i, int *quotes);
int		find_qoutes_supp(char *str, int i, int *quotes);
char	*ft_chardup(char c);
t_list	*write_expantion_on_lst(char *str);
char	*expantion(char *str, int check);
int		first_handle(t_list **lst, char *line, int *qoutes);
void	write_expand_supp(t_list **lst, char *str, int check);
void	write_expand(t_list **lst, char *env, int *qoutes);
int		get_expand(t_list **lst, char *line, int *qoutes);
int		handle_single_qoutes(t_list **lst, char *line, int *qoutes);
int		handel_default(t_list **lst, char *line, int *qoutes);
t_list	*join_arr_to_lst(char **args);
char	**join_lst_to_arr(t_list *lst);
char	**join_lst_to_arr_supp(t_list *lst);
void	expand(t_cmd **list);

/* bultins and env */
t_env	*get_line_of_env(t_list **lst, char *str);
t_list	*get_env(t_list **lst, char **str);
char	*get_env_value(t_list *lst, char *name);
void	add_var_to_env(t_list **lst, char *old_str);
void	free_env(void *ptr);
int		unset_env(t_list **lst, char *name);
void	print_env(t_list *lst);
int		exec_cd(t_cmd cmd, t_list *list_env);
int		exec_echo(char **args);
int		exec_pwd(t_list *env);
int		exec_env(t_cmd cmd, t_list **lst_env);
int		exec_export(t_cmd cmd, t_list **lst_env);
int		exec_unset(t_cmd cmd, t_list **lst_env);
int		builtins(t_cmd *cmd);
int		env_is_valid(t_list *lst, char *name);
char	**arr_of_env(void);

/* -----------
	execuetion 
--------------*/
/* redirection and builtins */
void	setup_red_(t_cmd *node);
int		exec_builtin(t_cmd *cmd);
int		is_builtins(char *cmd);
/* path */
char	*path_cmd_(char *s, t_list *lst);
char	*get_path(char *s);
/* exit status */
void	set_last_status(int stts);
int		get_last_status(void);
int		get_exit_status(int pid);
/* main execution */
void	handle_pipes(int *pipes, int fd);
int		exec_one_cmd(t_cmd *cmd, int *pipes, int fd, int must_fork);
void	cases_of_exec(int *fd, int *p, int *fds, int check);
int		exec_multiple_cmds(t_cmd *cmd, int cmd_count);
void	execute(t_cmd *cmd);

#endif

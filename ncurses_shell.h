/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:51:03 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/08 17:59:37 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_SHELL_H
# define NCURSES_SHELL_H

# include <stdbool.h>
# include <curses.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "radix.h"
# include "hashtable.h"

# define RESIZE_LIB_RES 5
# define ESC 27
# define DEL_K 127
# define PROMPT_SZ 80
# define TAB_SIZE 7

typedef struct		s_pt
{
	unsigned int	x;
	unsigned int	y;
}					t_pt;

typedef struct		s_ctn
{
	char			c;
	struct s_ctn	*next;
	struct s_ctn	*prev;
}					t_ctn;

typedef struct		s_rmb
{
	char			*str;
	struct s_rmb	*next;
	struct s_rmb	*prev;
}					t_rmb;

typedef struct		s_str
{
	t_ctn			*cur;
	unsigned int	pos;
	unsigned int	pos_tab;
	unsigned int	sz;
}					t_str;

typedef struct		s_fct
{
	int				k;
	void			(*call)(void *);
}					t_fct;

typedef struct		s_ncurses
{
	WINDOW			*win;
	t_pt			sz;
	char			prompt[PROMPT_SZ];
	bool			stopped;
	char			*input;
	t_str			str;
	t_rmb			*remember;
	t_rmb			*hist;
	t_rmb			*cur_hist;
	t_pt			coord;
	t_fct			fcts[TAB_SIZE];
	t_search		search;
	t_map			map;
	char			*help;
}					t_ncurses;

/*
**	nc user fct
*/

bool				nc_start(t_ncurses *nc, int ac, char **av);
void				nc_loop(t_ncurses *nc);
void				nc_add(t_ncurses *nc, char *ins);
int					nc_delete(t_ncurses *nc);

/*
**	nc inside fct
*/

void				ncurses_conf_from_file(t_ncurses *nc, char *file);
void				init_kvp(t_ncurses *nc, char *k, char *v);
void				nc_reset_completion(t_ncurses *n);
bool				nc_fct_exec(t_fct *fct, int k, void *arg);
void				nc_fct_init(t_fct *fct, int k, void (*f)(void *));

/*
**	treat key
*/

void				nc_left(void *arg);
void				nc_right(void *arg);
void				nc_del(void *arg);
void				nc_up(void *arg);
void				nc_down(void *arg);
void				nc_enter(void *arg);
void				nc_tab(void *arg);

/*
**	treat key
*/

void				nc_display(t_ncurses *nc);
void				nc_write_ptr(t_ncurses *nc, char *ptr);
void				display_help(t_ncurses *nc);

/*
**	nc utility
*/

void				nc_getprompt(t_ncurses *nc);
void				nc_carriage_return(t_ncurses *nc);

/*
**	nc history
*/

void				nc_add_history(t_rmb **lst, t_ctn *ptr);
void				nc_reset_history(t_ncurses *nc);
void				nc_attrib_history(t_str *str, t_ctn *ev);

/*
**	nc str
*/

void				ncurses_str_import(t_str *s, char *n,
	t_ctn *e, unsigned int *l);
void				reset_extracted_str(t_str *str, t_ctn *e, unsigned int sz);
char				*ncurses_str_extract(t_str *s, t_ctn **e, unsigned int *l);
void				clear_str(char **s);
void				str_clear(t_str *str);
void				ctn_create(t_str *str, char c);
void				ctn_del(t_ctn *ptr);
char				*rmb_create(t_rmb **lst, t_rmb **hist, t_str *cur,
	char prompt[PROMPT_SZ]);
void				rmb_add(t_rmb **lst, char *ins);

#endif

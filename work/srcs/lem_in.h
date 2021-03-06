/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:51:17 by otimofie          #+#    #+#             */
/*   Updated: 2018/04/18 12:51:19 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**------------------------  runtime declarations  ------------------------------
*/

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/ft_printf.h"

/*
**------------------------  type of the initial data  --------------------------
*/

# define ANTS_QUANTITY 1
# define UNVALID_COMMAND 2
# define COMMENT 3
# define VALID_COMMAND 4
# define ROOM 5
# define ROOM_START 6
# define ROOM_END 7
# define LINK 8
# define SKIP 9

/*
**---------------   data structure to keep the initial data set  ---------------
*/

typedef struct			s_init
{
	int					type_of_the_line;
	char				*valid_line;
	struct s_init		*prev;
	struct s_init		*next;
}						t_init;

/*
**---------------------------   graph data structure  --------------------------
*/

typedef struct			s_edge
{
	char				*room_name;
	char				visited;
	struct s_edge		*next;
}						t_edge;

typedef struct			s_vertex
{
	char				*vertex_name;
	char				visited;
	int					path;
	struct s_edge		*e_next;
	struct s_vertex		*v_next;
}						t_vertex;

/*
**-------------   data struct to keep: start, end, quantity of ants  -----------
*/

typedef struct			s_data
{
	char				*start;
	char				*end;
	int					quantity_of_ants;
	int					sounds;
}						t_data;

/*
**-------------------------   general  -----------------------------------------
*/

void					ft_print_ll(t_init *data);
void					ft_error(void);
void					ft_to_start(t_init **initial_data);
void					ft_init(t_init **i, t_vertex **v, t_data *d, char **a);

/*
**-------------------------   list of functions for validation  ----------------
*/

void					ft_validation(t_init **initial_data);
int						ft_ant_check(char *str, int *r, t_init **it);
int						ft_check_rooms(char *s, int *r, int *c, t_init **i);
int						ft_aspects(char *str, t_init *initial_data);
int						ft_exclusions(t_init *initial_data);
int						ft_detect_command(char *str, int *c_det);
int						ft_det_line(char *str, int **c_det);
int						ft_check_links(char *str, t_init **initial_data);
void					ft_list_builder(t_init **i, char *v, int iq);
t_init					*line_builder(char *valid_line, int i);
int						ft_detect_input(t_init *initial_data);
int						ft_x_y_unique(char **array, t_init *initial_data);

/*
**-------------------------   list of functions to build a graph  --------------
*/

void					ft_build_vertex_structure(t_init *i_d, t_vertex **ver);
void					ft_build_edge_structure(t_init *init, t_vertex *g);
void					ft_add_data_to_graph(t_init *init, t_data *data);

/*
**---------------------------------------   queue  -----------------------------
*/

typedef struct			s_qnode
{
	char				*str;
	char				*parent;
	int					wave;
	struct s_qnode		*next;
}						t_qnode;

typedef	struct			s_queue
{
	t_qnode				*front;
	t_qnode				*rear;
}						t_queue;

t_queue					*createqueue(void);
t_qnode					*dequeue(t_queue *q);
void					enqueue(t_queue *q, char *str, char *parent, int wave);
int						isempty(t_queue *q);
void					ft_clean_queue_node(t_qnode **node);

/*
**---------------------------------------   way  -------------------------------
*/

typedef struct			s_way
{
	char				*way_room;
	int					wave;
	struct s_way		*next;
}						t_way;

void					add_to_way(t_way **way, char *str, int wave);
void					reverse(t_way **head_ref);

/*
**---------------------------------------   plan_b  ----------------------------
*/

typedef struct			s_planb
{
	char				*vertex_name;
	char				*parent;
	struct s_planb		*prev;
	struct s_planb		*next;
}						t_planb;

void					add_to_the_key(t_planb **p, char *chi_s, char *par_s);

/*
**-----------------------------------------   bfs  -----------------------------
*/

void					bfs(t_data data, t_vertex *vertex, t_way **way);
void					b_end(t_way **w, t_qnode **n, t_planb **m, t_queue **q);
void					add(t_vertex *v, t_qnode *n, t_queue *q, t_planb **m);
void					ft_visited(t_vertex *vertex, char *str, char c);

/*
**-----------------------------------------   ways  ---------------------------
*/

typedef	struct			s_way_option
{
	char				*node_id;
	int					ant_number;
	int					way_vertex;
	int					color_id;
	struct s_way_option	*way;
	struct s_way_option	*next;
}						t_way_option;

typedef	struct			s_ways
{
	int					way_id;
	int					way_len;
	int					way_ants;
	int					activation;
	struct s_way_option	*o_next;
	struct s_ways		*next;
}						t_ways;

void					multiple_ways(t_way *way, t_ways **ways, t_data data);
t_ways					*find_to_add_the_full_path(t_ways **ways, int search);
void					ways_len(t_ways **ways);
void					d1(t_data data, t_ways *ways, int argc, char **argv);
int						q_of_act_w(t_ways *ways);
void					ft_init_len(int *len, t_ways *ways);
void					ft_init_way(int *way, int len);
void					ways_1(t_data data, t_ways *ways, int *way, int *len);
void					way_2(int *ants_quantity, int *way, int *len, int *buf);
void					ft_update_the_ways_data(t_ways *ways, int *way);

/*
**-----------------------------------------   bonus  ---------------------------
*/

void					activate_ways(t_ways **ways, t_data data);
void					ft_detect_bonus_adm(char **argv);
void					ft_detect_bonus_ways(char **a, t_ways *w, t_data d);
int						ft_detect_bonus_activation(char **argv);
int						ft_detect_sounds(char **argv);
int						ft_detect_colors(char **argv);
void					ft_print_ants_distributed(t_ways *ways);
void					ft_color_set(t_ways *ways);
void					moves(t_ways *ways);
void					we_have_ended(t_ways *ways);
void					push(t_way_option **head_ref, int new_ant);
void					ft_add_ant_nodes_to_the_ways(t_ways *ways);

#endif

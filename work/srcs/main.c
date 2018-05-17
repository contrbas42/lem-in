/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:49:44 by otimofie          #+#    #+#             */
/*   Updated: 2018/05/13 17:20:19 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	ft_print_lg(t_vertex *vertex) // intermidiaty function;
{
	t_edge *tmp;

	while (vertex)
	{

		ft_printf("%s", vertex->vertex_name);
		ft_printf(" <-%c !->", vertex->visited);

		tmp = vertex->e_next;
		while (tmp)
		{
			ft_printf(" %s", tmp->room_name);
			ft_printf(" <-%c", tmp->visited);

			tmp = tmp->next;
		}
		ft_printf("\n");
		vertex = vertex->v_next;
	}
}

void	ft_print_ways(t_ways *list) // intermidiaty function;
{
	t_way_option *tmp;

	while (list)
	{

		ft_printf("%d -> ", list->way_id);

		tmp = list->o_next;
		while (tmp)
		{
			if (!tmp->way)
				ft_printf("node->a:%d", tmp->ant_number);
			else
				ft_printf("v:%s->a:%d", tmp->way->node_id, tmp->ant_number);
			if (tmp->next != NULL)
				ft_printf("%s", " - ");
			tmp = tmp->next;
		}
		ft_printf(" | way len == %d", list->way_len);
		ft_printf(" | way ants == %d;\n", list->way_ants);
		list = list->next;
	}
}

void push(t_way_option **head_ref, int new_ant)
{
    t_way_option* new_node;

    new_node = (t_way_option*) malloc(sizeof(t_way_option));
  
    new_node->ant_number  = new_ant;
    new_node->node_id  = "tmp";
    new_node->way = *head_ref;
    new_node->way_vertex = 0;
    new_node->color_id = 1;
    new_node->next = *head_ref;
    (*head_ref) = new_node;
}

void	ft_add_ant_nodes_to_the_ways(t_ways *ways)
{
	int i;
	int ants_in_a_way;
	t_way_option **opt;

	i = 1;
	while (ways)
	{
		ants_in_a_way = ways->way_ants;
		opt = &(ways->o_next);
		while (ants_in_a_way)
		{
			push(opt, i++);
			ants_in_a_way--;
		}
		ways = ways->next;
	}
}

void	ft_color_set(t_ways *ways)
{
	t_way_option *opt;
	int i;

	while (ways)
	{
		i = 1;
		opt = ways->o_next;
		while (opt)
		{
			if (opt->way_vertex != 1)
			{
				opt->color_id = i++;
				if (i > 7)
					i = 1;
			}
			opt = opt->next;
		}

		ways = ways->next;
	}
	ft_printf("\n");
}

void	one_move(t_ways *ways)
{
	t_ways *_ways = ways;
	t_way_option *opt;
	while (_ways)
	{
		if (_ways->way_ants)
		{
			opt = _ways->o_next;
			while (opt)
			{
				if (opt->way)
					opt->way = opt->way->next;
				opt = opt->next;
			}
		}
		_ways = _ways->next;
	}
}

void	we_have_ended(t_ways *ways)
{
	int i;
	int j;
	t_way_option *general_opt;
	t_way_option *separate_opt;

	i = 0;
	j = 0;
	while (ways)
	{
		if (ways->way_ants != 0)
		{
			general_opt = ways->o_next;
			separate_opt = ways->o_next;
			while (general_opt)
			{
				i++;
				general_opt = general_opt->next;
			}
			while (separate_opt)
			{
				if (!separate_opt->way)
					j++;
				separate_opt = separate_opt->next;
			}
			if (i == j)
				ways->way_ants = 0;
		}
		ways = ways->next;
	}
}

int		check_ants(t_ways *ways)
{
	while (ways)
	{
		if (ways->way_ants != 0)
			return (1);
		ways = ways->next;
	}
	return (0);
}

void	ft_color_selector(int id)
{
	if (id == 1)
		ft_putstr(GREY);
	else if (id == 2)
		ft_putstr(RED);
	else if (id == 3)
		ft_putstr(GREEN);
	else if (id == 4)
		ft_putstr(YELLOW);
	else if (id == 5)
		ft_putstr(BLUE);
	else if (id == 6)
		ft_putstr(MAGENTA);
	else if (id == 7)
		ft_putstr(CYAN);
}

void	print_moves(t_ways *ways)
{
	t_way_option *opt;

	while (ways)
	{
		opt = ways->o_next;
		while (opt)
		{
			if (opt->way && opt->way->way_vertex == 1)
			{
				ft_color_selector(opt->color_id);
				ft_printf("L%d-%s ", opt->ant_number, opt->way->node_id);
				ft_printf("%s", RESET);

			}
			opt = opt->next;
		}
		ways = ways->next;
	}
}

void	moves(t_ways *ways)
{
	while (check_ants(ways))
	{
		one_move(ways);
		print_moves(ways);
		ft_printf("\n");
		we_have_ended(ways);
	}
}

int			ft_detect_bonus_ways_activation(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-ways_select"))
			return (1);
		i++;
	}
	return (0);
}

int			ft_detect_sounds(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], "-sounds"))
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_ants_distributed(t_ways *ways)
{
	ft_printf("------------------------------------------------------------\n");
	while (ways)
	{

		ft_printf("way -> %d, ants -> %d.\n", ways->way_id, ways->way_ants);
		ways = ways->next;
	}
	ft_printf("------------------------------------------------------------\n");
}




int		main(int argc, char **argv)
{
	t_init		*initial_data;
	t_vertex	*graph;
	t_way		*way;
	t_ways		*ways;
	t_data		data;

	ft_init(&initial_data, &graph, &data);
	(ft_detect_sounds(argv)) ? data.sounds = 1 : 0;
	ft_validation(&initial_data);
	ft_to_start(&initial_data);
	(ft_detect_input(initial_data)) ? ft_print_ll(initial_data) : ft_error();
	ft_build_vertex_structure(initial_data, &graph);
	ft_build_edge_structure(initial_data, graph);
	ft_add_data_to_graph(initial_data, &data);
	bfs(data, graph, &way);
	//
	(!way) ? ft_error() : reverse(&way);
	multiple_ways(way, &ways, data);
	(argc) ? ft_detect_bonus_ways(argv, ways) : 0 ;
	d1(data, ways, argc, argv);
	ft_add_ant_nodes_to_the_ways(ways);
	(ft_detect_bonus_ways_activation(argv)) ? ft_print_ants_distributed(ways) : 0 ;
	ft_color_set(ways);
	moves(ways);
	(argc) ? ft_detect_bonus_adm(argv) : 0 ;
	return (0);
}

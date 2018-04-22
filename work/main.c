/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 12:49:44 by otimofie          #+#    #+#             */
/*   Updated: 2018/04/18 12:49:46 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error_handler(int read_detector)
{
	if (read_detector == 0)
		ft_printf("%s\n", "ERROR: READING ANTS");
	else if (read_detector == 1)
		ft_printf("%s\n", "ERROR: READING ROOMS");
	else if (read_detector == 2)
		ft_printf("%s\n", "ERROR: READING LINKS");
}

int		ft_ant_check(char *str, int *read_detector) // add linked list methods;
{
	int		i;

	i = 0;
	if (str[0] == '#' && str[1] == '#' && (!ft_strequ(str, "##start") && !ft_strequ(str, "##end")))
		// ft_build(... , correspondent define);
		return (1);
	else if (str[0] == '#' && str[1] != '#')
	{
		// ft_build(... , correspondent define);
		ft_printf("%s\n", "create a linked list node for comments"); // reaplace with linked list building function;
		return (1);
	}
	else
	{
		if (!ft_strlen(str) || ft_strlen(str) < 1 || ft_strlen(str) > 10)
			return (0);
		while (i < (int)ft_strlen(str))
			if (ft_isdigit(str[i]) && ft_atoi(&str[0]) != 0)
				i++;
			else
				return (0);
		// ft_build(... , correspondent define);
		ft_printf("%s\n", "create a linked list node for ants data"); // reaplace with linked list building function;
		*read_detector = 1;
		return (1);
	}
}

int		ft_detect_command(char *str, int *command_detector)
{
	if (str[0] == '#' && str[1] == '#' && ft_strequ(str, "##start") && command_detector[1] == 0)
	{
		// ft_printf("%d\n", command_detector[1]);
		// ft_printf("%d\n", command_detector[2]);
		command_detector[0] = 1;
		command_detector[1] = 1;
		return (1);
	}
	else if ((str[0] == '#' && str[1] == '#') && ft_strequ(str, "##end") && command_detector[2] == 0)
	{
		// ft_printf("%d\n", command_detector[1]);
		// ft_printf("%d\n", command_detector[2]);
		command_detector[0] = 2;
		command_detector[2] = 1;
		return (1);
	}
	else if ((str[0] == '#' && str[1] == '#') && (!ft_strequ(str, "##start") && !ft_strequ(str, "##end")))
		return (1);
	return (0);
}

int		ft_find_space_is_correct_quantity(char *str)
{
	int i;
	int s_general;
	int s_inline;

	i = 0;
	s_general = 0;
	s_inline = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			s_general++;
		else if (str[i] != ' ' && str[i - 1] == ' ')
			s_inline++;
		i++;
	}
	if ((s_general == s_inline) && s_general == 2)
			return (1);
	return (0);
}

int		ft_room_validity_aspects(char *str)
{
	char	**array;
	int		array_size;	

	if (!(array = ft_strsplit(str, ' ')))
		return (0);
	array_size = ft_2d_arr_size(array);
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end")) // command was repeated;
		return (0);
	else if (array_size == 1 && str[0] == '#' && str[1] != '#') // line is a comment;
		return (2);
	else if ((!ft_strequ(str, "##start") && !ft_strequ(str, "##end"))
				 && (str[0] == '#' && str[1] == '#')) // unvalid command can be saved;			
		return (2);
	else if (array_size != 3) // not a valid line -> not sufficient data;
		return (0);
	else if (ft_str_find_chr(array[0], '-')) // i really do not like if the room contains '-';
		return (0);
	else if (array[0][0] == '#' || array [0][0] == 'L') // unvalid room <- forbidden chars;
		return (0);
	else if (!ft_isposint(array[1]) || !ft_isposint(array[2]) || !ft_find_space_is_correct_quantity(str) ) // unvalid line <- wrong data, have to be a positive int values;|| !ft_find_space_is_correct_quantity(str)
		return (0);
	// if (!room is unique) 
	// 		return (0);
	// free array;
	return (1);
}

int		ft_alpha_and_omega(int *command_detector)
{
	if (command_detector[1] && command_detector[2])
		return (1);
	return (0);
}

int		ft_check_rooms(char *str, int *read_detector, int *command_detector) // add linked list methods;
{
	if (command_detector[0] == 0 && ft_detect_command(str, command_detector))
	{
		// add linked list stuff -> command/invalid command/comment;
		ft_printf("%s\n", "command has been detected");
		return (1);
	}
	else if (command_detector[0] == 1 && ft_room_validity_aspects(str)) //ft_check_rooms_validity(str) - valid room or a comment; return 2 if ti was a comment
	{
		// add linked list stuff -> start;
		ft_printf("%s\n", "command has been detected and the start line is valid");
		command_detector[0] = 0; // maybe i`ll have to add it to the linked list function
		return (1);
	}
	else if (command_detector[0] == 2 && ft_room_validity_aspects(str)) //ft_check_rooms_validity(str) - valid room 
	{
		// add linked list stuff -> end;
		ft_printf("%s\n", "command has been detected and the end line is valid");
		command_detector[0] = 0; // maybe i`ll have to add it to the linked list function
		return (1);
	}
	else if (command_detector[0] == 0 && ft_room_validity_aspects(str)) //ft_check_rooms_validity(str) - valid room or a comment: unvalid command or comment or valid rooms == o.k.;
	{
		// add linked list stuff -> the correspondent room;
		return (1);
	}
	else if (command_detector[0] == 0 && !ft_room_validity_aspects(str))
	{
		// 1. check if we have start and end;
		// 2. check if the link is valid
		// 3. two flags regarding the validity of the room and the link;
		if (ft_alpha_and_omega(command_detector))
			ft_printf("%s\n", "Maybe we have a link ?");
		*read_detector = 2;
		// return (0);
		// add data tp list;
	}
	return (0); // will return false if the next line is not valid room;
}

void	ft_validation(void)
{
	int 	read_detector; // add to the array of flags maybe
	int		validity_detector; // add to the array of flags maybe
	int		command_detector[3]; 
	char	*line;

	//refactor with bitwise operations;
	read_detector = 0; //add to an array;

	command_detector[0] = 0;
	command_detector[1] = 0;
	command_detector[2] = 0;

	while (get_next_line(0, &line) == 1)
	{
		if (read_detector == 0)
			validity_detector = ft_ant_check(line, &read_detector);
		else if (read_detector == 1)
			validity_detector = ft_check_rooms(line, &read_detector, command_detector);
		// else if (initial_data_set->read_detector == 2)
		// 	...
		if (validity_detector == 0)
		{
			ft_error_handler(read_detector);
			break ;
		}
		// if no links -> exit(0);
	}
	ft_printf("read_detector -> %d\n", read_detector);
}

int		main(void)
{
	// char **array = ft_strsplit("1--1", '-');

	// ft_printf("%s\n", array[0]);
	// ft_printf("%s\n", array[1]);
	// ft_printf("%s\n", array[2]);
	// ft_printf("%s\n", array[3]);
	// ft_printf("%s\n", array[1]);
	//declaration of structure to store the initial data for the validator;
	//declare here a structure to save the valid lines;

	ft_validation(); //validation of the initial data set;
	// ft_buid_graph_and_data();
	// ft_printf("Read status -> %d\n", initial_data_set.read_detector);
	return (0);
}

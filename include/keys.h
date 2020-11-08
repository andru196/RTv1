/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 23:10:33 by andru             #+#    #+#             */
/*   Updated: 2020/10/29 23:21:01 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__

#  define PP
#  define NUM_1	18
#  define NUM_2	19
#  define NUM_3	20
#  define NUM_4	21
#  define NUM_5	22
#  define NUM_6	23
#  define NUM_7	24
#  define NUM_ESC	53
#  define NUMPAD_6	88
#  define NUMPAD_5	87
#  define NUMPAD_7	89
#  define NUM_S	1
#  define NUM_Q	12
#  define RED 2
#  define BLUE 0
# else
#  define PP ++
#  define NUM_1 49
#  define NUM_2 50
#  define NUM_3 51
#  define NUM_4 52
#  define NUM_5 53
#  define NUM_6 45
#  define NUM_7 55
#  define NUM_ESC	65307
#  define NUMPAD_6	88
#  define NUMPAD_5	87
#  define NUM_S	115
#  define NUM_Q	113
#  define RED 0
#  define BLUE 2
# endif


#  define ARROW_L 65361
#  define ARROW_U 65362
#  define ARROW_R 65363
#  define ARROW_D 65364

#  define NUM_PLUS 65451
#  define NUM_MINS 65453


#endif
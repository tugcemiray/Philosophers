# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tukaraca <tukaraca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 01:52:24 by tugcemiraya       #+#    #+#              #
#    Updated: 2025/07/26 19:31:34 by tukaraca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread

SRCS		= main.c \
			  check_args.c \
			  init.c \
			  routine.c \
			  monitor.c \
			  utils.c \
			  end_sim.c \

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

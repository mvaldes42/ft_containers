# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 13:56:37 by mvaldes           #+#    #+#              #
#    Updated: 2022/04/29 15:02:18 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

.PHONY: all clean fclean re
.SILENT: all clean fclean re

CC = clang++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3

SRCS = tests/main.cpp

OBJS = ${SRCS:.cpp=.o}

$(NAME):	$(OBJS) Makefile
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)
	
%.o:	%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm tests/*.o

fclean:		clean
			rm -f $(NAME)

re:			fclean all

#	make SRCS='tests/ft_main.cpp'; ./a.out > ft ; make flcean
#	make SRCS='tests/std_main.cpp'; ./a.out > std ; make fclean
#	diff ft std

#	make SRCS='tests/speedtest.cpp'; ./a.out 10 ; make fclean
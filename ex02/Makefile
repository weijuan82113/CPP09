# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 19:09:07 by yokamura          #+#    #+#              #
#    Updated: 2024/08/11 16:35:12 by yokamura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe
SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:%.cpp=%.o)
CXX	 = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

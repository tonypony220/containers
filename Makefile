SRCS	=   main.cpp
OBJS	=	${SRCS:.cpp=.o}
CFLAGS	=   -O0 -g #-fsanitize=address # -fsanitize=undefined -Wall -Wextra -Werror --std=c++98 -g 
CC		=	clang++
RM		=	-rm	-f
HEAD	=   vector.hpp algobase.hpp iter.hpp map.hpp pair.hpp utils.hpp tree.hpp stack.hpp
NAME	=	out

%.o: %.cpp $(HEAD)
	$(CC) ${CFLAGS} -c $< -o ${<:.cpp=.o}

${NAME}: ${OBJS}
		$(CC) ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean re

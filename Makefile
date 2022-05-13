SRCS	=   main.cpp tree.cpp
SRCSSUB	=   main_subject.cpp tree.cpp #main.cpp
OBJS	=	${SRCS:.cpp=.o}
OBJSSUB	=	${SRCSSUB:.cpp=.o}
CFLAGS	=   -O0 -g -Wall -Wextra -Werror -Wmacro-redefined --std=c++98 # -g -fsanitize=address -fsanitize=undefined 
CC		=	clang++
RM		=	-rm	-f
HEAD	=   vector.hpp algobase.hpp iter.hpp map.hpp pair.hpp utils.hpp tree.hpp stack.hpp
NAME	=	out

%.o: %.cpp $(HEAD)
	$(CC) ${CFLAGS} -c $< -o ${<:.cpp=.o}

${NAME}: ${OBJS}
		$(CC) ${CFLAGS} ${OBJS} -o ${NAME}
main: ${OBJS}
		$(CC) ${CFLAGS} ${OBJS} -o ${NAME}

ft: ${OBJSSUB}
		$(CC) ${CFLAGS} ${OBJSSUB} -o ${NAME}
std: ${OBJSSUB}
		$(CC) ${CFLAGS} -DSTD ${OBJSSUB} -o ${NAME}
diff: 
		@ echo " making diff...... "
		@ echo " \
				#!/bin/bash \n\
				$(CC) ${CFLAGS} ${SRCSSUB} -o ${NAME} \n\
				./${NAME} 4 > ft \n\
				$(CC) ${CFLAGS} -DSTD ${SRCSSUB} -o ${NAME} \n\
				./${NAME} 4 > std \n\
				diff ft std" > file.sh
		@ chmod 777 file.sh
		@ sh file.sh
		@ rm ft std file.sh
		@ echo " done "
		

all: ${NAME}

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean re

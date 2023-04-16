SRC = test_main \

SRCS = $(addsuffix .cpp, ${SRC})

CC	= c++

FLAGS1 = -Wall -Wextra -Werror -std=c++98 
FLAGS2 = -Wall -Wextra -Werror  

NAME1 = execft 

NAME2 = execstd 


OBJS = ${SRCS:.cpp=.o}


general:
	make FT
	make STD

FT:	clean
	$(CC) -c $(FLAGS1)  -D ns=ft $(SRCS) 
	$(CC) ${FLAGS1}  ${OBJS} -o ${NAME1}


STD:	clean
	$(CC) -c ${FLAGS2} -D ns=std $(SRCS)
	$(CC) ${FLAGS2}  ${OBJS} -o ${NAME2}

clean:
	rm -f ${OBJS}

fclean:		clean	
		rm -f ${NAME1}
		rm -f ${NAME2}

re: fclean



.PHONY: clean fclean re


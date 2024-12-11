NAME	=	RPN

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INC_DIR	=	inc/

SRCS	=	main.cpp\
			RPN.cpp

OBJS	=	$(SRCS:.cpp=.o)

SRC_PATH	=	$(addprefix $(SRC_DIR), $(SRCS))
OBJ_PATH	=	$(addprefix $(OBJ_DIR), $(OBJS))

CC			=	c++

CFLAGS		=	-Wall -Werror -Wextra -std=c++98

all	:	$(NAME)

$(NAME) :	$(OBJ_PATH)
			$(CC) $(CFLAGS) $(OBJ_PATH) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp $(INC_DIR)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean	:
			rm -rf $(OBJ_DIR)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
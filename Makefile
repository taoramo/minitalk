CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -o $@
SERVER_NAME = server 
SERVER_SRCS = srcs/server.c $(LIBFT) 
CLIENT_NAME = client
CLIENT_SRCS = srcs/client.c $(LIBFT)
SERVER_BONUS_NAME = server_bonus
SERVER_BONUS_SRCS = srcs/server_bonus.c $(LIBFT)
CLIENT_BONUS_NAME = client_bonus
CLIENT_BONUS_SRCS = srcs/client_bonus.c $(LIBFT)
AR = ar rcs
LIBFT = libft/libft.a
INCLUDES = ./incs/

OBJS = $(SRCS:.c=.o)
all: $(SERVER_NAME) $(CLIENT_NAME)

bonus : $(SERVER_BONUS_NAME) $(CLIENT_BONUS_NAME)

$(SERVER_BONUS_NAME) : $(SERVER_BONUS_SRCS)
	cc $(CFLAGS) $(SERVER_BONUS_SRCS) -o $(SERVER_BONUS_NAME)

$(CLIENT_BONUS_NAME) : $(CLIENT_BONUS_SRCS)
	cc $(CFLAGS) $(CLIENT_BONUS_SRCS) -o $(CLIENT_BONUS_NAME)

$(SERVER_NAME) : $(SERVER_SRCS)
	cc $(CFLAGS) $(SERVER_SRCS) 

$(CLIENT_NAME) : $(CLIENT_SRCS)
	cc $(CFLAGS) $(CLIENT_SRCS) 

$(OBJS) : $(LIBFT)
	cc $(CFLAGS) $(SRCS) -I $(INCLUDES) 

$(LIBFT):
	make -C ./libft/
clean:
	make -C ./libft/ clean

fclean: clean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME)
	make fclean -C ./libft/

re: fclean all

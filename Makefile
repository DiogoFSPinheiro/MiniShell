MAKEFLAGS += -s

CC = cc -g 

CFLAGS = -Wall -Wextra -Werror

#CFLAGS += -fsanitize=thread
#CFLAGS += -fsanitize=address 

NAME = minishell

SRCS = main.c tester.c syntax.c utils.c utils2.c utils3.c token_utils.c ft_quotes_split.c free_funcs.c \
	type_check.c syntax2.c expand.c build_commands.c create_env.c redirections.c heredoc.c \
	heredoc_utils.c utils4.c utilc5.c tokens.c fds_signals.c execute_utils.c fds_signals_utils.c \
	pedro_files/ft_pwd.c pedro_files/ft_echo.c\
	pedro_files/ft_built_in.c pedro_files/ft_cd.c\
	pedro_files/ft_env.c pedro_files/ft_built_errors.c \
	pedro_files/ft_execute_m.c pedro_files/ft_execute.c \
	pedro_files/utils.c pedro_files/ft_unset.c pedro_files/ft_export.c \
	pedro_files/ft_export_utils.c pedro_files/ft_pipes.c pedro_files/ft_exit.c


LIBFT = ./libraries/libft/libft.a
PRINTF = ./libraries/printf/ft_printf.a

# --- COLORS ----------------------------------------------------------------- #
# --- Normal --- #
RED_COLOR              = \033[0;31m
GREEN_COLOR            = \033[0;32m
YELLOW_COLOR           = \033[0;33m
BLUE_COLOR             = \033[0;34m
MAGENTA_COLOR          = \033[0;35m
CYAN_COLOR             = \033[0;36m
WHITE_COLOR            = \033[0;37m
# --- Bold --- #
RED_COLOR_BOLD         = \033[1;31m
GREEN_COLOR_BOLD       = \033[1;32m
YELLOW_COLOR_BOLD      = \033[1;33m
BLUE_COLOR_BOLD        = \033[1;34m
MAGENTA_COLOR_BOLD     = \033[1;35m
CYAN_COLOR_BOLD        = \033[1;36m
WHITE_COLOR_BOLD       = \033[1;37m
# --- Intensed --- #
RED_COLOR_HIGH         = \033[0;91m
GREEN_COLOR_HIGH       = \033[0;92m
YELLOW_COLOR_HIGH      = \033[0;93m
BLUE_COLOR_HIGH        = \033[0;94m
MAGENTA_COLOR_HIGH     = \033[0;95m
CYAN_COLOR_HIGH        = \033[0;96m
WHITE_COLOR_HIGH       = \033[0;97m
# --- Bold-Intensed --- #
RED_COLOR_BOLDHIGH     = \033[1;91m
GREEN_COLOR_BOLDHIGH   = \033[1;92m
YELLOW_COLOR_BOLDHIGH  = \033[1;93m
BLUE_COLOR_BOLDHIGH    = \033[1;94m
MAGENTA_COLOR_BOLDHIGH = \033[1;95m
CYAN_COLOR_BOLDHIGH    = \033[1;96m
WHITE_COLOR_BOLDHIGH   = \033[1;97m
# --- Blinking --- #
RED_COLOR_BLINK        = \033[5;31m
GREEN_COLOR_BLINK      = \033[5;32m
YELLOW_COLOR_BLINK     = \033[5;33m
BLUE_COLOR_BLINK       = \033[5;34m
MAGENTA_COLOR_BLINK    = \033[5;35m
CYAN_COLOR_BLINK       = \033[5;36m
WHITE_COLOR_BLINK      = \033[5;37m
# --- Reset --- #
RESET_COLOR            = \033[0m


GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED		= \033[38;5;196m
RESET 		= \033[0m

#BONUS_SRCS = 

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline
	@echo "$(GREEN)Executable $(NAME) created"
	@echo " /###### /##          /##       /##                               /##"
	@echo "|_  ##_/| ##          | ##      |__/                              | ##"
	@echo "  | ## /######        | ##       /## /##    /## /######   /#######| ##"
	@echo "  | ##|_  ##_/        | ##      | ##|  ##  /##//##__  ## /##_____/| ##"
	@echo "  | ##  | ##          | ##      | ## \  ##/##/| ########|  ###### |__"
	@echo "  | ##  | ## /##      | ##      | ##  \  ###/ | ##_____/ \____ ##"
	@echo "/######|  ####/       | ########| ##   \  #/  |  ####### /######/ /##"
	@echo "|______/ \___/        |________/|__/    \_/    \_______/|_______/ |__"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⢿⣿⣿⢿⣿⡿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣉⠁⢈⣉⠁⠈⠛⠃⠘⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣦⣾⣿⡇⣼⣿⣧⣰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿ o ⣿⣿⣿ o ⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀  "
	@echo "⠀⠀⠀⠀⠀⢠⡄⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⣤⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⢸⡷⠶⠦⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠴⠶⣿⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠘⠃⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⠟⢀⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⣠⡀⠺⣿⣷⣦⣉⠛⠛⠛⠋⣡⣴⣿⣿⣿⣶⣤⡀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⢀⣾⣿⠟⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣾⣿⣿⣿⣿⣷⠄⠀⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⣿⣯⣶⣶⡀⠉⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⠛⢻⣿⣿⣥⣤⡈⠻⠛⣻⣿⣿⡟⠛⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣏⣠⡀⢿⣿⣿⡇⠀⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠉⠉⠉⠉⠀⠈⠉⠉⠉⠉⠉⠉⠉⠀⠉⠉⠁⠀⠉⠉⠉⠉⠀⠀⠀⠀$(RESET)"

#bonus: $(BONUS_OBJS) $(OBJS)
#	ar rc $(NAME) $(BONUS_OBJS) $(OBJS)  mete no clean -> $(BONUS_OBJS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --leak-check=full ./minishell

clean:
	rm -rf $(OBJS) 
	@echo "$(YELLOW)Removing $(NAME) and libraries objects files$(RESET)" 
	cd libraries && cd libft && make clean
	cd libraries && cd printf && make clean

fclean: clean
	rm -rf $(NAME) 
	@echo "$(RED)Removing $(NAME) executable"
	@echo " /###### /##          /#######  /##                 /##"
	@echo "|_  ##_/| ##         | ##__  ##|__/                | ##"
	@echo "  | ## /######       | ##  \ ## /##  /######   /#######"
	@echo "  | ##|_  ##_/       | ##  | ##| ## /##__  ## /##__  ##"
	@echo "  | ##  | ##         | ##  | ##| ##| ########| ##  | ##"
	@echo "  | ##  | ## /##     | ##  | ##| ##| ##_____/| ##  | ##"
	@echo " /######  ####/      | #######/| ##|  #######|  #######"
	@echo "|______/ \___/       |_______/ |__/ \_______/ \_______/"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⢿⣿⣿⢿⣿⡿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣉⠁⢈⣉⠁⠈⠛⠃⠘⠓⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣦⣾⣿⡇⣼⣿⣧⣰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿ x ⣿⣿⣿ x ⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⢠⡄⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⣤⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⢸⡷⠶⠦⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠴⠶⣿⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠘⠃⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⠟⢀⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⣠⡀⠺⣿⣷⣦⣉⠛⠛⠛⠋⣡⣴⣿⣿⣿⣶⣤⡀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⢀⣾⣿⠟⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣾⣿⣿⣿⣿⣷⠄⠀⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⣿⣯⣶⣶⡀⠉⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⠛⢻⣿⣿⣥⣤⡈⠻⠛⣻⣿⣿⡟⠛⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣏⣠⡀⢿⣿⣿⡇⠀⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠉⠉⠉⠉⠀⠈⠉⠉⠉⠉⠉⠉⠉⠀⠉⠉⠁⠀⠉⠉⠉⠉⠀⠀⠀⠀$(RESET)"
	cd libraries && cd libft && make fclean
	cd libraries && cd printf && make fclean


re: fclean all 

.phony: all bonus clean fclean re 

################################# Making librarys #########################
$(LIBFT):
	cd libraries && cd libft && make 
	
$(PRINTF):
	cd libraries && cd printf && make 

	
	
############################## Checking norm and Funcs #####################

PERMITTED_FUNCTIONS    = readline rl_clear_history rl_on_new_line \
                         rl_replace_line rl_redisplay add_history printf \
                         malloc free write access open read close fork wait \
                         waitpid wait3 wait4 signal sigaction sigemptyset \
                         sigaddset kill exit getcwd chdir stat lstat fstat \
                         unlink execve dup dup2 pipe opendir readdir \
                         closedir strerror perror isatty ttyname ttyslot \
                         ioctl getenv tcsetattr tcgetattr tgetent tgetflag \
                         tgetnum tgetstr tgoto tputs

check: all
	@echo "$(CYAN_COLOR)--- Norminette checking ---$(RESET_COLOR)"
	@for file in $(shell find . -name "*.c"); do \
		norminette $$file 1>/dev/null \
		&& echo "$(GREEN_COLOR)✓ $$file: OK$(RESET_COLOR)" \
		|| echo "$(RED_COLOR_BLINK)✗$(RESET_COLOR) $(RED_COLOR)$$file: KO$(RESET_COLOR)"; \
	done
	@echo "$(CYAN_COLOR)--- Forbidden functions checking ---$(RESET_COLOR)"
	@for func in $(shell nm -Puj --without-symbol-versions $(NAME) 2>/dev/null | grep -v '^_'); do \
		echo $(PERMITTED_FUNCTIONS) | tr ',' ' ' | tr ' ' '\n' | grep -v '^$$' | grep $$func > /dev/null; \
		if [ $$? != 0 ]; then \
			echo "$(RED_COLOR_BLINK)✗$(RESET_COLOR) $(RED_COLOR)$$func$(RESET_COLOR)"; \
		else \
			echo "$(GREEN_COLOR)✓ $$func$(RESET_COLOR)"; \
		fi \
	done


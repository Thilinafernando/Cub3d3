CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = mlx/libmlx.a -L/usr/lib/X11 -lXext -lX11 -lm
INCLUDES = -I/usr/include -Ilibft -Iget_next_line -Ilibprintf -Imlx

NAME = cub3d
NAME_BONUS = cub3d_bonus

MLXDIR = mlx/
MLX = $(MLXDIR)libmlx.a

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

PRINTDIR = libprintf/
PRINT = $(PRINTDIR)libftprintf.a

GNL = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c
GNL_OBJECTS = $(addprefix obj/, $(notdir $(GNL_SRC:.c=.o)))

EXECDIR = execution/
EXEC = execution/game_controls.c execution/rendering.c execution/main.c execution/free.c execution/mlxinit.c execution/movement.c execution/ray.c execution/draw_wall.c \
		execution/init_player.c

UTILSDIR = Utils/
UTILS =

PARSDIR = parssing/
PRC = parssing/parsing.c parsing_utils.c parsing_utils1.c parsing_utils2.c parsing_utils3.c parsing_utils4.c

BONUSDIR = bonus/
BONUS = \
	bonus/parssing_bonus/parsingb.c \
	bonus/parssing_bonus/parsing_utilsb.c \
	bonus/parssing_bonus/parsing_utils1b.c \
	bonus/parssing_bonus/parsing_utils2b.c \
	bonus/parssing_bonus/parsing_utils3b.c \
	bonus/parssing_bonus/parsing_utils4b.c \
	bonus/execution_bonus/control_mouse_bonus.c \
	bonus/execution_bonus/control_mouse_bonus_utils.c \
	bonus/execution_bonus/draw_wall_bonus.c \
	bonus/execution_bonus/draw_wall_bonus_utils.c \
	bonus/execution_bonus/draw_weapon_bonus.c \
	bonus/execution_bonus/event_bonus.c \
	bonus/execution_bonus/free_bonus.c \
	bonus/execution_bonus/game_controls_bonus.c \
	bonus/execution_bonus/game_controls_utils_bonus.c \
	bonus/execution_bonus/init_bonus.c \
	bonus/execution_bonus/init_player_bonus.c \
	bonus/execution_bonus/main_bonus.c \
	bonus/execution_bonus/draw_minimap.c\
	bonus/execution_bonus/draw_mini1.c\
	bonus/execution_bonus/draw_mini2.c\
	bonus/execution_bonus/rendering_bonus.c \
	bonus/execution_bonus/ray_bonus.c \
	bonus/execution_bonus/texture_bonus.c \
	bonus/execution_bonus/wall_door_bonus.c \

ALL_SRC = $(PRC) $(EXEC) $(UTILS)
OBJECTS = $(addprefix obj/, $(notdir $(ALL_SRC:.c=.o)))
OBJECT_BONUS = $(addprefix obj/, $(notdir $(BONUS:.c=.o)))

# Build MLX if not already
mlx:
	@if [ ! -f "$(MLX)" ]; then \
        if [ ! -d "$(MLXDIR)" ]; then \
            echo "Cloning MLX..."; \
            git clone https://github.com/42Paris/minilibx-linux.git mlx; \
            rm -rf mlx/.git; \
            echo "Removed .git from mlx/"; \
        fi; \
	    $(MAKE) -C $(MLXDIR); \
    else \
        echo "MLX already built, skipping..."; \
    fi

# Build main project
all: $(NAME)

$(NAME): $(LIBFT) mlx $(OBJECTS) $(GNL_OBJECTS) $(PRINT)
	@bash -c 'tput blink; echo -ne "Compiling Cub3d     \r"; tput sgr0; sleep 0.5; echo "Cub3d is ready to be played!     "'
	@$(CC) $(CFLAGS) $(OBJECTS) $(GNL_OBJECTS) -o $(NAME) $(MLX_FLAGS) $(LIBFT) $(PRINT)

# Bonus target
bonus: $(NAME_BONUS)
	@echo "Bonus build complete: $(NAME_BONUS)"

$(NAME_BONUS): $(LIBFT) mlx $(OBJECT_BONUS) $(GNL_OBJECTS) $(PRINT)
	@$(CC) $(CFLAGS) $(OBJECT_BONUS) $(GNL_OBJECTS) -o $(NAME_BONUS) $(PRINT) $(MLX_FLAGS) $(LIBFT)

# Object compilation rules, flat obj directory, source files in different dirs
obj/%.o: bonus/execution_bonus/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

obj/%.o: bonus/parssing_bonus/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

obj/%.o: parssing/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

obj/%.o: execution/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

obj/%.o: Utils/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

obj/%.o: get_next_line/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# Library builds
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) bonus --quiet
	@$(MAKE) -C $(LIBFTDIR) --quiet

$(PRINT):
	@$(MAKE) -C $(PRINTDIR) --quiet

# Cleanup
clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(MAKE) clean -C $(PRINTDIR)
	@rm -rf obj
	@clear

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(MAKE) fclean -C $(PRINTDIR)
	@rm -rf obj
	@rm -f $(MLXDIR)*.o $(MLXDIR)*.a
	@rm -rf $(NAME) $(NAME_BONUS)
	@clear

re: fclean all

clean_mlx:
	@bash -c 'tput blink; echo -ne "Cleaning MLX     \r"; tput sgr0; sleep 2; echo "MLX Gone!     "'
	@rm -rf $(MLXDIR)

#vall: all clean
#	valgrind --track-origins=yes -q --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./cub3d map.cub

.PHONY: all bonus clean fclean re clean_mlx mlx

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h> 
# define STEP_LINE 0.1
# define STEP_ANGLE 0.05
# define M_PI 3.14159265358979323846


# define WINDOW_W 400
# define WINDOW_H 300

# define VIEW_ANGLE (M_PI / 3)

# include "libft.h"

// # include <X11/keysym.h>
// # include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

#define EXTENSION "Error: Map extension is not valid. Please use \".cub\" extension.\n"
#define OPENFD "Error: Map file descriptor is not valid\n"
#define MALLOC "Error: Allocation failed\n"
#define ID_TXT "Error: Texture id is not valid \n"
#define ID_COLORS "Error: Color id is not valid \n"
#define NUM_RGB "Error: RGB arguments' number invalid, please respect RGB format\n"
#define RGB_COMA_FORMAT "Error: RGB format is not valid because of comas' or arguments' number\n"
#define CHAR_NOT_VALID "Error: Character invalid in the map\n"
#define STARTING_POINT "Error: Starting point not valid\n"
#define TXT_AFTER_MAP "Error: Textures and colors have to be before your map\n"
#define MAP_OPENED "Error: Map is opened\n"
#define MAP_INVALID "Error : No valid map found\n"
#define RGB_SUP "Error: RGB colors are between 0 and 255\n"
#define CLEAN "Error: Informations have to be separated by empty lines, please clean your file\n"


typedef struct s_texture {
    void *img;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    char *addr;
} t_texture;


typedef struct s_image {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_image;

typedef struct s_draw_params {
    float line_height;
    float texture_position;
    float texture_step;
    t_texture *texture;
} t_draw_params;


typedef struct {
    int		map_lines;
	int		map_start;
	int		end_map;
	int		*f_color;
	int		*c_color;
	char	**file;
    char	*path_text[4];
	char	**map;
	char	**new_map;
	int		x_pos;
	int		y_pos;

    int color_ceiling;
    int color_floor;
    int map_height;
    int map_width;
    int temp_j;
    int temp_i;
    float player_x;
    float player_y;
    float player_angle;
    t_texture texture[4];  // Текстуры для N, S, W, E
    void *mlx;  // Экземпляр MiniLibX
    void *win;  // Указатель на окно
    t_image img;  // Изображение для рендеринга
    int textur_index;  // Индекс текущей текстуры
    float textur_shift;   // Смещение в текстуре

} t_data;

// Структура для работы с лучами
typedef struct s_ray {
    float direction_x;
    float direction_y;
    float step_x;
    float step_y;
    float next_vertical_x;
    float next_vertical_y;
    float next_horizontal_x;
    float next_horizontal_y;
    float vertical_distance;
    float horizontal_distance;
    float texture_x; 
    float texture_y;
        int map_x;
    int map_y;
} Ray;

void part_2(t_data *data);
int ft_prepare_texture(t_data *data, float distance, t_draw_params *params);
void ft_draw_column(t_data *data, int x, t_draw_params *params);
void ft_draw_vertical_line(t_data *data, int x, float distance);
void ft_init_vertical_line(t_data *data);
void ft_draw_ceiling_and_floor(t_data *data);
int ft_draw(t_data *data);

void find_player_position(t_data *data);
void ft_resoures_initialisation(t_data *data);
void ft_param_initialisation(t_data *data);

void ft_move(t_data *data, int direction);
int ft_key(int keycode, t_data *data);

float trace_ray(t_data *data, float angle);
float handle_horizontal_intersection(t_data *data, Ray *ray);
float handle_vertical_intersection(t_data *data, Ray *ray);
float handle_check(t_data *data, Ray *ray, int flag);
void calculate_next_intersection(t_data *data, Ray *ray);
void initialize_ray(t_data *data, Ray *ray, float angle);


int ft_destroy_exit(t_data *data);
int get_sign(float value);


// MAIN
void	init_data(t_data *data);
void	parsing_cub(char *argv);

// PARSING
bool	is_valid_data_extension(char *argv);
void	copy_cub_file(char *argv, t_data *data);
void	where_is_the_map(t_data *data, char **file, int *map_lines);
void	save_map(t_data *data, char **file, char ***map, int *map_lines);
void	check_starting_point(char **map, int map_lines, t_data *data, int j);

// TEXTURES AND COLORS
char	*find_textures_paths(char *file, t_data *data);
void	extract_textures(t_data *data);
int		*find_rgb_colors(char *file, int *colors, int k, t_data *data);
void	extract_valid_colors(t_data *data);
bool	are_colors_and_textures_before_map(t_data *data, int j);


// PARSING MAP
void	parsing_map(t_data *data);
char	*create_first_and_bottom_lines(int max_len, char *x_lines, t_data *data);
char	*fill_line(char *map, int len, int i);
char	**create_new_map(t_data *data, int max_len, char **new_map, char *x_lines);
bool	is_map_closed(char **map, int len, int rows, int i);

// CLEAN FILE
bool	line_is_not_texture(t_data *data, int i, int *checker);
bool	line_is_not_color(t_data *data, int i, int *checker);
bool	line_is_not_empty(t_data *data, int i);
bool	file_is_clean(t_data *data);
void	file_end_is_clean(t_data *data);


// UTILS
void	print_char_tab(char **tab);
void	err(t_data *data, char *str);
int 	count_lines_fd(char *argv);
int 	map_line_max_lenght(char **map);
bool	is_valid_char(char c);

// UITILS 2
void	check_colors(char *file, t_data *data);
bool	is_starting_point(char **map, int i, int j);
void	color_is_valid(int *color, t_data *data);
int		skip_whitespaces(char **save, int i, int j, int *start);

//FREE
void	free_char_tab(char **tab);
void	free_all(t_data *data);
void	error_color(int *colors, char **save, t_data *data);


#endif

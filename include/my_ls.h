// ------- include ------- //
#include <sys/stat.h> // include: stat, lstat
#include <dirent.h> // include: opendir, readdir, closedir

#include "./utils.h" // the utils

// ------- function ------- //

// ----- option ----- //

// --- sort --- //
int* sort_folder_by_lexical(char**, int*, int);
void dispach_sort_file(array_file_t*, char);

// --- get --- //

// - main var - //
main_var_t* get_main_var(char**, int);

// - flags - //
char get_display_caract(flag_t*);
flag_t* get_flags(main_var_t*, char**);

// - folder - //
void folder_gestion(flag_t*, char*, int);

// --- print --- //
void print_array(array_file_t*, char*, char*, char, int, int, int);

// ----- my_ls.c ----- //

void my_ls(main_var_t*, flag_t*, char**);
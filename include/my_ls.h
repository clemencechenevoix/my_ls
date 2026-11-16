// ------- include ------- //
#include <sys/stat.h> // include: stat, lstat
#include <dirent.h> // include: opendir, readdir, closedir

#include "./utils.h" // the utils

// ------- function ------- //

// ----- option ----- //

// --- sort --- //
void sort_file_by_time(file_t**, int*, int);
void sort_file_by_size(file_t**, int*, int);
void sort_file_by_lexical(file_t**, int*, int);
int* sort_folder_by_lexical(char**, int*, int);
void dispach_sort_file(array_file_t*, char);

// --- get --- //

// - main var - //
array_file_t* get_main_file_array_file(char**, int*, int);
void get_main_var_int_array(main_var_t*, char**, int);
main_var_t* get_main_var(char**, int);

// - flags - //
char get_display_caract(flag_t*);
int get_flags_in_string(flag_t*, char*, char*, char*, char*, int);
void get_flags_in_array(main_var_t*, flag_t*, char**, char*, char*, char*);
flag_t* get_flags(main_var_t*, char**);

// - folder - //
char* get_path(char*, char*);
int get_nb_entry_folder(char*);
int get_folder_info(array_file_t*, char*);
array_file_t* get_files(char*);

// --- print --- //
void print_array(array_file_t*, char*, char*, char, int, bool, bool);

// --- gestion --- //
void folder_gestion(flag_t*, char*, bool);

// ----- my_ls.c ----- //

void my_ls(main_var_t*, flag_t*, char**);
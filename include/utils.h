// ----- include ----- //
#include <stdio.h> // include: printf, fopen
#include <stdlib.h> // include: malloc, free

// ----- structure ----- //

typedef struct struct_flag_s {
    char* column;
    char sort;
    char display;
    int way;
    int status;
} flag_t;

typedef struct struct_file_s {
    char* name;
    long time;
    int size;
} file_t;

typedef struct struct_array_file_s {
    file_t** array;
    int* array_index_sorted;
    int size;
    int length;
    int status;
} array_file_t;

typedef struct struct_main_var_s {
    int* flags;
    int* files;
    int* folder;
    int length_flags;
    int length_files;
    int length_folder;
    int status;
} main_var_t;

// ----- function ----- //

// --- utils.c --- //
int my_length(char*);
void my_strcpy(char*, char*);
char* my_strcmp(char*, char*);
void my_memset(char*, char, int);
void append_int_at_index(int*, int, int, int);

// - check - //
int check_if_char_in_string(char*, char);
int check_if_file_exist(char*);

// - free - //
void free_struct_main_var(main_var_t*);
void free_struct_flags(flag_t*);
void free_struct_files(array_file_t*);
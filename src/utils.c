// ----- include ----- //
#include "../include/utils.h"

// ----- function ----- //

/** 
* @brief count the number of characters in a string
* @param char* str (a word or a sentence)
* @return int (the length of the string)
*/
int my_length(char* string) {
    int index = 0;
    while (string[index] != '\0') {
        index += 1;
    }
    return index;
}

/** 
* @brief copy string_copy into string_var
* @param char* string_var (a malloc buffer with enough place)
* @param char* string_copy (the string to copy)
* @return void
*/
void my_strcpy(char* string_var, char* string_copy) {
    int index = 0;
    int length = my_length(string_copy);
    while (index < length) {
        string_var[index] = string_copy[index];
        index += 1;
    }
    string_var[index] = '\0';
    return;
}

/** 
* @brief compare two string and return the smallest
* @param char* string1 (a malloc buffer with enough place)
* @param char* string2 (the string to copy)
* @return char* the smallest string
*/
char* my_strcmp(char* string1, char* string2) {
    int index = 0;
    int length = my_length(string1);
    int length2 = my_length(string2);
    char* return_string = string1;
    if (length > length2){
        length = length2;
        return_string = string2;
    }

    while (index < length) {
        if (string1[index] < string2[index]){
            return string1;
        } else if (string2[index] < string1[index]){
            return string2;
        }
        index += 1;
    }
    return return_string;
}

/** 
* @brief replace all character of the given string by a given character
* @param char* string
* @param char charact
* @param int length (the length of the string)
* @return void
*/
void my_memset(char* string, char charact, int length) {
    int index = 0;
    while (index < length) {
        string[index] = charact;
        index += 1;
    }
}

/** 
* @brief add a int in the given int* at a given index
* @param index* index_array (the array need to have enough space in the malloc to add a new entitie)
* @param int length (length of index_array)
* @param int integer (the int to add in the array)
* @param int index_add (index of the add integer)
* @return void
*/
void append_int_at_index(int* index_array, int length, int integer, int index_add) {
    if (length == 0 || length == index_add) {
        index_array[length] = integer;
        return;
    }

    int index = length - 1;
    while (index > index_add) {
        index_array[index + 1] = index_array[index];
        index -= 1;
    }
    index_array[index + 1] = index_array[index];
    index_array[index] = integer;
}

// --- check --- //

/** 
* @brief search if the given character is in the given string
* @param char* string
* @param char charact
* @return int 1 if found, else 0
*/
int check_if_char_in_string(char* string, char charact) {
    int index = 0;
    while (index < my_length(string)) {
        if (string[index] == charact) {
            return 1;
        }
        index += 1;
    }
    return 0;
}

/** 
* @brief verify if a file with the given name exist
* @param char* filename
* @return int 1 if yes, 0 if not
*/
int check_if_file_exist(char* filename) {
    FILE *file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }

    return 0;
}

// --- free --- //

/**
* @brief free the struct main var and its composants
* @param main_var_t* struct_main_var (the struct with the different index of the informations given to ./my_ls)
* @return void
*/
void free_struct_main_var(main_var_t* struct_main_var) {
    if (struct_main_var->status == 0) {
        free(struct_main_var->flags);
        free(struct_main_var->folder);
        free(struct_main_var->files);
    }
    free(struct_main_var);
    return;
}

/**
* @brief free the struct flags and its composants
* @param flag_t* struct_flag (the structure containing the different flags)
* @return void
*/
void free_struct_flags(flag_t* struct_flag) {
    free(struct_flag->column);
    free(struct_flag);
    return;
}

/**
* @brief free the array files and its composants
* @param array_file_t* struct_file (the struct with the different informations of the files)
* @return void
*/
void free_struct_files(array_file_t* struct_file) {
    int index = 0;

    if (struct_file->status != -1) {
        while(index < struct_file->length) {
            free(struct_file->array[index]->name);
            free(struct_file->array[index]);
            index += 1;
        }   
        free(struct_file->array_index_sorted);
        free(struct_file->array);
    }
    free(struct_file);
}

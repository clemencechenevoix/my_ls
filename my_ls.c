// --- include --- //
#include <stdio.h> // include: printf
#include <stdlib.h> // include: malloc, free
//#include <sys/stat.h> // include: files stats function
#include <unistd.h>
#include <dirent.h> // include: opendir, readdir, closedir

// --- structure --- //

typedef struct StructFile {
    char* name;
    // TYPE time;
} File;

typedef struct StructArrayFiles {
    File** array;
    int length;
} ArrayFiles;

typedef struct StructFlags {
    char* column;
    char sort;
    int nb_argv;
    int status;
} Flags;

// --- function --- //

int my_length(char* string) {
    int index = 0;
    while (string[index] != '\0') {
        index += 1;
    }
    return index;
}

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

int is_char_in_string(char caract, char* string) {
    int index = 0;
    while (index < my_length(string)) {
        if (string[index] == caract) {
            return 1;
        }
        index += 1;
    }
    return 0;
}

// --- main --- //
int main(int argc, char **argv){

}
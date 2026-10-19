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

// --- main --- //
int main(int argc, char **argv){

}
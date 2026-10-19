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
    int status;
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

// - get - //

int get_nb_entry_folder(char* folder_name){
    DIR *directory;
    struct dirent *entry;
    int nb_files = 0;

    directory = opendir(folder_name);
    if(directory == NULL){
        printf("%s\n\n", folder_name);
        return -1;
    }
    while((entry = readdir(directory)) != NULL) {
        nb_files += 1;
    }
    if(closedir(directory) == -1){
        printf("Error closing directory\n");
        return -2;
    }
    return nb_files;
}

int get_folder_info(char* folder_name, ArrayFiles* struct_file) {
    DIR* directory;
    struct dirent* entry;
    int index = 0;
    
    directory = opendir(folder_name);
    if(directory == NULL){
        printf("Error openning directory\n");
        return 0;
    }

    while((entry = readdir(directory)) != NULL) {
        struct_file->array[index]= malloc(sizeof(File) * 1);
        struct_file->array[index]->name = malloc(sizeof(char) * (my_length(entry->d_name) + 1));
        my_strcpy(struct_file->array[index]->name, entry->d_name);
        index += 1;
    }

    if(closedir(directory) == -1){
        printf("Error closing directory\n");
        return -2;
    }

    return 0;
}

ArrayFiles* get_files(char* folder_name) {
    int nb_files = get_nb_entry_folder(folder_name);

    ArrayFiles* struct_file = malloc(sizeof(ArrayFiles));
    if (nb_files < 0) {
        struct_file->status = nb_files;
        return struct_file;
    }

    struct_file->array = malloc(sizeof(File) * nb_files);
    struct_file->length = nb_files;
    struct_file->status = get_folder_info(folder_name, struct_file);
    return struct_file;
}

// - print - //
void print_array(ArrayFiles* struct_file, char* folder_name, bool multiple_folder) {
    int number_column = 0;
    int index_file = 0;

    if (multiple_folder == true) {
        printf("%s:\n", folder_name);
    }
    while (index_file < struct_file->length) {
        printf("%s\n", struct_file->array[index_file]->name);
        index_file += 1;
    }
    printf("\n");

    return;
}

// - free - //

void free_struct_files(ArrayFiles* StructureFiles) {
    int index = 0;
    while(index < StructureFiles->length) {
        free(StructureFiles->array[index]->name);
        free(StructureFiles->array[index]);
        index += 1;
    }
    free(StructureFiles->array);
    free(StructureFiles);
}

// - ls - //

void my_ls(char* folder_name, bool multiple_folder) {
    ArrayFiles* structure_file = get_files(folder_name);
    if (structure_file->status < 0) {
        return;
    }

    print_array(structure_file, folder_name, multiple_folder);
    free_struct_files(structure_file);
    return;
}

// --- main --- //
int main(int argc, char **argv){
    int nb_argv = 1;

    if ((nb_argv == argc)) {
        my_ls(".", false);
    }
    else if (nb_argv == (argc - 1)) {
        my_ls(argv[nb_argv], false);
    }
    else {
        int index = nb_argv;
        while (index < argc) {
            my_ls(argv[index], true);
            index += 1;
        }
    }

    return 0;
}
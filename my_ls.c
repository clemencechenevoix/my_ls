// --- include --- //
#include <stdio.h> // include: printf
#include <stdlib.h> // include: malloc, free
#include <sys/stat.h> // include: files stats function
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
    int status;
} Flags;

typedef struct StructMainVar {
    int* flags;
    int* files;
    int* folder;
    int length_flags;
    int length_files;
    int length_folder;
    int status;
} MainVar;

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

void my_memset(char* string, char caract, int length) {
    int index = 0;
    while (index < length) {
        string[index] = caract;
        index += 1;
    }
}

int checkIfFileExists(const char *filename) {
  FILE *file;
  if (file = fopen(filename, "r")) {
    fclose(file);
    return 1;
  }

  return 0;
}

// - sort - //

// void sort_by_lexic(ArrayFiles* struct_file, int* index_sort) {

// }

// void sort_by_time(ArrayFiles* struct_file, int* index_sort) {

// }

// void sort_by_size(ArrayFiles* struct_file, int* index_sort) {

// }

// int* dispach_sort(ArrayFiles* struct_file, char sort_flag) {
//     int* index_sort = malloc(sizeof(int) * struct_file->length);
    
//     if (sort_flag == 't'){
//         sort_by_time(struct_file, index_sort);
//     } else if (sort_flag == 's'){
//         sort_by_size(struct_file, index_sort);
//     }

//     return index_sort;
// }

// - get - //
void get_main_var_int_array(MainVar* StructMainVar, char** argv, int argc){
    DIR *directory;
    int index_flags = 0;
    int index_folder = 0;
    int index_files = 0;
    int index_argv = 1;

    while (index_argv < argc) {
        directory = opendir(argv[index_argv]);
        if (argv[index_argv][0] == '-') {
            StructMainVar->flags[index_flags] = index_argv;
            index_flags += 1;
        } else if (directory != NULL) {
            closedir(directory);
            StructMainVar->folder[index_folder] = index_argv;
            index_folder += 1;
        } else {
            StructMainVar->files[index_files] = index_argv;
            index_files += 1;
        }
        index_argv += 1;
    }
    StructMainVar->status = 0;
    return;
}

MainVar* get_main_var(char** argv, int argc){
    MainVar* StructMainVar = malloc(sizeof(MainVar));
    DIR *directory;
    int index = 1;
    int length_flags = 0;
    int length_folder = 0;
    int length_files = 0;

    while (index < argc) {
        directory = opendir(argv[index]);
        if (argv[index][0] == '-') {
            length_flags += 1;
        } else if (directory != NULL) {
            closedir(directory);
            length_folder += 1;
        } else if (checkIfFileExists(argv[index])){
            length_files += 1;
        } else {
            StructMainVar->status = -1;
            return StructMainVar;
        }
        index += 1;
    }

    StructMainVar->flags = malloc(sizeof(int) * length_flags);
    StructMainVar->files = malloc(sizeof(int) * length_files);
    StructMainVar->folder = malloc(sizeof(int) * length_folder);
    StructMainVar->length_flags = length_flags;
    StructMainVar->length_files = length_files;
    StructMainVar->length_folder = length_folder;
    
    get_main_var_int_array(StructMainVar, argv, argc);
    return StructMainVar;
}

int get_flags_in_string(Flags* StructFlag, char* flag_string, char* autorize_column, char* autorize_sort, int index_struct) {
    int index_column = 1;
    int is_in_column = 0;
    int is_in_sort = 0;
    int index_struct_column = index_struct;

    while (index_column < my_length(flag_string)) {
        if (is_char_in_string(flag_string[index_column], autorize_sort) == 1) {
            StructFlag->sort = flag_string[index_column];
            is_in_sort = 1;
        }
        if (is_char_in_string(flag_string[index_column], autorize_column) == 1) {
            if (is_char_in_string(flag_string[index_column], StructFlag->column) == 0) {
                StructFlag->column[index_struct_column] = flag_string[index_column];
                index_struct_column += 1;
                is_in_column = 1;
            }
        }
        if (is_in_sort == 0 && is_in_column == 0) {
            StructFlag->status = -1;
            printf("One of the option doesn't exist\n");
            return index_struct_column;
        }

        is_in_sort = 0;
        is_in_column = 0;
        index_column += 1;
    }
    return index_struct_column;
}

void get_flags_in_array(MainVar* StructMainVar, Flags* StructFlag, char** argv, char* autorize_column, char* autorize_sort) {
    int index_struct_column = 0;
    int index = 0;

    StructFlag->status = 0;
    while (index < StructMainVar->length_flags) {
        index_struct_column = get_flags_in_string(StructFlag, argv[StructMainVar->flags[index]], autorize_column, autorize_sort, index_struct_column);
        if (StructFlag->status < 0) {
            return;
        }
        index += 1;
    }

    return;
}

Flags* get_flags(MainVar* StructMainVar, char** argv) {
    Flags* StructFlag = malloc(sizeof(Flags));
    int index = 0;
    int nb_flag = 0;

    char* autorize_column = malloc(sizeof(char) * 4);
    my_strcpy(autorize_column, "ats");
    char* autorize_sort = malloc(sizeof(char) * 3);
    my_strcpy(autorize_sort, "ts");

    while (index < StructMainVar->length_flags) {
        nb_flag += my_length(argv[StructMainVar->flags[index]]) - 1;
        index += 1;
    }
    StructFlag->column = malloc(sizeof(char) * (nb_flag + 1));
    my_memset(StructFlag->column, '\0', nb_flag + 1);
    StructFlag->sort = '\0';
    
    get_flags_in_array(StructMainVar, StructFlag, argv, autorize_column, autorize_sort);
    free(autorize_column);
    free(autorize_sort);
    return StructFlag;
}

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
void print_files(MainVar* StructureMainVar, char** argv) {
    int index = 0;
    while (index < StructureMainVar->length_files) {
        printf("%s\n", argv[StructureMainVar->files[index]]);
        index += 1;
    }
    printf("\n");
}

void print_array(ArrayFiles* struct_file, char* folder_name, char* column, char sort, bool multiple_folder) {
    int index_file = 0;
    int a_flag = is_char_in_string('a', column);

    if (multiple_folder == true) {
        printf("%s:\n", folder_name);
    }
    while (index_file < struct_file->length) {
        if (a_flag == 1 || struct_file->array[index_file]->name[0] != '.') {
            printf("%s\n", struct_file->array[index_file]->name);
        }
        index_file += 1;
    }
    printf("\n");

    return;
}

// - free - //

void free_struct_main_var(MainVar* StuctureMainVar) {
    printf("%d\n", StuctureMainVar->status);
    if (StuctureMainVar->status == 0) {
        free(StuctureMainVar->flags);
        free(StuctureMainVar->folder);
        free(StuctureMainVar->files);
    }
    free(StuctureMainVar);
    return;
}

void free_struct_flags(Flags* StuctureFlags) {
    free(StuctureFlags->column);
    free(StuctureFlags);
    return;
}

void free_struct_files(ArrayFiles* StructureFiles) {
    int index = 0;

    if (StructureFiles->status != -1) {
        while(index < StructureFiles->length) {
        free(StructureFiles->array[index]->name);
        free(StructureFiles->array[index]);
        index += 1;
    }
        free(StructureFiles->array);
    }
    free(StructureFiles);
}

// - ls - //

void my_ls(Flags* StuctureFlags, char* folder_name, bool multiple_folder) {
    ArrayFiles* structure_file = get_files(folder_name);
    if (structure_file->status < 0) {
        free_struct_files(structure_file) ;
        return;
    }

    print_array(structure_file, folder_name, StuctureFlags->column, StuctureFlags->sort, multiple_folder);
    free_struct_files(structure_file);
    return;
}

// --- main --- //
int main(int argc, char **argv){
    MainVar* structMainVar = get_main_var(argv, argc);
    if (structMainVar->status < 0) {
        free_struct_main_var(structMainVar);
        return 0;
    }

    Flags* structure_flags = get_flags(structMainVar, argv);
    if (structure_flags->status < 0) {
        free_struct_main_var(structMainVar);
        free_struct_flags(structure_flags);
        return 1;
    }

    print_files(structMainVar, argv);

    if ((structMainVar->length_folder == 0)) {
        my_ls(structure_flags, ".", false);
    }
    else {
        int index = 0;
        while (index < structMainVar->length_folder) {
            my_ls(structure_flags, argv[structMainVar->folder[index]], true);
            index += 1;
        }
    }

    free_struct_main_var(structMainVar);
    free_struct_flags(structure_flags);
    return 0;
}
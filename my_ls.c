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

void my_memset(char* string, char caract, int length) {
    int index = 0;
    while (index < length) {
        string[index] = caract;
        index += 1;
    }
}

// - get - //

int get_flags_in_string(Flags* StructFlag, char** argv, char* autorize_column, char* autorize_sort, int index_argv, int index_struct) {
    int index_column = 1;
    int is_in_column = 0;
    int is_in_sort = 0;
    int index_struct_column = index_struct;

    while (index_column < my_length(argv[index_argv])) {
        if (is_char_in_string(argv[index_argv][index_column], autorize_sort) == 1) {
            StructFlag->sort = argv[index_argv][index_column];
            is_in_sort = 1;
        }
        if (is_char_in_string(argv[index_argv][index_column], autorize_column) == 1) {
            if (is_char_in_string(argv[index_argv][index_column], StructFlag->column) == 1) {
                StructFlag->status = -2;
                printf("Duplicated option\n");
                return index_struct_column;
            }
            StructFlag->column[index_struct_column] = argv[index_argv][index_column];
            index_struct_column += 1;
            is_in_column = 1;
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

void get_flags_in_array(Flags* StructFlag, char** argv, char* autorize_column, char* autorize_sort) {
    int index_struct_column = 0;
    int index_argv = 1;

    StructFlag->status = 0;
    while (index_argv < StructFlag->nb_argv) {
        index_struct_column = get_flags_in_string(StructFlag, argv, autorize_column, autorize_sort, index_argv, index_struct_column);
        if (StructFlag->status < 0) {
            return;
        }
        index_argv += 1;
    }

    return;
}

Flags* get_flags(int argc, char** argv) {
    Flags* StructFlag = malloc(sizeof(Flags));
    int index_argv = 1;
    int nb_flag = 0;

    char* autorize_column = malloc(sizeof(char) * 4);
    my_strcpy(autorize_column, "ats");
    char* autorize_sort = malloc(sizeof(char) * 3);
    my_strcpy(autorize_sort, "ts");

    while (index_argv < argc && argv[index_argv][0] == '-') {
        nb_flag += my_length(argv[index_argv]) - 1;
        index_argv += 1;
    }
    StructFlag->column = malloc(sizeof(char) * (nb_flag + 1));
    my_memset(StructFlag->column, '\0', nb_flag + 1);
    StructFlag->nb_argv = index_argv;
    StructFlag->sort = '\0';
    
    get_flags_in_array(StructFlag, argv, autorize_column, autorize_sort);
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

void free_struct_flags(Flags* StuctureFlags) {
    free(StuctureFlags->column);
    free(StuctureFlags);
    return;
}

void free_struct_files(ArrayFiles* StructureFiles, int status) {
    int index = 0;

    if (status != -1) {
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
        free_struct_files(structure_file, structure_file->status) ;
        return;
    }

    print_array(structure_file, folder_name, StuctureFlags->column, StuctureFlags->sort, multiple_folder);
    free_struct_files(structure_file, structure_file->status);
    return;
}

// --- main --- //
int main(int argc, char **argv){
    Flags* structure_flags = get_flags(argc, argv);
    if (structure_flags->status < 0) {
        free_struct_flags(structure_flags);
        return 1;
    }
    
    if ((structure_flags->nb_argv == argc)) {
        my_ls(structure_flags, ".", false);
    }
    else if (structure_flags->nb_argv == (argc - 1)) {
        my_ls(structure_flags, argv[structure_flags->nb_argv], false);
    }
    else {
        int index = structure_flags->nb_argv;
        while (index < argc) {
            my_ls(structure_flags, argv[index], true);
            index += 1;
        }
    }

    free_struct_flags(structure_flags);
    return 0;
}
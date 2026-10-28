// --- include --- //
#include <stdio.h> // include: printf
#include <stdlib.h> // include: malloc, free
#include <sys/stat.h> // include: stat, lstat
#include <unistd.h>
#include <dirent.h> // include: opendir, readdir, closedir

// --- structure --- //

typedef struct StructFile {
    char* name;
    long time;
    int size;
} File;

typedef struct StructArrayFiles {
    File** array;
    int* array_index_sorted;
    int size;
    int length;
    int status;
} ArrayFiles;

typedef struct StructFlags {
    char* column;
    char sort;
    char display;
    int way;
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

void print_int(int* array, int length){
    printf("------------\n");
    int index = 0;
    while(index < length){
        printf("%d\n", array[index]);
        index += 1;
    }
    printf("------------\n");
}

void sort_file_by_time(File** file_array, int* index_array_to_sort, int length) {
    if (length < 1) {
        return;
    }
    index_array_to_sort[0] = 0;
    int length_sort = 1;
    int index_to_sort = 1;
    int index_sort = 0;
    
    while(index_to_sort < length && length_sort < length){
        if (index_sort == length_sort || file_array[index_to_sort]->time >= file_array[index_array_to_sort[index_sort]]->time) {
            append_int_at_index(index_array_to_sort, length_sort, index_to_sort, index_sort);
            index_sort = 0;
            index_to_sort += 1;
            length_sort += 1;
        } else {
            index_sort += 1;
        }
    }
}

void sort_file_by_size(File** file_array, int* index_array_to_sort, int length) {
    if (length < 1) {
        return;
    }
    index_array_to_sort[0] = 0;
    int length_sort = 1;
    int index_to_sort = 1;
    int index_sort = 0;
    
    while(index_to_sort < length && length_sort < length){
        if (index_sort == length_sort || file_array[index_to_sort]->size > file_array[index_array_to_sort[index_sort]]->size) {
            append_int_at_index(index_array_to_sort, length_sort, index_to_sort, index_sort);
            index_sort = 0;
            index_to_sort += 1;
            length_sort += 1;
        } else {
            index_sort += 1;
        }
    }
}

void sort_file_by_lexical(File** file_array, int* index_array_to_sort, int length) {
    if (length < 1) {
        return;
    }
    index_array_to_sort[0] = 0;
    int length_sort = 1;
    int index_to_sort = 1;
    int index_sort = 0;
    
    while(index_to_sort < length && length_sort < length){
        if (index_sort == length_sort || my_strcmp(file_array[index_to_sort]->name, file_array[index_array_to_sort[index_sort]]->name) == file_array[index_to_sort]->name) {
            append_int_at_index(index_array_to_sort, length_sort, index_to_sort, index_sort);
            index_sort = 0;
            index_to_sort += 1;
            length_sort += 1;
        } else {
            index_sort += 1;
        }
    }
}

int* sort_main_var_by_lexical(char** argv, int* index_array_to_sort, int length) {
    if (length < 2) {
        return index_array_to_sort;
    }
    int* index_array_sorted = malloc(sizeof(int) * length);
    index_array_sorted[0] = index_array_to_sort[0];
    int length_sort = 1;

    int index_to_sort = 1;
    int index_sort = 0;
    
    while(index_to_sort < length && length_sort < length){
        if (index_sort == length_sort || my_strcmp(argv[index_array_to_sort[index_to_sort]], argv[index_array_sorted[index_sort]]) == argv[index_array_to_sort[index_to_sort]]) {
            append_int_at_index(index_array_sorted, length_sort, index_array_to_sort[index_to_sort], index_sort);
            index_sort = 0;
            index_to_sort += 1;
            length_sort += 1;
        } else {
            index_sort += 1;
        }
    }

    free(index_array_to_sort);
    return index_array_sorted;
}

void dispach_sort_file(ArrayFiles* structArrayFile, char sort_flag) {  
    if (sort_flag == 't'){
        sort_file_by_time(structArrayFile->array, structArrayFile->array_index_sorted, structArrayFile->length);
    } else if (sort_flag == 'S'){
        sort_file_by_size(structArrayFile->array, structArrayFile->array_index_sorted, structArrayFile->length);
    } else {
        sort_file_by_lexical(structArrayFile->array, structArrayFile->array_index_sorted, structArrayFile->length);
    }
    return;
}

// - get - //
char get_display_caract(Flags* StructFlag) {
    if (StructFlag->display == 'l') {
        return '\n';
    } else if (StructFlag->display == 'x') {
        return ' ';
    }
    return '\n';
}

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

int get_flags_in_string(Flags* StructFlag, char* flag_string, char* autorize_column, char* autorize_sort, char* autorize_display, int index_struct) {
    int index_column = 1;
    int is_in_column = 0;
    int is_in_sort = 0;
    int is_in_display = 0;
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
            }
            is_in_column = 1;
        }
        if(is_char_in_string(flag_string[index_column], autorize_display) == 1){
            StructFlag->display = flag_string[index_column]; 
            is_in_display = 1;
        }
        if (is_in_sort == 0 && is_in_column == 0 && is_in_display == 0) {
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

void get_flags_in_array(MainVar* StructMainVar, Flags* StructFlag, char** argv, char* autorize_column, char* autorize_sort, char* autorize_display) {
    int index_struct_column = 0;
    int index = 0;

    StructFlag->status = 0;
    StructFlag->display = '1';
    while (index < StructMainVar->length_flags) {
        index_struct_column = get_flags_in_string(StructFlag, argv[StructMainVar->flags[index]], autorize_column, autorize_sort, autorize_display, index_struct_column);
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
    my_strcpy(autorize_sort, "tS");
    char* autorize_display = malloc(sizeof(char) * 3);
    my_strcpy(autorize_display, "1x");

    while (index < StructMainVar->length_flags) {
        nb_flag += my_length(argv[StructMainVar->flags[index]]) - 1;
        index += 1;
    }
    StructFlag->column = malloc(sizeof(char) * (nb_flag + 1));
    my_memset(StructFlag->column, '\0', nb_flag + 1);
    StructFlag->sort = '\0';
    
    get_flags_in_array(StructMainVar, StructFlag, argv, autorize_column, autorize_sort, autorize_display);
    free(autorize_column);
    free(autorize_sort);
    free(autorize_display);
    return StructFlag;
}

char* get_path(char* folder_name, char* file_name){
    int length_folder_name = my_length(folder_name);
    int length_file_name = my_length(file_name);
    char* path = malloc(sizeof(char) * ( length_folder_name + length_file_name + 2));
    int index = 0;
    int index_path = 0;
    
    while (index < length_folder_name) {
        path[index_path] = folder_name[index];
        index += 1;
        index_path += 1;
    }
    path[index_path] = '/';
    index_path += 1;
    index = 0;
    while (index < length_file_name) {
        path[index_path] = file_name[index];
        index += 1;
        index_path += 1;
    }
    path[index_path] = '\0';
    return path;
}

int get_nb_entry_folder(char* folder_name){
    DIR *directory;
    struct dirent *entry;
    int nb_files = 0;

    directory = opendir(folder_name);
    if(directory == NULL){
        printf("Error opening directory\n");
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
    struct stat informations;
    struct dirent* entry;
    char* path;
    int index = 0;
    
    directory = opendir(folder_name);
    if(directory == NULL){
        printf("Error openning directory\n");
        return 0;
    }

    while((entry = readdir(directory)) != NULL) {
        struct_file->array[index]= malloc(sizeof(File) * 1);

        path = get_path(folder_name, entry->d_name);
        stat(path, &informations);
        free(path);
        struct_file->array[index]->size = (informations.st_blocks * informations.st_blksize)/1000;
        struct_file->size += struct_file->array[index]->size;
        struct_file->array[index]->time = informations.st_mtim.tv_sec;

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
    struct_file->array_index_sorted = malloc(sizeof(int) * nb_files);
    struct_file->size = 0;
    struct_file->status = get_folder_info(folder_name, struct_file);
    return struct_file;
}

// - print - //
void print_files(MainVar* StructureMainVar, char** argv, char display_caract) {
    int index = 0;
    while (index < StructureMainVar->length_files) {
        printf("%s \n", argv[StructureMainVar->files[index]]);
        index += 1;
    }
    printf("%c", display_caract);
}

void print_array(ArrayFiles* struct_file, char* folder_name, char* column, char sort, char display_caract, bool multiple_folder) {
    int index_file = 0;
    int a_flag = is_char_in_string('a', column);
    int s_flag = is_char_in_string('s', column);
    bool a_condition;

    if (multiple_folder == true) {
        printf("%s:\n", folder_name);
    }
    if (s_flag == 1) {
        printf("total %d\n", struct_file->size);
    }
    while (index_file < struct_file->length) {
        a_condition = a_flag == 1 || struct_file->array[struct_file->array_index_sorted[index_file]]->name[0] != '.';
        if (s_flag == 1 && a_condition) {
            printf("%d ", struct_file->array[struct_file->array_index_sorted[index_file]]->size);
        } 
        if (a_condition) {
            printf("%s %c", struct_file->array[struct_file->array_index_sorted[index_file]]->name, display_caract);
        }
        index_file += 1;
    }
    printf("\n");
    if (display_caract == ' ' && multiple_folder == true) {
        printf("\n");
    }

    return;
}

// - free - //

void free_struct_main_var(MainVar* StuctureMainVar) {
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
        free(StructureFiles->array_index_sorted);
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
    
    dispach_sort_file(structure_file, StuctureFlags->sort);
    print_array(structure_file, folder_name, StuctureFlags->column, StuctureFlags->sort, StuctureFlags->display, multiple_folder);
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

    structure_flags->display = get_display_caract(structure_flags);
    structMainVar->folder = sort_main_var_by_lexical(argv, structMainVar->folder, structMainVar->length_folder);
    structMainVar->files = sort_main_var_by_lexical(argv, structMainVar->files, structMainVar->length_files);
    print_files(structMainVar, argv, structure_flags->display);

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
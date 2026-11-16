// ----- include ----- //
#include "../include/my_ls.h"

// ----- function ----- //

// --- sort --- //

/**
* @brief sort the file by time by sorting their index
* @param file_t** file_array (the array of structure file to sort)
* @param int* index_array_to_sort (the malloc array to stock the index)
* @param int length (the length of index_array_to_sort)
* @return void
*/
void sort_file_by_time(file_t** file_array, int* index_array_to_sort, int length) {
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

/** 
* @brief sort the file by size by sorting their index
* @param file_t** file_array (the array of structure file to sort)
* @param int* index_array_to_sort (the malloc array to stock the index)
* @param int length (the length of index_array_to_sort)
* @return void
*/
void sort_file_by_size(file_t** file_array, int* index_array_to_sort, int length) {
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

/** 
* @brief sort the file by lexical order by sorting their index
* @param file_t** file_array (the array of structure file to sort)
* @param int* index_array_to_sort (the malloc array to stock the index)
* @param int length (the length of index_array_to_sort)
* @return void
*/
void sort_file_by_lexical(file_t** file_array, int* index_array_to_sort, int length) {
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

/** 
* @brief sort the folder given when executing my_ls.c by lexical order by sorting their index
* @param char** argv (the string array given when executing my_ls.c)
* @param int* index_array_to_sort (the array with the index to sort)
* @param int length (the length of index_array_to_sort)
* @return int* the new array with the sorted index
*/
int* sort_folder_by_lexical(char** argv, int* index_array_to_sort, int length) {
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


/** 
* @brief call the right sorting function for the file depending on the given sorting flag
* @param array_file_t* struct_array_file (the struct with the different informations of the files)
* @param char sort_flag (the given sorting flag)
* @return void
*/
void dispach_sort_file(array_file_t* struct_array_file, char sort_flag) {  
    if (sort_flag == 't'){
        sort_file_by_time(struct_array_file->array, struct_array_file->array_index_sorted, struct_array_file->length);
    } else if (sort_flag == 'S'){
        sort_file_by_size(struct_array_file->array, struct_array_file->array_index_sorted, struct_array_file->length);
    } else {
        sort_file_by_lexical(struct_array_file->array, struct_array_file->array_index_sorted, struct_array_file->length);
    }
    return;
}

// --- get --- //

// - main var - //

/** 
* @brief create an entity of the structure ArrayFile with the file given when executing my_ls.c
* @param char** argv (the string array given when executing my_ls.c)
* @param int* int_array (the struct with the different informations of the files)
* @param int length (the length of int_array)
* @return array_file_t*
*/
array_file_t* get_main_file_array_file(char** argv, int* int_array, int length){
    array_file_t* main_file_array = malloc(sizeof(array_file_t));
    struct stat informations;
    int index = 0;

    if (length == 0) {
        main_file_array->status = -1;
        return main_file_array;
    }

    main_file_array->array = malloc(sizeof(file_t*) * length);
    main_file_array->length = length;
    main_file_array->status = 0;
    
    while (index < length) {
        main_file_array->array[index] = malloc(sizeof(file_t));
        stat(argv[int_array[index]], &informations);
        main_file_array->array[index]->size = (informations.st_blocks * informations.st_blksize)/1000;
        main_file_array->array[index]->time = informations.st_mtim.tv_sec;
        main_file_array->array[index]->name = malloc(sizeof(char) * (my_length(argv[int_array[index]]) + 1));
        my_strcpy(main_file_array->array[index]->name, argv[int_array[index]]);

        index += 1;
    }
    main_file_array->array_index_sorted = malloc(sizeof(int) * length);
    return main_file_array;
}

/** 
* @brief scan all the elements of argv and fill the right int array in struct_main_var
* @param main_var_t* struct_main_var (the struct with the different index of the informations given to ./my_ls)
* @param char** argv (the string array given when executing my_ls.c)
* @param int argc (the number of elements in argv)
* @return void
*/
void get_main_var_int_array(main_var_t* struct_main_var, char** argv, int argc){
    DIR *directory;
    int index_flags = 0;
    int index_folder = 0;
    int index_files = 0;
    int index_argv = 1;

    while (index_argv < argc) {
        directory = opendir(argv[index_argv]);
        if (argv[index_argv][0] == '-') {
            struct_main_var->flags[index_flags] = index_argv;
            index_flags += 1;
        } else if (directory != NULL) {
            closedir(directory);
            struct_main_var->folder[index_folder] = index_argv;
            index_folder += 1;
        } else {
            struct_main_var->files[index_files] = index_argv;
            index_files += 1;
        }
        index_argv += 1;
    }
    struct_main_var->status = 0;
    return;
}

/** 
* @brief scan all the elements of argv and dispach it in the right category (flags, files or folders)
* @param char** argv (the string array given when executing my_ls.c)
* @param int argc (the number of elements in argv)
* @return main_var_t* the structure with the index dispached in array
*/
main_var_t* get_main_var(char** argv, int argc){
    main_var_t* struct_main_var = malloc(sizeof(main_var_t));
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
        } else if (check_if_file_exist(argv[index])){
            length_files += 1;
        } else {
            printf("file or directory %s does'nt exist\n", argv[index]);
            struct_main_var->status = -1;
            return struct_main_var;
        }
        index += 1;
    }

    struct_main_var->flags = malloc(sizeof(int) * length_flags);
    struct_main_var->files = malloc(sizeof(int) * length_files);
    struct_main_var->folder = malloc(sizeof(int) * length_folder);
    struct_main_var->length_flags = length_flags;
    struct_main_var->length_files = length_files;
    struct_main_var->length_folder = length_folder;
    get_main_var_int_array(struct_main_var, argv, argc);
    return struct_main_var;
}

// - flags - //

/**
* @brief find the right character that change how the print is display depending on the given display flag (-1 or -x) 
* @param flag_t* struct_flag (the structure containing the different flags)
* @return char
*/
char get_display_caract(flag_t* struct_flag) {
    if (struct_flag->display == 'l') {
        return '\n';
    } else if (struct_flag->display == 'x') {
        return ' ';
    }
    return '\n';
}

/**
* @brief scan a string and find all the flag given in it 
* @param flag_t* struct_flag (the structure containing the different flags)
* @param char* flag_string (the string to scan)
* @param char* autorize_column (all the flag authorize for the category column)
* @param char* autorize_sort (all the flag authorize for the category sort)
* @param char* autorize_display (all the flag authorize for the category display)
* @param int index_struct (index of the empty space in column in order to add a new element/flag in it)
* @return int index_struct_column the new index of the empty space in column
*/
int get_flags_in_string(flag_t* struct_flag, char* flag_string, char* autorize_column, char* autorize_sort, char* autorize_display, int index_struct) {
    int index_column = 1;
    int is_in_column = 0;
    int is_in_sort = 0;
    int is_in_display = 0;
    int index_struct_column = index_struct;
    
    while (index_column < my_length(flag_string)) {
        if (check_if_char_in_string(autorize_sort, flag_string[index_column]) == 1) {
            struct_flag->sort = flag_string[index_column];
            is_in_sort = 1;
        }
        if (check_if_char_in_string(autorize_column, flag_string[index_column]) == 1) {
            if (check_if_char_in_string(struct_flag->column, flag_string[index_column]) == 0) {
                struct_flag->column[index_struct_column] = flag_string[index_column];
                index_struct_column += 1;
            }
            is_in_column = 1;
        }
        if(check_if_char_in_string(autorize_display, flag_string[index_column]) == 1){
            struct_flag->display = flag_string[index_column]; 
            is_in_display = 1;
        }
        if(flag_string[index_column] == 'r' && struct_flag->way == 1){
            struct_flag->way = -1; 
        }
        if (is_in_sort == 0 && is_in_column == 0 && is_in_display == 0 && flag_string[index_column] != 'r') {
            struct_flag->status = -1;
            printf("One of the option doesn't exist\n");
            return index_struct_column;
        }

        is_in_sort = 0;
        is_in_column = 0;
        is_in_display = 0;
        index_column += 1;
    }
    return index_struct_column;
}

/**
* @brief find the right character that change how the print is display depending on the given display flag (-1 or -x) 
* @param main_var_t* struct_main_var (the struct with the different index of the informations given to ./my_ls)
* @param flag_t* struct_flag (the structure containing the different flags)
* @param char** argv (the string array given when executing my_ls.c)
* @param char* autorize_column (all the flag authorize for the category column)
* @param char* autorize_sort (all the flag authorize for the category sort)
* @param char* autorize_display (all the flag authorize for the category display)
* @return void
*/
void get_flags_in_array(main_var_t* struct_main_var, flag_t* struct_flag, char** argv, char* autorize_column, char* autorize_sort, char* autorize_display) {
    int index_struct_column = 0;
    int index = 0;

    struct_flag->status = 0;
    struct_flag->display = '1';
    struct_flag->way = 1;
    while (index < struct_main_var->length_flags) {
        index_struct_column = get_flags_in_string(struct_flag, argv[struct_main_var->flags[index]], autorize_column, autorize_sort, autorize_display, index_struct_column);
        if (struct_flag->status < 0) {
            return;
        }
        index += 1;
    }
}

/**
* @brief create the structure with all the information about the flag by searching the flag in argv
* @param main_var_t* struct_main_var (the struct with the different index of the informations given to ./my_ls)
* @param char** argv (the string array given when executing my_ls.c)
* @return Flag* the structure with all the information about the flag
*/
flag_t* get_flags(main_var_t* struct_main_var, char** argv) {
    flag_t* struct_flag = malloc(sizeof(flag_t));
    int index = 0;
    int nb_flag = 0;

    char* autorize_column = malloc(sizeof(char) * 4);
    my_strcpy(autorize_column, "ats");
    char* autorize_sort = malloc(sizeof(char) * 3);
    my_strcpy(autorize_sort, "tS");
    char* autorize_display = malloc(sizeof(char) * 3);
    my_strcpy(autorize_display, "1x");

    while (index < struct_main_var->length_flags) {
        nb_flag += my_length(argv[struct_main_var->flags[index]]) - 1;
        index += 1;
    }
    struct_flag->column = malloc(sizeof(char) * (nb_flag + 1));
    my_memset(struct_flag->column, '\0', nb_flag + 1);
    struct_flag->sort = '\0';
    
    get_flags_in_array(struct_main_var, struct_flag, argv, autorize_column, autorize_sort, autorize_display);
    free(autorize_column);
    free(autorize_sort);
    free(autorize_display);
    return struct_flag;
}

// - files - //

/**
* @brief find the path of the file with the named file_name
* @param char* file_name (the name of the file)
* @param char* folder_name (the name of the folder containing the file)
* @return char* the path of the file
*/
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

/**
* @brief find the number of entity (file and folder) in the folder named folder_name
* @param char* folder_name (the name of the folder)
* @return int the number of entity (file and folder)
*/
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

/**
* @brief stock the information about the files in a folder in struct_file
* @param array_file_t* struct_file (the malloc structure that will contain all the information about the files)
* @param char* folder_name (the name of the folder)
* @return int the status (if an error happpends or not)
*/
int get_folder_info(array_file_t* struct_file, char* folder_name) {
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
        struct_file->array[index]= malloc(sizeof(file_t) * 1);

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

/**
* @brief find the information about the files in the folder folder_name
* @param char* folder_name (the name of the folder)
* @return array_file_t* the structure that contain all the information about the files
*/
array_file_t* get_files(char* folder_name) {
    int nb_files = get_nb_entry_folder(folder_name);

    array_file_t* struct_file = malloc(sizeof(array_file_t));
    if (nb_files < 0) {
        struct_file->status = nb_files;
        return struct_file;
    }

    struct_file->array = malloc(sizeof(file_t) * nb_files);
    struct_file->length = nb_files;
    struct_file->array_index_sorted = malloc(sizeof(int) * nb_files);
    struct_file->size = 0;
    struct_file->status = get_folder_info(struct_file, folder_name);
    return struct_file;
}

// --- print --- //

/**
* @brief print the files according to the flags
* @param array_file_t* struct_file (the structure that contain all the information about the files)
* @param char* folder_name (the name of the folder)
* @param char* column (the printing information flags)
* @param char display_caract (the caracter in order to print in column or rows)
* @param int way (-1 or 1 depending if there is the flag -r or not)
* @param bool multiple_folder (True if there is multiple folder given to ./my_ls)
* @param bool is_main_file (True if struct_file is madwith the file given to ./my_ls)
* @return void
*/
void print_array(array_file_t* struct_file, char* folder_name, char* column, char display_caract, int way, bool multiple_folder, bool is_main_file) {
    int index_file = 0;
    int a_flag = check_if_char_in_string(column, 'a');
    int s_flag = check_if_char_in_string(column, 's');
    bool a_condition;
    bool limit_condition = index_file < struct_file->length;
    
    if (way < 0) {
        index_file = struct_file->length - 1;
        limit_condition = index_file > -1;
    }
    if (multiple_folder == true) {
        printf("%s:\n", folder_name);
    }
    if (s_flag == 1 && is_main_file == false) {
        printf("total %d\n", struct_file->size);
    }

    while (limit_condition) {
        a_condition = a_flag == 1 || struct_file->array[struct_file->array_index_sorted[index_file]]->name[0] != '.';
        if (s_flag == 1 && (a_condition || is_main_file == true)) {
            printf("%d ", struct_file->array[struct_file->array_index_sorted[index_file]]->size);
        } 
        if (a_condition || is_main_file == true) {
            printf("%s %c", struct_file->array[struct_file->array_index_sorted[index_file]]->name, display_caract);
        }
        index_file += way;
        if (way < 0) {
            limit_condition = index_file > -1;
        }else{
            limit_condition = index_file < struct_file->length;
        }
    }
    printf("\n");
    if (display_caract == ' ' && (multiple_folder == true || is_main_file == true)) {
        printf("\n");
    }
}


/**
* @brief get the informations of the files in the given folder and print it according to the given flags
* @param flag_t* struct_flag (the structure containing the different flags)
* @param char* folder_name (the name of the folder)
* @param bool multiple_folder (True if there are multiple folder given to ./my_ls)
* @return void
*/
void folder_gestion(flag_t* struct_flag, char* folder_name, bool multiple_folder) {
    array_file_t* structure_file = get_files(folder_name);
    if (structure_file->status < 0) {
        free_struct_files(structure_file) ;
        return;
    }
    
    dispach_sort_file(structure_file, struct_flag->sort);
    print_array(structure_file, folder_name, struct_flag->column, struct_flag->display, struct_flag->way, multiple_folder, false);
    free_struct_files(structure_file);
    return;
}
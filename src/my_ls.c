// ----- include ----- //
#include "../include/my_ls.h"

// ----- function ----- //

/**
* @brief get the informations of the files in the given folder and print it according to the given flags
* @param main_var_t* struct_main_var (the struct with the different index of the informations given to ./my_ls)
* @param flag_t* struct_flag (the structure containing the different flags)
* @param char** argv (the string array given when executing my_ls.c)
* @return void
*/
void my_ls(main_var_t* struct_main_var, flag_t* struct_flag, char** argv) {
    array_file_t* struct_array_main_file = get_main_file_array_file(argv, struct_main_var->files, struct_main_var->length_files);
    struct_flag->display = get_display_caract(struct_flag);
    struct_main_var->folder = sort_folder_by_lexical(argv, struct_main_var->folder, struct_main_var->length_folder);
    
    if (struct_array_main_file->status != -1){
        sort_file(struct_array_main_file, struct_flag->sort_secondary, struct_flag->sort_secondary);
        print_array(struct_array_main_file, "", struct_flag->column, struct_flag->display, struct_flag->way, 0, 1);
    }
    
    if (struct_main_var->length_folder == 0) {
        folder_gestion(struct_flag, ".", 0);
    } else if (struct_main_var->length_folder == 1) {
        folder_gestion(struct_flag, argv[struct_main_var->folder[0]], 0);
    } else {
        int index = 0;
        int limit_condition = index < struct_main_var->length_folder;
        if (struct_flag->way < 0) {
            index = struct_main_var->length_folder - 1;
            limit_condition = index > -1;
        }
        while (limit_condition) {
            folder_gestion(struct_flag, argv[struct_main_var->folder[index]], 1);

            index += 1 * struct_flag->way;
            if (struct_flag->way < 0) {
                limit_condition = index > -1;
            } else {
                limit_condition = index < struct_main_var->length_folder;
            }
        }
    }

    free_struct_files(struct_array_main_file);
}
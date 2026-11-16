// ----- include ----- //
#include "../include/my_ls.h"

// ----- main ------ //

/**
* @brief the main of my_ls.c
* @param int argc (the number of elements in argv)
* @param char** argv (the string array given when executing my_ls.c)
* @return int
*/
int main(int argc, char **argv){
    main_var_t* struct_main_var = get_main_var(argv, argc);
    if (struct_main_var->status < 0) {
        free_struct_main_var(struct_main_var);
        return 1;
    }

    flag_t* struct_flag = get_flags(struct_main_var, argv);
    if (struct_flag->status < 0) {
        free_struct_main_var(struct_main_var);
        free_struct_flags(struct_flag);
        return 1;
    }

    my_ls(struct_main_var, struct_flag, argv);

    free_struct_main_var(struct_main_var);
    free_struct_flags(struct_flag);
    return 0;
}
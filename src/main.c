#define _GNU_SOURCE

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int walk(const char *path, int indent);
void print_file(const char *name, int is_dir, int indent, int is_last);

int main(int argc, char **argv) {
    const char *path = "."; // default path is current dir

    if(argc > 1) {
        path = argv[1];
    }

    int err = walk(path, 0);
    return err;
}

int walk(const char *path, int indent) {
    DIR *dir = opendir(path);

    if(!dir) {
        perror("opendir");
        return 1;
    }
    
    struct dirent *dp = NULL;
    while((dp = readdir(dir)) != NULL) {
        const char *name = dp->d_name;

        // ignore files
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        //printf("%s\n", name);

        if(dp->d_type == DT_DIR) {
            // is dir
            print_file(name, 1, indent, 0);

            // walk to sub path
            size_t len = strlen(path) + strlen(name) + 2;
            char sub_path[len];

            snprintf(sub_path, len, "%s/%s", path, name);
            walk(sub_path, indent+1);

        } else {
            // is file
            print_file(name, 0, indent, 1);
        }
    }

    closedir(dir);
    return 0;
}

void print_file(const char *name, int is_dir, int indent, int is_last) {
    if(indent) {
        printf("%*c", (indent)*2, ' ');
        if(is_last) {
            printf("╰─");
        } else {
            printf("├─");
        }
    }
    if(is_dir) {
        printf("\033[0;34m%s\033[0m\n", name);
    } else {
        printf("%s\n", name);
    }
}
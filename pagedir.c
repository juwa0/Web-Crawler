#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include <unistd.h>
#include <sys/stat.h>

#define CRAWLER_FILE ".crawler"

bool pagedir_init(const char *pageDirectory) {
    if (pageDirectory == NULL || strlen(pageDirectory) == 0) {
        return false;
    }

    if (access(pageDirectory, F_OK) == -1) {
        if (mkdir(pageDirectory, 0700) != 0) {
            return false;
        }
    }

    return true;
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
    if (page == NULL || pageDirectory == NULL) {
        return;
    }

    char filename[strlen(pageDirectory) + 20];
    sprintf(filename, "%s/%d", pageDirectory, documentID);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create or write to the file %s\n", filename);
        return;
    }

    fprintf(file, "%s\n", page->url);
    fprintf(file, "%d\n", page->depth);
    fprintf(file, "%s", page->html);

    fclose(file);
}

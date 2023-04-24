#include <stdio.h>
#include <stdlib.h>
#include "file.h"

myFile newFile(char* path) {
    myFile file;
    
    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s", path);
        // return 1;
    }

    fseek(fp, 0, SEEK_END);
    file.size = ftell(fp);
    rewind(fp);

    // allocate buffer and read file contents
    file.content = (char*)malloc(file.size + 1);
    fread(file.content, file.size, 1, fp);
    file.content[file.size] = '\0'; // add null terminator to end of buffer

    fclose(fp);

    return file;
}

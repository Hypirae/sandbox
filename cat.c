#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>

char * readFile (const char *fileName) {
    FILE *fp;
    char *fileContent;
    long  fileSize;

    // open file for reading and find its length
    fp = fopen(fileName, "r");

    if (!fp) {
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp) + 1;
    fseek(fp, 0L, SEEK_SET);

    // allocate a buffer and read the file
    fileContent = malloc(fileSize);

    if (!fileContent) {
        return NULL;
    }

    fread(fileContent, sizeof(char), fileSize, fp);
    fclose(fp);

    // add a null byte
    fileContent[fileSize - 1] = '\0'; 

    return fileContent;
}

void useage () {
    printf("cat <filename>\n");
}

int main (int argc, char **argv) {
    if (argc != 2) {
        useage();
        return 1;
    }

    char *content = readFile(argv[1]);

    if (!content) {
        printf("Could not read file: %s\n", argv[1]);
        return 2;
    }

    printf("%s\n", content);

    return 0;
}
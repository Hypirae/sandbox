#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>

void clearBuffer (char *buff, int buffSize) {
    int i;

    if (!buff) {
        return;
    }
    
    i = 0;

    while (i < buffSize) {
        buff[i] = '\0';
        i++;
    }
}

FILE * getFileHandle (const char *fileName) {
    return fopen(fileName, "r");
}

void destroyFileHandle (FILE *fp) {
    if (!fp) {
        return;
    }

    fclose(fp);
}

long getFileSize (FILE *fp) {
    long fileSize;

    if (!fp) {
        return 0;
    }

    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    return fileSize;
}

char * getChunk (char *buff, int buffSize, FILE *fp, int offset) {
    if (!buff) {
        buff = malloc(buffSize);
    }

    if (!fp) {
        return NULL;
    }

    clearBuffer(buff, buffSize);
    fseek(fp, (long)offset, SEEK_SET);
    fread(buff, sizeof(char), buffSize - 1, fp);

    return buff;
}

void useage () {
    printf("cats <filename>\n");
}

void cleanup (FILE *fp, char *buff) {
    if (fp) {
        destroyFileHandle(fp);
    }

    if (buff) {
        free(buff);
    }
}

int panic (const char *msg, FILE *fp, char *buff) {
    cleanup(fp, buff);
    printf("[Panic]: %s\n", msg);

    return 1;
}

int main (int argc, char **argv) {
    const int  buffSize = 1025; // +1 for \0
    int        offset = 0;
    long       fileSize;
    char      *buff;
    FILE      *fp;

    if (argc != 2) {
        useage();
        return 1;
    }

    buff = malloc(buffSize);
    fp = getFileHandle(argv[1]);

    if (!buff) {
        return panic("Couldn't allocate memory", fp, buff);
    }

    if (!fp) {
        return panic("Couldn't find file", fp, buff);
    }

    fileSize = getFileSize(fp);

    while (fileSize > 0) {
        getChunk(buff, buffSize, fp, offset * (buffSize - 1));

        if (!buff) {
            return panic("Buff was null", fp, buff);
        }

        printf("%s", buff);
        fileSize -= buffSize;
        offset   += 1;
    }

    printf("\n");
    cleanup(fp, buff);
    return 0;
}

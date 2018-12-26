#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tokens {
    T_COLON     = ':',
    T_HYPHEN    = '-',
    T_SPACE     = ' '
} tokens_e;

int findColonOffset (char *search, size_t searchLen) {
    int i = 0;

    while (i < searchLen) {
        if (search[i] == T_COLON) {
            break;
        }

        i++;
    }

    return i;
}

int findLookbackBound (char *search, size_t searchLen, int offset) {
    int found   = 0;
    int i       = offset;

    while (i > 0) {
        if (found == 2) {
            break;
        }

        if (search[i] == T_SPACE) {
            found++;
        }

        i--;
    }

    return i + 2;
}

int findLookaheadBound (char *search, size_t searchLen, int offset) {
    int i = offset;

    while (i < searchLen) {
        if (search[i] == T_SPACE) {
            break;
        }

        i++;
    }

    return i - 1;
}

char * findVerse (char *search, size_t searchLen) {
    int         i = 0;
    int token   = findColonOffset(search, searchLen);
    int start   = findLookbackBound(search, searchLen, token);
    int end     = findLookaheadBound(search, searchLen, token);
    int diff    = (end - start) + 1;
    char *verse = calloc(diff, sizeof(char));

    while (i < diff) {
        verse[i] = search[i + start];
        i++;
    }

    return verse;
}

int main () {
    char *searchText = "Hello, John 1:12 is a good verse.";
    size_t searchLength = strlen(searchText) + 1;

    char *verse = findVerse(searchText, searchLength);

    printf("Verse: %s\n", verse);
    return 0;
}
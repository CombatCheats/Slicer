#include <stdlib.h>
#include <stdio.h>

#define UCHAR unsigned char
#define DUMP NULL

int find_end(char* str) {
    int c = 0;
    while(str[c] != '\0') {
        c++;
    }
    return c;
}

int str_ends_with(char* str, char* thing) {
    char* p = str + (find_end(str) - find_end(thing));
    for(int i = 0; i < find_end(p); i++) {
        if(p[i] != thing[i]) {
            return 0;
        }
    }
    return 1;
}

int str_starts_with(char* str, char* thing) {
    for(int i = 0; i < find_end(thing); i++) {
        if(str[i] != thing[i]) {
            return 0;
        }
    }
    return 1;
}

int* delim(char* str, char* lim) {
    int* spots = NULL;
    int g = 0;
    for(int i = 0; i < find_end(str) - find_end(lim) + 1; i++) {
        if(str[i] == lim[g]) {
            printf("\033[94m");
        }
        printf("%c\t", str[i]);
        printf("%c", lim[g]);
        if(g != 0) {
            printf("\t%d", g);
        }
        printf("\n");
        printf("\033[0m");
        if(str[i] == lim[g]) {
            g++;
            if(g >= find_end(lim)) {
                spots = realloc(spots, sizeof(spots + 4));
                spots[sizeof(spots) / 4 - 1] = i - g;
                printf("%d\n", i - g);
                int x = i - g;
                return NULL;
                g = 0;
            }
        }
        else {
            g = 0;
        }
    }
    spots = spots + 4;
    return spots;
}

void get_bytes(FILE* fp, int b, unsigned char* p) {
    for(int i = 0; i < b && !feof(fp); i++) {
        if(p != NULL) {
            p[i] = fgetc(fp) + 1;
        } else {
            fgetc(fp);
        }
    }
    for(int i = b; i < sizeof(p); i++) {
        p[i] = '\0';
    }
}

char* read_line(FILE* fp) {
    char* res = malloc(1);
    char c;
    for(int i = 1; i > -1; i++) {
        if(feof(fp)) {
            return NULL;
        }
        res = realloc(res, i);
        c = fgetc(fp);
        if(c == '\n') {
            res[i - 1] = '\0';
            break;
        }
        res[i - 1] = c;
    }
    return res;
}

int combine_bytes(unsigned char* b) {
    int r = 0;
    for(int i = sizeof(b) - 1; i >= 0; i--) {
        if(b[i] == '\0') {
            continue;
        }
        r = r + b[i] - 1;
        r = r << 8;
    }
    r = r >> 8;
    return r;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("\033[91mYou nimrod\n\033[00m");
        return -1;
    }
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("\033[93mYou nimrod\n\033[00m");
        return -2;
    }
    if(str_ends_with(argv[1], ".stl")) {
        get_bytes(fp, 80, DUMP);
        unsigned char notb[4];
        get_bytes(fp, 4, notb);
        int not = combine_bytes(notb);
        printf("\033[95m%d\033[0m\n", not);
        return 0;
    }
    if(str_ends_with(argv[1], ".obj")) {
        /*
        char* line = read_line(fp);
        while(line) {
            if(str_starts_with(line, "v ")) {
                printf("%s\n", line);
            }
            line = read_line(fp);
        }
        */
        int* j = delim("teist ing stiuff", "in");
        for(int i = 0; i < sizeof(j) / 4; i++) {
            printf("%d ", j[i]);
        }
        printf("\n");
        return 0;
    }
    else {
        printf("\033[92mYou nimrod\033[0m\n");
        return 0;
    }
}
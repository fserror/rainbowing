#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define RED     "\x1b[38;5;196m"
#define ORANGE  "\x1b[38;5;208m"
#define YELLOW  "\x1b[38;5;226m"
#define GREEN   "\x1b[38;5;46m"
#define BLUE    "\x1b[38;5;21m"
#define INDIGO  "\x1b[38;5;57m"
#define VIOLET  "\x1b[38;5;93m"
#define RESET   "\x1b[0m"

int is_root() {
    return (getuid() == 0);
}

void rainbow_io()
{
    char text[1000];
    const char* colors[] = {RED, ORANGE, YELLOW, GREEN, INDIGO, BLUE, VIOLET};
    int i;

    while (fgets(text, sizeof(text), stdin))
    {
        if (text[strlen(text) - 1] == '\n') {
            text[strlen(text) - 1] = '\0';
        }
        
        for (i = 0; text[i] != '\0'; i++) {
            printf("%s%c" RESET, colors[i % 7], text[i]);
        }
        printf("\n");
    }
}

void rainbow_file() {
    const char* colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};
    int num_colors = 7;
    
    char filename[256];
    printf("Enter absolute path to file: ");
    
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("Error reading filename");
        return;
    }
    
    filename[strcspn(filename, "\n")] = '\0';
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    
    char ch;
    int char_count = 0;
    
    while ((ch = fgetc(fp)) != EOF) {
        int color_index = char_count % num_colors;
        printf("%s%c%s", colors[color_index], ch, RESET);
        char_count++;
    }
    
    fclose(fp);
    printf("\n");
}

int main() {
    if (is_root())
    {
        printf(RED "WARNING: Program is running by root.\n" RESET);
    }

    char format[10];
    
    printf("\nThis program prints rainbow text :)\n\n");
    printf("Enter 't' for rainbow text mode, enter 'f' for rainbow text from file, 'q' for quit program: ");
    
    if (fgets(format, sizeof(format), stdin) != NULL) {
        size_t len = strlen(format);
        if (len > 0 && format[len - 1] == '\n') {
            format[len - 1] = '\0';
        }
        
        if (strcmp(format, "t") == 0) {
            rainbow_io();
        } else if (strcmp(format, "f") == 0) {
            rainbow_file();
        } else if (strcmp(format, "q") == 0) {
            printf("Exiting...");
            exit(0);
        } else {
            printf("Unknown command - %s", format);
        }
    }

    return 0;
}
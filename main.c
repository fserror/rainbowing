#include <stdio.h>
#include <string.h>

#define RED     "\x1b[38;5;196m"
#define ORANGE  "\x1b[38;5;208m"
#define YELLOW  "\x1b[38;5;226m"
#define GREEN   "\x1b[38;5;46m"
#define BLUE    "\x1b[38;5;21m"
#define INDIGO  "\x1b[38;5;57m"
#define VIOLET  "\x1b[38;5;93m"
#define RESET   "\x1b[0m"

int main() {
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
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables


void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}



int findPath(char** arr, char* word, int** path,
             int row, int col, int index) {

    // Check if the current character matches
    if (toUpper(*(*(arr + row) + col)) != toUpper(*(word + index))) {
        return 0;
    }

    // Record the position of the current letter
    int *cell = *(path + row) + col;

    *cell = *cell * 10 + (index + 1);

    // Check if we've reached the last letter
    if (*(word + index + 1) == '\0') {
        return 1;
    }

    // Search neighboring positions
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {

            // Skip out-of-bounds positions
            if (i < 0 || i >= bSize || j < 0 || j >= bSize) {
                continue;
            }

            // Skip current position
            if (i == row && j == col) {
                continue;
            }

            if (findPath(arr, word, path, i, j, index + 1)) {
                return 1;
            }
        }
    }

    // Undo the current position if this path failed
    *cell /= 10;

    return 0;
}



void printPuzzle(char** arr) {
    int i, j;

    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            printf("%c", *(*(arr + i) + j));

            if (j < bSize - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}


void printPath(int** path) {
    int i, j;

    printf("Printing the search path:\n");

    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            printf("%d\t", *(*(path + i) + j));
        }
        printf("\n");
    }
}


void searchPuzzle(char** arr, char* word) {
// This function checks if arr contains the search word. If the
// word appears in arr, it will print out a message and the path
// as shown in the sample runs. If not found, it will print a
// different message as shown in the sample runs.
// Your implementation here...

int i, j;

int **path = malloc(bSize * sizeof(int *));

for (int i = 0; i < bSize; i++) {
    *(path + i) = malloc(bSize * sizeof(int));

    for (int j = 0; j < bSize; j++) {
        *(*(path + i) + j) = 0;
    }
}

    for (i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {

            if (toUpper(*(*(arr + i) + j)) == toUpper(*word)) {

                if (findPath(arr, word, path, i, j, 0)) {
                    printf("\nWord found!\n");
                    printPath(path);
                    return;
                }

            }
        }
    }

    printf("\nWord not found!\n");
}

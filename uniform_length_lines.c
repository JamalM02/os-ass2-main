/*
  Operating Systems
  Semester 1 5784
  Kinneret College on the Sea of Galilee
  Michael J. May
  
  Assignment 2:
  Find lines with uniform word length.
  
  Students:
  Jamal Majadle TZ-207513722
  Nagham Mousa TZ-208260018
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2000 
#define MIN_UNIFORM_WORD_COUNT 2

/* [word_length] [calculate the alpha length of a given word]
* Input: [word - a pointer to the character array representing the word]
* Output: [The number of alphabetical characters in the word]
*/
int word_length(char* word) {
    int word_length = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            word_length++;
        }
    }
    return word_length;
}

/* [line_uniform_length] [handles the line that has been provided, 
    dividing the line into separate words by spaces and putting each word in lineCopy (to avoid affecting the original line). 
    It sends one word at a time to the word_length function and checks if the value returned is equal to the alpha length of the first word in the same line]
* Input: [line - a pointer to the character array representing the line, it contains the words of the line, one at a time]
* Output: [If all the words in the line have the same alpha length and there are at least 2 words: the number of words that matched the alpha length of the provided line, 
    else it returns -1 ("false" indicating that at least one word doesn't match)]
*/
int line_uniform_length(char* line) {
    int length = 0;
    int wordCount = 0;
    char* lineCopy = strdup(line);
    if (lineCopy == NULL) {
        perror("Error duplicating line");
        return -1;
    }

    char* token = strtok(lineCopy, " ");
    while (token != NULL) {
        int wordLen = word_length(token);
        if (wordLen > 0) {
            if (length == 0) {
                length = wordLen;
            } else if (wordLen != length) {
                free(lineCopy); 
                return -1;
            }
            wordCount++;
        }
        token = strtok(NULL, " ");
    }
    free(lineCopy);
    if (wordCount < MIN_UNIFORM_WORD_COUNT) {
        return -1;
    }
    return length;
}

/* print_uniform_length_words: Prints lines from a file containing words with uniform lengths 
        by calling line_uniform_length function to check and print if found such in two different prints accoreding the input type (STDIN/txt File) 
* Input: inFile - a pointer to the FILE structure representing the input file,
*       fileName - the name of the input file (or "STDIN" for standard input)
* Output: The number of lines in the file containing words with uniform lengths
*/
int print_uniform_length_words(FILE *inFile, char *fileName) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;
    int uniformLinesCount = 0;
    
    while (fgets(line, sizeof(line), inFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        lineNumber++;

        int count = line_uniform_length(line);

        if (count != -1) {
            if(strcmp(fileName, "STDIN") != 0){
            printf("%s: %3d: length %2d: %s\n", fileName, lineNumber, count, line);
            }
            else
            printf("STDIN: %6d: length %2d:   %s\n", lineNumber, count, line);
            uniformLinesCount++;
        }
    }
    return uniformLinesCount;
}

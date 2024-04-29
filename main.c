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
#include <sys/wait.h>
#include <unistd.h>
#include "uniform_length_lines.h"

#define MAX_LINE_LENGTH 2000

int main(int argc, char *argv[]) {
    int totalUniformLines = 0;
    int totalFiles = argc - 1;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            FILE *inFile = fopen(argv[i], "r");
            if (inFile == NULL) {
                perror("Error opening file");
                totalFiles--;
                continue;
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("Error forking process");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                int count = print_uniform_length_words(inFile, argv[i]);
                fclose(inFile);
                exit(count);
            }
        }

        if (totalFiles > 0) {
            for (int i = 1; i <= totalFiles; i++) {
                int status;
                wait(&status);

                if (WIFEXITED(status)) {
                    int child_count = WEXITSTATUS(status);
                    totalUniformLines += child_count;
                }
            }
        }

        printf("%d children finished. Total %d lines found\n", totalFiles, totalUniformLines);
    } else {
        totalUniformLines = print_uniform_length_words(stdin, "STDIN");
        printf("1 children finished. Total %d lines found\n", totalUniformLines);
    }

    return 0;
}

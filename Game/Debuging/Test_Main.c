//
// Created by Spencer on 4/25/2024.
//

#include <stdio.h>
#include <intrin.h>
#include "stdarg.h"

int Test_Main(){
    FILE * debug;
    debug = fopen("debug", "a");
    fprintf(debug, "Tests\n");
    fclose(debug);
}

void clearFrameBugReports(){
    FILE * frameBug;
    frameBug = fopen("frameManager", "w");
    fprintf(frameBug, "Cleared \n");
    fclose(frameBug);
}

void clearTikBugReports(){
    FILE * tikBug;
    tikBug = fopen("tikManager", "w");
    fprintf(tikBug, "Cleared \n");
    fclose(tikBug);
}

void clearWorldBugs(){
    FILE * worldBug;
    worldBug = fopen("worldBug", "w");
    fprintf(worldBug, "Cleared \n");
    fclose(worldBug);
}

void clearBugReports(){
    clearFrameBugReports();
    clearTikBugReports();
    clearWorldBugs();
    FILE * debug;
    debug = fopen("debug", "w");
    fprintf(debug, "Cleared \n");
    fclose(debug);
}

void reportBug(const char* format, ...) { // Accept a format string and variable arguments
    FILE *debug;
    debug = fopen("debug", "a");
    if (debug != NULL) {
        va_list args; // Define a variable of type va_list to hold the variable arguments
        va_start(args, format); // Initialize the va_list with the arguments after the format string
        vfprintf(debug, format, args); // Use vfprintf to print the formatted message to the file
        va_end(args); // Clean up the va_list
        fclose(debug);
    } else {
        printf("Error: Unable to open debug file.\n");
    }
}

void reportWorldBug(const char* format, ...){
    FILE *debug;
    debug = fopen("worldBug", "a");
    if (debug != NULL) {
        va_list args; // Define a variable of type va_list to hold the variable arguments
        va_start(args, format); // Initialize the va_list with the arguments after the format string
        vfprintf(debug, format, args); // Use vfprintf to print the formatted message to the file
        va_end(args); // Clean up the va_list
        fclose(debug);
    } else {
        printf("Error: Unable to open debug file.\n");
    }
}

void reportTikBug(const char* format, ...) { // Accept a format string and variable arguments
    FILE *debug;
    debug = fopen("tikManager", "a");
    if (debug != NULL) {
        va_list args; // Define a variable of type va_list to hold the variable arguments
        va_start(args, format); // Initialize the va_list with the arguments after the format string
        vfprintf(debug, format, args); // Use vfprintf to print the formatted message to the file
        va_end(args); // Clean up the va_list
        fclose(debug);
    } else {
        printf("Error: Unable to open debug file.\n");
    }
}

void reportFrameBug(const char* format, ...) { // Accept a format string and variable arguments
    FILE *debug;
    debug = fopen("frameManager", "a");
    if (debug != NULL) {
        va_list args; // Define a variable of type va_list to hold the variable arguments
        va_start(args, format); // Initialize the va_list with the arguments after the format string
        vfprintf(debug, format, args); // Use vfprintf to print the formatted message to the file
        va_end(args); // Clean up the va_list
        fclose(debug);
    } else {
        printf("Error: Unable to open debug file.\n");
    }
}
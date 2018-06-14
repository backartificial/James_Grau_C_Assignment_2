/**
 * 
 * File:   main.c/main.txt
 * Author: James Grau
 * Date: June 12, 2018
 * 
**/

// Include required packages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constant for max size and declare new data type
const unsigned int MAX_SIZE = 100;
typedef unsigned int uint;
static int i = 0;

// This function will be used to swap "pointers".
void swap(char** , char** );

// Bubble sort function here.
void bubbleSort(char**, uint);

// Read quotes from quotes.txt file file and add them to array. Adjust the size as well!
// Note: size should reflect the number of quotes in the array/quotes.txt file!
void read_in(char**, uint*);

// Print the quotes using array of pointers.
void print_out(char**, uint);

// Save the sorted quotes in the output.txt file
void write_out(char**, uint);

// Free memory!
void free_memory(char**, uint);

/**
 * 
 * This method is used as the main area that runs the application
 * 
 * @return 0 on success
 * 
 **/
int main() {
    // Create array of pointers. Each pointer should point to heap memory where
    // each quote is kept. I.e. arr[0] points to quote N1 saved on the heap.
    char *arr[MAX_SIZE];

    // Number of quotes in the file quotes.txt. Must be adjusted when the file is read!
    uint size = MAX_SIZE; 

    read_in(arr, &size);

    printf("--- Input:\n");
    print_out(arr, size);
    
    bubbleSort(arr, size);
    
    printf("--- Output:\n");    
    print_out(arr, size);
    write_out(arr, size);
    
    free_memory(arr, size);
    
    return (0);
}

/**
 * 
 * This function is used to swap pointer
 * 
 * @param pointer1: is the first pointer reference
 * @param pointer2: is the second pointer reference
 * 
 */
void swap(char **pointer1, char **pointer2) {
    // Create tmp pointer to hold first pointer
    char *temp = *pointer1; // Store first pointer into temp
    *pointer1 = *pointer2; // Set first pointer to second pointer
    *pointer2 = temp; // Set second pointer to tmp pointer (which is first pointer)
}  

/**
 * 
 * This method is used to read in data from the quotes.txt file and store it into an array
 * 
 * @param array: is the pointer to the array that will hold the strings from the file
 * @param lineCount: is the count of lines the file has
 * 
 * References:
 * 1. Exercise3_12
 * 2. Exercise4_5 - Part 3
 * 
 */
void read_in(char** array, uint* lineCount) {
    // Create and initialize needed variables
    FILE *file = fopen("quotes.txt", "r"); // Create a file stream and read in the "quotes.txt" file
    char line[MAX_SIZE][256]; // Create an array of chars that will hold MAX_Size characters (max to allow for long strings)
    
    // Check if the file cannot be opened
    if(file == NULL) {
        // Print an error message
        printf("Cannot open quotes.txt!\n");

        // Exit with an error message
        exit(1);
    }
    
    // Loop through each non NULL line if the file
    while(fgets(*(line + i), 250, file) != NULL) {
        // Check if trying to add more then allowed to be stored in array (MAX_SIZE)
        if(i > MAX_SIZE) {
            // Print warning message
            printf("You have reached your alloted amount of string to read in. (%u). Program will continue without reading in more strings.\n", MAX_SIZE);
            
            // Break out of the loop
            break;
        }
        
        // Check to see if line start with \n or \r -- if true, continue onto next loop iteration (line)
        if(*(line[i] + 0) == '\n' || *(line[i] + 0) == '\r') { continue; }
        
        // Set any \r or \n to 0
        *(line[i] + (strcspn(*(line + i), "\r\n"))) = 0;
        
        // Allocate enough space for the string to be store in the correct array location
        *(array + i) = (char *)malloc((strlen(*(line + i)) + 1) * sizeof(char));
        
        // Check if the allocated memory array is NULL
        if (*(array + i) == NULL) {
            // Print an error message
            printf("Cannot allocate memory for %d string!\n", (i + 1));
            
            // Exit with an error message
            exit(1);
        }
        
        // Copy the string into the allocated memory array taking into account the null character
        strncpy(*(array + i), *(line + i), (strlen(*(line + i)) + 1));
        
        // Increment the line counter
        i++;
    }
    
    // Try and close the error -- print error message on error
    if (fclose(file)) { printf("Error closing \"quotes.txt\" file.\n"); }
    
    // Set the lineCount value to the value of i (casted as uint)
    *lineCount = (uint) i;
};

/**
 * 
 * This method is used to output the array of string to the console
 * 
 * @param array: is the array of string
 * @param lineCount: is the line count
 * 
 */
void print_out(char** array, uint lineCount) {
    // Loop through each line (array element)
    for(i = 0; i < lineCount; i++) {
        // Print element to console
        printf("%s\n", *(array + i));
    }
}

/**
 * 
 * This function is used to bubble sort the array of string based on the string length
 * 
 * @param array: is the array of string
 * @param lineCount: is the amount of lines (array elements)
 * 
 * References:
 * 1. https://brilliant.org/wiki/bubble-sort/
 * 2. https://www.geeksforgeeks.org/bubble-sort/
 * 
 */
void bubbleSort(char** array, uint lineCount) {
    // Loop through the loop as many times are there are array elements
    for(i = lineCount; i > 0; i--) {
        // Loop through every array element
        for(int j = 0; j < (i - 1); j++) {
            // Compare the length of the first element to the second based on if its greater than
            if(strlen(*(array + j)) > strlen(*(array + (j + 1)))) {
                // If left element is greater than right element, swap position
                swap(&*(array + j), &*(array + (j + 1)));
            }
        }
    }
}

/**
 * 
 * This method is used to write the sorted array to a file (output.txt)
 * 
 * @param array: is the string array
 * @param lineCount: is the amount of lines (array elements)
 * 
 */
void write_out(char** array, uint lineCount) {
    // Create a file stream and assign it to a file to write to
    FILE *output = fopen("output.txt", "w");
    
    // Loop through each array element
    for(i = 0; i < lineCount; i++) {
        // Print the data to the file
        fputs(*(array + i), output);
        
        // Prints new line to the file
        fputs("\n", output);
    }
}

/**
 * 
 * This function is used for freeing memory as operation complete on string array
 * 
 * @param array: is the string array
 * @param lineCount: is the amount of lines (array elements)
 * 
 */
void free_memory(char** array, uint lineCount) {
    // Loop through each array element
    for(i = 0; i < lineCount; i++) {
        // Free the array element
        free(*(array + i));
    }
}
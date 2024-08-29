#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

/*
 * Complete the 'rotateLeft' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER d
 *  2. INTEGER_ARRAY arr
 */
int* rotateLeft(int d, int arr_count, int* arr, int* result_count) {
    // Ensure d is within the bounds of arr_count
    d = d % arr_count;

    // Allocate memory for the result array
    int* result = malloc(arr_count * sizeof(int));
    if (result == NULL) {
        exit(EXIT_FAILURE); // Handle memory allocation failure
    }

    // Fill the result array with rotated values
    for (int i = 0; i < arr_count; i++) {
        result[i] = arr[(i + d) % arr_count];
    }

    // Set the result_count
    *result_count = arr_count;

    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    if (fptr == NULL) {
        exit(EXIT_FAILURE); // Handle file opening failure
    }

    char** first_multiple_input = split_string(rtrim(readline()));
    int n = parse_int(*(first_multiple_input + 0));
    int d = parse_int(*(first_multiple_input + 1));

    char** arr_temp = split_string(rtrim(readline()));
    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        exit(EXIT_FAILURE); // Handle memory allocation failure
    }

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));
        *(arr + i) = arr_item;
    }

    int result_count;
    int* result = rotateLeft(d, n, arr, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));
        if (i != result_count - 1) {
            fprintf(fptr, " ");
        }
    }
    fprintf(fptr, "\n");

    // Clean up
    fclose(fptr);
    free(arr);
    free(result);
    free(first_multiple_input);
    free(arr_temp);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);
    if (data == NULL) {
        exit(EXIT_FAILURE); // Handle memory allocation failure
    }

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (data == NULL) {
            exit(EXIT_FAILURE); // Handle memory allocation failure
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (data == NULL) {
            exit(EXIT_FAILURE); // Handle memory allocation failure
        }
    } else {
        data = realloc(data, data_length + 1);
        if (data == NULL) {
            exit(EXIT_FAILURE); // Handle memory allocation failure
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return NULL;
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return NULL;
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE); // Handle parsing error
    }
    return value;
}

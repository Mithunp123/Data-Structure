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

typedef struct {
    int *array;
    int size;
    int capacity;
} DynamicArray;

// Initialize a dynamic array
DynamicArray createDynamicArray() {
    DynamicArray dArray;
    dArray.size = 0;
    dArray.capacity = 4; // Initial capacity
    dArray.array = (int *)malloc(dArray.capacity * sizeof(int));
    return dArray;
}

// Append to dynamic array
void appendToDynamicArray(DynamicArray *dArray, int value) {
    if (dArray->size == dArray->capacity) {
        dArray->capacity *= 2;
        dArray->array = (int *)realloc(dArray->array, dArray->capacity * sizeof(int));
    }
    dArray->array[dArray->size++] = value;
}

// Get value from dynamic array
int getFromDynamicArray(DynamicArray *dArray, int index) {
    return dArray->array[index];
}

// Free dynamic array memory
void freeDynamicArray(DynamicArray *dArray) {
    free(dArray->array);
}

int* dynamicArray(int n, int q, int** queries, int* resultSize) {
    DynamicArray *arr = (DynamicArray *)malloc(n * sizeof(DynamicArray));
    for (int i = 0; i < n; i++) {
        arr[i] = createDynamicArray();
    }

    int lastAns = 0;
    int *results = (int *)malloc(q * sizeof(int));
    int resCount = 0;

    for (int i = 0; i < q; i++) {
        int queryType = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];
        
        int idx = (x ^ lastAns) % n;

        if (queryType == 1) {
            // Query type 1: Append y to arr[idx]
            appendToDynamicArray(&arr[idx], y);
        } else if (queryType == 2) {
            // Query type 2: Get value at index y from arr[idx]
            lastAns = getFromDynamicArray(&arr[idx], y);
            results[resCount++] = lastAns;
        }
    }

    // Free dynamic arrays
    for (int i = 0; i < n; i++) {
        freeDynamicArray(&arr[i]);
    }
    free(arr);

    *resultSize = resCount;
    return results;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    int** queries = malloc(q * sizeof(int*));

    for (int i = 0; i < q; i++) {
        queries[i] = malloc(3 * sizeof(int));
        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            queries[i][j] = parse_int(queries_item_temp[j]);
        }
    }

    int resultSize;
    int* result = dynamicArray(n, q, queries, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        fprintf(fptr, "%d\n", result[i]);
    }

    fclose(fptr);

    // Free allocated memory
    for (int i = 0; i < q; i++) {
        free(queries[i]);
    }
    free(queries);
    free(result);

    return 0;
}

// Function implementations
char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

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

        if (!data) {
            data = '\0';
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
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
        return '\0';
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
        exit(EXIT_FAILURE);
    }

    return value;
}

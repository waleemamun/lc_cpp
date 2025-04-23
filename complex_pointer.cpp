#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <functional>
#include <iostream>

int try_function_pointer() {
    // Define fp
    std::function<std::function<int()>(int, int)> fp;

    // Assign a lambda to fp
    fp = [](int a, int b) -> std::function<int()> {
        int sum = a + b;
        // Return a function that captures `sum` and returns it later
        return [sum]() {
            return sum * 2;
        };
    };

    // Usage
    std::function<int()> resultFunc = fp(3, 4);  // sum = 7, so resultFunc() = 14
    std::cout << "function pointer output " <<resultFunc() << std::endl;      // Outputs: 14

    return 0;
}

int main(int argc, char *argv[]) {
    // Setup some sample data for our examples
    char *args[] = {(char*)"program", (char*)"Hello", (char*)"World", NULL};
    // We can't reassign argv directly, so we'll use our own pointer
    char **my_argv = args; 
    int my_argc = 3;
    
    printf("Example data setup:\n");
    printf("my_argv[0] = \"%s\"\n", my_argv[0]);  // Output: "program"
    printf("my_argv[1] = \"%s\"\n", my_argv[1]);  // Output: "Hello"
    printf("my_argv[2] = \"%s\"\n\n", my_argv[2]);  // Output: "World"
    
    // Example 1: *++argv[1]
    char *original_arg1 = my_argv[1];
    printf("1. *++my_argv[1]:\n");
    printf("   Before: my_argv[1] points to \"%s\"\n", my_argv[1]);  // Output: "Hello"
    char result1 = *++my_argv[1];  // Increments pointer, then dereferences
    printf("   *++my_argv[1] = '%c'\n", result1);  // Output: 'e' (second char of "Hello")
    printf("   After: my_argv[1] now points to \"%s\"\n\n", my_argv[1]);  // Output: "ello"
    my_argv[1] = original_arg1; // Reset for next example
    
    // Example 2: **++argv
    printf("2. **++my_argv:\n");
    printf("   Before: my_argv points to \"%s\"\n", *my_argv);  // Output: "program"
    char **original_argv = my_argv; // Save for reset
    char result2 = **++my_argv;
    printf("   **++my_argv = '%c'\n", result2);  // Output: 'H' (first char of "Hello")
    printf("   After: my_argv now points to \"%s\"\n\n", *my_argv);  // Output: "Hello"
    my_argv = original_argv; // Reset for next example
    
    // Example 3: *(*p++)
    printf("3. *(*p++):\n");
    char **p = my_argv;
    printf("   Before: *p = \"%s\"\n", *p);  // Output: "program"
    //char result3 = *(*p++);
    printf("   *(*p++) = '%c'\n", *(*p++));  // Output: 'p' (first char of "program")
    printf("   After: *p = \"%s\"\n\n", *p);  // Output: "Hello"
    
    // Example 4: ++**ppp
    printf("4. ++**ppp:\n");
    char x = 'A';
    char *px = &x;
    char **ppx = &px;
    char ***ppp = &ppx;
    printf("   Before: **ppp points to '%c'\n", **(*ppp));  // Output: 'A'
    ++**(*ppp);
    printf("   After ++**ppp: **ppp now points to '%c'\n\n", **(*ppp));  // Output: 'B'
    
    // Example 5: *--(*arr + i)
    printf("5. *--(*arr + i):\n");
    char str[] = "abcdef";
    char *str_arr[1] = {str};
    char **arr = str_arr;
    int i = 2;
    printf("   *arr = \"%s\", i = %d\n", *arr, i);  // Output: "abcdef", 2
    
    // FIX: Create a temporary pointer that we can modify
    char *temp_ptr = *arr + i;  // Points to 'c'
    temp_ptr--;                 // Decrement to point to 'b'
    char result5 = *temp_ptr;   // Dereference to get 'b'
    
    printf("   Equivalent to *--(*arr + i) = '%c'\n\n", result5);  // Output: 'b'
    
    // Example 6: *p++ = **q--
    printf("6. *p++ = **q--:\n");
    char a = 'X';
    char b = 'Y';
    char *pa = &a;
    char *pb = &b;
    char **q = &pb;
    char *p_local = &a;
    printf("   Before: *p_local = '%c', **q = '%c'\n", *p_local, **q);  // Output: 'X', 'Y'
    *p_local++ = **q--;
    printf("   After: a = '%c', b = '%c'\n", a, b);  // Output: 'Y', 'Y'
    printf("   p_local now points %s original location\n\n", (p_local == &a) ? "to" : "past");  // Output: "past"
    
    // Example 7: (**(mat + i))[j]
    printf("7. (**(mat + i))[j]:\n");
    char matrix[2][3] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}};
    char **rows = (char **)malloc(2 * sizeof(char *));
    rows[0] = matrix[0];
    rows[1] = matrix[1];
    char ***mat = (char ***)malloc(sizeof(char **));
    *mat = rows;
    i = 1;
    int j = 2;
    printf("   Matrix = {{'a','b','c'},{'d','e','f'}}, i = %d, j = %d\n", i, j);
    // char result7 = (**(mat + i))[j]; // segement fault
    // printf("   (**(mat + i))[j] = '%c'\n\n", result7);  // Output: 'f'
    
    // Example 8: *(&(*p)[i])
    printf("8. *(&(*p)[i]):\n");
    char *array = (char *)"Hello";
    char **p_array = &array;
    i = 3;
    printf("   *p_array = \"%s\", i = %d\n", *p_array, i);  // Output: "Hello", 3
    char result8 = *(&(*p_array)[i]);
    printf("   *(&(*p_array)[i]) = '%c'\n\n", result8);  // Output: 'l'
    
    // Example 9: *++*pp
    printf("9. *++*pp:\n");
    char *ptr = (char *)"Test";
    char **pp = &ptr;
    printf("   Before: *pp points to \"%s\"\n", *pp);  // Output: "Test"
    char result9 = *++*pp;
    printf("   *++*pp = '%c'\n", result9);  // Output: 'e'
    printf("   After: *pp now points to \"%s\"\n\n", *pp);  // Output: "est"
    
    // Example 10: &**&p
    printf("10. &**&p:\n");
    ptr = (char *)"Demo";
    char **p_ptr = &ptr;
    printf("   p_ptr points to \"%s\"\n", *p_ptr);  // Output: "Demo"
    
    // FIX: Correct the pointer types
    char *temp_ptr10 = *p_ptr;          // Dereference p_ptr to get ptr
    char *result10 = temp_ptr10;        // Result is the address of the first char in "Demo"
    
    printf("   &**&p_ptr equivalent points to \"%s\"\n\n", result10);  // Output: "Demo"
    
    // Example 11: ++*&**q
    printf("11. ++*&**q:\n");
    char value = 'M';
    char *pvalue = &value;
    char **ppvalue = &pvalue;
    char ***q_val = &ppvalue;
    printf("   Before: value = '%c'\n", value);  // Output: 'M'
    ++*&**q_val;
    printf("   After ++*&**q_val: value = '%c'\n\n", value);  // Output: 'N'
    
    // Free allocated memory
    free(rows);
    free(mat);
    try_function_pointer();
    return 0;
}
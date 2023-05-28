# Coding Style

1. Use prefix ds (avoid conflicts with external libraries)
```c
// Macros, enums, constants (all capital letters separated by '_')
#define DS_ERROR_CODE 1
const int DS_SUCESS_CODE = 0;

// functions
int dsStackPush(){ ... }

// structs, typedefs, unions
typedef struct dsLinkedList {
    // local variables (no need for prefix)
    int prefer_snake_case;
    struct dsLinkedList *next;
} dsLinkedList_t;

// global variables
int dsGlobalVariable = 0;

// file names
"files_should_use_names_like_this.txt"
```

2. Avoid abreviations except universally-know such as:
    i,j,k for iterations
    T,U,V for generic types

3. Use tabs, not spaces

4. Each header file should have this boiler plate to ensure
    it is defined only once. The format is `<PROJECT>_<PATH>_<FILE>_H_` 
```c
// folder: foo/src/bar/baz.h
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_
...
#endif  // FOO_BAR_BAZ_H_ 
```

5. Include only what you use

6. Use inline functions if functions shouln't be exposed
    to the user of the library 

7. Use local variables as much as possible

8. ALWAYS declare a variable and initiate it
```c
// BAD 
int i,j;
i = f();
j = 1;

// GOOD
int i = f();
int j = 1;
```

9. Declare a variable only where you need.

10. Use TODO: comments

11. ALWAYS make explicit casting
```c
// bad
int *pointer = malloc(sizeof(int))

// good
int *pointer = (int *) malloc(sizeof(int))
```

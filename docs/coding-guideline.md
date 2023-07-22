# Coding Style

1. Use prefix `ds` for exposed things(avoid conflicts with external libraries) and prefix `_` for internal things

```c
// Macros, enums, constants (all capital letters separated by '_')
#define DS_ERROR_CODE 1
const int DS_SUCESS_CODE = 0;
#define _MAX(x,y) (x > y ? x : y)

// functions
int ds_stack_push(){ ... }
void _fix_something(){ ... }

// structs, typedefs, unions
typedef struct ds_linked_list {
    // local variables (no need for prefix)
    int prefer_snake_case;
    struct ds_linked_list *next;
} ds_linked_list_t;

struct _helper_type {
    int snake_case_still;
};

// global variables
int ds_global_variable = 0;
int _hidden_global_variable = 0;

// file names
"files_should_use_names_like_this.txt"
```

2. Avoid abreviations except universally-know such as:
   i,j,k for iterations

3. Use tabs, not spaces

4. Each header file should have this boiler plate to ensure
   it is defined only once. The format is `<IDENTIFIER>_H_`

```c
// folder: src/stack/stack.h
#ifndef STACK_H_
#define STACK_H_
...
#endif  /* STACK_H_ */

```

5. Include only headers you'll use

6. Use static functions if functions shouln't be exposed
   to any other file in the library

7. Use lesser scope variable as possible

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

10. make explicit casting if type isn't obvious at the sentence

```c
int *ptr = NULL;

// bad
ptr = malloc(sizeof(int))
// good
ptr = (int *) malloc(sizeof(int))
// good
int *pointer = malloc(sizeof(int))

```

11. don't use comma instead semi-colon for variables with different use cases

```c
// OK
int i = 0, j = 0, k = 0;

// bad
int *ptr = NULL, i = 0, nodes_count = 0;
```

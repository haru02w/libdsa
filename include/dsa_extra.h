#ifndef DSA_EXTRA_H_
#define DSA_EXTRA_H_

typedef unsigned char ds_byte_t;

typedef enum { DS_FALSE, DS_TRUE } ds_bool_t;

// General purpose index specifier
enum ds_abs_pos {
	DS_AT_START = -4,
	DS_AT_END = -1,
};

enum ds_rel_pos {
	DS_BEFORE = -3,
	DS_AFTER = -2,
};

// Function pointer type to compare elements
typedef int ds_comparator_ft(const void *, const void *);

#endif // !DSA_EXTRA_H_

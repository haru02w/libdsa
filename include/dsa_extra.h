#ifndef DSA_EXTRA_H_
#define DSA_EXTRA_H_

typedef unsigned char ds_byte_t;

typedef enum { DS_FALSE, DS_TRUE } ds_bool_t;

// General purpose index specifier
enum dsIndex {
	DS_AT_START = -2,
	DS_AT_END = -1,
};

#endif // !DSA_EXTRA_H_

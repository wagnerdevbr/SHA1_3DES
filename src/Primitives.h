#ifndef _PRIMITIVES_HPP
#define _PRIMITIVES_HPP


#ifdef __GNUC__

#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int8_t int8;


#else

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;


#define UINT8_MAX           0xff
#define UINT16_MAX          0xffff
#define UINT32_MAX          0xffffffff

#endif


#ifndef NULL
    #define NULL                                0
#endif

typedef enum {
    False = 0,
    True = 1
} Boolean;


#define SIZEOF_ARRAY( arrayObj )                    ( sizeof( arrayObj ) / sizeof( arrayObj[ 0 ] ))
#define BOOLEAN_TO_STRING( booleanValue ) \
    ( (booleanValue) ? "true" : "false" )


#endif //_PRIMITIVES_HPP

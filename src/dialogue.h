#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "raylib.h"

#define MAX_STRINGS     100

typedef struct {
    char*       str;
    int         curr_pos;
    int         size;
    float       delta;
} str8;

typedef struct dialogue_s {
    str8        strings[MAX_STRINGS];
    int         stringcount;
} dialogue_t;

extern Font dfont;

/**
 * @brief get the numerically smaller a or b
 * @param a number
 * @param b number
 * @return the smaller number of a and b
 */
#define MIN(a, b) (a > b ? b : a)
/**
 * @brief creates a 'str8': string (utf-8) with size
 * @param s a char array
 * @return 'str8' struct with a char array and an int size
 */
#define STR8_LITR(s) (str8) { .str = (char*)(s), .curr_pos = 0, .size = (sizeof(s)-1), .delta = 0.0f }
/**
 * @brief formats a const char* substring from a 'str8' struct
 * @param s pointer to a 'str8' struct
 * @param start an int telling where the substring will start
 * @param length an int size
 * @return const char* array that is length long
 */
#define STR8_SUBSTR(s, start, length) TextFormat("%.*s", MIN(length, s->size), (char*)((str8){ s->str+start, s->size-start}).str)

/**
 * @brief returns the position of 'count' newline in given string from 'str8' struct
 * @param s pointer to a 'str8' struct
 * @param count the nth newline to extract position from
 * @return int position of the nth 'count' newline in s->str
 */
int str8_findnewl(str8 *s, int count);  

void DrawDialogue(str8 *string, int posx, int posy);

#endif
#ifndef DIALOGUE_H
#define DIALOGUE_H
#include "raylib.h"

typedef struct str8_s {
    char*       str;
    int         curr_pos;
    int         size;
    float       delta;
    bool        done;
} str8_t;

extern Font dfont;

/**
 * @brief get the numerically smaller a or b
 * @param a number
 * @param b number
 * @return the smaller number of a and b
 */
#define MIN(a, b) (a > b ? b : a)
/**
 * @brief creates a 'str8_t': string (utf-8) with size
 * @param s a char array
 * @return 'str8_t' struct with a char array and an int size
 */
#define STR8_LITR(s) (str8_t) { .str = (char*)(s), .size = (sizeof(s)-1) }
/**
 * @brief formats a const char* substring from a 'str8_t' struct
 * @param s pointer to a 'str8_t' struct
 * @param start an int telling where the substring will start
 * @param length an int size
 * @return const char* array that is length long
 */
#define STR8_SUBSTR(s, start, length) TextFormat("%.*s", MIN(length, s->size), (char*)((str8_t){ s->str+start, s->size-start}).str)

/**
 * @brief draws a char* from a 'str8_t' struct pointer at position (posx,posy)
 * @param string pointer to a 'str8_t' struct
 * @param posx x-position
 * @param posy y-position
 */
void DrawDialogue(str8_t *string, int posx, int posy);

/**
 * @brief checks if the whole char* substring from a 'str8_t' struct pointer has been reaad
 * @param string pointer to a 'str8_t' struct
 * @return true if fully drawn, false otherwise
 */
bool IsDialogueDone(str8_t *string);

#endif
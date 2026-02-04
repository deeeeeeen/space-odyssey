#include "dialogue.h"

int str8_findnewl(str8 *s, int count) {
    if (count < 1) return -1;

    char *curr_char = s->str;
    int curr_count = 0;
    for (int pos = 0; pos < s->size; pos++) {
        if (*(curr_char+pos) == '\n') {
            curr_count++;
        }
        if (curr_count == count) {
            return pos+1;
        }
    }
}

void DrawDialogue(str8 *string, int posx, int posy) {
    string->delta += GetFrameTime();
    if (IsKeyPressed(KEY_ENTER)) {
        string->curr_pos = string->size;
    }
    if (string->delta > 0.05) {
        string->delta = 0;
        string->curr_pos++;
        string->curr_pos = MIN(string->curr_pos, string->size);
    }
    posy -= 6 * (string->curr_pos > str8_findnewl(string, 1) > 0 ? 1 : 0);
    
    DrawTextEx(dfont, STR8_SUBSTR(string, 0, string->curr_pos), (Vector2) { posx, posy }, dfont.baseSize, 0, WHITE);
}
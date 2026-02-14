#include "dialogue.h"

int str8_strtvispos(str8_t *s) {
    char *curr_char = s->str+s->curr_pos;
    int count = 0;
    for (int pos = 0; s->curr_pos-pos > 0; pos++) {
        if (*(curr_char-pos) == '\n') {
            count++;
        }
        if (count > 1) {
            return s->curr_pos-pos+1;
        }
    }
}

int str8_nlcount(str8_t *s) {
    char *curr_char = s->str+s->curr_pos-1;
    int nlcount = 0;
    for (int pos = 0; s->curr_pos-pos > 0; pos++) {
        if (*(curr_char-pos) == '\n') {
            nlcount++;
        }
    }
    return nlcount;
}

int str8_findnextstop(str8_t *s) {
    char *curr_char = s->str+s->curr_pos;
    for (int pos = 0; pos < s->size; pos++) {
        if (*(curr_char+pos) == '.' || *(curr_char+pos) == '?' || *(curr_char+pos) == '!') {
            return pos;
        }
    }
}

bool IsDialogueDone(str8_t *string) {
    return string->done;
}

int GetEndOfIdentifierPos(str8_t *string) {
    char *curr_char = string->str+string->curr_pos;
    for (int pos = 0; pos < string->size; pos++) {
        if (*(curr_char+pos) == ']') {
            return pos+2;
        }
    }
}

int GetEndOfSpaceFormatPos(str8_t *string) {
    char *curr_char = string->str+string->curr_pos;
    for (int pos = 0; pos < string->size; pos++) {
        if (*(curr_char+pos) != ' ') {
            return pos;
        }
    }
}

void DrawDialogue(str8_t *string, int posx, int posy) {
    int startpos = 0;

    if (string->curr_pos == string->size && IsKeyPressed(GetControl(C_CONFIRM))) {
        string->done = true;
    }
    string->delta += FrameGetDelta();

    if (string->str[string->curr_pos-1] == ' ' && string->str[string->curr_pos] == ' ') {
        string->curr_pos += GetEndOfSpaceFormatPos(string);
    }

    if (string->str[string->curr_pos-1] == '[') {
        string->curr_pos += GetEndOfIdentifierPos(string);
    }

    if (string->str[string->curr_pos-1] == '.' || string->str[string->curr_pos-1] == '?' || string->str[string->curr_pos-1] == '!') {
        if (IsKeyPressed(GetControl(C_CONFIRM))) {
            string->curr_pos++;
        }
    }
    else if (IsKeyPressed(GetControl(C_CONFIRM)) && (string->str[string->curr_pos-1] != '.' || string->str[string->curr_pos-1] != '?' || string->str[string->curr_pos-1] != '!')) {
        string->curr_pos += str8_findnextstop(string);
    }
    else if (string->delta > GetDialogueSpeed()) {
        string->delta = 0;
        string->curr_pos++;
        string->curr_pos = MIN(string->curr_pos, string->size);
    }

    if (str8_nlcount(string) > 0) {
        posy -= GetFont(DIALOGUE).baseSize/2.0;
    }
    if (str8_nlcount(string) > 1) {
        startpos = str8_strtvispos(string);
    }

    DrawTextEx(GetFont(DIALOGUE), STR8_SUBSTR(string, startpos, string->curr_pos-startpos), (Vector2) { posx, posy }, GetFont(DIALOGUE).baseSize, 0, WHITE);
}
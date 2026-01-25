#ifndef FRAME_H
#define FRAME_H

#include "raylib.h"
#include "player.h"

typedef struct frame_s    frame_t;

typedef struct frame_s {
    Camera2D camera;
} frame_t;

void InitFrame(frame_t *framemgr);

#endif
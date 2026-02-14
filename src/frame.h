#ifndef FRAME_H
#define FRAME_H

#include "raylib.h"

typedef struct frame_s    frame_t;

typedef struct frame_s {
    Camera2D camera;
} frame_t;

/**
 * @brief refresh the static float delta using raylib's GetFrameTime()
 */
void FrameUpdateDelta();

/**
 * @brief get the static float delta's value
 * @return GetFrameTime()
 */
float FrameGetDelta();

void InitFrame(frame_t *framemgr);

#endif
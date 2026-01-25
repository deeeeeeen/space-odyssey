#include "frame.h"

void InitFrame(frame_t *framemgr) {
    framemgr->camera.offset = (Vector2){ 0.f, 0.f };
    framemgr->camera.zoom = 1.0f;

    TraceLog(LOG_INFO, "FRAME: Initialised!");
}
#include "semState.h"

void incr(enum semState *state) {
  switch(*state) {
    case LEFT:
      *state = LTOR;
      return;
    case LTOR:
      *state = RIGHT;
      return;
    case RTOL:
      *state = LEFT;
      return;
    case RIGHT:
      *state = RTOL;
      return;
  }
}
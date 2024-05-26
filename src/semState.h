#ifndef __ROB_SEM_STATE__
#define __ROB_SEM_STATE__

enum semState {
  LEFT = 0,
  LTOR = 1,
  RIGHT = 2,
  RTOL = 3
};

void incr(enum semState*);

#endif
#include "../inc/Timer.hpp"

/* chrono::steady_clock::time_point timeStart =
chrono::steady_clock::now(); */

decisecond timeDelta;

bool doNotTiming = true;

status action;

mutex mut;
condition_variable cvar;
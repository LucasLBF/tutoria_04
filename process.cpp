#include "process.h"

Process createProcess(int arrivalTime, int duration) {
  Process p;
  p.arrivalTime = arrivalTime;
  p.duration = duration;
  return p;
}

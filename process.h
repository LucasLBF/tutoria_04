#ifndef PROCESS_H
#define PROCESS_H

struct Process {
  int arrivalTime;
  int duration;
  int remainingDuration;
};

Process createProcess(int arrivalTime, int duration);

#endif

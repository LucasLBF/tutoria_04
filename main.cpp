#include "process.h"
#include "roundRobin.h"
#include <iostream>
#include <list>

using namespace std;

int main() {
  int processQty = 0, timeQuantum = 0;
  int arrivalTime = 0, duration = 0;
  list<Process> processes;
  cin >> processQty >> timeQuantum;
  for (int i = 0; i < processQty; i++) {
    cin >> arrivalTime >> duration;
    processes.push_back(createProcess(arrivalTime, duration));
  }

  roundRobin(processes, timeQuantum);
}

#include "roundRobin.h"
#include <iostream>
#include <queue>

void roundRobin(std::list<Process> processes, int quantum) {
  double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
         responseTimeAverage = 0.0;
  int finishTime = 0, waitTime = 0, responseTime = 0, i = quantum;
  int processQty = processes.size();
  std::list<Process>::iterator it = processes.begin();
  Process running;
  std::queue<Process> processQueue;
  bool processRunning = false;
  for (int clock = 0; true; clock++) {

    // adicionar processos com mesmo arrivalTime a fila
    while (it != processes.end() && clock == (*it).arrivalTime) {
      processes.push_back((*it));
      it++;
    }
    // caso não haja processos executando, adicionar o primeiro processo da fila
    // no processador e resetar o quantum
    if (!processRunning) {
      if (!processes.empty()) {
        running = processes.front();
        processes.pop_front();
        processRunning = true;
        i = quantum;
        // armazenar o responseTime do processo executando pela primeira vez
        if (running.duration == running.remainingDuration) {
          responseTime = clock - running.arrivalTime;
        }
      } else {
        if (it == processes.end()) {
          break;
        }
      }
      //
    } else {
      running.remainingDuration--;
      i--;
      if (running.remainingDuration == 0) {
        finishTime = waitTime + running.duration;
        processRunning = false;
        finishTimeAverage += finishTime;
        responseTimeAverage += responseTime;
        waitTimeAverage += waitTime;

        finishTime = 0;
        responseTime = 0;
        waitTime = 0;
        continue;
      } else if (i == 0) {
        processes.push_back(running);
        processRunning = false;
      }
    }
  }
  std::cout << "RR" << finishTimeAverage << " " << responseTimeAverage << " "
            << waitTimeAverage << std::endl;
}

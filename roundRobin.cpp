#include "roundRobin.h"
#include <iostream>
#include <queue>

void roundRobin(std::list<Process> processes, int quantum) {
  double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
         responseTimeAverage = 0.0;
  int finishTime = 0, waitTime = 0, responseTime = 0, i = quantum;
  int processQty = processes.size();
  std::list<Process>::iterator it = processes.begin();
  std::list<Process>::iterator it2;
  Process running;
  std::queue<Process> processQueue;
  bool processRunning = false;
  for (int clock = 0; true; clock++) {

    // adicionar processos com mesmo arrivalTime a fila
    while (it != processes.end() && clock == it->arrivalTime) {
      std::cout << "pushing: " << it->remainingDuration << std::endl;
      processQueue.push((*it));
      it++;
    }
    // caso não haja processos executando, adicionar o primeiro processo da fila
    // no processador e resetar o quantum
    if (!processRunning) {
      if (!processQueue.empty()) {
        // std::cout << "===== current processes queue =====" << std::endl;
        // for (it2 = processQueue.begin(); it2 != processQueue.end(); it2++) {
        // std::cout << it2->remainingDuration << std::endl;
        //}
        running = processQueue.front();
        std::cout << "scheduling new process: " << running.remainingDuration
                  << std::endl;
        processQueue.pop();
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
    } else {
      std::cout << "executing process..." << std::endl;
      running.remainingDuration--;
      std::cout << "remaining duration is now " << running.remainingDuration
                << std::endl;
      i--;
      if (running.remainingDuration <= 0) {
        finishTime = clock - running.arrivalTime;
        waitTime = finishTime - running.duration;
        processRunning = false;
        finishTimeAverage += finishTime;
        responseTimeAverage += responseTime;
        waitTimeAverage += waitTime;

        finishTime = 0;
        responseTime = 0;
        waitTime = 0;
        continue;
      } else if (i == 0) {
        std::cout << "Time quantum expired. Storing process: "
                  << running.remainingDuration << std::endl;
        processQueue.push(running);
        processRunning = false;
      }
    }
  }
  finishTimeAverage /= processQty;
  responseTimeAverage /= processQty;
  waitTimeAverage /= processQty;
  std::cout << "RR " << finishTimeAverage << " " << responseTimeAverage << " "
            << waitTimeAverage << std::endl;
}

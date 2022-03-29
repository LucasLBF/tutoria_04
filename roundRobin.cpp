#include "roundRobin.h"
#include <iomanip>
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

    // adicionar processos que acabaram de chegar na fila
    // de ready
    // std::cout << "current clock: " << clock << std::endl;
    while (it != processes.end() && clock == it->arrivalTime) {
      // std::cout << "pushing: " << it->remainingDuration << std::endl;
      processQueue.push((*it));
      it++;
    }

    // adicionar o processo que acabou seu time slice
    // no final da fila de ready
    if (i == 0 && running.arrivalTime >= 0 && running.remainingDuration > 0) {
      processQueue.push(running);
    }
    // caso não haja processos executando, adicionar o primeiro processo da fila
    // no processador e resetar o quantum
    if (!processRunning) {
      if (!processQueue.empty()) {
        running = processQueue.front();
        // std::cout << "scheduling new process: " << running.remainingDuration
        //          << std::endl;
        processQueue.pop();
        processRunning = true;
        i = quantum;
        // armazenar o responseTime do processo executando pela primeira vez
        if (running.duration == running.remainingDuration) {
          responseTime = clock - running.arrivalTime;
          responseTimeAverage += responseTime;
          responseTime = 0;
        }
      } else {
        if (it == processes.end()) {
          break;
        }
      }
    }
    // std::cout << "executing process..." << std::endl;
    running.remainingDuration--;
    // std::cout << "remaining duration is now " << running.remainingDuration
    //          << std::endl;
    i--;
    if (running.remainingDuration == 0) {
      finishTime = clock - running.arrivalTime + 1;
      waitTime = finishTime - running.duration;
      processRunning = false;
      finishTimeAverage += finishTime;
      waitTimeAverage += waitTime;
      // std::cout << "finish time: " << finishTimeAverage << std::endl;
      // std::cout << "response time: " << responseTimeAverage << std::endl;
      // std::cout << "wait time: " << waitTimeAverage << std::endl;

      finishTime = 0;
      waitTime = 0;
      continue;
    } else if (i == 0) {
      // std::cout << "Time quantum expired. Storing process: "
      //           << running.remainingDuration << std::endl;
      //  processQueue.push(running);
      processRunning = false;
    }
  }
  finishTimeAverage /= processQty;
  responseTimeAverage /= processQty;
  waitTimeAverage /= processQty;
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  std::cout << "RR " << finishTimeAverage << " " << responseTimeAverage << " "
            << waitTimeAverage << std::endl;
}

#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "process.h"
#include <list>

void roundRobin(std::list<Process> processes, int quantum);

#endif

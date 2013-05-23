/*
 * File Name: ProcessManager.h
 * Date:      May 16, 2013
 * Author:    Milan Sobat
 * Student #: 0469245
 * Course:    INFO-5051
 * Purpose:   A Process manager to contain all the Process classes.
 */

#ifndef __PROCESSMANAGER_H__
#define __PROCESSMANAGER_H__

#include <memory>
#include <vector>
#include "Process.h"

typedef std::shared_ptr<Process> process_ptr;

class ProcessManager : public Process {
private:
	std::vector<process_ptr> _vecProcesses;

public:
	ProcessManager() : Process() {}
	virtual ~ProcessManager() {}

	void addProcess( Process* prc ) {
		process_ptr ptr( prc );
		_vecProcesses.push_back( ptr );
	}

	size_t getVecSize() { return _vecProcesses.size(); }
	std::vector<process_ptr> getVector() { return _vecProcesses; }
};

#endif
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
	std::vector<process_ptr> getProcesses() { return _vecProcesses; }
};

#endif
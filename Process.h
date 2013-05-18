#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <string>

class Process {
private:
	int _launchGroup;
	std::string _programName;
	std::string _cmdLnPrmtrs;

public:
	Process () : _launchGroup( 0 ), _programName( "" ), _cmdLnPrmtrs( "" ) {}
	Process ( int lnchGrp, std::string prgName, std::string cmdPrmtrs ) : _launchGroup( lnchGrp ), _programName( prgName ), _cmdLnPrmtrs( cmdPrmtrs ) {}
	virtual ~Process() {}

	int getLaunchGroup() { return _launchGroup; }
	std::string getProgramName() { return _programName; }
	std::string getCmdLnPars() { return _cmdLnPrmtrs; }

	void setLaunchGroup( int num ) {
		_launchGroup = num;
	}
	void setProgramName( std::string name ) {
		_programName = name;
	}
	void setCommandLinePars( std::string cmdLnPars ) {
		_cmdLnPrmtrs = cmdLnPars;
	}
};

#endif
/*
 * File Name: Process.h
 * Date:      May 16, 2013
 * Author:    Milan Sobat
 * Student #: 0469245
 * Course:    INFO-5051
 * Purpose:   Container class for a process to be launched.
 */

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <string>

class Process {
private:
	int _launchGroup;
	std::wstring _programName;
	std::wstring _cmdLnPrmtrs;

public:
	Process () : _launchGroup( 0 ), _programName( L"" ), _cmdLnPrmtrs( L"" ) {}
	Process ( int lnchGrp, std::wstring prgName, std::wstring cmdPrmtrs ) : _launchGroup( lnchGrp ), _programName( prgName ), _cmdLnPrmtrs( cmdPrmtrs ) {}
	virtual ~Process() {}

	int getLaunchGroup() { return _launchGroup; }
	std::wstring getProgramName() { return _programName; }
	std::wstring getCmdLnPars() { return _cmdLnPrmtrs; }

	void setLaunchGroup( int num ) {
		_launchGroup = num;
	}
	void setProgramName( std::wstring name ) {
		_programName = name;
	}
	void setCommandLinePars( std::wstring cmdLnPars ) {
		_cmdLnPrmtrs = cmdLnPars;
	}

	bool operator == ( Process& rhs ) {
		return _launchGroup == rhs.getLaunchGroup();
	}

	bool operator < ( Process& rhs ) {
		return _launchGroup < rhs.getLaunchGroup() || ( _launchGroup == rhs.getLaunchGroup() && _launchGroup < rhs.getLaunchGroup());
	}
};

#endif
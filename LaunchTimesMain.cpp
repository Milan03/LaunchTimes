/*
 * File Name: LaunchTimesMain.cpp
 * Date:      May 16, 2013
 * Author:    Milan Sobat
 * Student #: 0469245
 * Course:    INFO-5051
 * Purpose:   Launches and times a set of processes. The processes and times are 
			  provided via a ASCII text file given on the command line.
 */
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <process.h>
#include <algorithm>
#include <map>
#include <iomanip>

#include "Process.h"
#include "ProcessManager.h"

using namespace std;

typedef std::shared_ptr<Process> process_ptr;

/*
 * Function Name: AppendFile
 * Purpose:       Takes in a file input and appends commas to it for delimiting
				  purposes.
 * Accepts:       theFile -- file input from user
 * Returns:       Nothing
 */
void AppendFile( wstring theFile ) {
	wstring glStr = L"";
	// Open filestream
	wifstream fileStream ( theFile.c_str(), ios::in );
	if ( !fileStream.is_open() ) {
		cout << "Unable to open file." << endl;
		//return prcsMngr;
	}

	// Append comma to each line for delimiting purposes
	wstringstream buffer;
	while ( getline( fileStream, glStr )) 
		buffer << glStr+L",\n";
	wofstream fout( theFile, ios::out );
	fout << buffer.rdbuf();
	fileStream.close();
}

/*
 * Function Name: LoadFile
 * Purpose:       Takes in a file input and extracts the data to a Process class.
 * Accepts:       theFile -- file input from user
 * Returns:       ProcessManager -- holds a vector of Process classes
 */
ProcessManager LoadFile( wstring theFile ) {
	string comma  = ",";
	ProcessManager prcsMngr = ProcessManager();
	wstring glStr = L"";



	wifstream fileStream ( theFile.c_str(), ios::in );
	if ( !fileStream.is_open() ) {
		cout << "Unable to open file." << endl;
		return prcsMngr;
	}
	// Create Process objects
	bool loopDone = false;
	glStr = L"";
	while ( !fileStream.eof() && !loopDone ) {
		Process* prcs = new Process();
		for ( int i = 0; i < 3; ++i ) {
			getline( fileStream, glStr, L',' );
			if ( i == 0 ) {
				try {
					prcs->setLaunchGroup( stoi( glStr ) );
				} catch ( invalid_argument e ) { // catch bad input such as '\n'
					loopDone = true;
					break;
				}
			} else if ( i == 1 ) {
				try {
					prcs->setProgramName( glStr );
				} catch ( invalid_argument e ) { 
					loopDone = true;
					break;
				}
			} else {
				try {
					prcs->setCommandLinePars( glStr );
				} catch ( invalid_argument e ) { 
					loopDone = true;
					break;
				}
			}
		}
		if ( !loopDone )
			prcsMngr.addProcess( prcs );
		else if ( loopDone && !fileStream.eof() )
			wcerr << "Problem parsing file." << endl;
	}

	return prcsMngr;
	
	// Close the file stream
	fileStream.close();
}

int main( int argc, char* argv[] ) {
	// Must be 2 command line arguements
	if( argc != 2 ) { 
		cout << "Error: invalid command line" << endl;
		return -1;
	}

	// Get input file
	wstring theFile = L"";
	wcin >> theFile;

	AppendFile( theFile );
	ProcessManager prcsMngr = ProcessManager();
	prcsMngr = LoadFile( theFile );
	
	vector<process_ptr> vecProcesses = prcsMngr.getVector();

	vector<Process> vP;

	for ( unsigned i = 0; i < vecProcesses.size(); ++i ) {
		Process newPrcs = Process( vecProcesses[i]->getLaunchGroup(), vecProcesses[i]->getProgramName(), 
			vecProcesses[i]->getCmdLnPars() );
		vP.push_back( newPrcs );
	}

	sort( vP.begin(), vP.end() );

	map<int, vector<Process>> vecMap;

	// Put processes in map with each group holding the associated processes to be launched
	for ( unsigned i = 0; i < vP.size(); ++i ) {
		vecMap[ vP[i].getLaunchGroup() ].push_back( vP[i] );
	}
	
	cout << "LaunchTimes - Milan Sobat 2013" << endl;
	cout << endl;
	typedef map<int, vector<Process>>::iterator it;	
	
	// Go through each group in map and call CreateProcess
	for ( it iterator = vecMap.begin(); iterator != vecMap.end(); iterator++ ) {
		// Vector to hold handles from CreateProcess
		vector<HANDLE> vecHandles;

		// Go through each group and call CreateProcess
		// Store the CreateProcess handle in vecHandles
		for ( unsigned i = 0; i < iterator->second.size(); ++i ) {
			wstring program = iterator->second[i].getProgramName();
			wstring params = iterator->second[i].getCmdLnPars();
			wstring command = program + L" " + params;

			STARTUPINFO sinfo = { 0 };
			sinfo.cb = sizeof(STARTUPINFO);
			PROCESS_INFORMATION pi = { 0 };

			//Buffer
			try {
				unsigned long const CP_MAX_COMMAND_LINE = 32768;
				wchar_t* commandLine = new wchar_t [CP_MAX_COMMAND_LINE];

				//copy from wide string to wchar_t[]
				wcsncpy_s( commandLine, CP_MAX_COMMAND_LINE, command.c_str(),											command.size() + 1 );

				CreateProcess( NULL, //app name is in the command line param
					commandLine,     //full command line (appname + params)
					NULL,			 //process securtiy
					NULL,			 //main thread security
					false,
					0x00000010,
					NULL,
					NULL,			 
					&sinfo,
					&pi );


				delete [] commandLine;
			} catch ( bad_alloc ) {
				wcerr << L"Insuffiecient memory to launch application" << endl;
			}
			vecHandles.push_back( pi.hProcess );

		}

		// If only one handle, lauch serially
		if ( vecHandles.size() < 2 ) 
			WaitForSingleObject( vecHandles[0], INFINITE );
		else // Else launch all together
			WaitForMultipleObjects( vecHandles.size(),  vecHandles.data(), true, INFINITE );

		// Output
		for ( unsigned i = 0; i < vecHandles.size(); ++i ) {
			DWORD exitCode;
			GetExitCodeProcess( vecHandles[i], &exitCode );
			FILETIME creationTime, exitTime, kernelTime, userTime;
			GetProcessTimes( vecHandles[i], &creationTime, &exitTime, &kernelTime, &userTime );
			SYSTEMTIME kTime, uTime;
			FileTimeToSystemTime( &kernelTime, &kTime );
			FileTimeToSystemTime( &userTime, &uTime );
			
			wcout << "K:" << kTime.wHour << ":" << setw(2) << setfill(L'0') << kTime.wMinute << ":" << setw(2) << setfill(L'0') << kTime.wSecond << "." << kTime.wMilliseconds << 
				" U:" << uTime.wHour << ":" << setw(2) << setfill(L'0') << uTime.wMinute << ":" << setw(2) << setfill(L'0') << uTime.wSecond << "." << uTime.wMilliseconds << 
				" E:" << exitCode << 
				" G:" << iterator->second[i].getLaunchGroup() <<
				" " <<  iterator->second[i].getProgramName() << " " << iterator->second[i].getCmdLnPars() << endl;

		}
		cout << endl;
		// Close handles
		for ( unsigned i = 0; i < vecHandles.size(); ++i )
			CloseHandle( vecHandles[i] );

	}
	return 0;		
};
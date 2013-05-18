/*
 * File Name: LaunchTimesMain.cpp
 * Date:      May 16, 2013
 * Author:    Milan Sobat
 * Student #: 0469245
 * Course:    INFO-5051
 * Purpose:   Launches and times a set of processes. The processes and times are 
			  provided via a ASCII text file given on the command line.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Process.h"
#include "ProcessManager.h"

using namespace std;

/*
 * Function Name: LoadFile
 * Purpose:       Takes in a file input and extracts the data to a Process class.
 * Accepts:       theFile -- file input from user
 * Returns:       ProcessManager -- holds a vector of Process classes
 */
ProcessManager LoadFile( string theFile ) {
	string comma  = ",";
	ProcessManager prcsMngr = ProcessManager();
	string glStr;

	// Open filestream
	ifstream fileStream ( theFile.c_str(), ios::in );
	if ( !fileStream.is_open() ) {
		cout << "Unable to open file." << endl;
		return prcsMngr;
	}

	// Append comma to each line for delimiting purposes
	//stringstream buffer;
	//while ( getline( fileStream, glStr )) 
	//	buffer << glStr+",\n";
	//ofstream fout( theFile, ios::out );
	//fout << buffer.rdbuf();
	
	// Create Process objects
	bool loopDone = false;
	glStr = "";
	while ( !fileStream.eof() ) {
	Process* prcs = new Process();
		for ( int i = 0; i < 3; ++i ) {
			getline( fileStream, glStr, ',' );
			if ( i == 0 ) {
				try {
					prcs->setLaunchGroup( stoi( glStr ) );
				} catch ( invalid_argument e ) { // catch bad input such as '\n'
					int breakpoint = 0;
					loopDone = true;
					break;
				}
			} else if ( i == 1 ) {
				prcs->setProgramName( glStr );
			} else
				prcs->setCommandLinePars( glStr );
		}
		if ( !loopDone )
			prcsMngr.addProcess( prcs );

	}

	return prcsMngr;
	
	// Close the file stream
	fileStream.close();
}

//int main( int argc, char* argv[] ) {
//	// Must be 2 command line arguements
//	if( argc != 2 ) { 
//		cout << "Error: invalid command line" << endl;
//		return -1;
//	}
//
//	// Get input file
//	string theFile = "";
//	cin >> theFile;
//
//	ProcessManager prcsMngr = ProcessManager();
//	prcsMngr = LoadFile( theFile );
//
//	int breakpoint = 0;
//
//	return 0;
//		
//};
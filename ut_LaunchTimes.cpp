/*
 * File Name: ut_LaunchTimes.cpp
 * Date:      May 18, 2013
 * Author:    Milan Sobat
 * Student #: 0469245
 * Course:    INFO-5051
 * Purpose:   Unit test class to test classes/functions of LaunchTimes
 */

#define BOOST_TEST_MODULE LaunchTimesTest
#include <boost\test\auto_unit_test.hpp>
#include <iostream>

using namespace std;

#include "Process.h"
#include "ProcessManager.h"

typedef std::shared_ptr<Process> process_ptr;

BOOST_AUTO_TEST_CASE( introduction ) {
	cout << "\nLaunchTimes Unit Test." << endl;
	cout << "Last compiled: " __TIMESTAMP__ << endl;
}

BOOST_AUTO_TEST_CASE( process_constructor_test ) {
	Process p = Process();

	BOOST_CHECK( p.getLaunchGroup() == 0 );
	BOOST_CHECK( p.getCmdLnPars() == L"" );
	BOOST_CHECK( p.getProgramName() == L"" );
}

BOOST_AUTO_TEST_CASE( process_three_arg_constructor_test ) {
	Process p = Process( 1, L"ShellCommand", L"10 10000" );

	BOOST_CHECK( p.getLaunchGroup() == 1 );
	BOOST_CHECK( p.getCmdLnPars() == L"10 10000" );
	BOOST_CHECK( p.getProgramName() == L"ShellCommand" );
}

BOOST_AUTO_TEST_CASE( process_equal_op_test ) {
	Process p = Process( 1, L"ShellCommand", L"10 10000" );
	Process p2 = Process( 1, L"ShellCommand", L"10 10000" );
	Process p3 = Process( 2, L"ShellCommand", L"10 10000" );

	BOOST_CHECK( p.getLaunchGroup() == p2.getLaunchGroup() );
	BOOST_CHECK( p.getLaunchGroup() != p3.getLaunchGroup() );
}

BOOST_AUTO_TEST_CASE( process_manager_constructor_test ) {
	ProcessManager pm = ProcessManager();

	// Check that the vector was created
	BOOST_CHECK( pm.getVecSize() == 0 );
}

BOOST_AUTO_TEST_CASE( process_manager_add_process_test ) {
	ProcessManager pm = ProcessManager();
	Process* p = new Process( 1, L"ShellCommand", L"10 10000" );
	pm.addProcess( p );

	// Check size of vector to see if pushed back
	BOOST_CHECK( pm.getVecSize() == 1 );
}

BOOST_AUTO_TEST_CASE( process_manager_get_vector_test ) {
	ProcessManager pm = ProcessManager();
	Process* p = new Process( 1, L"ShellCommand", L"10 10000" );
	pm.addProcess( p );

	vector<process_ptr> tempVec = pm.getVector();

	// Check size of vector to see if pushed back
	BOOST_CHECK( pm.getVecSize() == tempVec.size() );
}
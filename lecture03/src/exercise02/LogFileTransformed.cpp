//
// Created by KasperSK on 14-09-2016.
//

//
// Created by kaspersk on 9/14/16.
//



#include <lecture03/exercise02/LogFileTransformed.h>
#include <iostream>
#include <fstream>
#include <exception>


using namespace std;
using namespace exercise02;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogFileTransformed::LogFileTransformed()
{
    cout << "Creating LogFile Object" << endl;
}

LogFileTransformed::LogFileTransformed( const string& logfilename )
{
    init( logfilename );
}

LogFileTransformed::~LogFileTransformed()
{
    cout << "Deleting LogFile Object" << endl;
}

void LogFileTransformed::init( const string& logfilename )
{
    if( logfilename_ == "" )
    {
        throw std::invalid_argument("File name is empty");
    }
    logfilename_ = logfilename;
}

void LogFileTransformed::write( const string& data )
{
    if( logfilename_ == "" )
    {
        throw std::invalid_argument("LogFile is not initialized");
    }
    std::ofstream out;
    out.open( logfilename_.c_str(), std::ofstream::out | std::ofstream::app);
    if( out )
        out << data+"\n";
    else
    {
        cerr << "Cannot open file " << logfilename_ << endl;
        throw std::runtime_error("Could not open file");

    }
}

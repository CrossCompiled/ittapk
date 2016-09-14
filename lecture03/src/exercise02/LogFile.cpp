//
// Created by kaspersk on 9/14/16.
//



#include <lecture03/exercise02/LogFile.h>
#include <iostream>
#include <fstream>
#include <exception>


using namespace std;
using namespace exercise02;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogFile::LogFile()
{
    state_ = es_NOT_INITIALIZED;
    cout << "Creating LogFile Object" << endl;
}

LogFile::LogFile( const string& logfilename )
{
    init( logfilename );
}

LogFile::~LogFile()
{
    cout << "Deleting LogFile Object" << endl;
}

void LogFile::init( const string& logfilename )
{
    state_ = es_OK;
    logfilename_ = logfilename;
    internalWrite( "" );

}

void LogFile::write( const string& data )
{
    internalWrite( data+"\n" );
}

bool LogFile::internalWrite( const string& data )
{
    if(state_ != es_OK){
        throw std::runtime_error("Logfile not initialized");
    }
    if( logfilename_ == "" )
    {
        //state_ = es_FILENAME_IS_EMPTY;
        //return false;
        throw std::invalid_argument("File name is empty");
    }
    std::ofstream out;
    out.open( logfilename_.c_str(), std::ofstream::out | std::ofstream::app);
    if( out )
        out << data;
    else
    {
        //state_ = es_COULD_NOT_OPEN_FILE;
        cerr << "Cannot open file " << logfilename_ << endl;
        throw std::runtime_error("Could not open file");
        //return false;
    }
    //state_ = es_OK;
    return true;
}
//
// Created by kaspersk on 9/14/16.
//

// ProgramTransformation.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <lecture03/exercise02/LogFile.h>

using namespace std;

typedef exercise02::LogFile LogFile;

int main()
{
    {
        try {
            LogFile dummy;
            dummy.write("Writing from main");
        } catch (std::exception& e) {
            cerr << e.what() << endl;
        }
    }

    try {
        LogFile logFile( "Exceptions.log" );
        logFile.write( "Writing from main" );
        logFile.write( "Writing from main - again" );
    } catch (std::exception& e) {
        cerr << e.what() << endl;
    }

 /*   else if(!logFile.write( "Writing from main" ) )
    {
        switch( logFile.getState() )
        {
            case LogFile::es_OK:
                break;
            case LogFile::es_NOT_INITIALIZED:
                cerr << "LogFile not initialized" << endl;
                break;
            case LogFile::es_COULD_NOT_OPEN_FILE:
                cerr << "Could not open LogFile" << endl;
                break;
            case LogFile::es_FILENAME_IS_EMPTY:
                cerr << "LogFile filename is empty" << endl;
                break;
        }
    }

    if(logFile.getState() == LogFile::es_OK)
        if( !logFile.write( "Writing from main - again" ) )
        {
            switch( logFile.getState() )
            {
                case LogFile::es_OK:
                    break;
                case LogFile::es_NOT_INITIALIZED:
                    cerr << "LogFile not initialized" << endl;
                    break;
                case LogFile::es_COULD_NOT_OPEN_FILE:
                    cerr << "Could not open LogFile" << endl;
                    break;
                case LogFile::es_FILENAME_IS_EMPTY:
                    cerr << "LogFile filename is empty" << endl;
                    break;
            }
        }*/
}
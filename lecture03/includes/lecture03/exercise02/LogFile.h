//
// Created by kaspersk on 9/14/16.
//

#ifndef LECTURE03_LOGFILE_H
#define LECTURE03_LOGFILE_H

#include <string>
#include <stdexcept>

namespace exercise02 {

    class LogFile {
    public:
        enum EState {
            es_OK, es_NOT_INITIALIZED, es_COULD_NOT_OPEN_FILE, es_FILENAME_IS_EMPTY
        };

        void write(const std::string &data);

        void init(const std::string &logfilename);

        //EState getState() { return state_; }


        LogFile();

        explicit LogFile(const std::string &logfilename);

        ~LogFile();

    private:
        std::string logfilename_;
        EState state_;

        bool internalWrite(const std::string &data);
    };

}

#endif //LECTURE03_LOGFILE_H

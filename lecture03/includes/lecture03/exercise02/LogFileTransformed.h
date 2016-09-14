//
// Created by KasperSK on 14-09-2016.
//

#ifndef LECTURE03_LOGFILETRANSFORMED_H
#define LECTURE03_LOGFILETRANSFORMED_H

#include <string>
#include <stdexcept>

namespace exercise02 {

    class LogFileTransformed {
    public:
        void write(const std::string &data);

        void init(const std::string &logfilename);

        LogFileTransformed();

        explicit LogFileTransformed(const std::string &logfilename);

        ~LogFileTransformed();

    private:
        std::string logfilename_;
    };

}
#endif //LECTURE03_LOGFILETRANSFORMED_H

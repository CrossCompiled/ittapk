#ifndef LECTURE06_EXERCISE01_TIMER_HPP_
#define LECTURE06_EXERCISE01_TIMER_HPP_

#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <boost/any.hpp>

namespace exercise01 {


    class Timer {
    public:
        explicit Timer(int timer = 10);
        ~Timer();
        int attach(std::function<void(const std::shared_ptr<Event>&)> cb);
        void detach(int cbId);

    private:
        int timerThreadFunction();
        void notifyAll(const std::shared_ptr<Event>& any);

    private:
        int eventTimer_;
        std::thread *thread_;
        bool terminator_;
        std::unordered_map< int, std::function<void(const std::shared_ptr<Event>&)> > cbs_;
        int cbscounter_;
    };


}


#endif

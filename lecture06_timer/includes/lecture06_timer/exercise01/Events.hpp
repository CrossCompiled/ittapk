#ifndef LECTURE06_EXERCISE01_EVENTS_HPP_
#define LECTURE06_EXERCISE01_EVENTS_HPP_

#include <chrono>

namespace exercise01 {
    /**
 * Event
 */
    class Event
    {
    public:
        Event()
                : creationTime_(std::chrono::system_clock::now())
        {
        }
        std::chrono::time_point<std::chrono::system_clock> creationTime() const
        {
          return creationTime_;
        }
        virtual ~Event(){}; // Event need to be polymorphic

    private:
        std::chrono::time_point<std::chrono::system_clock> creationTime_;
    };


/**
 * EventOther
 */
    class EventOther : public Event {};



}

std::ostream& operator<<(std::ostream& os, const exercise01::Event& ev);




#endif

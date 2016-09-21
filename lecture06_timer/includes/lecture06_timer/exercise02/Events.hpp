#ifndef LECTURE06_EXERCISE02_EVENTS_HPP_
#define LECTURE06_EXERCISE02_EVENTS_HPP_

#include <chrono>

namespace exercise02 {
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

std::ostream& operator<<(std::ostream& os, const exercise02::Event& ev);




#endif

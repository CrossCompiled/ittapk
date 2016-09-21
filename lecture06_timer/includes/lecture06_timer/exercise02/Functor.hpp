//
// Created by Kalle Møller on 21/09/16.
//

#ifndef LECTURE06_EXERCISE02_FUNCTOR_H
#define LECTURE06_EXERCISE02_FUNCTOR_H

#include <lecture06_timer/exercise02/Events.hpp>

namespace exercise02 {
    class Functor {
    public:
        Functor(std::mutex* stdioProt);
        ~Functor();
        void operator()(const std::shared_ptr<exercise02::Event>& event);
    private:
        int count;
        std::mutex* stdioProt;
    };
}


#endif //LECTURE06_EXERCISE02_FUNCTOR_H

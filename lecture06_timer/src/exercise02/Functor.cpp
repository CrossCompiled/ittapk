//
// Created by Kalle Møller on 21/09/16.
//
#include <iostream>
#include <mutex>
#include <lecture06_timer/exercise02/Functor.hpp>

exercise02::Functor::Functor(std::mutex* stdioProt) : count(0), stdioProt(stdioProt) {}

void exercise02::Functor::operator()(const std::shared_ptr<exercise02::Event>& event) {
    ++count;
    std::lock_guard<std::mutex> lock(*stdioProt );
    std::cout << "I've been called " << count << " times." << std::endl;
}

exercise02::Functor::~Functor() {}
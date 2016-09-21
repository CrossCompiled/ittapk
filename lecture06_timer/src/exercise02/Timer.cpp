#include <iostream>
#include <functional>
#include <lecture06_timer/exercise02/Events.hpp>
#include <lecture06_timer/exercise02/Timer.hpp>

using namespace exercise02;

Timer::Timer( int timer) :
	eventTimer_( timer ), terminator_(false), cbscounter_(0)
{
	thread_     = new std::thread( std::bind( &Timer::timerThreadFunction, this ) );
}

Timer::~Timer()
{
	terminator_ = true;
	thread_->join();
	delete thread_;
}

int Timer::timerThreadFunction()
{
  int counter = 0;
  while( !terminator_ )
  {
    std::chrono::milliseconds sleepFor( 1000 );
    std::this_thread::sleep_for( sleepFor );

    notifyAll( std::make_shared<Event>() );
    if( ++counter >= eventTimer_ )
    {	
      counter = 0;
      std::cout << "EventOther created..." << std::endl;
      
      notifyAll( std::make_shared<EventOther>() );
    }
  }
  return 0;
}

int Timer::attach(std::function<void(const std::shared_ptr<Event> &)> cb) {
    ++cbscounter_;
    while (cbs_.count(cbscounter_) > 0) {++cbscounter_;}
    cbs_[cbscounter_] = cb;
    return cbscounter_;
}

void Timer::detach(int cbId) {
    cbs_.erase(cbId);
}

void Timer::notifyAll(const std::shared_ptr<Event> &any) {

    for(const auto& cb : cbs_) {
        cb.second(any);
    }
}
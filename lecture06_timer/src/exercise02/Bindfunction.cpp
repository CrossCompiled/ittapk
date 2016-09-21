/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <functional>
#include <mutex>
#include <lecture06_timer/exercise02/Events.hpp>
#include <lecture06_timer/exercise02/Timer.hpp>
#include <lecture06_timer/exercise02/Functor.hpp>
#include <array>

std::mutex stdioProt;


void freeFunction( const std::shared_ptr<exercise02::Event>& event )
{
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt );
    std::cout << *event;
    if (dynamic_cast<exercise02::EventOther*>(event.get())) {
        std::cout << "OMG Other Event" << std::endl;
    }

}


void withAnExtra(const std::shared_ptr<exercise02::Event>& event, const std::string text)
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );
    std::cout << text << " " << *event;
  /* MISSING EVENT PRINT OUT */

}


class ReferenceObj
{
public:
   ReferenceObj() : called_(0) 
   {
   }

  void call( const std::shared_ptr<exercise02::Event>& event )
  {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt );

    /* MISSING EVENT PRINT OUT */
    
    ++called_;
  }

   int gotCalled()
   {
      return called_;
   }
  
private:
   int   called_;
};



int main()
{
    // Try to make several timers with different callbacks
    exercise02::Timer t1( 4 );
    t1.attach( freeFunction );
    t1.attach( exercise02::Functor(&stdioProt) );
    t1.attach(  std::bind(withAnExtra, std::placeholders::_1, "Hola") );

    auto r = ReferenceObj();

    t1.attach( std::bind(&ReferenceObj::call, &r, std::placeholders::_1));

    // The threads run naturally in the background (no clean up has been added for the threads)

    // You might wanna change the loop below such that you can extract the value of called_
    //  from your instance of ReferenceObj

    for(;;)
    {
        std::chrono::milliseconds sleepFor(100);
        std::this_thread::sleep_for(sleepFor);
        std::lock_guard<std::mutex> lock(stdioProt );
        std::cout << r.gotCalled() << std::endl;
    }
   
    return EXIT_SUCCESS;
}

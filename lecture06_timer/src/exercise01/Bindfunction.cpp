/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <mutex>
#include <lecture06_timer/exercise01/Events.hpp>
#include <lecture06_timer/exercise01/Timer.hpp>

std::mutex stdioProt;


void freeFunction( const std::shared_ptr<exercise01::Event>& event )
{
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt );
    std::cout << *event;
    if (dynamic_cast<exercise01::EventOther*>(event.get())) {
        std::cout << "OMG Other Event" << std::endl;
    }
  
}


void withAnExtra(const std::shared_ptr<exercise01::Event>& event, const std::string text)
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

  /* MISSING EVENT PRINT OUT */

}


class ReferenceObj
{
public:
   ReferenceObj() : called_(0) 
   {
   }

  void call( const std::shared_ptr<exercise01::Event>& event )
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
  exercise01::Timer t1( 4 );
  t1.attach( freeFunction );



  // The threads run naturally in the background (no clean up has been added for the threads)

   
  // You might wanna change the loop below such that you can extract the value of called_
  //  from your instance of ReferenceObj
  for(;;)
  {
    std::chrono::milliseconds sleepFor(1000);
    std::this_thread::sleep_for(sleepFor);
  }
   

  return EXIT_SUCCESS;
}
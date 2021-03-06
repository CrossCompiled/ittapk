#include <ostream>
#include <ctime>
#include <lecture06_timer/exercise02/Events.hpp>


std::ostream& operator<<( std::ostream& os, const exercise02::Event& ev )
{
   std::time_t creationTime = std::chrono::system_clock::to_time_t(ev.creationTime());
   os << std::ctime(&creationTime);

   return os;
}

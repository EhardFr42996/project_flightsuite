#include <iostream>
#include <cstring>
#include <cstdlib>

#include "OSCListener.h"
#include "osc/OscReceivedElements.h"


int main(int argc, char* argv[])
{
   
   boost::posix_time::seconds sleepTime(2);

   std::cout << "start asking\n";
   for (int i = 0; i <= 5; i++)
   {
      std::cout << "asking " << i << "\n";
      BlenderOSCPacketListener *listener;

      listener = BlenderOSCPacketListener::getInstance();

         if (listener->requestNewMessage())
         {
            try{
               const osc::ReceivedMessage *m = listener->getMessage();
               if( std::strcmp( m->AddressPattern(), "/color" ) == 0 ){
                  osc::ReceivedMessage::const_iterator arg = m->ArgumentsBegin();
                  int a1 = (arg++)->AsInt32();
                  if( arg != m->ArgumentsEnd() )
                     throw osc::ExcessArgumentException();

                  std::cout << "asked for message and got: " << a1 << "\n";
               }
            }catch( osc::Exception& e ){
               std::cout << "error while parsing message: " << e.what() << "\n";
            }
         }
      boost::this_thread::sleep(sleepTime);
   }

   std::cout << "end\n";
   BlenderOSCPacketListener::deleteInstance();

   return 0;
}

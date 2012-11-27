#ifndef OSCLISTENER_H
#define OSCLISTENER_H

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <boost/thread.hpp>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"

class BlenderOSCPacketListener : public osc::OscPacketListener 
{
	public:
      static BlenderOSCPacketListener *getInstance();
      static void deleteInstance();
      ~BlenderOSCPacketListener();
      bool requestNewMessage();
      const osc::ReceivedMessage *getMessage();

   protected:

      virtual void ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint );

   private:
      BlenderOSCPacketListener();
      static BlenderOSCPacketListener *sm_instance;     

      void startListening();

      IpEndpointName m_endpoint;
      UdpListeningReceiveSocket *m_socket;
      unsigned long m_ipadress;
      int m_port;

      bool m_newMessageFlag;
      const osc::ReceivedMessage *m_message;

      boost::thread m_Thread;
      boost::mutex m_mutex;
};

#endif

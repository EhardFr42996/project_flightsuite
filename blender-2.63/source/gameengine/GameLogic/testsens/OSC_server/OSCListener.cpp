#include "examples/OSCListener.h"

BlenderOSCPacketListener *BlenderOSCPacketListener::sm_instance = NULL;     

BlenderOSCPacketListener* BlenderOSCPacketListener::getInstance() 
{
   if (!sm_instance) 
      sm_instance = new BlenderOSCPacketListener();
   return sm_instance;
}

void BlenderOSCPacketListener::deleteInstance() 
{
   if (!sm_instance) return;
   delete sm_instance;
}

BlenderOSCPacketListener::BlenderOSCPacketListener()
{
   m_ipadress = 0xFFFFFFFF;
   m_port = 1234;
   m_endpoint = IpEndpointName( m_ipadress,  m_port );
   m_socket = new UdpListeningReceiveSocket( m_endpoint, this );
   m_Thread = boost::thread(&BlenderOSCPacketListener::startListening, this);
}

BlenderOSCPacketListener::~BlenderOSCPacketListener()
{
   m_socket->AsynchronousBreak();
   m_Thread.join();
}

void BlenderOSCPacketListener::startListening()
{
   m_socket->Run();
}

bool BlenderOSCPacketListener::requestNewMessage()
{
   bool flag = false;
   m_mutex.lock();
   flag =  m_newMessageFlag;
   m_mutex.unlock();
   return flag;
}

const osc::ReceivedMessage *BlenderOSCPacketListener::getMessage()
{
   const osc::ReceivedMessage *msg;
   m_mutex.lock();
   m_newMessageFlag = false;
   msg = m_message;
   m_mutex.unlock();
   return msg;
}

void BlenderOSCPacketListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint )
{
	try{
		if( std::strcmp( m.AddressPattern(), "/color" ) == 0 ){
         m_mutex.lock();
         if (m_newMessageFlag) delete m_message; //overwrite old message
         m_message = new osc::ReceivedMessage(m); 
         m_newMessageFlag = true;
         m_mutex.unlock();
         /*
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			int a1 = (arg++)->AsInt32();
			if( arg != m.ArgumentsEnd() )
				throw osc::ExcessArgumentException();

			std::cout << "received '/color' message with arguments: " << a1 << "\n";
         */
		}
	}catch( osc::Exception& e ){
		std::cout << "error while parsing message: "
			<< m.AddressPattern() << ": " << e.what() << "\n";
	}
}

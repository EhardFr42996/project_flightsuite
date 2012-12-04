cmake_minimum_required(VERSION 2.6)
PROJECT(TestMyOSCListener)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})


IF(WIN32)
 set(SystemTypePath ip/win32)
ELSE(WIN32)
 set(SystemTypePath ip/posix)
ENDIF(WIN32)

ADD_LIBRARY(OSC 

ip/IpEndpointName.cpp 
${SystemTypePath}/NetworkingUtils.cpp
${SystemTypePath}/UdpSocket.cpp

osc/OscPrintReceivedElements.cpp
osc/OscReceivedElements.cpp 
osc/OscTypes.cpp 
osc/OscOutboundPacketStream.cpp

)

IF(WIN32)
 ADD_EXECUTABLE(ListenerTest examples/main.cpp examples/OSCListener.cpp)
 TARGET_LINK_LIBRARIES(ListenerTest OSC Ws2_32 winmm)

 ADD_EXECUTABLE(MySend examples/SimpleSend.cpp)
 TARGET_LINK_LIBRARIES(MySend OSC Ws2_32 winmm)
ELSE(WIN32)
 ADD_EXECUTABLE(ListenerTest examples/main.cpp examples/OSCListener.cpp)
 TARGET_LINK_LIBRARIES(ListenerTest OSC)

 ADD_EXECUTABLE(MySend examples/SimpleSend.cpp)
 TARGET_LINK_LIBRARIES(MySend OSC)
ENDIF(WIN32)

//TODO: Queue manager 

#ifndef EMANEMODELSTDMAQUEUEMANAGERHB_HEADER_
#define EMANEMODELSTDMAQUEUEMANAGERHB_HEADER_



#include "emane/component.h"
#include "emane/platformserviceuser.h"
#include "emane/runningstatemutable.h"
#include "emane/downstreampacket.h"
#include "emane/models/tdma/types.h"
#include "emane/models/tdma/messagecomponent.h"
#include "emane/models/tdma/packetstatuspublisheruser.h"

#include <tuple>
#include <map>


namespace EMANE
{
 namespace Models
 {
  namespace HeavyBallTDMA
  {
    class QueueManagerHB : public Component,
                           public PlatformServiceUser,
                           public RunningStateMutable,
                           public PacketStatusPublisherUser
  
    {
    public:
      virtual ~QueueManagerHB(){};
      

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
      
      
      
      virtual 
      size_t enqueue(std::uint8_t u8QueueIndex, DownstreamPacket && pkt) = 0;
      
      
      virtual std::tuple<EMANE::Models::TDMA::MessageComponenets,size_t>
      dequeue(std::uint8_t u8QueueIndex,size_t length,NEMId destination) = 0;
      
      
      
      virtual std::map<std::uint64_t,size_t> getDestQueueLength(int priority) = 0;
      
      virtual QueueInfos getPacketQueueInfo() const = 0;

      protected:
        NEMId id_;
        
        
        
       QueueManager(NEMId id,
                     PlatformServiceProvider * pPlatformServiceProvider):
          PlatformServiceUser{pPlatformServiceProvider},
          id_{id}{}
          
          
       private:
        void processEvent(const EventId &, const Serialization &) final{};

        void processTimedEvent(TimerEventId,
                               const TimePoint &,
                               const TimePoint &,
                               const TimePoint &,
                               const void *) final {};

      };
    }
  }
}

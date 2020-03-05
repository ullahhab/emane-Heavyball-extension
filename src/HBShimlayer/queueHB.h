#ifndef EMANEMODELSTDMAQUEUE_HEADER_
#define EMANEMODELSTDMAQUEUE_HEADER_

#include "emane/types.h"
#include "emane/downstreampacket.h"
#include "emane/models/tdma/messagecomponent.h"

#include <cstdint>
#include <map>

namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallShimlayer
    {
      /**
       * @class Queue
       *
       * @brief Downstream packet queue with both FIFO and
       * By-Destination FIFO dequeue mechanisms.
       */
      class QueueHB
      {
      public:
        QueueHB();

        void initialize(std::uint16_t u16QueueDepth,
                        bool bFragment,
                        bool bAggregate,
                        bool bIsControl);

        std::pair<std::unique_ptr<DownstreamPacket>,bool>
        enqueue(DownstreamPacket && pkt);

        std::tuple<MessageComponents,
                   size_t,
                   std::list<std::unique_ptr<DownstreamPacket>>>
          dequeue(size_t requestedBytes,NEMId destination,bool bDrop);

        // packets, bytes
        std::tuple<size_t,size_t> getStatus() const;

        std::map<std::uint64_t,size_t> getDestQueueLength();

      private:
        class MetaInfo
        {
        public:
          size_t index_{};
          size_t offset_{};
        };
        using PacketQueue = std::map<std::uint64_t,
                                     std::pair<DownstreamPacket *,MetaInfo *>>;
        PacketQueue queue_;
        std::map<NEMId,PacketQueue> destQueue_;
        std::uint16_t u16QueueDepth_;
        bool bFragment_;
        std::uint64_t u64Counter_;
        size_t currentBytes_;
        bool bIsControl_;
        bool bAggregate_;

        std::pair<MessageComponent,size_t> fragmentPacket(DownstreamPacket * pPacket,
                                                          MetaInfo * pMetaInfo,
                                                          std::uint64_t u64Sequence,
                                                          size_t bytes);
      };
    }
  }
}

#endif // EMANEMODELSTDMAQUEUE_HEADER_

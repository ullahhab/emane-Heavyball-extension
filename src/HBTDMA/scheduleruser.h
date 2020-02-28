#ifndef EMANETDMARADIOMODELSCHEDULERUSER_HEADER_
#define EMANETDMARADIOMODELSCHEDULERUSER_HEADER_

#include "emane/models/tdma/types.h"
#include "emane/downstreampacket.h"
#include "emane/controlmessage.h"

namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallTDMA
    {
      /**
       * @class SchedulerUser
       *
       * @brief Interface used by a scheduler module to communicate
       * information with BaseModel.
       */
      class SchedulerUser
      {
      public:
        /**
         * Destroys an instance
         */
        virtual ~SchedulerUser(){};

        /**
         * Notifies when a schedule change occurs
         *
         * @param frequencies Set of frequencies used in the schedule
         * @param u64BandwidthHz Transceiver bandwidth
         * @param slotDuration Slot duration
         * @param slotOverhead Slot overhead
         */
        virtual void notifyScheduleChange(const Frequencies & frequencies,
                                          std::uint64_t u64BandwidthHz,
                                          const Microseconds & slotDuration,
                                          const Microseconds & slotOverhead,
                                          float beta) = 0;

        /**
         * Processes a Scheduler packet for transmission over-the-air
         *
         * @param pkt Packet to transmit
         */
        virtual void processSchedulerPacket(DownstreamPacket & pkt) = 0;

        /**
         * Processes Scheduler control messages for communication
         * with the downsteam NEM layer
         *
         * @param msgs Control messages
         */
        virtual void processSchedulerControl(const ControlMessages & msgs) = 0;


        /**
         * Gets queue status.
         *
         * @return A list of QueueInfo entries.
         */
        virtual QueueInfos getPacketQueueInfo() const = 0;


        static const ControlMessages empty;

      protected:
        /**
         * Creates an instance
         */
        SchedulerUser(){}
      };
    }
  }
}

#endif // EMANETDMARADIOMODELSCHEDULERUSER_HEADER_

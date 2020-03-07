#ifndef EMANETDMARADIOMODELEVENTSCHEDULER_HEADER_
#define EMANETDMARADIOMODELEVENTSCHEDULER_HEADER_

#include "emane/models/tdma/scheduler.h"
#include "emane/events/slotinfo.h"
#include "emane/events/slotstructure.h"
#include "emane/statisticnumeric.h"
#include "emane/src/mac/models/tdma/eventscheduler/eventtablepublisher.h"
#include "emane/src/mac/models/tdma/eventscheduler/slotter.h"

namespace EMANE
{
  namespace Models
  {
    namespace HBShimlayer
    {
      /**
       * @class EventScheduler
       *
       * @brief Reference Scheduler implementation
       *
       * Implementation receives a %TDMA schdule via an event.
       */
      class EventScheduler : public Scheduler
      {
      public:
        EventScheduler(NEMId id,
                       PlatformServiceProvider * pPlatformServiceProvider,
                       SchedulerUser * pSchedulerUser);

        ~EventScheduler();

        void initialize(Registrar & registrar) override;

        void configure(const ConfigurationUpdate & update) override;

        void start() override;

        void postStart() override;

        void stop() override;

        void destroy() throw() override;

        void processEvent(const EventId & eventId,
                          const Serialization & serialization) override;

        std::pair<RxSlotInfo,bool> getRxSlotInfo(const TimePoint & timePoint) const override;

        std::pair<TxSlotInfos,TimePoint> getTxSlotInfo(const TimePoint & timePoint,
                                                       int multiframes) const override;

        SlotInfo getSlotInfo(std::uint64_t u64AbsoluteSlotIndex) const override;

        SlotInfo getSlotInfo(const TimePoint & timePoint) const override;

        void processSchedulerPacket(UpstreamPacket & pkt,
                                    const PacketMetaInfo & packetMetaInfo) override;

        void processPacketMetaInfo(const PacketMetaInfo & packetMetaInfo) override;

      private:
        Events::SlotInfos slotInfos_;
        Events::SlotStructure structure_;
        EventTablePublisher eventTablePublisher_;
        Slotter slotter_;
        mutable bool bWaitingFirstTxSlotInfoRequest_;
        Frequencies frequencies_;
        StatisticNumeric<std::uint64_t> * pNumScheduleRejectSlotIndexOutOfRange_;
        StatisticNumeric<std::uint64_t> * pNumScheduleRejectFrameIndexOutOfRange_;
        StatisticNumeric<std::uint64_t> * pNumScheduleRejectUpdateBeforeFull_;
        StatisticNumeric<std::uint64_t> * pNumScheduleRejectOther_;
        StatisticNumeric<std::uint64_t> * pNumScheduleFullAccept_;
        StatisticNumeric<std::uint64_t> * pNumScheduleUpdateAccept_;

        void flushSchedule();
      };
    }
  }
}

#endif // EMANETDMARADIOMODELEVENTSCHEDULER_HEADER_

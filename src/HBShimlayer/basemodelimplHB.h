


#ifndef EMANETDMABASEMODELIMPL_HEADER_
#define EMANETDMABASEMODELIMPL_HEADER_

#include "emane/maclayerimpl.h"
#include "emane/flowcontrolmanager.h"
#include "emane/neighbormetricmanager.h"
#include "emane/models/tdma/basemodel.h"
#include "emane/models/tdma/scheduler.h"
#include "emane/models/tdma/queuemanager.h"

#include "slotstatustablepublisher.h"
#include "receivemanager.h"
#include "packetstatuspublisherimpl.h"
#include "aggregationstatuspublisher.h"

namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallShimlayer
    {
      /**
       * @class BaseModel::Implementation
       *
       * @brief Implementation of BaseModel
       */
      class BaseModel::ImplementationHB : public MACLayerImplementor,
                                        public SchedulerUser
      {
      public:
        ImplementationHB(NEMId id,
                       PlatformServiceProvider *pPlatformServiceProvider,
                       RadioServiceProvider * pRadioServiceProvider,
                       Scheduler * pScheduler,
                       QueueManager * pQueueManager,
                       MACLayerImplementor * pRadioModel);

        ~ImplementationHB();

        void initialize(Registrar & registrar) override;

        void configure(const ConfigurationUpdate & update) override;

        void start() override;

        void postStart() override;

        void stop() override;

        void destroy() throw() override;

        void processUpstreamControl(const ControlMessages & msgs) override;


        void processUpstreamPacket(const CommonMACHeader & hdr,
                                   UpstreamPacket & pkt,
                                   const ControlMessages & msgs) override;

        void processDownstreamControl(const ControlMessages & msgs) override;


        void processDownstreamPacket(DownstreamPacket & pkt,
                                     const ControlMessages & msgs) override;


        void processEvent(const EventId &, const Serialization &) override;

        void processConfiguration(const ConfigurationUpdate & update) override;

        void notifyScheduleChange(const Frequencies & frequencies,
                                  std::uint64_t u64BandwidthHz,
                                  const Microseconds & slotDuration,
                                  const Microseconds & slotOverhead) override;


        void processSchedulerPacket(DownstreamPacket & pkt) override;

        void processSchedulerControl(const ControlMessages & msgs) override;

        QueueInfos getPacketQueueInfo() const override;

      private:
        std::unique_ptr<Scheduler> pScheduler_;
        std::unique_ptr<QueueManager> pQueueManager_;
        MACLayerImplementor * pRadioModel_;

        bool bFlowControlEnable_;
        std::uint16_t u16FlowControlTokens_;
        std::string sPCRCurveURI_;
        TimerEventId transmitTimedEventId_;
        TxSlotInfo pendingTxSlotInfo_;
        TimePoint  nextMultiFrameTime_;
        TxSlotInfos txSlotInfos_;
        Microseconds slotDuration_;
        Microseconds slotOverhead_;
        SlotStatusTablePublisher slotStatusTablePublisher_;
        std::uint64_t u64SequenceNumber_;
        Frequencies frequencies_;
        std::uint64_t u64BandwidthHz_;
        Microseconds neighborMetricUpdateInterval_;
        PacketStatusPublisherImpl packetStatusPublisher_;
        NeighborMetricManager neighborMetricManager_;
        ReceiveManager receiveManager_;
        FlowControlManager flowControlManager_;
        std::uint64_t u64ScheduleIndex_;
        AggregationStatusPublisher aggregationStatusPublisher_;

        void sendDownstreamPacket(double dSlotRemainingRatio);

        void processTxOpportunity(std::uint64_t u64ScheduleIndex);

        NEMId getDstByMaxWeight();
      };
    }
  }
}

#endif // EMANETDMABASEMODELIMPL_HEADER_

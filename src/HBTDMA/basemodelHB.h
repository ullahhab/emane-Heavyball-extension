#ifndef EMANETDMABASEMODEL_HEADER_
#define EMANETDMABASEMODEL_HEADER_

#include "emane/maclayerimpl.h"
#include "emane/models/tdma/scheduler.h"
#include "emane/models/tdma/queuemanager.h"

namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallTDMA
    {
      /**
       * @class BaseModel
       *
       * @brief %TDMA radio module implementation that uses
       * specialized scheduler and queue manager modules to allow
       * variant model development.
       */
      class BaseModelHB : public MACLayerImplementor,
                        public SchedulerUser
      {
      public:
        BaseModelHB(NEMId id,
                  PlatformServiceProvider *pPlatformServiceProvider,
                  RadioServiceProvider * pRadioServiceProvider,
                  Scheduler * pScheduler,
                  QueueManager * pQueueManager);

        ~BaseModelHB();

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
                                  const Microseconds & slotOverhead,
                                  float beta) override;

        void processSchedulerPacket(DownstreamPacket & pkt) override;

        void processSchedulerControl(const ControlMessages & msgs) override;

        QueueInfos getPacketQueueInfo() const override;

      private:
        class Implementation;
        std::unique_ptr<Implementation> pImpl_;
      };
    }
  }
}

#endif // EMANETDMABASEMODEL_HEADER_

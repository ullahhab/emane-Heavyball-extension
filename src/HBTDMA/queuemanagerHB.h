//TODO: HeavyBall algorithm
#ifndef EMANEMODELSTDMABASICQUEUEMANAGERHB_HEADER_
#define EMANEMODELSTDMABASICQUEUEMANAGERHB_HEADER_
#include "emane/models/HeavyBallTDMA/queuemanager.h"
#include <map>




namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallTDMA
    {
      class BasicQueueManagerHeavyBall : public QueueManager
      {
      public:
         BasicQueueManagerHeavyBall(NEMId id,
                          PlatformServiceProvider * pPlatformServiceProvider);

        ~BasicQueueManagerHeavyBall();

        void initialize(Registrar & registrar) override;

        void configure(const ConfigurationUpdate & update) override;

        void start() override;

        void postStart() override;

        void stop() override;

        void destroy() throw() override;

        size_t enqueue(std::uint8_t u8QueueIndex, DownstreamPacket && pkt) override;

        std::tuple<EMANE::Models::TDMA::MessageComponents,
                   size_t>
          dequeue(std::uint8_t u8QueueIndex,
                  size_t length,
                  NEMId destination) override;

        QueueInfos getPacketQueueInfo() const override;

        std::map<std::uint64_t,size_t> getDestQueueLength(int priority) override;

      private:
        class Implementation;
        std::unique_ptr<Implementation> pImpl_;
      };
    }
  }
}

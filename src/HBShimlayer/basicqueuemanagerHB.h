#ifndef EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_
#define EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_
//TODO: THis line would most likely change
#include "queuemanager.h"

namespace EMANE
{
  namespace Models
  {
    namespace HeavyBallShimlayer
    {
      /**
       * @class BasicQueueManager
       *
       * @brief Reference QueueManager implementation
       */
      class BasicQueueManagerHB : public QueueManagerHB
      {
      public:
        BasicQueueManagerHB(NEMId id,
                          PlatformServiceProvider * pPlatformServiceProvider);

        ~BasicQueueManagerHB();

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
      //TODO: Check this line
      private:
        class Implementation;
        std::unique_ptr<Implementation> pImpl_;
      };
    }
  }
}


#endif // EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_

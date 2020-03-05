#ifndef EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_
#define EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_
//TODO: THis line would most likely change
#include "emane/models/tdma/queuemanager.h"

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
      class BasicQueueManager : public QueueManager
      {
      public:
        BasicQueueManager(NEMId id,
                          PlatformServiceProvider * pPlatformServiceProvider);

        ~BasicQueueManager();

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

      private:
        class Implementation;
        std::unique_ptr<Implementation> pImpl_;
      };
    }
  }
}


#endif // EMANEMODELSTDMABASICQUEUEMANAGER_HEADER_

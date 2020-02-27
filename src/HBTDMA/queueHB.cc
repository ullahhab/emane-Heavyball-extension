#include "emane/models/tdma/basicqueuemanager.h"
#include "emane/configureexception.h"
#include "queue.h"
#include "queuestatuspublisher.h"

namespace
{
  const int MAX_QUEUES = 5;
}
//THis would change
class EMANE::Models::TDMA::BasicQueueManager::Implementation
{
public:
  bool bAggregationEnable_{};
  bool bFragmentationEnable_{};
  bool bStrictDequeueEnable_{};
  double dAggregationSlotThreshold_{};
  Queue queues_[MAX_QUEUES];
  QueueStatusPublisher queueStatusPublisher_;
};

//TODO: This would change
EMANE::Models::TDMA::BasicQueueManager::BasicQueueManager(NEMId id,
                                                          PlatformServiceProvider * pPlatformServiceProvider):
  QueueManager{id,pPlatformServiceProvider},
  pImpl_{new Implementation{}}{}
//TODO: THis would change
EMANE::Models::TDMA::BasicQueueManager::~BasicQueueManager(){}
//TODO: This would change
void EMANE::Models::TDMA::BasicQueueManager::initialize(Registrar & registrar)
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);

  auto & configRegistrar = registrar.configurationRegistrar();

  configRegistrar.registerNumeric<std::uint16_t>("queue.depth",
                                                 ConfigurationProperties::DEFAULT,
                                                 {256},
                                                 "Defines the size of the per service class downstream packet"
                                                 " queues (in packets). Each of the 5 queues (control + 4"
                                                 " service classes) will be 'queuedepth' size.");

  configRegistrar.registerNumeric<bool>("queue.aggregationenable",
                                        ConfigurationProperties::DEFAULT,
                                        {true},
                                        "Defines whether packet aggregation is enabled for transmission. When"
                                        " enabled, multiple packets can be sent in the same transmission when"
                                        " there is additional room within the slot.");


  configRegistrar.registerNumeric<bool>("queue.fragmentationenable",
                                        ConfigurationProperties::DEFAULT,
                                        {true},
                                        "Defines whether packet fragmentation is enabled. When enabled, a single"
                                        " packet will be fragmented into multiple message components to be sent"
                                        " over multiple transmissions when the slot is too small.  When disabled"
                                        " and the packet matches the traffic class for the transmit slot as"
                                        " defined in the TDMA schedule, the packet will be discarded.");


  configRegistrar.registerNumeric<bool>("queue.strictdequeueenable",
                                        ConfigurationProperties::DEFAULT,
                                        {false},
                                        "Defines whether packets will be dequeued from a queue other than what"
                                        " has been specified when there are no eligible packets for dequeue in"
                                        " the specified queue. Queues are dequeued highest priority first.");

  configRegistrar.registerNumeric<double>("queue.aggregationslotthreshold",
                                          ConfigurationProperties::DEFAULT,
                                          {90.0},
                                          "Defines the percentage of a slot that must be filled in order to conclude"
                                          " aggregation when queue.aggregationenable is enabled.",
                                          0,
                                          100.0);

  auto & statisticRegistrar = registrar.statisticRegistrar();

  pImpl_->queueStatusPublisher_.registerStatistics(statisticRegistrar);

}
//TODO: This would change
void EMANE::Models::TDMA::BasicQueueManager::configure(const ConfigurationUpdate & update)
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);

  std::uint16_t u16QueueDepth{};

  for(const auto & item : update)
    {
      if(item.first == "queue.depth")
        {
          u16QueueDepth = item.second[0].asUINT16();

          LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                                  INFO_LEVEL,
                                  "MACI %03hu TDMA::BasicQueueManager::%s: %s = %hu",
                                  id_,
                                  __func__,
                                  item.first.c_str(),
                                  u16QueueDepth);
        }
      else if(item.first == "queue.aggregationenable")
        {
          pImpl_->bAggregationEnable_ = item.second[0].asBool();

          LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                                  INFO_LEVEL,
                                  "MACI %03hu TDMA::BaseModel::%s: %s = %s",
                                  id_,
                                  __func__,
                                  item.first.c_str(),
                                  pImpl_->bAggregationEnable_ ? "on" : "off");
        }
      else if(item.first == "queue.fragmentationenable")
        {
          pImpl_->bFragmentationEnable_ = item.second[0].asBool();

          LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                                  INFO_LEVEL,
                                  "MACI %03hu TDMA::BaseModel::%s: %s = %s",
                                  id_,
                                  __func__,
                                  item.first.c_str(),
                                  pImpl_->bFragmentationEnable_ ? "on" : "off");
        }
      else if(item.first == "queue.strictdequeueenable")
        {
          pImpl_->bStrictDequeueEnable_ = item.second[0].asBool();

          LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                                  INFO_LEVEL,
                                  "MACI %03hu TDMA::BaseModel::%s: %s = %s",
                                  id_,
                                  __func__,
                                  item.first.c_str(),
                                  pImpl_->bStrictDequeueEnable_ ? "on" : "off");
        }
      else if(item.first == "queue.aggregationslotthreshold")
        {
          pImpl_->dAggregationSlotThreshold_ = item.second[0].asDouble();

          LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                                  INFO_LEVEL,
                                  "MACI %03hu TDMA::BaseModel::%s: %s = %lf",
                                  id_,
                                  __func__,
                                  item.first.c_str(),
                                  pImpl_->dAggregationSlotThreshold_);
        }

      else
        {
          throw makeException<ConfigureException>("TDMA::BasicQueueManager: "
                                                   "Unexpected configuration item %s",
                                                   item.first.c_str());
        }
    }

  // queue for user traffic mapped by dhcp
  pImpl_->queues_[0].initialize(u16QueueDepth,
                                pImpl_->bFragmentationEnable_,
                                pImpl_->bAggregationEnable_,
                                false);

  pImpl_->queues_[1].initialize(u16QueueDepth,
                                pImpl_->bFragmentationEnable_,
                                pImpl_->bAggregationEnable_,
                                false);

  pImpl_->queues_[2].initialize(u16QueueDepth,
                                pImpl_->bFragmentationEnable_,
                                pImpl_->bAggregationEnable_,
                                false);
  pImpl_->queues_[3].initialize(u16QueueDepth,
                                pImpl_->bFragmentationEnable_,
                                pImpl_->bAggregationEnable_,
                                false);

  // control queue for scheduler-to-scheduler OTA messages
  pImpl_->queues_[4].initialize(u16QueueDepth,
                                pImpl_->bFragmentationEnable_,
                                pImpl_->bAggregationEnable_,
                                true);


}
//TODO: This would change
void EMANE::Models::TDMA::BasicQueueManager::start()
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);
}
//TODO: This would change
void EMANE::Models::TDMA::BasicQueueManager::postStart()
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);
}
//TODO: THis would change
void EMANE::Models::TDMA::BasicQueueManager::stop()
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);
}
//TODO: THis would change
void EMANE::Models::TDMA::BasicQueueManager::destroy() throw()
{
  LOGGER_STANDARD_LOGGING(pPlatformService_->logService(),
                          DEBUG_LEVEL,
                          "MACI %03hu TDMA::BasicQueueManager::%s",
                          id_,
                          __func__);
}
//TODO: This would change
size_t EMANE::Models::TDMA::BasicQueueManager::enqueue(std::uint8_t u8QueueIndex,
                                                     DownstreamPacket && pkt)
{
  size_t packetsDropped{};

  if(u8QueueIndex < MAX_QUEUES)
    {
      auto ret = pImpl_->queues_[u8QueueIndex].enqueue(std::move(pkt));

      if(ret.second)
        {
          packetsDropped = 1;

          pImpl_->queueStatusPublisher_.drop(u8QueueIndex,
                                             QueueStatusPublisher::DropReason::DROP_OVERFLOW,
                                             1);

          const auto & pktInfo = ret.first->getPacketInfo();

          pPacketStatusPublisher_->outbound(pktInfo.getSource(),
                                            pktInfo.getDestination(),
                                            pktInfo.getPriority(),
                                            ret.first->length(),
                                            PacketStatusPublisher::OutboundAction::DROP_OVERFLOW);
        }

      pImpl_->queueStatusPublisher_.enqueue(u8QueueIndex);
    }

  return packetsDropped;
}
//TODO: THis would change possible basic queue dequeue
std::tuple<EMANE::Models::TDMA::MessageComponents,size_t>
EMANE::Models::TDMA::BasicQueueManager::dequeue(std::uint8_t u8QueueIndex,
                                                size_t requestedBytes,
                                                NEMId destination)
{
  MessageComponents components{};
  size_t totalLength{};

  if(u8QueueIndex < MAX_QUEUES)
    {
      auto ret = pImpl_->queues_[u8QueueIndex].dequeue(requestedBytes,
                                                       destination,
                                                       true);

      auto length = std::get<1>(ret);

      if(length)
        {
          totalLength += length;

          auto & parts = std::get<0>(ret);

          pImpl_->queueStatusPublisher_.dequeue(u8QueueIndex,
                                                u8QueueIndex,
                                                parts);

          components.splice(components.end(),parts);
        }

      // update drop info
      for(const auto & pPkt : std::get<2>(ret))
        {
          const auto & pktInfo = pPkt->getPacketInfo();

          pPacketStatusPublisher_->outbound(pktInfo.getSource(),
                                            pktInfo.getDestination(),
                                            pktInfo.getPriority(),
                                            pPkt->length(),
                                            PacketStatusPublisher::OutboundAction::DROP_TOO_BIG);

          pImpl_->queueStatusPublisher_.drop(u8QueueIndex,
                                             QueueStatusPublisher::DropReason::DROP_TOOBIG,
                                             1);
        }

      size_t aggregationThreshold{static_cast<size_t>(requestedBytes *
                                                      pImpl_->dAggregationSlotThreshold_ / 100.0)};


      // if allowed, check the other queues to see if they have components that will
      //  fit in the slot
      if(!pImpl_->bStrictDequeueEnable_)
        {
          std::uint8_t i{MAX_QUEUES};

          while((!totalLength || (totalLength && pImpl_->bAggregationEnable_)) &&
                totalLength <= aggregationThreshold &&
                i > 0)
            {
              // check all queues except the original from highest priority to lowest
              if(i-1 != u8QueueIndex)
                {
                  auto ret = pImpl_->queues_[i-1].dequeue(requestedBytes - totalLength,
                                                          destination,
                                                          false);

                  auto length = std::get<1>(ret);

                  // if component data was dequeued, record it
                  if(length)
                    {
                      auto & parts = std::get<0>(ret);

                      totalLength += length;

                      pImpl_->queueStatusPublisher_.dequeue(u8QueueIndex,
                                                            i-1,
                                                            parts);

                      components.splice(components.end(),parts);
                    }
                }

              --i;
            }
        }
    }

  pPacketStatusPublisher_->outbound(id_,
                                    components,
                                    PacketStatusPublisher::OutboundAction::ACCEPT_GOOD);

  return std::make_tuple(std::move(components),totalLength);
}
//TODO: Maybe not change 
EMANE::Models::TDMA::QueueInfos
EMANE::Models::TDMA::BasicQueueManager::getPacketQueueInfo() const
{
  QueueInfos queueInfos{};

  for(int i = 0; i < MAX_QUEUES; ++i)
    {
      auto status = pImpl_->queues_[i].getStatus();

      queueInfos.push_back({static_cast<std::uint8_t>(i), //queue id
            std::get<0>(status), // packets
            std::get<1>(status)}); //bytes
    }

  return queueInfos;
}
//TODO: Maybe and most possibly change
std::map<std::uint64_t,size_t> EMANE::Models::TDMA::BasicQueueManager::getDestQueueLength(int priority)
{
  return pImpl_->queues_[priority].getDestQueueLength();
}

#include "emane/models/HBShimlayer/basemodelHB.h"
#include "basemodelimplHB.h"


//TODO: THis line would change
EMANE::Models::HeavyBallShimlayer::BaseModelHB::BaseModelHB(NEMId id,
                                          PlatformServiceProvider * pPlatformServiceProvider,
                                          RadioServiceProvider * pRadioServiceProvider,
                                          Scheduler * pScheduler,
                                          QueueManager * pQueueManager):
  MACLayerImplementor{id, pPlatformServiceProvider, pRadioServiceProvider},
  pImpl_{new Implementation{id,
        pPlatformServiceProvider,
        pRadioServiceProvider,
        pScheduler,
        pQueueManager,
        this}}
{}


//TODO: THis line would change
EMANE::Models::HBShimlayer::BaseModelHB::~BaseModelHB()
{}


void
EMANE::Models::HBShimlayer::BaseModelHB::initialize(Registrar & registrar)
{
  pImpl_->initialize(registrar);
}



void
EMANE::Models::HBShimlayer::BaseModelHB::configure(const ConfigurationUpdate & update)
{
  pImpl_->configure(update);
}

void
EMANE::Models::HBShimlayer::BaseModelHB::start()
{
  pImpl_->start();
}


void
EMANE::Models::HBShimlayer::BaseModelHB::postStart()
{
  pImpl_->postStart();
}


void
EMANE::Models::HBShimlayer::BaseModelHB::stop()
{
  pImpl_->stop();
}



void
EMANE::Models::HBShimlayer::BaseModelHB::destroy()
  throw()
{
  pImpl_->destroy();
}

void EMANE::Models::HBShimlayer::BaseModelHB::processUpstreamControl(const ControlMessages & msgs)
{
  pImpl_->processUpstreamControl(msgs);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processUpstreamPacket(const CommonMACHeader & hdr,
                                                           UpstreamPacket & pkt,
                                                           const ControlMessages & msgs)
{
  pImpl_->processUpstreamPacket(hdr,pkt,msgs);
}

void EMANE::Models::HBShimlayer::BaseModelHB::processDownstreamControl(const ControlMessages & msgs)
{
  pImpl_->processDownstreamControl(msgs);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processDownstreamPacket(DownstreamPacket & pkt,
                                                             const ControlMessages & msgs)
{
  pImpl_->processDownstreamPacket(pkt,msgs);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processEvent(const EventId & eventId,
                                                  const Serialization & serialization)
{
  pImpl_->processEvent(eventId,serialization);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processConfiguration(const ConfigurationUpdate & update)
{
  pImpl_->processConfiguration(update);
}

void EMANE::Models::HBShimlayer::BaseModelHB::notifyScheduleChange(const Frequencies & frequencies,
                                                          std::uint64_t u64BandwidthHz,
                                                          const Microseconds & slotDuration,
                                                          const Microseconds & slotOverhead,
                                                          float beta)
{
  pImpl_->notifyScheduleChange(frequencies,u64BandwidthHz,slotDuration,slotOverhead,beta);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processSchedulerPacket(DownstreamPacket & pkt)
{
  pImpl_->processSchedulerPacket(pkt);
}


void EMANE::Models::HBShimlayer::BaseModelHB::processSchedulerControl(const ControlMessages & msgs)
{
  pImpl_->processSchedulerControl(msgs);
}


EMANE::Models::TDMA::QueueInfos EMANE::Models::HBShimlayer::BaseModelHB::getPacketQueueInfo() const
{
  return pImpl_->getPacketQueueInfo();
}

#include "emane/models/tdma/basemodel.h"
#include "basemodelimpl.h"


//TODO: THis line would change
EMANE::Models::TDMA::BaseModel::BaseModel(NEMId id,
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
EMANE::Models::TDMA::BaseModel::~BaseModel()
{}


void
EMANE::Models::TDMA::BaseModel::initialize(Registrar & registrar)
{
  pImpl_->initialize(registrar);
}



void
EMANE::Models::TDMA::BaseModel::configure(const ConfigurationUpdate & update)
{
  pImpl_->configure(update);
}

void
EMANE::Models::TDMA::BaseModel::start()
{
  pImpl_->start();
}


void
EMANE::Models::TDMA::BaseModel::postStart()
{
  pImpl_->postStart();
}


void
EMANE::Models::TDMA::BaseModel::stop()
{
  pImpl_->stop();
}



void
EMANE::Models::TDMA::BaseModel::destroy()
  throw()
{
  pImpl_->destroy();
}

void EMANE::Models::TDMA::BaseModel::processUpstreamControl(const ControlMessages & msgs)
{
  pImpl_->processUpstreamControl(msgs);
}


void EMANE::Models::TDMA::BaseModel::processUpstreamPacket(const CommonMACHeader & hdr,
                                                           UpstreamPacket & pkt,
                                                           const ControlMessages & msgs)
{
  pImpl_->processUpstreamPacket(hdr,pkt,msgs);
}

void EMANE::Models::TDMA::BaseModel::processDownstreamControl(const ControlMessages & msgs)
{
  pImpl_->processDownstreamControl(msgs);
}


void EMANE::Models::TDMA::BaseModel::processDownstreamPacket(DownstreamPacket & pkt,
                                                             const ControlMessages & msgs)
{
  pImpl_->processDownstreamPacket(pkt,msgs);
}


void EMANE::Models::TDMA::BaseModel::processEvent(const EventId & eventId,
                                                  const Serialization & serialization)
{
  pImpl_->processEvent(eventId,serialization);
}


void EMANE::Models::TDMA::BaseModel::processConfiguration(const ConfigurationUpdate & update)
{
  pImpl_->processConfiguration(update);
}

void EMANE::Models::TDMA::BaseModel::notifyScheduleChange(const Frequencies & frequencies,
                                                          std::uint64_t u64BandwidthHz,
                                                          const Microseconds & slotDuration,
                                                          const Microseconds & slotOverhead,
                                                          float beta)
{
  pImpl_->notifyScheduleChange(frequencies,u64BandwidthHz,slotDuration,slotOverhead,beta);
}


void EMANE::Models::TDMA::BaseModel::processSchedulerPacket(DownstreamPacket & pkt)
{
  pImpl_->processSchedulerPacket(pkt);
}


void EMANE::Models::TDMA::BaseModel::processSchedulerControl(const ControlMessages & msgs)
{
  pImpl_->processSchedulerControl(msgs);
}


EMANE::Models::TDMA::QueueInfos EMANE::Models::TDMA::BaseModel::getPacketQueueInfo() const
{
  return pImpl_->getPacketQueueInfo();
}

#ifndef EMANEFRAMEWORK_HEADER_
#define EMANEFRAMEWORK_HEADER_

#include "emane/phylayerimpl.h"
#include "emane/phytypes.h"
#include "emane/utils/commonlayerstatistics.h"

#include "locationmanager.h"
#include "spectrummonitor.h"
#include "gainmanager.h"
#include "propagationmodelalgorithm.h"
#include "eventtablepublisher.h"
#include "receivepowertablepublisher.h"
#include "fadingmanager.h"

#include <set>
#include <cstdint>
#include <memory>

namespace EMANE
{
  namespace shim
  {
  class FrameworkPHY : public PHYLayerImplementor
  {
  public:
    FrameworkPHY(NEMId id,
                 PlatformServiceProvider* pPlatformService,
                 SpectrumMonitor * pSpectrumMonitor);

    ~FrameworkPHY();

    void initialize(Registrar & registrar) override;

    void configure(const ConfigurationUpdate & update) override;

    void start() override;

    void stop() override;

    void destroy() throw() override;

    void processConfiguration(const ConfigurationUpdate & update) override;

    void processUpstreamPacket(const CommonPHYHeader & hdr,
                               UpstreamPacket & pkt,
                               const ControlMessages & msgs) override;

    // provides test harness access
    void processUpstreamPacket_i(const TimePoint & now,
                                 const CommonPHYHeader & hdr,
                                 UpstreamPacket & pkt,
                                 const ControlMessages & msgs);

    void processDownstreamControl(const ControlMessages & msgs) override;

    void processDownstreamPacket(DownstreamPacket & pkt,
                                 const ControlMessages & msgs) override;

    void processEvent(const EventId & eventId,
                      const Serialization & serialization) override;


    SpectrumMonitor & getSpectrumMonitor();

  private:
    SpectrumMonitor * pSpectrumMonitor_;
    GainManager gainManager_;
    LocationManager locationManager_;
    std::uint64_t u64BandwidthHz_;
    double dTxPowerdBm_;
    std::uint64_t u64TxFrequencyHz_;
    double dReceiverSensitivitydBm_;
    SpectrumMonitor::NoiseMode noiseMode_;
    std::uint16_t u16SubId_;
    std::uint16_t u16TxSequenceNumber_;
    std::pair<double,bool> optionalFixedAntennaGaindBi_;
    std::unique_ptr<PropagationModelAlgorithm> pPropagationModelAlgorithm_;
    Utils::CommonLayerStatistics commonLayerStatistics_;
    EventTablePublisher eventTablePublisher_;
    ReceivePowerTablePublisher receivePowerTablePublisher_;
    Microseconds noiseBinSize_;
    Microseconds maxSegmentOffset_;
    Microseconds maxMessagePropagation_;
    Microseconds maxSegmentDuration_;
    Microseconds timeSyncThreshold_;
    bool bNoiseMaxClamp_;
    double dSystemNoiseFiguredB_;
    StatisticNumeric<std::uint64_t> * pTimeSyncThresholdRewrite_;
    FadingManager fadingManager_;
  };
}
}

#endif // EMANEFRAMEWORK_HEADER_

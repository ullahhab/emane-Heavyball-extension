#ifndef EMANEEVENTSSLOTSTRUCTURE_HEADER_
#define EMANEEVENTSSLOTSTRUCTURE_HEADER_

#include "emane/types.h"
#include <set>

namespace EMANE
{
  namespace Events
  {
    class SlotStructureHB
    {
    public:
      SlotStructureHB(std::uint64_t u64BandwidthHz,
                    std::uint32_t u32FramePerMultiFrame,
                    std::uint32_t u32SlotsPerFrame,
                    const Microseconds & slotDuration,
                    const Microseconds & slotOverhead,
                    float beta);

      SlotStructureHB();

      std::uint64_t getBandwidth() const;

      std::uint32_t getFramesPerMultiFrame() const;

      std::uint32_t getSlotsPerFrame() const;

      const Microseconds & getSlotDuration() const;

      const Microseconds & getSlotOverhead() const;

      float getBeta() const;

    private:
      std::uint64_t u64BandwidthHz_;
      std::uint32_t u32FramePerMultiFrame_;
      std::uint32_t u32SlotsPerFrame_;
      Microseconds slotDuration_;
      Microseconds slotOverhead_;
      float beta_;

    };
  }
}

#include "emane/events/slotstructure.inl"

#endif // EMANEEVENTSSLOTSTRUCTURE_HEADER_

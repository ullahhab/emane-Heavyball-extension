#include "emane/types.h"
#include <set>

inline
EMANE::Events::SlotStructure::SlotStructure(std::uint64_t u64BandwidthHz,
                                            std::uint32_t u32FramePerMultiFrame,
                                            std::uint32_t u32SlotsPerFrame,
                                            const Microseconds & slotDuration,
                                            const Microseconds & slotOverhead,
                                            float beta):
  u64BandwidthHz_{u64BandwidthHz},
  u32FramePerMultiFrame_{u32FramePerMultiFrame},
  u32SlotsPerFrame_{u32SlotsPerFrame},
  slotDuration_{slotDuration},
  slotOverhead_{slotOverhead},
  beta_{beta}{}

inline
EMANE::Events::SlotStructure::SlotStructure():
  u64BandwidthHz_{},
  u32FramePerMultiFrame_{},
  u32SlotsPerFrame_{},
  slotDuration_{},
  slotOverhead_{},
  beta_{}{}

inline
std::uint64_t EMANE::Events::SlotStructure::getBandwidth() const
{
  return u64BandwidthHz_;
}

inline
std::uint32_t EMANE::Events::SlotStructure::getFramesPerMultiFrame() const
{
  return u32FramePerMultiFrame_;
}

inline
std::uint32_t EMANE::Events::SlotStructure::getSlotsPerFrame() const
{
  return u32SlotsPerFrame_;;
}

inline
const EMANE::Microseconds & EMANE::Events::SlotStructure::getSlotDuration() const
{
  return slotDuration_;
}

inline
const EMANE::Microseconds & EMANE::Events::SlotStructure::getSlotOverhead() const
{
  return slotOverhead_;
}

inline
float EMANE::Events::SlotStructure::getBeta() const
{
  return beta_;;
}

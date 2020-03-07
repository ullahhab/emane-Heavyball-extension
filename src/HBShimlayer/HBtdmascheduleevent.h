#ifndef EMANEEVENTSTDMASCHEDULEEVENT_HEADER_
#define EMANEEVENTSTDMASCHEDULEEVENT_HEADER_

#include "emane/event.h"
#include "emane/events/eventids.h"
#include "emane/events/slotinfo.h"
#include "emane/events/slotstructure.h"

#include <memory>

namespace EMANE
{
  namespace Events
  {
   namespace shim
   {
    class TDMAScheduleEvent : public Event
    {
    public:
      using Frequencies = std::set<uint64_t>;

      /**
       * Creates a TDMAScheduleEvent instance from a serialization
       *
       * @param serialization Message serialization
       *
       * @throw SerializationException when a valid message cannot be de-serialized
       */
      TDMAScheduleEvent(const Serialization & serialization);


      /**
       * Destroys an instance
       */
      ~TDMAScheduleEvent();

      const SlotInfos & getSlotInfos() const;


      const Frequencies & getFrequencies() const;

      std::pair<const SlotStructure &,bool> getSlotStructure() const;


      enum {IDENTIFIER = EMANE_EVENT_TDMA_SCHEDULE};

    private:
      class Implementation;
      std::unique_ptr<Implementation> pImpl_;
    };
  }
}
}

#endif // EMANEEVENTSTDMASCHEDULEEVENT_HEADER_

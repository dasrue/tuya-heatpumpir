#include <vector>
#include <IRSender.h>

class IRSenderVirt : public IRSender
{
  public:
    IRSenderVirt();
    void setFrequency(int frequency);
    void space(int spaceLength);
    void mark(int markLength);
    std::vector<int> getPulses();

  protected:
    int _halfPeriodicTime; 
    std::vector<int> _pulses;
};
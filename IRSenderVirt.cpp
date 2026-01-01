#include <IRSenderVirt.h>

// Send IR using the 'bit banging' on ESP8266 etc.


IRSenderVirt::IRSenderVirt() : IRSender(0)
{
  ;
}


void IRSenderVirt::setFrequency(int frequency)
{
  // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
  _halfPeriodicTime = 500/frequency; // T = 1/f but we need T/2 in microsecond and f is in kHz
  (void)frequency;
}


// Record a mark symbol
void IRSenderVirt::mark(int markLength)
{
  // Based on the tuya IR codes, even numbers are marks, odd numbers are spaces.
  if(_pulses.size() % 2 == 0) {
    _pulses.push_back(markLength);
  } else {
    _pulses.back() += markLength;
  }
}


// Send an IR 'space' symbol, i.e. transmitter OFF
void IRSenderVirt::space(int spaceLength)
{
  // Based on the tuya IR codes, even numbers are marks, odd numbers are spaces.
  if(_pulses.size() % 2 == 1) {
    _pulses.push_back(spaceLength);
  } else {
    _pulses.back() += spaceLength;
  }
}

std::vector<int> IRSenderVirt::getPulses() {
    return _pulses;
}
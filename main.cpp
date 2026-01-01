#include <iostream>
#include <MitsubishiHeatpumpIR.h>
#include <IRSenderVirt.h>

MitsubishiFDHeatpumpIR *heatpumpIR;
IRSenderVirt irSender;

int main() {

    heatpumpIR = new MitsubishiFDHeatpumpIR();
    std::cout << "Running as " << heatpumpIR->model() << ", info: " << heatpumpIR->info() << std::endl;

    heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);

    std::cout << "Generated " << irSender.getPulses().size() << " pulses:" << std::endl;
    for (int pulse : irSender.getPulses()) {
        std::cout << pulse << " ";
    }
    std::cout << std::endl;

    return 0;
}
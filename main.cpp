#include <iostream>
#include <MitsubishiHeatpumpIR.h>

MitsubishiFDHeatpumpIR *heatpumpIR;

int main() {

    heatpumpIR = new MitsubishiFDHeatpumpIR();

    std::cout << "Hello World From C++!" << std::endl;
    return 0;
}
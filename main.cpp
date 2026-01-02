#include <iostream>
#include <MitsubishiHeatpumpIR.h>
#include <IRSenderVirt.h>
#include <fastlz.h>
#include <base64.hpp>

MitsubishiFDHeatpumpIR *heatpumpIR;
IRSenderVirt irSender;


uint8_t * int_vector_to_16le_bytes(const std::vector<int>& vec) {
    size_t len = vec.size();
    uint8_t* bytes = new uint8_t[len * 2];
    for (size_t i = 0; i < len; ++i) {
        uint16_t val = vec[i] > 65535 ? 65535 : static_cast<uint16_t>(vec[i]);
        bytes[i * 2] = static_cast<uint8_t>(val & 0xFF);
        bytes[i * 2 + 1] = static_cast<uint8_t>((val >> 8) & 0xFF);
    }
    return bytes;
}

int main() {

    heatpumpIR = new MitsubishiFDHeatpumpIR();
    std::cout << "Running as " << heatpumpIR->model() << ", info: " << heatpumpIR->info() << std::endl;

    heatpumpIR->send(irSender, POWER_OFF, MODE_COOL, FAN_4, 17, VDIR_UP, HDIR_AUTO);

    std::vector<int> pulses = irSender.getPulses();

    if (pulses.back() == 0) {
        std::cout << "Removing trailing zero pulse." << std::endl;
        pulses.pop_back();
    }

    std::cout << "Generated " << pulses.size() << " pulses." << std::endl;

    if (pulses.size() < 8) {
        std::cout << "Padding to min 8 pulses to meet 16 byte minimum for fastlz." << std::endl;
        while (pulses.size() < 8) {
            pulses.push_back(0);
        }
    }

    uint8_t *to_compress_bytes = int_vector_to_16le_bytes(pulses);
    uint8_t *compressed_bytes = new uint8_t[pulses.size() * 3 + 18]; // Need 5% overhead and minimum 66 bytes output

    int comp_res = fastlz_compress_level(2, to_compress_bytes, pulses.size() * 2, compressed_bytes);

    std::cout << "Original size: " << pulses.size() * 2 << " bytes, Compressed size: " << comp_res << " bytes." << std::endl;

    std::string_view view(reinterpret_cast<const char*>(compressed_bytes), comp_res);
    auto encoded = base64::to_base64(view);  
    std::cout << "Base64 encoded compressed data: " << encoded << std::endl;

    return 0;
}
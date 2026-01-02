#include <iostream>
#include <strings.h>
#include <HeatpumpIRFactory.h>
#include <IRSenderVirt.h>
#include <fastlz.h>
#include <base64.hpp>

HeatpumpIR *heatpumpIR;
IRSenderVirt irSender;

void print_models() {
    // Generate using grep -o '"[^"]\+"' arduino-heatpumpir/HeatpumpIRFactory.cpp
    std::cout << "AUX" << std::endl;
    std::cout << "ballu" << std::endl;
    std::cout << "carrier_mca" << std::endl;
    std::cout << "carrier_nqv" << std::endl;
    std::cout << "daikin_arc417" << std::endl;
    std::cout << "daikin_arc480" << std::endl;
    std::cout << "daikin" << std::endl;
    std::cout << "electroluxyal" << std::endl;
    std::cout << "fuego" << std::endl;
    std::cout << "fujitsu_awyz" << std::endl;
    std::cout << "gree" << std::endl;
    std::cout << "greeyaa" << std::endl;
    std::cout << "greeyan" << std::endl;
    std::cout << "greeyac" << std::endl;
    std::cout << "greeyt" << std::endl;
    std::cout << "hisense_aud" << std::endl;
    std::cout << "hitachi" << std::endl;
    std::cout << "hyundai" << std::endl;
    std::cout << "ivt" << std::endl;
    std::cout << "nibe" << std::endl;
    std::cout << "midea" << std::endl;
    std::cout << "mitsubishi_fa" << std::endl;
    std::cout << "mitsubishi_fd" << std::endl;
    std::cout << "mitsubishi_fe" << std::endl;
    std::cout << "mitsubishi_heavy_fdtc" << std::endl;
    std::cout << "mitsubishi_heavy_zj" << std::endl;
    std::cout << "mitsubishi_heavy_zm" << std::endl;
    std::cout << "mitsubishi_kj" << std::endl;
    std::cout << "mitsubishi_msc" << std::endl;
    std::cout << "mitsubishi_msy" << std::endl;
    std::cout << "mitsubishi_sez" << std::endl;
    std::cout << "olimpia" << std::endl;
    std::cout << "panasonic_ckp" << std::endl;
    std::cout << "panasonic_dke" << std::endl;
    std::cout << "panasonic_eke" << std::endl;
    std::cout << "panasonic_jke" << std::endl;
    std::cout << "panasonic_lke" << std::endl;
    std::cout << "panasonic_nke" << std::endl;
    std::cout << "philco_phs32" << std::endl;
    std::cout << "samsung_aqv" << std::endl;
    std::cout << "samsung_fjm" << std::endl;
    std::cout << "sharp" << std::endl;
    std::cout << "toshiba_daiseikai" << std::endl;
    std::cout << "toshiba" << std::endl;
    std::cout << "ZHJG01" << std::endl;
    std::cout << "ZHLT01" << std::endl;
    std::cout << "KY-26" << std::endl;
}

uint8_t interpret_power(const char* arg) {
    if(strcasecmp(arg, "on") == 0 || strcasecmp(arg, "true") == 0 || strcasecmp(arg, "POWER_ON") == 0 || strcmp(arg, "1") == 0) {
        return POWER_ON;
    } else {
        return POWER_OFF;
    }
}

uint8_t interpret_mode(const char* arg) {
    if(strcasecmp(arg, "auto") == 0 || strcasecmp(arg, "MODE_AUTO") == 0 || strcmp(arg, "1") == 0) {
        return MODE_AUTO;
    } else if(strcasecmp(arg, "heat") == 0 || strcasecmp(arg, "MODE_HEAT") == 0 || strcmp(arg, "2") == 0) {
        return MODE_HEAT;
    } else if(strcasecmp(arg, "cool") == 0 || strcasecmp(arg, "MODE_COOL") == 0 || strcmp(arg, "3") == 0) {
        return MODE_COOL;
    } else if(strcasecmp(arg, "dry") == 0 || strcasecmp(arg, "MODE_DRY") == 0 || strcmp(arg, "4") == 0) {
        return MODE_DRY;
    } else if(strcasecmp(arg, "fan") == 0 || strcasecmp(arg, "MODE_FAN") == 0 || strcmp(arg, "5") == 0) {
        return MODE_FAN;
    } else if(strcasecmp(arg, "maint") == 0 || strcasecmp(arg, "MODE_MAINT") == 0 || strcmp(arg, "6") == 0) {
        return MODE_MAINT;
    } else {
        return 255;
    }
}

uint8_t interpret_fan(const char* arg) {
    if(strcasecmp(arg, "auto") == 0 || strcasecmp(arg, "FAN_AUTO") == 0 || strcmp(arg, "0") == 0) {
        return FAN_AUTO;
    } else if(strcmp(arg, "1") == 0 || strcasecmp(arg, "FAN_1") == 0) {
        return FAN_1;
    } else if(strcmp(arg, "2") == 0 || strcasecmp(arg, "FAN_2") == 0) {
        return FAN_2;
    } else if(strcmp(arg, "3") == 0 || strcasecmp(arg, "FAN_3") == 0) {
        return FAN_3;
    } else if(strcmp(arg, "4") == 0 || strcasecmp(arg, "FAN_4") == 0) {
        return FAN_4;
    } else if(strcmp(arg, "5") == 0 || strcasecmp(arg, "FAN_5") == 0) {
        return FAN_5;
    } else if(strcmp(arg, "6") == 0 || strcasecmp(arg, "silent") == 0 || strcasecmp(arg, "FAN_SILENT") == 0) {
        return FAN_SILENT;
    } else {
        return 255;
    }
}

uint8_t interpret_temperature(const char* arg) {
    int temp = atoi(arg);
    if(temp < 0 || temp > 40) {
        return 255;
    } else {
        return static_cast<uint8_t>(temp);
    }
}

uint8_t interpret_vane(const char* arg) {
    if(strcasecmp(arg, "auto") == 0 || strcasecmp(arg, "VDIR_AUTO") == 0 || strcmp(arg, "0") == 0) {
        return VDIR_AUTO;
    } else if(strcasecmp(arg, "swing") == 0 || strcasecmp(arg, "VDIR_SWING") == 0 || strcmp(arg, "1") == 0) {
        return VDIR_SWING;
    } else if(strcasecmp(arg, "up") == 0 || strcasecmp(arg, "VDIR_UP") == 0 || strcmp(arg, "2") == 0) {
        return VDIR_UP;
    } else if(strcasecmp(arg, "mup") == 0 || strcasecmp(arg, "VDIR_MUP") == 0 || strcmp(arg, "3") == 0) {
        return VDIR_MUP;
    } else if(strcasecmp(arg, "middle") == 0 || strcasecmp(arg, "VDIR_MIDDLE") == 0 || strcmp(arg, "4") == 0) {
        return VDIR_MIDDLE;
    } else if(strcasecmp(arg, "mdown") == 0 || strcasecmp(arg, "VDIR_MDOWN") == 0 || strcmp(arg, "5") == 0) {
        return VDIR_MDOWN;
    } else if(strcasecmp(arg, "down") == 0 || strcasecmp(arg, "VDIR_DOWN") == 0 || strcmp(arg, "6") == 0) {
        return VDIR_DOWN;
    } else {
        return 255;
    }
}

uint8_t interpret_hvane(const char* arg) {
    if(strcasecmp(arg, "auto") == 0 || strcasecmp(arg, "HDIR_AUTO") == 0 || strcmp(arg, "0") == 0) {
        return HDIR_AUTO;
    } else if(strcasecmp(arg, "swing") == 0 || strcasecmp(arg, "HDIR_SWING") == 0 || strcmp(arg, "1") == 0) {
        return HDIR_SWING;
    } else if(strcasecmp(arg, "middle") == 0 || strcasecmp(arg, "HDIR_MIDDLE") == 0 || strcmp(arg, "2") == 0) {
        return HDIR_MIDDLE;
    } else if(strcasecmp(arg, "left") == 0 || strcasecmp(arg, "HDIR_LEFT") == 0 || strcmp(arg, "3") == 0) {
        return HDIR_LEFT;
    } else if(strcasecmp(arg, "mleft") == 0 || strcasecmp(arg, "HDIR_MLEFT") == 0 || strcmp(arg, "4") == 0) {
        return HDIR_MLEFT;
    } else if(strcasecmp(arg, "mright") == 0 || strcasecmp(arg, "HDIR_MRIGHT") == 0 || strcmp(arg, "5") == 0) {
        return HDIR_MRIGHT;
    } else if(strcasecmp(arg, "right") == 0 || strcasecmp(arg, "HDIR_RIGHT") == 0 || strcmp(arg, "6") == 0) {
        return HDIR_RIGHT;
    } else {
        return 255;
    }
}

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

int main(int argc, char* argv[]) {

    if(argc < 8) {
        std::cout << "Usage: " << argv[0] << " <model> <power> <mode> <fan> <temperature> <vertical vane> <horizontal vane>" << std::endl;
        std::cout << "Model can be one of:" << std::endl;
        print_models();
        return 1;
    }

    heatpumpIR = HeatpumpIRFactory::create(argv[1]);
    if(!heatpumpIR) {
        std::cout << "Invalid model \"" << argv[1] << "\", valid models:" <<std::endl;
        print_models();
        return 1;
    }
    uint8_t power = interpret_power(argv[2]);
    uint8_t mode = interpret_mode(argv[3]);
    uint8_t fan = interpret_fan(argv[4]);
    uint8_t temperature = interpret_temperature(argv[5]);
    uint8_t vvane = interpret_vane(argv[6]);
    uint8_t hvane = interpret_hvane(argv[7]);

    if(power == 255) {
        std::cout << "Invalid power value \"" << argv[2] << "\"" << std::endl;
        return 1;
    }
    if(mode == 255) {
        std::cout << "Invalid mode value \"" << argv[3] << "\"" << std::endl;
        return 1;
    }
    if(fan == 255) {
        std::cout << "Invalid fan value \"" << argv[4] << "\"" << std::endl;
        return 1;
    }
    if(temperature == 255) {
        std::cout << "Invalid temperature value \"" << argv[5] << "\"" << std::endl;
        return 1;
    }
    if(vvane == 255) {
        std::cout << "Invalid vertical vane value \"" << argv[6] << "\"" << std::endl;
        return 1;
    }
    if(hvane == 255) {
        std::cout << "Invalid horizontal vane value \"" << argv[7] << "\"" << std::endl;
        return 1;
    }


    std::cout << "Running as " << heatpumpIR->model() << ", info: " << heatpumpIR->info() << std::endl;

    heatpumpIR->send(irSender, power, mode, fan, temperature, vvane, hvane);
    
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
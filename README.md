# Tuya Heatpump IR Encoder

This program generates base64-encoded IR commands for various heatpump models, compatible with Tuya Zigbee IR blasters. It takes command-line arguments specifying the heatpump model and desired settings, then outputs a compressed and encoded string that can be sent to the IR blaster to control the heatpump.

## Building

This project uses CMake for building and depends on several git submodules. Ensure you have CMake and a C++17 compatible compiler installed.

First, clone the repository with submodules:

```bash
git clone --recursive https://github.com/your-repo/tuya-heatpumpir.git
cd tuya-heatpumpir
```

Or if you already cloned without submodules:

```bash
git submodule update --init --recursive
```

Fix the bug in the `IRSenderPWM.cpp` file in the `arduino-heatpumpir` submodule by removing the first line, `IRSenderPWM.cpp`, otherwise the program won't compile

Then build:

```bash
mkdir build
cd build
cmake ..
make
```

On Windows with Ninja (as shown in the build directory):

```bash
mkdir build
cd build
cmake ..
ninja
```

## Usage

The program requires exactly 7 command-line arguments:

```
tuyaenc <model> <power> <mode> <fan> <temperature> <vertical_vane> <horizontal_vane>
```

### Arguments

1. **model**: The heatpump model identifier (see supported models below)
2. **power**: Power state - `on` or `off` (also accepts `true`, `false`, `1`, `0`)
3. **mode**: Operation mode - `auto`, `heat`, `cool`, `dry`, `fan`, `maint`
4. **fan**: Fan speed - `auto`, `1`, `2`, `3`, `4`, `5`, `silent`
5. **temperature**: Target temperature in Celsius (0-40)
6. **vertical_vane**: Vertical air direction - `auto`, `swing`, `up`, `mup`, `middle`, `mdown`, `down`
7. **horizontal_vane**: Horizontal air direction - `auto`, `swing`, `middle`, `left`, `mleft`, `mright`, `right`

### Supported Models

The following heatpump models are supported:

- AUX
- ballu
- carrier_mca
- carrier_nqv
- daikin_arc417
- daikin_arc480
- daikin
- electroluxyal
- fuego
- fujitsu_awyz
- gree
- greeyaa
- greeyan
- greeyac
- greeyt
- hisense_aud
- hitachi
- hyundai
- ivt
- nibe
- midea
- mitsubishi_fa
- mitsubishi_fd
- mitsubishi_fe
- mitsubishi_heavy_fdtc
- mitsubishi_heavy_zj
- mitsubishi_heavy_zm
- mitsubishi_kj
- mitsubishi_msc
- mitsubishi_msy
- mitsubishi_sez
- olimpia
- panasonic_ckp
- panasonic_dke
- panasonic_eke
- panasonic_jke
- panasonic_lke
- panasonic_nke
- philco_phs32
- samsung_aqv
- samsung_fjm
- sharp
- toshiba_daiseikai
- toshiba
- ZHJG01
- ZHLT01
- KY-26

### Example

```bash
./tuyaenc mitsubishi_kj on cool 1 18 up middle
```

This command generates an IR command for a Mitsubishi KJ model to turn on, set to cooling mode, fan speed 1, temperature 18°C, vertical vane up, horizontal vane middle.

The program will output:
- Model information
- Number of pulses generated
- Compression details
- The base64-encoded compressed IR data

### Output

The base64 string can be sent directly to a Tuya Zigbee IR blaster device to transmit the IR command to your heatpump.

## Dependencies

- Arduino Heatpump IR library (included in arduino-heatpumpir/)
- FastLZ compression library (included in FastLZ/)
- Base64 encoding library (included in base64/)
- Standard C++17 libraries

## License

See LICENSE file for details.

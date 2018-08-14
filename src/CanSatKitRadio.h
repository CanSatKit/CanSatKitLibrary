#ifndef CANSATKITLIBRARY_CANSATKITRADIO_H_
#define CANSATKITLIBRARY_CANSATKITRADIO_H_

#include <cstdint>


class CanSatKitRadio_ {
 public:
  enum class Bandwidth {
    _7800_Hz = 0b00000000,
    _10400_Hz = 0b00010000,
    _15600_Hz = 0b00100000,
    _20800_Hz = 0b00110000,
    _31250_Hz = 0b01000000,
    _41700_Hz = 0b01010000,
    _62500_Hz = 0b01100000,
    _125000_Hz = 0b01110000,
    _250000_Hz = 0b10000000,
    _500000_Hz = 0b10010000,
  };
  
  enum class SpreadingFactor {
    _7 = 0b01110000,
    _8 = 0b10000000,
    _9 = 0b10010000,
    _10 = 0b10100000,
    _11 = 0b10110000,
    _12 = 0b11000000,
  };
  
  enum class CodingRate {
    _4_5 = 0b00000010,
    _4_6 = 0b00000100,
    _4_7 = 0b00000110,
    _4_8 = 0b00001000,
  };
  
  
  static bool begin(int pin_cs_, int pin_dio0_, float frequency_in_mhz, Bandwidth bandwidth, SpreadingFactor spreadingFactor, CodingRate codingRate);
  static void disable_debug();
  
  static bool transmit(const char* str);
  static bool transmit(const char* data, std::uint8_t length);
  static bool transmit(const std::uint8_t* data, std::uint8_t length);
  static void flush();
  
  static std::uint8_t available();
  static void receive(char* data, std::uint8_t& length);
  static void receive(std::uint8_t* data, std::uint8_t& length);
  static std::int8_t get_rssi_last();
  static std::int8_t get_rssi_now();  
};

extern CanSatKitRadio_ CanSatKitRadio;

constexpr static auto Bandwidth_7800_Hz = CanSatKitRadio_::Bandwidth::_7800_Hz;
constexpr static auto Bandwidth_10400_Hz = CanSatKitRadio_::Bandwidth::_10400_Hz;
constexpr static auto Bandwidth_15600_Hz = CanSatKitRadio_::Bandwidth::_15600_Hz;
constexpr static auto Bandwidth_20800_Hz = CanSatKitRadio_::Bandwidth::_20800_Hz;
constexpr static auto Bandwidth_31250_Hz = CanSatKitRadio_::Bandwidth::_31250_Hz;
constexpr static auto Bandwidth_41700_Hz = CanSatKitRadio_::Bandwidth::_41700_Hz;
constexpr static auto Bandwidth_62500_Hz = CanSatKitRadio_::Bandwidth::_62500_Hz;
constexpr static auto Bandwidth_125000_Hz = CanSatKitRadio_::Bandwidth::_125000_Hz;
constexpr static auto Bandwidth_250000_Hz = CanSatKitRadio_::Bandwidth::_250000_Hz;
constexpr static auto Bandwidth_500000_Hz = CanSatKitRadio_::Bandwidth::_500000_Hz;

constexpr static auto SpreadingFactor_7 = CanSatKitRadio_::SpreadingFactor::_7;
constexpr static auto SpreadingFactor_8 = CanSatKitRadio_::SpreadingFactor::_8;
constexpr static auto SpreadingFactor_9 = CanSatKitRadio_::SpreadingFactor::_9;
constexpr static auto SpreadingFactor_10 = CanSatKitRadio_::SpreadingFactor::_10;
constexpr static auto SpreadingFactor_11 = CanSatKitRadio_::SpreadingFactor::_11;
constexpr static auto SpreadingFactor_12 = CanSatKitRadio_::SpreadingFactor::_12;

constexpr static auto CodingRate_4_5 = CanSatKitRadio_::CodingRate::_4_5;
constexpr static auto CodingRate_4_6 = CanSatKitRadio_::CodingRate::_4_6;
constexpr static auto CodingRate_4_7 = CanSatKitRadio_::CodingRate::_4_7;
constexpr static auto CodingRate_4_8 = CanSatKitRadio_::CodingRate::_4_8;


class CanSatKitRadioFrame : public Print {
 public:
  int size;
  char buffer[256];

  CanSatKitRadioFrame() : size(0) {}

  virtual size_t write(uint8_t x) {
    buffer[size++] = x;
    return 1;
  }

  void send() {
    CanSatKitRadio.transmit(buffer, size);
    size = 0;
  }
};


#endif  // CANSATKITLIBRARY_CANSATKITRADIO_H_

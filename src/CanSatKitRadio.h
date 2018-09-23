#ifndef CANSATKITLIBRARY_RadioH_
#define CANSATKITLIBRARY_RadioH_

#include <cstdint>

namespace CanSatKit {

class Frame : public Print {
  public:
  constexpr static std::uint8_t max_size = 255;
  std::uint8_t size;
  char buffer[max_size];

  Frame() : size(0) {}

  virtual size_t write(uint8_t x) {
    // one byte for null termination
    if (size >= max_size - 1) {
      return 0;
    }
    buffer[size++] = x;
    return 1;
  }

  operator const char*() {
    buffer[size] = '\0';
    return buffer;
  }

  void clear() {
    size = 0;
  }
};

class Radio {
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
  
  
  Radio(int pin_cs_, int pin_dio0_, float frequency_in_mhz, Bandwidth bandwidth, SpreadingFactor spreadingFactor, CodingRate codingRate);
  static bool begin();
  static void disable_debug();
  
  static bool transmit(Frame frame);
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

constexpr static auto Bandwidth_7800_Hz = Radio::Bandwidth::_7800_Hz;
constexpr static auto Bandwidth_10400_Hz = Radio::Bandwidth::_10400_Hz;
constexpr static auto Bandwidth_15600_Hz = Radio::Bandwidth::_15600_Hz;
constexpr static auto Bandwidth_20800_Hz = Radio::Bandwidth::_20800_Hz;
constexpr static auto Bandwidth_31250_Hz = Radio::Bandwidth::_31250_Hz;
constexpr static auto Bandwidth_41700_Hz = Radio::Bandwidth::_41700_Hz;
constexpr static auto Bandwidth_62500_Hz = Radio::Bandwidth::_62500_Hz;
constexpr static auto Bandwidth_125000_Hz = Radio::Bandwidth::_125000_Hz;
constexpr static auto Bandwidth_250000_Hz = Radio::Bandwidth::_250000_Hz;
constexpr static auto Bandwidth_500000_Hz = Radio::Bandwidth::_500000_Hz;

constexpr static auto SpreadingFactor_7 = Radio::SpreadingFactor::_7;
constexpr static auto SpreadingFactor_8 = Radio::SpreadingFactor::_8;
constexpr static auto SpreadingFactor_9 = Radio::SpreadingFactor::_9;
constexpr static auto SpreadingFactor_10 = Radio::SpreadingFactor::_10;
constexpr static auto SpreadingFactor_11 = Radio::SpreadingFactor::_11;
constexpr static auto SpreadingFactor_12 = Radio::SpreadingFactor::_12;

constexpr static auto CodingRate_4_5 = Radio::CodingRate::_4_5;
constexpr static auto CodingRate_4_6 = Radio::CodingRate::_4_6;
constexpr static auto CodingRate_4_7 = Radio::CodingRate::_4_7;
constexpr static auto CodingRate_4_8 = Radio::CodingRate::_4_8;




};  // namespace CanSatKit

#endif  // CANSATKITLIBRARY_RadioH_

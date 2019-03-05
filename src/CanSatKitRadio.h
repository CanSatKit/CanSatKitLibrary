#ifndef CANSATKITLIBRARY_RadioH_
#define CANSATKITLIBRARY_RadioH_

#include <cstdint>

namespace CanSatKit {

/**
 * @brief Frame object represents one radio frame to be send over the RF link.
 * Use it the same as Serial/SerialUSB devices.
 * Frame should consist of ASCII-characters only.
 * Remembers data in internal buffer, to be send using radio.transmit() method.
 * Maximum data length is 254 bytes (+1 byte of null termination).
 */
class Frame : public Print {
 public:
  Frame() : size(0) {}
  
  /**
  * @brief actual size of the frame (string length)
  */
  std::uint8_t size;

  /**
   * @brief Returns null-terminated string object
   * 
   * @return const char* string object
   */
  operator const char*() {
    buffer[size] = '\0';
    return buffer;
  }

  /**
   * @brief Clear frame
   */
  void clear() {
    size = 0;
  }


 private:
  constexpr static std::uint8_t max_size = 255;
  char buffer[max_size];

  virtual size_t write(uint8_t x) {
    // one byte for null termination
    if (size >= max_size - 1) {
      return 0;
    }
    buffer[size++] = x;
    return 1;
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
  
  /**
   * @brief Construct a new Radio object. 
   * Settings should be the same on the receiver and transmitter.
   * Make sure that you comply with CanSat and local regulations.
   * Settings reflect on bitrate and link budget.
   * Bitrate = bandwidth/(2**spreadingFactor) * codingRate
   * 
   * @param pin_cs_  Arduino pin number connected to radio CS pin. Set to `Pins::Radio::ChipSelect` if you use CanSatKit.
   * @param pin_dio0_ Arduino pin number connected to radio DIO0 pin. Set to `Pins::Radio::DIO0` if you use CanSatKit.
   * @param frequency_in_mhz Set radio center frequency.
   * @param bandwidth Set module radio bandwidth.
   * @param spreadingFactor Set module spreading factor.
   * @param codingRate Set module coding rate.
   */
  Radio(int pin_cs_, int pin_dio0_, float frequency_in_mhz, Bandwidth bandwidth, SpreadingFactor spreadingFactor, CodingRate codingRate);
  /**
   * @brief Start communication with radio module.
   * Sets proper radio settings and starts module in receive mode.
   * 
   * @return `true`: Communication succeeded, module initialised properly. `false`: Module initialisation failed.
   */
  static bool begin();

  /**
   * @brief Disable debug messages on SerialUSB.
   */
  static void disable_debug();
  
  /**
   * @brief Put frame into the transmit buffer.
   * @return `true` if frame put into buffer. `false` if not enough space in the buffer.
   */
  static bool transmit(Frame frame);

  /**
   * @brief Put String str into the transmit buffer.
   * @return `true` if frame put into buffer. `false` if not enough space in the buffer.
   */
  static bool transmit(String str);

  /**
   * @brief Put string str into the transmit buffer.
   * @return `true` if frame put into buffer. `false` if not enough space in the buffer.
   */
  static bool transmit(const char* str);

  /**
   * @brief Put binary data into the transmit buffer (byte table of length length).
   * @return `true` if frame put into buffer. `false` if not enough space in the buffer.
   */
  static bool transmit(const std::uint8_t* data, std::uint8_t length);

  /**
   * @brief Waits until all frames in the transmit buffer are transmitted.
   */
  static void flush();
  
  /**
   * @brief Checks if transmit fifo is empty, which means that radio module is sending last frame or is idle.
   *
   * @return `true` if transmit fifo is empty
   */
  static bool tx_fifo_empty();


  /**
   * @brief Get number of frames in receive buffer
   * 
   * @return std::uint8_t Number of received frames.
   */
  static std::uint8_t available();

  /**
   * @brief Get character string from receive buffer
   * @param data pointer to fill with data
   */
  static void receive(char* data);

  /**
   * @brief Get binary data from receive buffer
   * 
   * @param data pointer to fill with data
   * @param length length of received frame
   */
  static void receive(std::uint8_t* data, std::uint8_t& length);

  /**
   * @brief Get the RSSI of last frame.
   * 
   * @return int RSSI in dBm
   */
  static int get_rssi_last();

  /**
   * @brief Get the actual RSSI value.
   * 
   * @return int RSSI in dBm
   */
  static int get_rssi_now();
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

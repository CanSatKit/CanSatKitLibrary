#ifndef CANSATKITLIBRARY_CANSATKIT_H_
#define CANSATKITLIBRARY_CANSATKIT_H_

#include "CanSatKitRadio.h"
#include "CanSatKitBMP280.h"

namespace CanSatKit {
namespace Pins {

namespace Radio {
constexpr int ChipSelect = 10;
constexpr int DIO0 = 12;
};  // namespace Radio

namespace SD {
constexpr int ChipSelect = 11;
};  // namespace SD

constexpr int LED = 13;
  
  
namespace EM1 {
namespace Radio {
constexpr int ChipSelect = 9;
constexpr int DIO0 = 10;
};  // namespace Radio

namespace SD {
constexpr int ChipSelect = 8;
};  // namespace SD
};  // namespace EM1

};  // namespace Pins
};  // namespace CanSatKit

#endif  // CANSATKITLIBRARY_CANSATKIT_H_

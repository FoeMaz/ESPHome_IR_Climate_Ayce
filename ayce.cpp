#include "ayce.h"
#include "esphome/core/log.h"

namespace esphome::ayce {

static const char *const TAG = "ayce.climate";

static constexpr const char BASE_FRAME[] =
"0001100000100111010000011000000000000000000000000000000010000000000000001000000000010000000111101";

void AyceClimate::transmit_state() {

  bool bits[96] = {false};

  for (int i = 0; i < 95; i++) {
    bits[i] = BASE_FRAME[i] == '1';
  }

  //
  // Power
  //
  bits[24] = this->mode != climate::CLIMATE_MODE_OFF;

  //
  // Temperatur
  //
  uint8_t temp =
      ((uint8_t)this->target_temperature - 16) << 1;
  
  for (int i = 0; i < 5; i++) {
      bits[16 + i] =
          (temp >> (4 - i)) & 1;
  }

  //
  // Modus
  //
  switch (this->mode) {

    case climate::CLIMATE_MODE_COOL:
      bits[22] = 0;
      bits[23] = 1;
      break;

    case climate::CLIMATE_MODE_DRY:
      bits[22] = 1;
      bits[23] = 0;
      break;

    case climate::CLIMATE_MODE_FAN_ONLY:
      bits[22] = 1;
      bits[23] = 1;
      break;

    default:
      break;
  }

  //
  // Swing
  //
  bits[25] =
      this->swing_mode ==
      climate::CLIMATE_SWING_VERTICAL;

  //
  // Sleep
  //
  bits[41] =
      this->preset.value_or(
          climate::CLIMATE_PRESET_NONE) ==
      climate::CLIMATE_PRESET_SLEEP;

  //
  // Fan
  //
  bits[81] = 0;
  bits[82] = 0;
  bits[83] = 0;

  switch (
      this->fan_mode.value_or(
          climate::CLIMATE_FAN_LOW)) {

    case climate::CLIMATE_FAN_HIGH:
      bits[81] = 1;
      break;

    case climate::CLIMATE_FAN_MEDIUM:
      bits[82] = 1;
      break;

    case climate::CLIMATE_FAN_LOW:
    default:
      bits[83] = 1;
      break;
  }

  //
  // Checksum
  //
  uint8_t checksum = 0;

  for (int nib = 0; nib < 22; nib++) {

    uint8_t value = 0;

    for (int b = 0; b < 4; b++) {
      value <<= 1;
      value |= bits[nib * 4 + b];
    }

    checksum += value;
  }

  checksum -= 18;

  for (int i = 0; i < 8; i++) {
    bits[88 + i] =
        (checksum >> (7 - i)) & 1;
  }

  ESP_LOGD(TAG,
           "Mode=%d Temp=%.0f Fan=%d",
           (int) this->mode,
           this->target_temperature,
           (int) this->fan_mode.value_or(
               climate::CLIMATE_FAN_LOW));

  auto transmit =
      this->transmitter_->transmit();

  auto *data =
      transmit.get_data();

  data->set_carrier_frequency(38000);

  //
  // Header
  //
  data->mark(AYCE_HDR_MARK);
  data->space(AYCE_HDR_SPACE);

  //
  // Datenbits
  //
  for (int i = 0; i < 96; i++) {

    data->mark(AYCE_BIT_MARK);

    if (bits[i])
      data->space(AYCE_ONE_SPACE);
    else
      data->space(AYCE_ZERO_SPACE);
  }

  //
  // Footer
  //
  data->mark(AYCE_BIT_MARK);
  data->space(0);

  transmit.perform();
}

}  // namespace esphome::ayce

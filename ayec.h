#pragma once

#include "esphome/components/climate_ir/climate_ir.h"
#include "esphome/components/sensor/sensor.h"
#include <cmath>

namespace esphome::ayce {

static const float AYCE_TEMP_MIN = 18.0f;
static const float AYCE_TEMP_MAX = 32.0f;
static const float AYCE_TEMP_INC = 1.0f;

// AYCE IR timings
static const uint32_t AYCE_HDR_MARK = 3200;
static const uint32_t AYCE_HDR_SPACE = 3200;

static const uint32_t AYCE_BIT_MARK = 450;
static const uint32_t AYCE_ZERO_SPACE = 450;
static const uint32_t AYCE_ONE_SPACE = 1150;

class AyceClimate final : public climate_ir::ClimateIR {
 public:
  AyceClimate()
      : climate_ir::ClimateIR(
            AYCE_TEMP_MIN,
            AYCE_TEMP_MAX,
            AYCE_TEMP_INC,

            true,   // supports cool
            false,  // supports heat

            {
                climate::CLIMATE_FAN_LOW,
                climate::CLIMATE_FAN_MEDIUM,
                climate::CLIMATE_FAN_HIGH,
            },

            {
                climate::CLIMATE_SWING_OFF,
                climate::CLIMATE_SWING_VERTICAL,
            },

            {
                climate::CLIMATE_PRESET_NONE,
                climate::CLIMATE_PRESET_SLEEP,
            }) {}

  void set_temperature_sensor(sensor::Sensor *sensor) {
    this->temperature_sensor_ = sensor;
  }

  void setup() override {
    climate_ir::ClimateIR::setup();
  }

  void loop() override {
    if (this->temperature_sensor_ != nullptr &&
        !std::isnan(this->temperature_sensor_->state) &&
        this->current_temperature != this->temperature_sensor_->state) {

      this->current_temperature =
          this->temperature_sensor_->state;

      this->publish_state();
    }
  }

 protected:
  climate::ClimateTraits traits() override {
    auto traits = climate_ir::ClimateIR::traits();

    traits.set_supported_modes({
        climate::CLIMATE_MODE_OFF,
        climate::CLIMATE_MODE_COOL,
        climate::CLIMATE_MODE_DRY,
        climate::CLIMATE_MODE_FAN_ONLY,
    });

    traits.set_supported_fan_modes({
        climate::CLIMATE_FAN_LOW,
        climate::CLIMATE_FAN_MEDIUM,
        climate::CLIMATE_FAN_HIGH,
    });

    traits.set_supported_swing_modes({
        climate::CLIMATE_SWING_OFF,
        climate::CLIMATE_SWING_VERTICAL,
    });

    traits.set_supported_presets({
        climate::CLIMATE_PRESET_NONE,
        climate::CLIMATE_PRESET_SLEEP,
    });

    return traits;
  }

  void transmit_state() override;

  bool on_receive(remote_base::RemoteReceiveData data) override {
    return false;
  }

  sensor::Sensor *temperature_sensor_{nullptr};
};

}  // namespace esphome::ayce

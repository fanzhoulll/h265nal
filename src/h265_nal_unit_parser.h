/*
 *  Copyright (c) Facebook, Inc. and its affiliates.
 */

#pragma once

#include <vector>

#include "absl/types/optional.h"

#include "rtc_base/bit_buffer.h"

#include "h265_vps_parser.h"

namespace h265nal {

// A class for parsing out an H265 NAL Unit Header.
class H265NalUnitHeaderParser {
 public:
  // The parsed state of the NAL Unit Header.
  struct NalUnitHeaderState {
    NalUnitHeaderState() = default;
    NalUnitHeaderState(const NalUnitHeaderState&) = default;
    ~NalUnitHeaderState() = default;

    uint32_t forbidden_zero_bit = 0;
    uint32_t nal_unit_type = 0;
    uint32_t nuh_layer_id = 0;
    uint32_t nuh_temporal_id_plus1 = 0;
  };

  // Unpack RBSP and parse NAL unit header state from the supplied buffer.
  static absl::optional<NalUnitHeaderState> ParseNalUnitHeader(
      const uint8_t* data, size_t length);
  static absl::optional<NalUnitHeaderState> ParseNalUnitHeader(
      rtc::BitBuffer* bit_buffer);
};


// A class for parsing out an H265 NAL Unit.
class H265NalUnitParser {
 public:
  // The parsed state of the NAL Unit. Only some select values are stored.
  // Add more as they are actually needed.
  struct NalUnitState {
    NalUnitState() = default;
    NalUnitState(const NalUnitState&) = default;
    ~NalUnitState() = default;

    struct H265NalUnitHeaderParser::NalUnitHeaderState nal_unit_header;
    // payload
    struct H265VpsParser::VpsState vps;
  };

  // Unpack RBSP and parse NAL unit state from the supplied buffer.
  static absl::optional<NalUnitState> ParseNalUnit(
      const uint8_t* data, size_t length);
  static absl::optional<NalUnitState> ParseNalUnit(
      rtc::BitBuffer* bit_buffer);
};

}  // namespace h265nal
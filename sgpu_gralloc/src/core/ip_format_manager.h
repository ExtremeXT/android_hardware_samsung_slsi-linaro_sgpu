///
/// @file ip_format_manager.h
/// @copyright 2020-2021 Samsung Electronics
///

#pragma once

#include <cstdint>

#include "hidl_defines.h"
#include "interface/metadata_gralloc.h"
#include "interface/private_handle.h"

namespace android {
namespace samsung {
namespace gralloc {

enum class FormatLayout : uint32_t;

enum class Ip : uint32_t {
        CPU = 0,
        GPU,
        HWC,
        CAMERA,
        VIDEO,
        COUNT
};

enum class IpBitMask : uint32_t {
        CPU    = (0x1 << static_cast<uint32_t>(Ip::CPU)),
        GPU    = (0x1 << static_cast<uint32_t>(Ip::GPU)),
        HWC    = (0x1 << static_cast<uint32_t>(Ip::HWC)),
        CAMERA = (0x1 << static_cast<uint32_t>(Ip::CAMERA)),
        VIDEO  = (0x1 << static_cast<uint32_t>(Ip::VIDEO)),
};

struct align_info {
        uint32_t stride_in_bytes;        // stride for each plane
        uint32_t vstride_in_pixels;      // vertical stride for each plane
        uint32_t plane_padding_in_bytes; // padding added to each plane
        uint32_t alloc_padding_in_bytes; // padding added to each allocation
};

class IpFormatManager {
public:
        virtual ~IpFormatManager() = default;
        IpFormatManager(const IpFormatManager&) = delete;
        IpFormatManager(const IpFormatManager&&) = delete;
        IpFormatManager& operator=(const IpFormatManager&) = delete;
        IpFormatManager& operator=(const IpFormatManager&&) = delete;

        virtual uint32_t      get_layout(PixelFormat format, const BufferDescriptor &descriptor) const  = 0;
        virtual align_info    get_linear_alignment(PixelFormat format) const  = 0;

protected:
        IpFormatManager() = default;
        void disable_sajc_if_needed(const BufferDescriptor &descriptor, uint32_t *layout) const;
};

} // gralloc
} // samsung
} // android

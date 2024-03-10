#pragma once

#include <vendor/mc/aproximity/1.0/IAproximity.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include "dev/proximity_sensor.h"

namespace vendor::mc::aproximity::V1_0::implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Aproximity : public IAproximity {

	Aproximity();
	~Aproximity();

    // Methods from ::vendor::mc::aproximity::V1_0::IAproximity follow.
    Return<int32_t> poll(int32_t precision) override;
    Return<void> get_details(get_details_cb _hidl_cb) override;
    Return<void> summarize(summarize_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.
    // Methods from ::android::hidl::base::V1_0::IBase follow.
    Return<void> debug(const hidl_handle &handle,
                       const hidl_vec<hidl_string> &options) override;

private:
	uint64_t 			pollCallCount;
	int64_t 			lastPollCalledMs;
	int 				fd;
	proximity_params_t	params;

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IAproximity* HIDL_FETCH_IAproximity(const char* name);

}  // namespace vendor::mc::aproximity::implementation
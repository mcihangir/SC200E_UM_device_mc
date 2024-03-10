#include <chrono>
#include "Aproximity.h"

using namespace std::chrono;

namespace vendor::mc::aproximity::V1_0::implementation {
/////////////////////////////////////////////////////////////////////////////////////////
static int64_t now(){
	time_point now = system_clock().now();
	milliseconds nowMs = duration_cast<milliseconds> (now.time_since_epoch());
	return static_cast<int64_t> (nowMs.count());

}
/////////////////////////////////////////////////////////////////////////////////////////
Aproximity::Aproximity() {
	this->fd = open_sensor(this->params);
	if(this->fd < 0){
		this->params.precision.min = -1;
		this->params.precision.max = -1;
		this->params.proximity.min = -1;
		this->params.proximity.max = -1;
	}
}
Aproximity::~Aproximity() {
	if(this->fd >= 0){
		close_sensor(this->fd);
		this->fd = -1;
	}
	this->pollCallCount = 0;
	this->lastPollCalledMs = 0;	
}
/////////////////////////////////////////////////////////////////////////////////////////
// Methods from ::vendor::mc::aproximity::V1_0::IAproximity follow.
Return<int32_t> Aproximity::poll(int32_t precision) {
    this->pollCallCount++;
	this->lastPollCalledMs = now();

	if(this->fd <= 0){
		return -1;
	}
	int shimPrecision = static_cast<int>(precision);
	int32_t result = static_cast<int32_t>(poll_sensor(this->fd, shimPrecision));
	
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////
Return<void> Aproximity::get_details(get_details_cb _hidl_cb) {
	ProximityDetails result;

	result.precision.min = static_cast<int32_t>(this->params.precision.min);
	result.precision.max = static_cast<int32_t>(this->params.precision.max);
	result.proximity.min = static_cast<int32_t>(this->params.proximity.min);
	result.proximity.max = static_cast<int32_t>(this->params.proximity.max);

	_hidl_cb(result);
    return Void();
}
/////////////////////////////////////////////////////////////////////////////////////////
Return<void> Aproximity::summarize(summarize_cb _hidl_cb) {
	ProximitySummary result;

	result.pollCallCount = this->pollCallCount;
	result.lastPollCalledMs = this->lastPollCalledMs;
	_hidl_cb(result);
    return Void();
}
/////////////////////////////////////////////////////////////////////////////////////////
Return<void> Aproximity::debug(const hidl_handle &handle, const hidl_vec<hidl_string> & /*options*/ ){
	if( handle == nullptr || handle->numFds < 1 || handle->data[0] < 0){
		return Void();
	}
	int fd = handle->data[0];
	dprintf(fd, "HIDL:\n");
	dprintf(fd, " Poll Call Count: %llu\n", static_cast<unsigned long long>(this->pollCallCount) );
	dprintf(fd, " Last Poll  Call: %lld\n", static_cast<long long>(this->lastPollCalledMs) );
	fsync(fd);
	return Void();
}
// Methods from ::android::hidl::base::V1_0::IBase follow.

//IAproximity* HIDL_FETCH_IAproximity(const char* /* name */) {
    //return new Aproximity();
//}
//
}  // namespace vendor::mc::aproximity::implementation
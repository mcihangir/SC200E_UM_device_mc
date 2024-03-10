#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/Errors.h>
#include <utils/StrongPointer.h>

#include "Aproximity.h"

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
//using vendor::mc::aproximity::V1_0::implementation::Aproximity;
using vendor::mc::aproximity::V1_0::implementation::Aproximity;

using namespace android;

int main() {
	configureRpcThreadpool(1, true);

	sp<Aproximity> aproximity = new Aproximity();
	status_t status = aproximity->registerAsService("default");
	if(status != 0){
		return status;
	}

	joinRpcThreadpool();	
}


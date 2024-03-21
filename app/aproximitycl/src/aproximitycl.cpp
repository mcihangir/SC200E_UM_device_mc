
#include <hidl/HidlSupport.h>
#include <vendor/mc/aproximity/1.0/IAproximity.h>
#include <vendor/mc/aproximity/1.0/types.h>
#include <utils/StrongPointer.h>
#include <getopt.h>

#define DELAY_SECS 5

using vendor::mc::aproximity::V1_0::IAproximity;
using vendor::mc::aproximity::V1_0::ProximityDetails;
using vendor::mc::aproximity::V1_0::ProximitySummary;
using android::sp;

using namespace android::hardware;

/////////////////////////////////////////////////////////////////////////////////////////
static void detailsCP(const ProximityDetails& details){
	printf("[details] precision min/max: %d/%d\n", details.precision.min, details.precision.max);
	printf("[details] proximity min/max: %d/%d\n", details.proximity.min, details.proximity.max);
}
/////////////////////////////////////////////////////////////////////////////////////////
static void summaryCP(const ProximitySummary& summary){
	printf("[summary] poll call count: %lu last call(mc): %ld\n", summary.pollCallCount, summary.lastPollCalledMs);	
}
/////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	//Get the HIDL to use
	sp<IAproximity> client = IAproximity::getService();
	if(client == nullptr){
		fprintf(stderr, "Unable to get aproximity service interface\n");
		return -2;
	}	

	int32_t cnt = 0;
	while(true){
		Return<void> result = client->get_details(detailsCP);
		if(!result.isOk()){
			fprintf(stderr, "Unable to get aproximity service details, Error: %s\n", result.description().c_str());
			return -1;			
		}	
		client->summarize(summaryCP);
		Return<int32_t> retProximity = client->poll(++cnt%2?10:90);
		if(!retProximity.isOk()){
			fprintf(stderr, "Unable to get aproximity service poll, Error: %s\n", retProximity.description().c_str());
			return -1;			
		}	
		printf("[proximity] : %d\n", static_cast<int32_t>(retProximity));
		sleep(DELAY_SECS);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////





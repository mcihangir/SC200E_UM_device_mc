# Inherit from the bengal based definition
#$(call inherit-product, device/qcom/bengal/bengal.mk)


LOCAL_PATH := $(call my-dir)
# $(LOCAL_PATH)/
######################################################################
#PRODUCT_MANUFACTURER := MC
#PRODUCT_NAME := mcdevice
#PRODUCT_DEVICE := bengal
#PRODUCT_BRAND := Android
#PRODUCT_MODEL := AOSP on qcm2290
######################################################################
BOARD_SEPOLICY_DIRS += \
	device/mc/sepolicy

BOARD_SEPOLICY_UNION += \
	file_contexts \
	hwservice_contexts
######################################################################
# mcdevice init scripts
######################################################################
# Bu örnek, init_mcdevice.rc dosyasını hedef cihaza kopyalar ve başlatma sırasında çalıştırır
# Özel rc dosyanızı hedef cihaza kopyalamak için PRODUCT_COPY_FILES kullanın
# copy init.mcdevice.system.rc to /system/etc/init folder in the target file system
#PRODUCT_COPY_FILES += device/mcdevice/mcdevice.rc:/system/etc/init/mcdevice.rc 
# init_mcdevice.rc dosyasını başlatma sırasında çalıştırmak için INIT etiketini kullanın
#INIT += /system/etc/init/mcdevice.rc

######################################################################
# Add the following Packages
######################################################################
# Added to M.9.15/hardware/interfaces/compatibility_matrices/compatibility_matrix.5.xml
# DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE := device/mc/device_framework_matrix.xml

# files are incompatible: The following instances are in the device manifest but not specified in framework compatibility matrix: 
#     vendor.mc.aproximity@1.0::IAproximity/default
# Suggested fix:
# 1. Update deprecated HALs to the latest version.
# 2. Check for any typos in device manifest or framework compatibility matrices with FCM version >= 5.
# 3. For new platform HALs, add them to any framework compatibility matrix with FCM version >= 5 where applicable.
# 4. For device-specific HALs, add to DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE or DEVICE_PRODUCT_COMPATIBILITY_MATRIX_FILE.: Success

PRODUCT_PACKAGES += \
	libacmeproximityshim \
	proximityhal.default \
	vendor.mc.aproximity@1.0-service \
	vendor.mc.aproximity@1.0-impl \
	aproximitycl \

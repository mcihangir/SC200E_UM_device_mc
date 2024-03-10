# Inherit from the bengal based definition
#$(call inherit-product, device/qcom/bengal/bengal.mk)
$(call inherit-product, device/qcom/bengal/bengal.mk)

######################################################################
PRODUCT_MANUFACTURER := MC
PRODUCT_NAME := mcdevice
PRODUCT_DEVICE := bengal
PRODUCT_BRAND := Android
PRODUCT_MODEL := AOSP on qcm2290
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
DEVICE_MANIFEST_FILE += \
	device/mc/manifests/framework_compatibility_matrix.xml
	#device/mc/manifests/manifest.xml

PRODUCT_PACKAGES += \
	libacmeproximityshim \
	proximityhal.default \
	vendor.acme.one.aproximity@1.0-service \


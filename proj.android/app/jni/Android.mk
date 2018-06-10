LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH)/../../../libs/cocos_creator)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes/Headers
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../libs/cocos_creator/reader

define walk
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

FILE_LIST := $(filter %.cpp, $(call walk, $(LOCAL_PATH)/../../../Classes/Source))

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += creator_reader

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)
$(call import-module, reader)

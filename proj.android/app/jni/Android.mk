LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Components/Hud.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Managers/CameraManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Managers/ResourceManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Managers/MapManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Managers/SceneManager.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Scenes/GameplayScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Scenes/LogoScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Scenes/MainMenuScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Units/BaseUnit.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Units/Boss.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Units/EnemyUnit.cpp \
                   $(LOCAL_PATH)/../../../Classes/Source/Units/PlayerUnit.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes/Headers

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += creator_reader   # add dependence

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)
$(call import-module, ./../../libs/cocos_creator/reader)  # import module path

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AppConsts.cpp \
                   ../../Classes/Scene/SplashScene.cpp \
                   ../../Classes/Scene/MainScene.cpp \
                   ../../Classes/GameLogic/World.cpp \
                   ../../Classes/GameLogic/Physics.cpp \
                   ../../Classes/GameLogic/Collidable.cpp \
                   ../../Classes/GameLogic/Player/Cannon.cpp \
                   ../../Classes/GameLogic/Projectile/Projectile.cpp \
                   ../../Classes/GameLogic/Projectile/CannonBall.cpp \
                   ../../Classes/GameLogic/Enemy/Enemy.cpp \
                   ../../Classes/GameLogic/Enemy/Balloon.cpp \
                   ../../Classes/GameLogic/GameObject/Wind.cpp \
                   ../../Classes/Support/StringHelper.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

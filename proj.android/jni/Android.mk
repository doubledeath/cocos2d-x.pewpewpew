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
                   ../../Classes/GameLogic/Enemy/Balloon.cpp \
                   ../../Classes/GameLogic/Enemy/Enemy.cpp \
                   ../../Classes/GameLogic/Physics/CollidableNode.cpp \
                   ../../Classes/GameLogic/Physics/CollidableSprite.cpp \
                   ../../Classes/GameLogic/Physics/Damageable.cpp \
                   ../../Classes/GameLogic/Physics/Movable.cpp \
                   ../../Classes/GameLogic/Physics/MovableSprite.cpp \
                   ../../Classes/GameLogic/Physics/ParentCollidable.cpp \
                   ../../Classes/GameLogic/Physics/Physics.cpp \
                   ../../Classes/GameLogic/Physics/Projectile.cpp \
                   ../../Classes/GameLogic/Player/Cannon.cpp \
                   ../../Classes/GameLogic/Projectile/CannonBall.cpp \
                   ../../Classes/GameLogic/World/World.cpp \
                   ../../Classes/Scene/MainScene.cpp \
                   ../../Classes/Scene/SplashScene.cpp

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

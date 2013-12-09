LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# OSG SDK for Android 
OSG_SDK := $(LOCAL_PATH)/OpenSceneGraph-3.0.1-Android-GLESv1

LOCAL_MODULE            := libjniosg

LOCAL_C_INCLUDES        := $(OSG_SDK)/include
LOCAL_CFLAGS    		:= -Werror -fno-short-enums
LOCAL_CPPFLAGS  		:= -DOSG_LIBRARY_STATIC 
LOCAL_LDFLAGS   		:= -L$(OSG_SDK)/obj/armeabi-v7a -fno-short-enums

LOCAL_SRC_FILES 		:= \
TabBoxDraggerTransparent.cpp \
TabPlaneDraggerTransparent.cpp \
Translate2DDraggerTransparent.cpp \
TranslatePlaneDraggerTransparent.cpp \
JNIosgGUIEventHandler.cpp \
JNIosgViewer.cpp \
JNIosg.cpp \
JNIosgDB.cpp \
JNIosgUtil.cpp \
JNIUtils.cpp \
MultiViewNode.cpp \

LOCAL_LDLIBS    		:= -llog -lGLESv1_CM -ldl -lz

TARGET_LDLIBS := \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_osg.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_ive.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgvolume.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgtext.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgterrain.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgsim.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgshadow.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgparticle.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgmanipulator.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osgfx.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osganimation.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_serializers_osg.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgViewer.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgVolume.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgTerrain.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgText.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgShadow.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgSim.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgParticle.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgManipulator.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgGA.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgFX.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgDB.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgAnimation.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgUtil.a \
$(OSG_SDK)/obj/armeabi-v7a/libosg.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_tga.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_gif.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_png.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_tga.a \
$(OSG_SDK)/obj/armeabi-v7a/libosgdb_jpeg.a \
$(OSG_SDK)/obj/armeabi-v7a/libOpenThreads.a \
$(OSG_SDK)/obj/armeabi-v7a/3rdparty/libft2.a \
$(OSG_SDK)/obj/armeabi-v7a/3rdparty/libgif.a \
$(OSG_SDK)/obj/armeabi-v7a/3rdparty/libjpeg.a \
$(OSG_SDK)/obj/armeabi-v7a/3rdparty/libpng.a \


include $(BUILD_SHARED_LIBRARY)


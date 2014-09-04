/* DO NOT EDIT THIS FILE - it is machine generated */
#include "AppDelegate.h"
#include "cocos2d.h"

#if COCOS2D_VERSION >= 0x00030000
#include "base/CCEventType.h"
#else
#include "CCEventType.h"
#endif

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "C2DXShareSDKTypeDef.h"
#include "CCJSONConverter.h"

USING_NS_CC;
using namespace cn::sharesdk;

/* Header for class ShareSDKUtils */
#ifndef _Included_ShareSDKUtils
#define _Included_ShareSDKUtils
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     aaa_bbb_Main
 * Method:    onJavaCallback
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_cn_sharesdk_ShareSDKUtils_onJavaCallback
  (JNIEnv * env, jclass thiz, jstring resp);

void callBackComplete(int action, int platformId, Dictionary* res);

void callBackError(int action, int platformId, Dictionary* res);

void callBackCancel(int action, int platformId, Dictionary* res);

bool initShareSDK(const char* appKey, bool useAppTrusteeship);

bool getMethod(JniMethodInfo &mi, const char *methodName, const char *paramCode);

void releaseMethod(JniMethodInfo &mi);

bool stopSDK();

bool setPlatformDevInfo(int platformId, Dictionary *info);

bool doAuthorize(int platformId, C2DXAuthResultEvent callback);

bool removeAccount(int platformId);

bool isValid(int platformId);

bool showUser(int platformId, C2DXGetUserInfoResultEvent callback);

bool doShare(int platformId, Dictionary *content, C2DXShareResultEvent callback);

bool multiShare(Array *platTypes, Dictionary *content, C2DXShareResultEvent callback);

bool onekeyShare(int platformId, Dictionary *content, C2DXShareResultEvent callback);

void toastShow(const char* msg);

#ifdef __cplusplus
}
#endif
#endif

/*
 * aneBasic.h
 *
 *  Created on: 2014. 5. 15.
 *      Author: Naver
 */

#ifndef ANEBASIC_H_
#define ANEBASIC_H_

#include "FlashRuntimeExtensions.h"


/**
 * The initialization function provided by each extension must conform
 * to the following signature.
 *
 * @param extDataToSet Provided for the extension to store per-extension instance data.
 *            For example, if the extension creates
 *            globals per-instance, it can store a pointer to them here.
 *
 * @param ctxInitializerToSet Must be set to a pointer to a function
 *            of type FREContextInitializer. Will be invoked whenever
 *            the ActionScript code creates a new context for this extension.
 *
 * @param ctxFinalizerToSet Must be set to a pointer to a function
 *            of type FREContextFinalizer.
 */

//typedef void (*FREInitializer)(
//        void**                 extDataToSet       ,
//        FREContextInitializer* ctxInitializerToSet,
//        FREContextFinalizer*   ctxFinalizerToSet
//);


/**
 * FRE가 C를 기반으로 한 프로그램이어서 함수가 C++형태로 선언되면 FRElib에서 initializer와 finalizer를 찾지못합니다.
 * C++일 경우 extern을 통해 C에서 접근 가능하도록 함수가 선언되어야 합니다.
 */
#ifdef __cplusplus
extern "C"{
#endif


/**
 * 초기화 함수,
 *  FlashRuntimeExtensions.h에 정의된 FREInitializer 형태로 정의되어야 합니다.
 */
__declspec( dllexport ) void kinectUtilInit( void **extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer );



/**
 * Called if the extension is unloaded from the process. Extensions
 * are not guaranteed to be unloaded; the runtime process may exit without
 * doing so.
 */

//typedef void (*FREFinalizer)(
//        void* extData
//);

/**
 * 종료 함수.
 *  같은 형태로 FREFinalizer 형태로 정의
 */
__declspec( dllexport ) void kinectUtilFin( void* extData );


#ifdef __cplusplus
}
#endif


#endif /* ANEBASIC_H_ */

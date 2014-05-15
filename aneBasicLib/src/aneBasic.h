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
 * FRE�� C�� ������� �� ���α׷��̾ �Լ��� C++���·� ����Ǹ� FRElib���� initializer�� finalizer�� ã�����մϴ�.
 * C++�� ��� extern�� ���� C���� ���� �����ϵ��� �Լ��� ����Ǿ�� �մϴ�.
 */
#ifdef __cplusplus
extern "C"{
#endif


/**
 * �ʱ�ȭ �Լ�,
 *  FlashRuntimeExtensions.h�� ���ǵ� FREInitializer ���·� ���ǵǾ�� �մϴ�.
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
 * ���� �Լ�.
 *  ���� ���·� FREFinalizer ���·� ����
 */
__declspec( dllexport ) void kinectUtilFin( void* extData );


#ifdef __cplusplus
}
#endif


#endif /* ANEBASIC_H_ */

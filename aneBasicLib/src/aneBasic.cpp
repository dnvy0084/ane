/*
 * aneBasic.cpp
 *
 *  Created on: 2014. 5. 15.
 *      Author: Naver
 */

#include <stdlib.h>
#include <string.h>

#include "aneBasic.h"

FREObject isSupported( FREContext, void*, uint32_t, FREObject[] );
FREObject getHelloWorldString( FREContext, void*, uint32_t, FREObject[] );


/**
 * �ʱ�ȭ �Լ�
 * 	extData�� ctxType�� �ϳ��� library���� ���� �ٸ� ���� �Ҷ� ����� �� �ִ�( flash�� ���� ���޵Ǵ� ) ������ �Դϴ�.
 * 	���� ����� �ʿ� ������. �׳� �Լ� � �� ����� ����.
 * 	�ʱ�ȭ �� �Լ��̸�(key)�� �Լ� ������(value)�� ���
 */
void contextInitializer(
		void*                    extData          ,
		const uint8_t*           ctxType          ,
		FREContext               ctx              ,
		uint32_t*                numFunctionsToSet,
		const FRENamedFunction** functionsToSet 	)
{
	uint8_t* key[] =
	{
		"isSupported",
		"getHelloWorldString"
	};

	FREFunction values[] =
	{
		&isSupported,
		&getHelloWorldString
	};

	int len = sizeof( key ) / sizeof( uint8_t* );

	FRENamedFunction* functionVO = (FRENamedFunction*) malloc( sizeof( FRENamedFunction ) * len );

	for( int i = 0; i < len; ++i )
	{
		functionVO[i].name = key[i];
		functionVO[i].function = values[i];
		functionVO[i].functionData = NULL;
	}

	*functionsToSet = functionVO;
}


/**
 * bool���� return�ϴ� �Լ�
 * FRENewObjectFromType�� ���� Flash���� ����� �� �ִ� ��ü�� ����.
 */
FREObject isSupported( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	FRENewObjectFromBool( 1, &result );
	return result;
}


/**
 * String�� return
 *  FRENewObjectFromUTF8���� String length�κ��� null byte�� ���Ե� �� �ֵ��� +1�� ����� �Ѵٰ� ��. -_-;; +1�ؼ� ������ �ɰ���..
 */
FREObject getHelloWorldString( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	const char* str = "Hello World from C++";

	FRENewObjectFromUTF8( strlen( str ) + 1, (const uint8_t*) str, &result );
	return result;
}


/**
 * ���� �Լ�
 *  dll�� process���� ���� �ɶ� ȣ��ǳ� �׻� �ȴٰ� ���� �� ���ٰ� ��. ��å���ѵ�..
 */
void contextFinalizer( FREContext ctx )
{
	return;
}


/**
 * �Ʒ� �ΰ� �Լ��� �ܺο��� C����� ã�� �� �ֵ��� C�������� ����Ǿ�� �մϴ�.
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * �ʱ�ȭ�� ���� �Լ��� �����մϴ�.
 * dll�� ����Ǹ� ������ �ʱ�ȭ �Լ��� �����մϴ�.
 */
void kinectUtilInit( void **extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer )
{
	*ctxInitializer = &contextInitializer;
	*ctxFinalizer = &contextFinalizer;
}

void kinectUtilFin( void* extData )
{
	return;
}

#ifdef __cplusplus
}
#endif

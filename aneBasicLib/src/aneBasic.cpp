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
 * 초기화 함수
 * 	extData와 ctxType은 하나의 library에서 각기 다른 일을 할때 사용할 수 있는( flash로 부터 전달되는 ) 데이터 입니다.
 * 	굳이 사용할 필욘 없을듯. 그냥 함수 몇개 더 만들면 될일.
 * 	초기화 시 함수이름(key)과 함수 포인터(value)를 등록
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
 * bool값을 return하는 함수
 * FRENewObjectFromType을 통해 Flash에서 사용할 수 있는 객체를 생성.
 */
FREObject isSupported( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	FRENewObjectFromBool( 1, &result );
	return result;
}


/**
 * String을 return
 *  FRENewObjectFromUTF8에서 String length부분은 null byte가 포함될 수 있도록 +1을 해줘야 한다고 함. -_-;; +1해서 읽으면 될것을..
 */
FREObject getHelloWorldString( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	const char* str = "Hello World from C++";

	FRENewObjectFromUTF8( strlen( str ) + 1, (const uint8_t*) str, &result );
	return result;
}


/**
 * 종료 함수
 *  dll이 process에서 해제 될때 호출되나 항상 된다고 말할 순 없다고 함. 무책임한데..
 */
void contextFinalizer( FREContext ctx )
{
	return;
}


/**
 * 아래 두개 함수는 외부에서 C모듈이 찾을 수 있도록 C형식으로 선언되어야 합니다.
 */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * 초기화와 종료 함수를 설정합니다.
 * dll이 실행되면 설정된 초기화 함수를 실행합니다.
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

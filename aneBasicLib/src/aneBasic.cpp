/*
 * aneBasic.cpp
 *
 *  Created on: 2014. 5. 15.
 *      Author: kim.jinhoon
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "aneBasic.h"


FREObject isSupported( FREContext, void*, uint32_t, FREObject[] );
FREObject getHelloWorldString( FREContext, void*, uint32_t, FREObject[] );
FREObject add( FREContext, void*, uint32_t, FREObject[] );
FREObject concatUTF8( FREContext, void*, uint32_t, FREObject[] );
FREObject createObject( FREContext, void*, uint32_t, FREObject[] );
FREObject vectorPP( FREContext, void*, uint32_t, FREObject[] );
FREObject byteArrayPP( FREContext, void*, uint32_t, FREObject[] );
FREObject writeByteArray( FREContext, void*, uint32_t, FREObject[] );


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
	const char* key[] =
	{
		"isSupported",
		"getHelloWorldString",
		"add",
		"concatUTF8",
		"createObject",
		"vectorPP",
		"byteArrayPP",
		"writeByteArray"
	};

	FREFunction values[] =
	{
		&isSupported,
		&getHelloWorldString,
		&add,
		&concatUTF8,
		&createObject,
		&vectorPP,
		&byteArrayPP,
		&writeByteArray
	};

	*numFunctionsToSet = sizeof( key ) / sizeof( uint8_t* );

	FRENamedFunction* functionVO =
			(FRENamedFunction*) malloc( sizeof( FRENamedFunction ) * (*numFunctionsToSet) );

	for( unsigned i = 0; i < *numFunctionsToSet; ++i )
	{
		functionVO[i].name = (const uint8_t*) key[i];
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
 * arguments안의 모든 숫자를 더해 반환하는 메소드.
 *  argc 및 플래시에서 전달된 argv 사용방법
 */
FREObject add( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	int sum = 0, n;

	for( unsigned i = 0; i < argc; ++i )
	{
		FREGetObjectAsInt32( argv[i], &n );
		sum += n;
	}

	FRENewObjectFromInt32( sum, &result );
	return result;
}


/**
 * argv로 전달된 string을 모두 합쳐 반환 return arguments.join()
 */
FREObject concatUTF8( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	int returnStrLen = 0;
	uint32_t len;

	const uint8_t** str = (const uint8_t**) malloc( sizeof( const uint8_t* ) * argc );

	for( unsigned i = 0; i < argc; ++i )
	{
		FREGetObjectAsUTF8( argv[i], &len, &str[i] );
		returnStrLen += len;
	}

	char *returnStr = (char*) malloc( sizeof( char ) * returnStrLen );
	char *p = returnStr;

	for( unsigned i = 0; i < argc; ++i )
	{
		strcpy( p, (const char*)str[i] );

		p += strlen( (const char*)str[i] );
	}

	FRENewObjectFromUTF8( returnStrLen + 1, (const uint8_t*)returnStr, &result );

	free( returnStr );
	free( str );

	return result;
}


/**
 * Vector.<int> 형태의 vector(array)를 받아 각 원소에 +1 해서 반환.
 * Vector / Array의 제어에 관한 예제.
 */
FREObject vectorPP( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	int len, n;
	FREObject element, *vec = &argv[0];

	FREGetArrayLength( *vec, (uint32_t*)&len );

	for( int i = 0; i < len; ++i )
	{
		FREGetArrayElementAt( *vec, (uint32_t)i, &element );
		FREGetObjectAsInt32( element, &n );

		sqrt( n );
		cos( n );
		sin( n );

		n++;

		FRENewObjectFromInt32( n, &element );
		FRESetArrayElementAt( *vec, i, element );
	}

	return *vec;
}


/**
 * [ className, number of constructor arguments, ...rest arguments ]
 * 형태의 매개변수를 받아( argv ) FRENewObject를 통해 객체 생성 후 반환
 */
FREObject createObject( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREObject result;

	uint32_t len;
	const uint8_t* className;

	FREGetObjectAsUTF8( argv[0], &len, &className );

	int constructorArgc;
	FREGetObjectAsInt32( argv[1], &constructorArgc );

	FREObject *constructorArgv = constructorArgc == 0 ?
			NULL : (FREObject*)malloc( sizeof( FREObject ) * constructorArgc );

	for( int i = 2; i < 2 + constructorArgc; ++i )
	{
		constructorArgv[ i - 2 ] = argv[i];
	}

	FRENewObject( (const uint8_t*) className, 0, NULL, &result, NULL );

	return result;
}


/**
 * ByteArray를 받아 각 값에 +1해서 반환
 * FREByteArray 구조체를 이용해 매개변수의 ByteArray를 Acquire하는게 포인트
 * AcquireByteArray는 C pointer를 이용해 ByteArray가 사용중인 메모리 영역에 직접 접근 할 수 있도록 해줌.
 * read, write 둘다 가능.
 */
FREObject byteArrayPP( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREByteArray bytes;

	FREAcquireByteArray( argv[0], &bytes );

	int* p = (int*)bytes.bytes;

	for( unsigned i = 0; i < bytes.length / 4; ++i )
	{
		*p = *p + 1;
		p++;
	}

	FREReleaseByteArray( argv[0] );

	return NULL;
}


/**
 * 대용량 데이터를 제어하는 경우 FREObject를 이용해 객체 생성은 성능 저하가 있음
 * write가 가능한 일정 길이의 byteArray를 flash로 부터 넘겨받아 메모리에 직접 쓰면 C의 성능을 최대한 살릴 수 있음.
 *
 */
FREObject writeByteArray( FREContext context, void* functionData, uint32_t argc, FREObject argv[] )
{
	FREByteArray read, write;

	FREAcquireByteArray( argv[0], &read );
	FREAcquireByteArray( argv[1], &write );

	short *ps = (short*) read.bytes;
	float *pf = (float*) write.bytes;

	for( unsigned i = 0; i < read.length / 2; i++, pf++ )
	{
		*pf = (float)*( ps + i );
	}

	FREReleaseByteArray( argv[1] );
	FREReleaseByteArray( argv[0] );

	return NULL;
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
 * 외부에서 C모듈이 찾을 수 있도록 C형식으로 선언되어야 합니다.
 */
#ifdef __cplusplus
extern "C"{
#endif


/**
 * 초기화와 종료 함수를 설정합니다.
 * dll이 실행되면 설정된 초기화 함수를 실행합니다.
 */
void initializer( void **extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer )
{
	*ctxInitializer = &contextInitializer;
	*ctxFinalizer = &contextFinalizer;
}

void finalizer( void* extData )
{
	return;
}


#ifdef __cplusplus
}
#endif

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
 * arguments���� ��� ���ڸ� ���� ��ȯ�ϴ� �޼ҵ�.
 *  argc �� �÷��ÿ��� ���޵� argv �����
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
 * argv�� ���޵� string�� ��� ���� ��ȯ return arguments.join()
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
 * Vector.<int> ������ vector(array)�� �޾� �� ���ҿ� +1 �ؼ� ��ȯ.
 * Vector / Array�� ��� ���� ����.
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
 * ������ �Ű������� �޾�( argv ) FRENewObject�� ���� ��ü ���� �� ��ȯ
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
 * ByteArray�� �޾� �� ���� +1�ؼ� ��ȯ
 * FREByteArray ����ü�� �̿��� �Ű������� ByteArray�� Acquire�ϴ°� ����Ʈ
 * AcquireByteArray�� C pointer�� �̿��� ByteArray�� ������� �޸� ������ ���� ���� �� �� �ֵ��� ����.
 * read, write �Ѵ� ����.
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
 * ��뷮 �����͸� �����ϴ� ��� FREObject�� �̿��� ��ü ������ ���� ���ϰ� ����
 * write�� ������ ���� ������ byteArray�� flash�� ���� �Ѱܹ޾� �޸𸮿� ���� ���� C�� ������ �ִ��� �츱 �� ����.
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
 * ���� �Լ�
 *  dll�� process���� ���� �ɶ� ȣ��ǳ� �׻� �ȴٰ� ���� �� ���ٰ� ��. ��å���ѵ�..
 */
void contextFinalizer( FREContext ctx )
{
	return;
}




/**
 * �ܺο��� C����� ã�� �� �ֵ��� C�������� ����Ǿ�� �մϴ�.
 */
#ifdef __cplusplus
extern "C"{
#endif


/**
 * �ʱ�ȭ�� ���� �Լ��� �����մϴ�.
 * dll�� ����Ǹ� ������ �ʱ�ȭ �Լ��� �����մϴ�.
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

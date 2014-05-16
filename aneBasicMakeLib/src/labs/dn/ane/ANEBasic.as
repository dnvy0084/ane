package labs.dn.ane
{
	import flash.events.EventDispatcher;
	import flash.events.IEventDispatcher;
	import flash.external.ExtensionContext;
	import flash.utils.ByteArray;
	
	public class ANEBasic extends EventDispatcher
	{
		/**
		 *확장 native lib의 gateway 객체 
		 */		
		private var extContext:ExtensionContext;
		
		public function ANEBasic()
		{
			super();
			
			this.extContext = 
				ExtensionContext.createExtensionContext( "labs.dn.ane", null );
		}
		
		/**
		 *dipose. extContext객체 제거 
		 * 
		 */		
		public function dispose(): void
		{
			this.extContext.dispose();
		}
		
		
		
		/**
		 * String 반환 예제
		 * @return 
		 * 
		 */		
		public function getHelloWorldString(): String
		{
			return String( this.extContext.call( "getHelloWorldString" ) );
		}
		
		
		/**
		 *integers 배열의 합 반환 
		 * @param integers
		 * @return 
		 * 
		 */		
		public function add( ...integers ): int
		{
			return int( this.extContext.call.apply( null, [ "add" ].concat( integers ) ) );
		}
		
		
		/**
		 *strings배열의 문자열들을 연결해서 반환 
		 * @param strings
		 * @return 
		 * 
		 */		
		public function concatUTF8( ...strings ): String
		{
			return String( 
				this.extContext.call.apply( null, [ "concatUTF8" ].concat( strings ) ) );
		}
		
		
		/**
		 * FRENewObject를 이용한 객체 생성 예제. 
		 * c에서 생성된 FREObject를 넘겨받을 경우 flash에서 생성했을때보다 시간이 더 걸리는 경우가 있으니
		 * 사용을 자제하는게 좋을듯.  
		 * @param className
		 * @param numConstructorArguments
		 * @param constructorArguments
		 * @return 
		 * 
		 */		
		public function createObject( className: String, numConstructorArguments: int, ...constructorArguments ): Object
		{
			return this.extContext.call.apply( 
				null, [ "createObject", className, numConstructorArguments ].concat( constructorArguments ) );
		}
		
		
		/**
		 * vector의 각 element에 + 1 후 반환
		 * Vector 및 Array의 element 제어 예제 
		 * @param vec
		 * @return 
		 * 
		 */		
		public function vectorPP( vec: Vector.<int> ): Vector.<int>
		{
			return this.extContext.call( "vectorPP", vec ) as Vector.<int>;
		}
		
		
		/**
		 * bytearray를 읽어들여 + 1 후 반환 
		 * @param bytesArrayWithInt
		 * @return 
		 * 
		 */		
		public function byteArrayPP( bytesArrayWithInt: ByteArray ): ByteArray
		{
			return this.extContext.call( "byteArrayPP", bytesArrayWithInt ) as ByteArray;
		}
		
		
		/**
		 * writebyteArray에 readByteArray의 short 값을 float으로 바꿔 기록. 
		 * multi thread라 c쪽에서 event dispatch가 필요할 듯.  
		 * @param readBytesWithShort
		 * @param writeBytesWithInt
		 * 
		 */		
		public function writeByteArray( readBytesWithShort: ByteArray, writeBytesWithInt: ByteArray ): void
		{
			this.extContext.call( "writeByteArray", readBytesWithShort, writeBytesWithInt );
		}
		
		/**
		 * bool 반환 예제 
		 * @return 
		 * 
		 */		
		public function get isSupported(): Boolean
		{
			return this.extContext.call( "isSupported" );
		}
		
	}//c
}//p
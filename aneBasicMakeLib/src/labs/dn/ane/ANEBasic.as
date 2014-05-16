package labs.dn.ane
{
	import flash.events.EventDispatcher;
	import flash.events.IEventDispatcher;
	import flash.external.ExtensionContext;
	
	public class ANEBasic extends EventDispatcher
	{
		/**
		 *확장 native lib의 gateway 객체 
		 */		
		private var extContext:ExtensionContext;
		
		public function ANEBasic()
		{
			super();
			
			this.extContext = ExtensionContext.createExtensionContext( "labs.dn.ane", null );
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
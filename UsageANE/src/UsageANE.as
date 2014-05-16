package
{
	import flash.display.Sprite;
	
	import labs.dn.ane.ANEBasic;
	
	public class UsageANE extends Sprite
	{
		private var aneBasic:ANEBasic;
		
		public function UsageANE()
		{
			this.aneBasic = new ANEBasic();
			
			trace( "isSupported:", this.aneBasic.isSupported );
			trace( "getHelloWorldString:", this.aneBasic.getHelloWorldString() ); 
		}
		
	}//c
}//p
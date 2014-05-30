package
{
	import flash.display.Bitmap;
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.utils.ByteArray;
	import flash.utils.Endian;
	import flash.utils.getQualifiedClassName;
	import flash.utils.getTimer;
	
	import labs.dn.ane.ANEBasic;
	
	import mx.core.BitmapAsset;
	
	[SWF(width="1024", height="768", frameRate="60")]
	public class UsageANE extends Sprite
	{
		[Embed(source="./img/wallpaper.jpg", mimeType="image/jpeg")]
		private var asset: Class;
		
		private var aneBasic:ANEBasic;
		
		public function UsageANE()
		{
			this.stage.align = StageAlign.TOP_LEFT;
			this.stage.scaleMode = StageScaleMode.NO_SCALE;
			
			this.aneBasic = new ANEBasic();
			
			trace( "isSupported:", this.aneBasic.isSupported );
			
			trace( "getHelloWorldString:", this.aneBasic.getHelloWorldString() );
			
			trace( "add:", this.aneBasic.add( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) );
			
			trace( "concatUTF8:", this.aneBasic.concatUTF8( "A_", "B_", "C_D_E", "_", "F" ) );
			
			trace( "vectorPP:", this.aneBasic.vectorPP( Vector.<int>( [ 0,1,2,3,4,5 ] ) ) );
			
			this.vectorPPTest();
			
			var vec: Vector.<int> = this.aneBasic.createObject( "Vector.<int>", 2, true ) as Vector.<int>;
			
			trace( 
				"createObject:", 
				getQualifiedClassName( vec ), vec.length 
			);
			
			this.byteArrayPPtest();
			this.memcopyWithByteArrayTest();
			this.manipulateImage();
			//this.manipulateInAir(); //같은 이미지에 대해 13배 정도 성능 차이가 있음. 
		}
		
		private function manipulateInAir():void
		{
			var img: BitmapAsset = new asset() as BitmapAsset;
			var bytes: ByteArray = img.bitmapData.getPixels( img.bitmapData.rect );
			
			bytes.position = 0;
			var c0: int;
			var c1: int, a: int, r: int, g: int, b: int;
			
			var n: int = getTimer();
			
			for( ; bytes.bytesAvailable >= 4; )
			{
				c0 = bytes.readInt();
				
				a = c0 & 0xff000000;
				r = c0 >> 16 & 0xff;
				g = c0 >> 8 & 0xff;
				b = c0 & 0xff;
				
				c1 = r * 0.2 + g * 0.7 + b * 0.1;
				bytes.position -= 4;
				bytes.writeInt( a | (c1 << 16) | (c1 << 8) | c1 );
			}
			
			
			bytes.position = 0;
			img.bitmapData.setPixels( img.bitmapData.rect, bytes );
			
			trace( "maupilateInAir:", getTimer() - n );
			
			this.addChild( new Bitmap( img.bitmapData ) );
			
		}
		
		private function manipulateImage():void
		{
			var img: BitmapAsset = new asset() as BitmapAsset;
			
			var bitmap:Bitmap = new Bitmap( img.bitmapData.clone() );
			this.addChild( bitmap );
			
			var n: int = getTimer();
			this.aneBasic.manipulateBitmap( img.bitmapData );
			trace( "maipulateImage:", getTimer() - n );
			
			var bitmap2:Bitmap = new Bitmap( img.bitmapData );
			bitmap2.x = this.stage.stageWidth >> 1;
			this.addChild( bitmap2 );
		}		
		
		/**
		 * Native Code에서 FREObject같은 플래시 객체를 여러개 만들 경우 심각한 성능 저하가 있음. 
		 * 플래시에서 생성하는것보다 더 느린 경우도 있어 대규모 데이터를 주고 받기 위해선 byteArray를 이용해 Native Code에서 
		 * memory를 직접 읽고 쓰는 식으로  데이터를 전달 받는게 Native Code 성능을 살리는 방법임. 
		 * 
		 */		
		private function memcopyWithByteArrayTest():void
		{
			var read:ByteArray = new ByteArray(); //C에서 읽을 데이터
			var write:ByteArray = new ByteArray(); //C에서 읽어 변형한 데이터를 기록하는 공간으로 사용
			
			read.endian = write.endian = Endian.LITTLE_ENDIAN; //기본 Endian이 BigEndian으로 되어 있어 native에서 읽고 쓸 수 있도록 little endian방식으로 기록
			// 자세히는 모르나 플랫폼 마다 endian이 다르다면 - cpu에 따라 다를 수 있는듯 - native쪽에서 endian을 반환해주는 메소드가 필요할듯. 예제에서는 그냥 고~ 
			
			for( var i: int = 0; i < 32768; i++ )
				read.writeShort( i );
			
			write.length = read.length << 1; //쓸 타입이 float 32비트 형이기 때문에 short형 16비트 길이보다 두배 긴 길이가 필요. x 2 
			
			var n: int = getTimer();
			
			this.aneBasic.writeByteArray( read, write );
			
			var s: String = "";
			
			write.position = Math.max( 0, write.length - 4 * 10 );
			
			for( ; write.bytesAvailable; )
			{
				s += write.readFloat() + ", ";
			}
			
			trace( s, getTimer() - n );
		}
		
		private function byteArrayPPtest( performanceTest: Boolean = false ):void
		{
			var bytes:ByteArray = this.getByteArray( 10 );
			
			this.aneBasic.byteArrayPP( bytes );
			this.printBytes( bytes, "ByteArray read and write Test" );
			
			if( !performanceTest ) return;
			
			bytes = this.getByteArray( 10000 );
			var n: int = getTimer();
			trace( "10,000", getTimer() - n );
			
			bytes = this.getByteArray( 100000 );
			n = getTimer();
			trace( "100,000", getTimer() - n );
			
			bytes = this.getByteArray( 1000000 );
			n = getTimer();
			trace( "1,000,000", getTimer() - n );
			
			bytes = this.getByteArray( 10000000 );
			n = getTimer();
			trace( "10,000,000", getTimer() - n );
			
			this.printDelay( n );
		}
		
		private function printDelay(n:int):void
		{
			trace( getTimer() - n );
		}
		
		private function getByteArray(len:int): ByteArray
		{
			var bytes:ByteArray = new ByteArray();
			bytes.endian = Endian.LITTLE_ENDIAN;
			
			var n: int = len;
			
			for( ; n--; )
			{
				bytes.writeInt( len - n ); 
			}
			
			return bytes;
		}
		
		private function printBytes( bytes: ByteArray, ...rest ):void
		{
			bytes.position = 0;
			
			var s: String = "";
			
			for( ; bytes.bytesAvailable; )
			{
				s += bytes.readInt() + ", ";
			}
			
			trace.apply( null, [s].concat( rest ) );
		}
		
		private function vectorPPTest( performanceTest: Boolean = false ): void
		{
			if( !performanceTest ) return;
			
			var vec: Vector.<int> = this.getVector(100);
			var n: int = getTimer();
			
			trace( "vectorPP( 100 ):", this.aneBasic.vectorPP( vec ).length, getTimer() - n );
			
			vec = this.getVector( 10000 );
			n = getTimer();
			trace( "vectorPP( 10,000 ):", this.aneBasic.vectorPP( vec ).length, getTimer() - n );
			
			vec = this.getVector( 100000 );
			n = getTimer();
			trace( "vectorPP( 100,000 ):", this.aneBasic.vectorPP( vec ).length, getTimer() - n );
			
			vec = this.getVector( 1000000 );
			n = getTimer();
			trace( "vectorPP( 1,000,000 ):", this.aneBasic.vectorPP( vec ).length, getTimer() - n );
			
			vec = this.getVector( 10000000 );
			n = getTimer();
			trace( "vectorPP( 10,000,000 ):", this.aneBasic.vectorPP( vec ).length, getTimer() - n );
			
			n = getTimer();
			
			for( var i: int = 0; i < 10000000; i++ )
			{
				Math.sqrt( i );
				Math.cos( i );
				Math.sin( i );
			}
			
			trace( getTimer() - n );
		}
		
		private function getVector( length: int ):Vector.<int>
		{
			var vector:Vector.<int> = new Vector.<int>( length, true );
			
			for( var i: int = 0; i < length; i++ )
			{
				vector[i] = i;
			}
			
			return vector;
		}
		
	}//c
}//p
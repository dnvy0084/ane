Air Native Extension
===
adobe air의 ane 제작 및 사용법에 관한 study용 project입니다. 

1.adobe air와 windows용 shared library( dll ) 간의 통신 예제
-
IDE: eclipse indigo(3.7.2) with CDT, 
Compiler: minGW gcc

project 설명

aneBasicLib: dll을 만들기 위한 C++ shared library project

aneBasicMakeLib: ane파일을 만들기 위한 flex library project - 여기서 adt를 이용해 ane로 compile

UsageANE: 만들어진 ane를 import하고 사용하는 예제 프로젝트


- ane 파일 만드는 방법

1. flex sdk 폴더 내 bin 폴더 adt.bat를 이용해 compile 합니다.(윈도우 환경변수에 bin폴더 경로를 잡아주면 편해요.)
2. command line prompt를 통해 adt -package -target ane {ouput ane file name} {descriptor xml file name} -swc {gateway swc file name} -platform Windows-x86 library.swf {dll file name} 명령으로 ane파일을 compile할 수 있습니다. 
3. aneBasicMakeLib 프로젝트 ane폴더 참고. library.swf 파일은 압축 프로그램 (7zip같은..)으로 swc파일을 열어서 가져올 수 있습니다. 



flash air에서는 ane( air native extension )를 통해 시스템을 제어하거나 접근할 수 없는 장치에 접근 할 수 있습니다.

native라는 말처럼 C/C++( 또는 ObjectiveC나 Java )로 만들어진 library를 ane파일로 컴파일하여 flash air에서 사용할 수 있는데, 당연하겠지만 flash 보다 빠릅니다. 겁나...

그러기 위해서 native library를 만들거나 기존에 있던 library에 flash player에서 접근하여 data를 주고 받을 수 있도록 wrapping이 필요하며, wrapping된 native library를 adt( adobe air developer tool )룰 이용해 ane로 compile 할 수 있습니다.

window os를 기준으로 dll( dynamic linked library )을 만들고 enternalContext를 이용해 dll method를 호출하는 swc 제작, adt로 dll과 swc를 최종 ane로 compile 하는 과정까지 설명 드리겠습니다.



0. 환결 설정하기

IDE는 eclipse에 cdt를 이용하였으며, flash builder를 eclipse에 설치하기 위해서는 eclipse indigo( 3.7 ) cdt4 버전이 적당합니다. cdt는 eclipse의 plugin중 하나인데, eclipse에서 c/c++ 개발툴입니다. 다만 cdt에는 compiler가 없기때문에 mingw나 cygwin같은 gcc, g++ compiler 환경을 갖추어야 합니다. 







c/c++ project를 만들고 컴파일하기 위해서 eclipse + cdt

eclipse



1. dll 파일 만들기


2. dll 함수 호출용 as adapter 만들기

3. adt를 이용해 ane파일로 컴파일 하기

4. flash builder에서 ane 설정 및 사용하기

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

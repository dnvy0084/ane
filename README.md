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


ane 파일 만드는 방법

- flex sdk 폴더 내 bin 폴더 adt.bat를 이용해 compile할 수 있다. 
-

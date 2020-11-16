#include "JY901.h"


void StartIIC()
{
	ucDevAddr = 0x50;
	
}
void StartIIC(unsigned char ucAddr)
{
	ucDevAddr = ucAddr;
	
}
void CopeSerialData(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) 
	{
		ucRxCnt=0;
		return;
	}
	
	}
}
void readRegisters(unsigned char deviceAddr,unsigned char addressToRead, unsigned char bytesToRead, char * dest)
{
  
}
void writeRegister(unsigned char deviceAddr,unsigned char addressToWrite,unsigned char bytesToRead, char *dataToWrite)
{
 
}


void WriteWord(unsigned char ucAddr,short sData)
{	
	writeRegister(ucDevAddr, ucAddr, 2, (char *)&sData);
}
void ReadData(unsigned char ucAddr,unsigned char ucLength,char chrData[])
{
	readRegisters(ucDevAddr, ucAddr, ucLength, chrData);
}

void GetTime()
{
	readRegisters(ucDevAddr, 0x30, 8, (char*)&sTime);	
}
void GetAcc()
{
	readRegisters(ucDevAddr, AX, 6, (char *)&sAcc);
}
void GetGyro()
{
	readRegisters(ucDevAddr, GX, 6, (char *)&sGyro);
}

void GetAngle()
{
	readRegisters(ucDevAddr, Roll, 6, (char *)&sAngle);
}
void GetMag()
{
	readRegisters(ucDevAddr, HX, 6, (char *)&sMag);
}
void CJY901::GetPress()
{
	readRegisters(ucDevAddr, PressureL, 8, (char *)&sPress);
}
void CJY901::GetDStatus()
{
	readRegisters(ucDevAddr, D0Status, 8, (char *)&sDStatus);
}
void CJY901::GetLonLat()
{
	readRegisters(ucDevAddr, LonL, 8, (char *)&sLonLat);
}
void CJY901::GetGPSV()
{
	readRegisters(ucDevAddr, GPSHeight, 8, (char *)&sGPSV);
}

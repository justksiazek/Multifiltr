#include <windows.h>
#include "cdll.h"

BYTE matryca[12] = { 1,2,1,2,4,2,1,2,1 };

BYTE szaryC(BYTE* dane)
{
	BYTE szary = (dane[0]+dane[1]+dane[2])/3;
	return szary;
}

void sepiaC(BYTE* dane, BYTE* wynik)
{
	wynik[0] = dane[0];			//B

	if (dane[1] + 30 > 255)		//G
		wynik[1] = 255;
	else
		wynik[1] = dane[1] + 30;

	if (dane[2] + 60 > 255)		//R
		wynik[2] = 255;
	else
		wynik[2] = dane[2] + 60;
}

void kontrC(BYTE* dane, BYTE* wynik)
{
	//uzyto float, gdy¿ obliczenia na int lub BYTE przek³amuj¹ kolory
	for (int i = 0; i < 3; i++)
	{
		float nowy = (2 * (dane[i] - 122)) + 122;
		if (nowy < 0)
			wynik[i] = 0;
		else if (nowy > 255)
			wynik[i] = 255;
		else
			wynik[i] = nowy;
	}
}

void solarC(BYTE* dane, BYTE* wynik)
{
	for (int i = 0; i < 3; i++)
	{
		if (dane[i] > 127)
			wynik[i] = 255 - dane[i];
		else
			wynik[i] = dane[i];
	}
}

void gaussC(BYTE dane[12], BYTE* wynik)
{
	int suma = 0;
	for (int j = 0; j < 9; j++)
	{
		suma += dane[j] * matryca[j];
	}
	*wynik = suma / 16;
}
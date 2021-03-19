#pragma once
#include <string>

//definicje typ�w fukncji zdefiniowanych w DLL w asemblerze
typedef BYTE(_fastcall* szaryASM)(BYTE*);
typedef void(_fastcall* sepiaASM)(BYTE*, BYTE*);
typedef void(_fastcall* kontrASM)(BYTE*, BYTE*);
typedef void(_fastcall* solarASM)(BYTE*, BYTE*);
typedef void(_fastcall* gaussASM)(BYTE*, int, BYTE*);

//uproszczona realizaja std::mutex - w kompilacjach /clr mutex nie dzia�a
class blokada
{
    //definicja obiektu sekcji krytycznej, do kt�rej program b�dzie wchodzi� podczas blokowania
    CRITICAL_SECTION sekcjaKrytyczna;
public:
    blokada()
    {
        //ininicja sekcji krytycznej
        InitializeCriticalSection(&sekcjaKrytyczna);
    }
    ~blokada()
    {
        //usuni�cie sekcji krytycznej
        DeleteCriticalSection(&sekcjaKrytyczna);
    }
    //implementacja std::mutex m.lock()
    void lock()
    {
        //wej�cie do sekcji krytycznej
        EnterCriticalSection(&sekcjaKrytyczna);
    }
    //implementacja std::mutex m.unlock()
    void unlock()
    {
        //wyj�cie z sekcji krytycznej
        LeaveCriticalSection(&sekcjaKrytyczna);
    }
};

//zwraca liczb� procesor�w
int procesory();

//return 0 - zakonczono poprawnie
//return -1 - b��d odczytu
//return -2 - b��d zapisu
double przetworz(std::string plik, char kod, int wywolania, int watki);

void uruchomWatki(szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA,
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss,
    BYTE* matryca, char kod, int rozmiarBitmapy, int szerokosc, int bufor, int wywolania, int watki, int wysokosc);

void modyfikujObraz(
    szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA,
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss,
    BYTE* matryca, char kod, int rozmiarBitmapy, int szerokosc, int bufor, int wysokosc);

void nalozFiltryC(
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss, 
    BYTE* matryca, int wiersz, int x, int szerokosc, int y, int wysokosc);

void nalozFiltryA(
    szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA,
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss,
    BYTE* matryca, int wiersz, int x, int szerokosc, int y, int wysokosc);

//zapisuje pliki wynikowe
    //return 0 - zako�czkono poprawnie
    //return -2 - b��d zapisu
int zapiszPlik(
    BITMAPFILEHEADER& naglowekBMP, BITMAPINFOHEADER& informacjeBMP, int rozmiarObrazu, int rozmiarBitmapy, 
    BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss);
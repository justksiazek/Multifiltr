#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include "..\libC\cdll.h" //dll in cpp
#include "multifiltr.h"

int iterator = 0;
auto zero = std::chrono::steady_clock::now();
std::chrono::duration<double> czasTrwania = zero - zero;
blokada blok;

int procesory()
{
    //zwraca ilo�� procesor�w logicznych
    return std::thread::hardware_concurrency();
}

double przetworz(std::string plik, char kod, int wywolania, int watki)
{
    /* ----- PO��CZENIE Z DLL W ASM ----- */
    HINSTANCE dllHandle = NULL;
    dllHandle = LoadLibrary(L"libASM.dll"); //dll in asm

    szaryASM szaryA = (szaryASM)GetProcAddress(dllHandle, "szaryASM");
    sepiaASM sepiaA = (sepiaASM)GetProcAddress(dllHandle, "sepiaASM");
    kontrASM kontrA = (kontrASM)GetProcAddress(dllHandle, "kontrASM");
    solarASM solarA = (solarASM)GetProcAddress(dllHandle, "solarASM");
    gaussASM gaussA = (gaussASM)GetProcAddress(dllHandle, "gaussASM");

    /* ----- PRZYGOTOWANIE OBRAZU ----- */
    const char* cplik = plik.c_str();

    //otworzenie odczytu bitmapy
    FILE* odczyt;
    if (!(odczyt = fopen(cplik, "rb")))
   // if (!(odczyt = fopen("img\\x.bmp", "rb")))
    {
        printf("blad odczytu");
        return -1;
    }

    //struktury przechowuj�ce informacje z nagl�wk�w odczytu BMP
    BITMAPFILEHEADER naglowekBMP;
    BITMAPINFOHEADER informacjeBMP;

    //odczytanie nag��wk�w z odczytu BMP
    fread(&naglowekBMP, sizeof(naglowekBMP), 1, odczyt); //do nagBMP, rozmiar struktury, 1 element, z odczytu 
    fread(&informacjeBMP, sizeof(informacjeBMP), 1, odczyt); //do infoBMP, rozmiar struktury, 1 element, z odczytu 

    //obliczenie wielko�ci bitmapy w bajtach
    int szerokosc = informacjeBMP.biWidth * 3; // bo ka�dy piksel ma 3 bajty
    int wysokosc = informacjeBMP.biHeight;
    int rozmiarObrazu = szerokosc * wysokosc;

    //obliczenie bufora - dope�nienie wiersza tak, aby liczba bajt�w by�a wielokrotno�ci� 4
    int bufor;
    if (szerokosc % 4) // je�eli liczba bajt�w wiersza jest wielokrotno�ci 4 to bufor jest r�wny 0
        bufor = 4 - szerokosc % 4;
    else //w przeciwnym przypadku rozmiar bufora to ilo�� bit�w brakuj�ca do 4 po obliczeniu reszty z dzielenia ilosci bajt�w w wierszu przez 4
        bufor = 0;

    //obliczenie rozmiaru bitmapy (obraz + bufor)
    int rozmiarBitmapy = wysokosc * (szerokosc + bufor);

    //alokacja pami�ci do przechowywania bitmapy
    BYTE* obraz = (BYTE*)malloc(rozmiarBitmapy);

    //odczytanie obrazu z odczytu BMP
    fread(obraz, rozmiarBitmapy, 1, odczyt);

    //zamkni�cie odczytu bitmapy
    fclose(odczyt);

    /* KOPIE OBRAZU DO EDYCJI */

    //alokacja pami�ci do przechowywania bitmapy
    BYTE* szary = (BYTE*)malloc(rozmiarBitmapy);
    BYTE* sepia = (BYTE*)malloc(rozmiarBitmapy);
    BYTE* kontr = (BYTE*)malloc(rozmiarBitmapy);
    BYTE* solar = (BYTE*)malloc(rozmiarBitmapy);
    BYTE* gauss = (BYTE*)malloc(rozmiarBitmapy);
    //definicja matrycy do filtru gaussa
    BYTE matryca[12] = { 1,2,1,2,4,2,1,2,1 };




        modyfikujObraz(szaryA, sepiaA, kontrA, solarA, gaussA,
            obraz, szary, sepia, kontr, solar, gauss, matryca, kod, rozmiarBitmapy, szerokosc, bufor, wysokosc);
   
    //modyfikacje obrazu
    /*
    uruchomWatki(szaryA, sepiaA, kontrA, solarA, gaussA,
        obraz, szary, sepia, kontr, solar, gauss,
        matryca, kod, rozmiarBitmapy, szerokosc, bufor, wywolania, watki, wysokosc);
    */

    
    std::cout << "czas wykonywania: " << czasTrwania.count() << "s" << std::endl;

    int stan = zapiszPlik(naglowekBMP, informacjeBMP, rozmiarObrazu, rozmiarBitmapy, szary, sepia, kontr, solar, gauss);
    if (stan != 0)
        return stan;

    free(obraz);
    //free(szary);
    //free(sepia);
   // free(kontr);
    //free(solar);
   // free(gauss);

    return czasTrwania.count();
}

void uruchomWatki(
    szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA,
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss,
    BYTE* matryca, char kod, int rozmiarBitmapy, int szerokosc, int bufor, int wywolania, int watki, int wysokosc)
{
    //std::cout << "w" << i;
    std::vector<std::thread> zasoby;
    for (int i = 0; i < watki; i++)
    {
        //wype�nienie wektora w�tkami odnosz�cymi si� do funkcji modyfikuj�ce obraz
        zasoby.push_back(std::thread(modyfikujObraz, std::ref(szaryA), std::ref(sepiaA), std::ref(kontrA), std::ref(solarA), std::ref(gaussA),
            obraz, szary, sepia, kontr, solar, gauss, matryca, kod, rozmiarBitmapy, szerokosc, bufor, wysokosc));
    }
    for (int i = 0; i < watki; i++)
    {
        //uruchomienie w�tk�w
        zasoby[i].join();
    }
    iterator = 0;
    // std::cout << "bye";
}

void modyfikujObraz(
    szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA,
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss,
    BYTE* matryca, char kod, int rozmiarBitmapy, int szerokosc, int bufor, int wysokosc)
{
    for (int i = 0; i < 10; i++)
    {
        //w�tek wchodzi do sekcji krytycznej, zabronione jest wprowadzanie zmian przez inne w�tki
       // blok.lock();
        while (iterator < rozmiarBitmapy)
        {
            //obliczenie numeru wiersza
            int y = iterator / szerokosc;
            //obliczenie adresu wiersza
            int wiersz = szerokosc * y;
            //obliczenie pozycji w wierszu
            int x = iterator - wiersz;
            //sprawdzenie kolejna iteracja wpadnie do bufora
            if (x + 1 == szerokosc)
            {
                //przej�cie do pierwszejgo bajtu kolejnej linii
                iterator = iterator + bufor + 1;
            }
            //kolejna iteracja wypadnie na piksel
            else
            {
                //przej�cia iteratorem do kolejnego piksela
                iterator = iterator + 3;
            }
            //w�tek wychodzi z sekcji krytycznej
           // blok.unlock();
            //obliczenie pozycji w pliku
            if (kod == 'c')
                nalozFiltryC(obraz, szary, sepia, kontr, solar, gauss, matryca, wiersz, x, szerokosc, y, wysokosc);
            else
                nalozFiltryA(szaryA, sepiaA, kontrA, solarA, gaussA, obraz, szary, sepia, kontr, solar, gauss, matryca, wiersz, x, szerokosc, y, wysokosc);
                
        }
        iterator = 0;
    }
}

void nalozFiltryC(
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss, 
    BYTE* matryca, int wiersz, int x, int szerokosc, int y, int wysokosc)
{
    //czas wykonywania programu
    auto pocz = std::chrono::steady_clock::now(); //pomiar czasu

    //SKALA ODCIENI SZARO�CI
    szary[wiersz + x + 2] = szary[wiersz + x + 1] = szary[wiersz + x] = szaryC(&obraz[wiersz + x]);

    //SEPIA
    sepiaC(&szary[wiersz + x], &sepia[wiersz + x]);

    //SOLARYZACJA
    solarC(&obraz[wiersz + x], &solar[wiersz + x]);

    //KONTRAST
    kontrC(&obraz[wiersz + x], &kontr[wiersz + x]);

    //GAUSS
    if ((y > 0 && y < (wysokosc - 1)) && (x > 2 && x < (szerokosc - 3))) 
    {

        gaussC(&obraz[wiersz + x], szerokosc, &gauss[wiersz + x]);
    }        
    
    auto koniec = std::chrono::steady_clock::now(); //koniec pomiaru
    czasTrwania += koniec - pocz;
}

void nalozFiltryA(
    szaryASM& szaryA, sepiaASM& sepiaA, kontrASM& kontrA, solarASM& solarA, gaussASM& gaussA, 
    BYTE* obraz, BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss, 
    BYTE* matryca, int wiersz, int x, int szerokosc, int y, int wysokosc)
{
    //czas wykonywania programu
    auto pocz = std::chrono::steady_clock::now(); //pomiar czasu

    //SKALA ODCIENI SZARO�CI
    szary[wiersz + x + 2] = szary[wiersz + x + 1] = szary[wiersz + x] = szaryA(&obraz[wiersz + x]);//szaryA(&obraz[wiersz + x]);
    
    //SEPIA
    //u�ycie szaro�ci obliczonej wcze�niej - przypisanie szaro�ci do tablicy sepii
    sepiaA(&szary[wiersz + x], &sepia[wiersz + x]);

    solarA(&obraz[wiersz + x], &solar[wiersz + x]);

    kontrA(&obraz[wiersz + x], &kontr[wiersz + x]);

    //GAUSS
    if ((y > 0 && y < (wysokosc - 1)) && (x > 2 && x < (szerokosc - 3)))
        gaussA(&obraz[wiersz + x], szerokosc, &gauss[wiersz + x]);
        

    auto koniec = std::chrono::steady_clock::now(); //koniec pomiaru
    czasTrwania += koniec - pocz;
}

int zapiszPlik(BITMAPFILEHEADER& naglowekBMP, BITMAPINFOHEADER& informacjeBMP, int rozmiarObrazu, int rozmiarBitmapy,
    BYTE* szary, BYTE* sepia, BYTE* kontr, BYTE* solar, BYTE* gauss)
{
    /* ----- ZAPISANIE OBRAZ�W WYNIKOWYCH ----- */

   //uaktualnienie nag��wk�w
    naglowekBMP.bfType = 0x4D42;
    naglowekBMP.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + rozmiarObrazu;
    naglowekBMP.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    informacjeBMP.biSize = sizeof(BITMAPINFOHEADER);
    informacjeBMP.biSizeImage = rozmiarBitmapy;

    //utworzenie pliku bitmapy
    FILE* zapis1;
    if (!(zapis1 = fopen("img\\SZARY.bmp", "wb")))
    {
        printf("blad zapisu 1");
        return -2;
    }

    //zapisanie informacji z nag��wk�w
    fwrite(&naglowekBMP, sizeof(naglowekBMP), 1, zapis1);
    fwrite(&informacjeBMP, sizeof(informacjeBMP), 1, zapis1);
    fwrite(szary, rozmiarBitmapy, 1, zapis1);

    fclose(zapis1);

    //utworzenie pliku bitmapy
    FILE* zapis2;
    if (!(zapis2 = fopen("img\\SEPIA.bmp", "wb")))
    {
        printf("blad zapisu 2");
        return -2;
    }

    //zapisanie informacji z nag��wk�w
    fwrite(&naglowekBMP, sizeof(naglowekBMP), 1, zapis2);
    fwrite(&informacjeBMP, sizeof(informacjeBMP), 1, zapis2);
    fwrite(sepia, rozmiarBitmapy, 1, zapis2);

    fclose(zapis2);

    //utworzenie pliku bitmapy
    FILE* zapis3;
    if (!(zapis3 = fopen("img\\KONTR.bmp", "wb")))
    {
        printf("blad zapisu 3");
        return -2;
    }

    //zapisanie informacji z nag��wk�w
    fwrite(&naglowekBMP, sizeof(naglowekBMP), 1, zapis3);
    fwrite(&informacjeBMP, sizeof(informacjeBMP), 1, zapis3);
    fwrite(kontr, rozmiarBitmapy, 1, zapis3);

    fclose(zapis3);

    //utworzenie pliku bitmapy
    FILE* zapis4;
    if (!(zapis4 = fopen("img\\SOLAR.bmp", "wb")))
    {
        printf("blad zapisu 4");
        return -2;
    }

    //zapisanie informacji z nag��wk�w
    fwrite(&naglowekBMP, sizeof(naglowekBMP), 1, zapis4);
    fwrite(&informacjeBMP, sizeof(informacjeBMP), 1, zapis4);
    fwrite(solar, rozmiarBitmapy, 1, zapis4);

    fclose(zapis4);

    //utworzenie pliku bitmapy
    FILE* zapis5;
    if (!(zapis5 = fopen("img\\GAUSS.bmp", "wb")))
    {
        printf("blad zapisu 5");
        return -2;
    }

    //zapisanie informacji z nag��wk�w
    fwrite(&naglowekBMP, sizeof(naglowekBMP), 1, zapis5);
    fwrite(&informacjeBMP, sizeof(informacjeBMP), 1, zapis5);
    fwrite(gauss, rozmiarBitmapy, 1, zapis5);

    fclose(zapis5);



    return 0;
}
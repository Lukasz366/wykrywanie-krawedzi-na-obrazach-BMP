#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int ROZMIAR_FILE_HEADER = 14;
const int ROZMIAR_INFO_HEADER = 40;
const int MAKSYMALNA_SZEROKOSC = 320;
const int MAKSYMALNA_WYSOKOSC = 320;


void stworz_file_header(int szerokosc, int wysokosc, unsigned char file_header[])
{
    int rozmiar_pliku = ROZMIAR_FILE_HEADER + ROZMIAR_INFO_HEADER + (szerokosc * wysokosc * 3);

    for (int j = 0; j < ROZMIAR_FILE_HEADER; j++)
    {
        file_header[j] = 0;
    }

    file_header[0] = (unsigned char)('B');
    file_header[1] = (unsigned char)('M');
    file_header[2] = (unsigned char)(rozmiar_pliku);
    file_header[3] = (unsigned char)(rozmiar_pliku >> 8);
    file_header[4] = (unsigned char)(rozmiar_pliku >> 16);
    file_header[5] = (unsigned char)(rozmiar_pliku >> 24);
    file_header[10] = (unsigned char)(ROZMIAR_FILE_HEADER + ROZMIAR_INFO_HEADER);
}

void stworz_info_header(int wysokosc, int szerokosc, unsigned char info_header[])
{
    for (int j = 0; j < ROZMIAR_INFO_HEADER; j++)
    {
        info_header[j] = 0;
    }

    info_header[0] = (unsigned char)(ROZMIAR_INFO_HEADER);
    info_header[4] = (unsigned char)(szerokosc);
    info_header[5] = (unsigned char)(szerokosc >> 8);
    info_header[6] = (unsigned char)(szerokosc >> 16);
    info_header[7] = (unsigned char)(szerokosc >> 24);
    info_header[8] = (unsigned char)(wysokosc);
    info_header[9] = (unsigned char)(wysokosc >> 8);
    info_header[10] = (unsigned char)(wysokosc >> 16);
    info_header[11] = (unsigned char)(wysokosc >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(3 * 8);
}

void stworzobraz(unsigned char tablica_pixeli2[MAKSYMALNA_WYSOKOSC][MAKSYMALNA_SZEROKOSC][3], int wysokosc, int szerokosc, char* nazwa_pliku_koncowego)
{


    fstream plik_koncowy;
    plik_koncowy.open(nazwa_pliku_koncowego, ios::out | ios::binary);

    unsigned char file_header[ROZMIAR_FILE_HEADER];
    stworz_file_header(szerokosc, wysokosc, file_header);

    for (int j = 0; j < ROZMIAR_FILE_HEADER; j++)
    {
        plik_koncowy << file_header[j];
    }

    unsigned char info_header[ROZMIAR_INFO_HEADER];
    stworz_info_header(wysokosc, szerokosc, info_header);
    for (int j = 0; j < ROZMIAR_INFO_HEADER; j++)
    {
        plik_koncowy << info_header[j];
    }

    int reszta = (4 - ((szerokosc * 3) % 4)) % 4;
    for (int i = wysokosc - 1; i >= 0; i--)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                plik_koncowy << tablica_pixeli2[i][j][k];
            }
        }
        for (int l = 0; l < reszta; l++)
        {
            plik_koncowy << '0';
        }
    }
    plik_koncowy.close();
}


int main()
{
    int S[8][3][3] = { {{-1,0,1},{-2,0,2},{-1,0,1}} , {{0,1,2},{-1,0,1},{-2,-1,0}} , {{1,2,1},{0,0,0},{-1,-2,-1}} , {{2,1,0},{1,0,-1},{0,-1,-2}} , {{1,0,-1},{2,0,-2},{1,0,-1}} , {{0,-1,-2},{1,0,-1},{2,1,0}} , {{-1,-2,-1},{0,0,0},{1,2,1}} , {{-2,-1,0},{-1,0,1},{0,1,2}} };
    unsigned char dane[400000];

    int nrdanej = 0;

    char nazwa_pliku_koncowego[30];
    char  nazwa_pliku_poczatkowego[30];
    cout << "wpisz nazwe pliku poczatkowego ";
    cin >> nazwa_pliku_poczatkowego;
    cout << "wpisz nazwe pliku koncowego ";
    cin >> nazwa_pliku_koncowego;

    fstream plik;
    plik.open(nazwa_pliku_poczatkowego, ios::in | ios::binary);
    char pomocnicza;

    if (plik.is_open())
    {

        while (plik.get(pomocnicza))
        {
            dane[nrdanej] = (unsigned char)pomocnicza;
            nrdanej++;
        }

        plik.close();
        int bfSize = dane[5] * 256 * 256 * 256 + dane[4] * 256 * 256 + dane[3] * 256 + dane[2];
        int bfReserved1 = dane[7] * 256 + dane[6];
        int bfReserved2 = dane[9] * 256 + dane[8];
        int bfOffBits = dane[13] * 256 * 256 * 256 + dane[12] * 256 * 256 + dane[11] * 256 + dane[10];

        int biSize = dane[17] * 256 * 256 * 256 + dane[16] * 256 * 256 + dane[15] * 256 + dane[14];
        int szerokosc = dane[19] * 256 + dane[18];
        int wysokosc = dane[23] * 256 + dane[22];
        int biplanes = dane[27] * 256 + dane[26];
        int biBitCount = dane[29] * 256 + dane[28];
        int biCompression = dane[33] * 256 * 256 * 256 + dane[32] * 256 * 256 + dane[31] * 256 + dane[30];
        int biSizeImage = dane[37] * 256 * 256 * 256 + dane[36] * 256 * 256 + dane[35] * 256 + dane[34];
        int biXpelsPerMeter = dane[41] * 256 * 256 * 256 + dane[40] * 256 * 256 + dane[39] * 256 + dane[38];
        int biYpelsPerMeter = dane[45] * 256 * 256 * 256 + dane[44] * 256 * 256 + dane[43] * 256 + dane[42];
        int biCrlUses = dane[49] * 256 * 256 * 256 + dane[48] * 256 * 256 + dane[47] * 256 + dane[46];
        int biCrlImportant = dane[53] * 256 * 256 * 256 + dane[52] * 256 * 256 + dane[51] * 256 + dane[50];

        int iloscbitow = dane[28];
        int poczatek = dane[13] * 256 * 256 * 256 + dane[12] * 256 * 256 + dane[11] * 256 + dane[10];
        int reszta = (4 - ((szerokosc * 3) % 4)) % 4;

        cout << "bfType=" << dane[0] << dane[1] << endl << "bfSize=" << bfSize << endl << "bfReserved1=" << bfReserved1 << endl << "bfReserved2=" << bfReserved2 << endl << "bfReserved2=" << bfReserved2 << endl << "bfOffBits=" << bfOffBits << endl << "biSize=" << biSize << endl << "biWidth=" << szerokosc
            << endl << "biHeight=" << wysokosc << endl << "biplanes=" << biplanes << endl << "biBitCount=" << biBitCount << endl << "biCompression=" << biCompression << endl << "biSizeImage=" << biSizeImage << endl << "biXpelsPerMeter=" << biXpelsPerMeter << endl << "biYpelsPerMeter=" << biYpelsPerMeter
            << endl << "biCrlUses=" << biCrlUses << endl << "biCrlImportant=" << biCrlImportant << endl;
        //cout << "szerokoâźÅ¤âÃ§=" << szerokosc << endl << "wysokoâźÅ¤âÃ§=" << wysokosc << endl << iloscbitow << " bajtââw" << endl;

        unsigned char tablica_pixeli[MAKSYMALNA_WYSOKOSC][MAKSYMALNA_SZEROKOSC][3];//tablica z pixelami czytana jest od doÅu od lewej do prawej 
        unsigned char tablica_pixeli2[MAKSYMALNA_WYSOKOSC][MAKSYMALNA_SZEROKOSC][3];
        int skladowa[8];

        for (int i = wysokosc - 1; i >= 0; i--)
        {
            for (int j = 0; j < szerokosc; j++)
            {
                tablica_pixeli[i][j][0] = dane[poczatek + j * 3 + szerokosc * (wysokosc - 1 - i) * 3 + reszta * (wysokosc - i)];//niebieski
                tablica_pixeli[i][j][1] = dane[poczatek + j * 3 + szerokosc * (wysokosc - 1 - i) * 3 + reszta * (wysokosc - i)];//zielony
                tablica_pixeli[i][j][2] = dane[poczatek + j * 3 + szerokosc * (wysokosc - 1 - i) * 3 + reszta * (wysokosc - i)];//czerwony
            }
        }

        for (int i = 1; i < wysokosc - 1; i++)
        {
            for (int j = 1; j < szerokosc - 1; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        skladowa[l] = tablica_pixeli[j - 1][i - 1][k] * S[l][0][0] + tablica_pixeli[j][i - 1][k] * S[l][1][0] + tablica_pixeli[j + 1][i - 1][k] * S[l][2][0] + tablica_pixeli[j - 1][i][k] * S[l][0][1] + tablica_pixeli[j][i][k] * S[l][1][1] + tablica_pixeli[j + 1][i][k] * S[l][2][1] + tablica_pixeli[j - 1][i + 1][k] * S[l][0][2] + tablica_pixeli[j][i + 1][k] * S[l][1][2] + tablica_pixeli[j + 1][i + 1][k] * S[l][2][2];
                    }
                    if (sqrt((skladowa[0] * skladowa[0] + skladowa[2] * skladowa[2])) <= 255)
                    {
                        tablica_pixeli2[j][i][k] = (unsigned char)sqrt((skladowa[0] * skladowa[0] + skladowa[2] * skladowa[2]));
                    }
                    else
                    {
                        tablica_pixeli2[j][i][k] = 255;
                    }
                }
            }
        }

        for (int i = 0; i < szerokosc; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tablica_pixeli2[i][0][j] = '\0';
                tablica_pixeli2[i][wysokosc - 1][j] = '\0';
            }
        }

        for (int i = 0; i < wysokosc; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tablica_pixeli2[0][i][j] = '\0';
                tablica_pixeli2[szerokosc - 1][i][j] = '\0';
            }
        }

        stworzobraz(tablica_pixeli2, wysokosc, szerokosc, nazwa_pliku_koncowego);
        cout << "obraz gotowy";

    }
    else
    {
        cout << "nie znaleziono pliku";
    }
}
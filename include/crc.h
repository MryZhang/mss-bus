/*
 *  Plik: crc.h
 *  Plik zawiera deklaracj� funkcji crc16() obliczaj�c� CRC 16-bitowe.
 */

#include "types.h"

/*
 *  Funkcja oblicza CRC 16-bitowe. Wykorzystuje tablic� crc_table (wyznaczonej
 *  dla danego polinominal). Je�li chcemy oblicza� crc w kilku krokach,
 *  mo�emy wywo�a� funkcj� wielokrotnie przekazuj�c jej kolejne ci�gi bajt�w
 *  z kt�rych chcemy policzy� CRC oraz CRC z poprzedniego kroku. Pocz�tkowe
 *  CRC powinno by� 0.
 *
 *  Parametry:
 *    data - wskazanie na bufor zawieraj�cy dane z kt�rych liczymy CRC,
 *    size - wielko�� bufora data,
 *    crc  - CRC z poprzedniego wywo�ania lub 0.
 *  Wynik:
 *    Obliczone CRC.
 */
mss_crc16 crc16 (const unsigned char * data, unsigned long size,
                 unsigned short crc = 0);


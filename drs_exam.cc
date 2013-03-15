/********************************************************************\

  Name:         drs_exam.cpp
  Created by:   Stefan Ritt

  Contents:     Simple example application to read out a DRS4
                evaluation board

  $Id: drs_exam.cpp 20380 2012-11-13 13:38:01Z ritt $

\********************************************************************/

#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;


#ifdef _MSC_VER

#include <windows.h>

#elif defined(OS_LINUX)

#define O_BINARY 0

#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <errno.h>

#define DIR_SEPARATOR '/'

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strlcpy.h"
#include "DRS.h"

/*------------------------------------------------------------------*/

int main()
{
   int i, j, nBoards;
   DRS *drs;
   DRSBoard *b;
   float time_array[1024];
   float wave_array[9][1024];
   FILE  *f;

   /* do initial scan */
   drs = new DRS();

   /* show any found board(s) */
   for (i=0 ; i<drs->GetNumberOfBoards() ; i++) {
      b = drs->GetBoard(i);
      printf("Found DRS4 evaluation board, serial #%d, firmware revision %d\n", 
         b->GetBoardSerialNumber(), b->GetFirmwareVersion());
   }

   /* exit if no board found */
   nBoards = drs->GetNumberOfBoards();
   if (nBoards == 0) {
      printf("No DRS4 evaluation board found\n");
      return 0;
   }

   /* continue working with first board only */
   b = drs->GetBoard(0);

   /* initialize board */
   b->Init();

   /* set sampling frequency */
   b->SetFrequency(5, true);

   /* enable transparent mode needed for analog trigger */
   b->SetTranspMode(1);

   /* set input range to -0.5V ... +0.5V */
   b->SetInputRange(0);


   /* use following line to set range to 0..1V */
   //b->SetInputRange(0.5);

   /* use following lines to enable hardware trigger on CH1 at 50 mV positive edge */
   b->EnableTrigger(1, 0);           // enable hardware trigger
   b->SetTriggerSource(0xf);        // set CH1 as source
      
   b->SetTriggerLevel(0.08, false);     // 0.05 V, positive edge
   b->SetTriggerDelayNs(0);             // zero ns trigger delay
   
   /* use following lines to enable the external trigger */
   //if (b->GetBoardType() == 8) {     // Evaluaiton Board V4
   //   b->EnableTrigger(1, 0);           // enable hardware trigger
   //   b->SetTriggerSource(1<<4);        // set external trigger as source
   //} else {                          // Evaluation Board V3
   //   b->EnableTrigger(1, 0);           // lemo on, analog trigger off
   // }

   /* open file to save waveforms */
   //   f = fopen("data.txt", "w");
   //if (f == NULL) {
   //   perror("ERROR: Cannot open file \"data.txt\"");
   //   return 1;
   //}

   /* use following line to switch the internal 60 MHz clock to channel #4 */
   //  b->EnableTcal(1);

   //sleep(2);

   
   /* repeat ten times */
   for (j=0 ; j<1 ; j++) {

      /* start board (activate domino wave) */
      b->StartDomino();

      // usleep (100000);
      
      // b->SoftTrigger();
      
      /* wait for trigger */
      while (b->IsBusy());

      /* read all waveforms */
      b->TransferWaves(0, 8);

      /* read time (X) array in ns */
      b->GetTime(0, b->GetTriggerCell(0), time_array);

      /* decode waveform (Y) array first channel in mV */

      int c;
      for ( c = 0; c < 9; c++)
	{
	  b->GetWave(0, c, wave_array[c]);
	}

      for ( c = 0; c < 1024; c++)
	{
	  std::cout << setw(10) << time_array[c] 
		    << setw(9) << wave_array[0][c]
		    << setw(9) << wave_array[1][c]
		    << setw(9) << wave_array[2][c]
		    << setw(9) << wave_array[3][c]
		    << setw(9) << wave_array[4][c]
		    << setw(9) << wave_array[5][c]
		    << setw(9) << wave_array[6][c]
		    << setw(9) << wave_array[7][c]
		    << setw(9) << wave_array[8][c]
		    << endl;
	}

      /* print some progress indication */
      if (j % 100 == 0)
         printf("\rEvent #%d read successfully\n", j);
   }

   //   fclose(f);
   
   /* delete DRS object -> close USB connection */
   delete drs;
}

/*
  horgand - a organ software

 organ.C  -  organ functions
  Copyright (C) 2003-2004 Josep Andreu (Holborn)
  Author: Josep Andreu

 This program is free software; you can redistribute it and/or modify
 it under the terms of version 2 of the GNU General Public License
 as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License (version 2) for more details.

 You should have received a copy of the GNU General Public License
 (version2)  along with this program; if not, write to the Free Software
 Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/


#include "Holrgan.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


pthread_mutex_t mutex;
int l1, i, j, k, Pexitprogram, vum, vumvum, espera,
UndoCount,programa,vavi,pr,pr1,tum,cambialo;
char NombreAcorde[16];
int solucion,Rit,commandline;
const char *FilePreset;


HOR::HOR ()
{

  //inicio de variables

  Rit = 0;
  espera = 0;
  perhis = 0;
  rperhis = 0;
  eperhis = 0;
  capsg=0;
  master = 0.70;
  incre = 0.5 / SAMPLE_RATE;
  lalapi = D_PI / SAMPLE_RATE;
  sbars = 1;
  ae = 1;
  fe = 0;  
  cprograma=1;

  lasfreq[1] = 0.5;
  lasfreq[2] = 0.75;
  lasfreq[3] = 1.0;
  lasfreq[4] = 1.5;
  lasfreq[5] = 2.0;
  lasfreq[6] = 2.5;
  lasfreq[7] = 3.0;
  lasfreq[8] = 4.0;
  lasfreq[9] = 4.5;
  lasfreq[10] = 5.0;
  lasfreq[11] = 6.0;
  lasfreq[12] = 7.0;
  lasfreq[13] = 7.5;
  lasfreq[14] = 8.0;
  lasfreq[15] = 9.0;
  lasfreq[16] = 10.0;
  lasfreq[17] = 10.5;
  lasfreq[18] = 11.0;
  lasfreq[19] = 12.0;
  lasfreq[20] = 13.0;
  lasfreq[21] = 14.0;
  lasfreq[22] = 16.0;



  for (i = 1; i <= 20; i++)
    {
      Operator[i].harmonic_fine = 0.0;
      Operator[i].volumen = 0.0;
    }

  Operator[1].harmonic = 1;
  Operator[2].harmonic = 3;
  Operator[3].harmonic = 4;
  Operator[4].harmonic = 5;
  Operator[5].harmonic = 7;
  Operator[6].harmonic = 8;
  Operator[7].harmonic = 11;
  Operator[8].harmonic = 14;
  Operator[9].harmonic = 19;
  Operator[10].harmonic = 22;
  Operator[11].harmonic = 1;
  Operator[12].harmonic = 3;
  Operator[13].harmonic = 4;
  Operator[14].harmonic = 5;
  Operator[15].harmonic = 7;
  Operator[16].harmonic = 8;
  Operator[17].harmonic = 11;
  Operator[18].harmonic = 14;
  Operator[19].harmonic = 19;
  Operator[20].harmonic = 22;
  


  solucion = 0;
  mastertune = 1;
  attack = 0.02;
  decay = 0.00;
  sustain = 0.99;
  release = 0.14;
  echoon = 0;
  echodelay = 0;
  echovol = 0;
  LFOspeed = 0;
  PLFOspeed = 0;
  PLFOdelay = 0;
  LFOpitch = 0;
  LFOamplitude = 99;
  modulation = 10;
  transpose = 0;
  pitch = 0;
  pedal = 0;
  UndoCount = 0;
  freq_note = 0;
  lado = 0;
  hacia = 0;
  partial = 0;
  sound = 0;
  xx = 0;
  xel = 0.0;
  xer = 0.25;
  ELFOspeed = 0;
  chorvol = 0.60;
  split = 0;
  ganmod = 1;
  revon = 0;
  rtime = 1.0;
  diffussion = 0.1;
  revvol = 0.20;
  tempo = 2;
  ritvol = 0.5;
  bassvol = 0.5;
  basspending = 0;
  lpos = 100;
  afina = 2.0;
  cambialo = 0;

int tcombl[16]= {10586, 12340, 6400, 13100, 8004, 7200,5130,9037,12045,11237,9456,7634,5389, 8056,10120,11432};
int tcombr[16]= {10586, 11340, 8450, 11100, 9644, 7560,9536,11507,12600,11111,8056,6048,7690,5978,8845,10056};
int tapsg[16]= {36,33,29,27,24,21,17,15,13,16,21,24,27,31,33,36};

for (i=0; i<16; i++)

{

  combl[i] = tcombl[i];
  combr[i] = tcombr[i];
  apsg[i] = tapsg[i];
  apss += apsg[i];

}



strcpy(NC[0].Nom,"C");
strcpy(NC[1].Nom,"Db");
strcpy(NC[2].Nom,"D");
strcpy(NC[3].Nom,"Eb");
strcpy(NC[4].Nom,"E");
strcpy(NC[5].Nom,"F");
strcpy(NC[6].Nom,"Gb");
strcpy(NC[7].Nom,"G");
strcpy(NC[8].Nom,"Ab");
strcpy(NC[9].Nom,"A");
strcpy(NC[10].Nom,"Bb");
strcpy(NC[11].Nom,"B");


AB[0].afin = 2.0;
AB[1].afin = 2.119;
AB[2].afin = 2.245;
AB[3].afin = 2.3785;
AB[4].afin = 2.519877;
AB[5].afin = 2.669724;
AB[6].afin = 2.828746;
AB[7].afin = 1.49847;
AB[8].afin = 1.587767;
AB[9].afin = 1.681957;
AB[10].afin = 1.782262;
AB[11].afin = 1.888073;



// Inicia TipoChords



//Maj7

TCh[1].ter = 0;
TCh[1].qui = 0;
TCh[1].sep = 0;

//7

TCh[2].ter = 0;
TCh[2].qui = 0;
TCh[2].sep = -1;

//-7

TCh[3].ter = -1;
TCh[3].qui = 0;
TCh[3].sep = -1;

//-7(b5)

TCh[4].ter = -1;
TCh[4].qui = -1;
TCh[4].sep = -1;

//dis

TCh[5].ter = -1;
TCh[5].qui = -1;
TCh[5].sep = -2;

//aug7

TCh[6].ter = 0;
TCh[6].qui = +1;
TCh[6].sep = -1;


//7Sus4

TCh[7].ter = +1;
TCh[7].qui = 0;
TCh[7].sep = -1;



// Inicia Chords

Chord3[1].tipo = 1;
Chord3[1].fund = 1;
Chord3[1].di1  = 4;
Chord3[1].di2  = 3;
strcpy(Chord3[1].Nom,"");

Chord3[2].tipo = 1;
Chord3[2].fund = 3;
Chord3[2].di1  = 3;
Chord3[2].di2  = 5;
strcpy(Chord3[2].Nom,"");

Chord3[3].tipo = 1;
Chord3[3].fund = 2;
Chord3[3].di1  = 5;
Chord3[3].di2  = 4;
strcpy(Chord3[3].Nom,"");

Chord3[4].tipo = 3;
Chord3[4].fund = 1;
Chord3[4].di1  = 3;
Chord3[4].di2  = 4;
strcpy(Chord3[4].Nom,"m");

Chord3[5].tipo = 3;
Chord3[5].fund = 3;
Chord3[5].di1  = 4;
Chord3[5].di2  = 5;
strcpy(Chord3[5].Nom,"m");

Chord3[6].tipo = 3;
Chord3[6].fund = 2;
Chord3[6].di1  = 5;
Chord3[6].di2  = 3;
strcpy(Chord3[6].Nom,"m");

Chord3[7].tipo = 5;
Chord3[7].fund = 1;
Chord3[7].di1  = 3;
Chord3[7].di2  = 3;
strcpy(Chord3[7].Nom,"°");

Chord3[8].tipo = 6;
Chord3[8].fund = 1;
Chord3[8].di1  = 4;
Chord3[8].di2  = 4;
strcpy(Chord3[8].Nom,"+");

Chord3[9].tipo = 1;
Chord3[9].fund = 1;
Chord3[9].di1  = 2;
Chord3[9].di2  = 5;
strcpy(Chord3[9].Nom,"2");

Chord3[10].tipo = 1;
Chord3[10].fund = 3;
Chord3[10].di1  = 3;
Chord3[10].di2  = 2;
strcpy(Chord3[10].Nom,"");

Chord3[11].tipo = 4;
Chord3[11].fund = 2;
Chord3[11].di1  = 6;
Chord3[11].di2  = 3;
strcpy(Chord3[11].Nom,"m(b5)");


Chord3[12].tipo = 2;
Chord3[12].fund = 1;
Chord3[12].di1  = 4;
Chord3[12].di2  = 6;
strcpy(Chord3[12].Nom,"7");

Chord3[13].tipo = 3;
Chord3[13].fund = 1;
Chord3[13].di1  = 3;
Chord3[13].di2  = 7;
strcpy(Chord3[13].Nom,"m7");

Chord3[14].tipo = 3;
Chord3[14].fund = 1;
Chord3[14].di1  = 3;
Chord3[14].di2  = 6;
strcpy(Chord3[14].Nom,"m6");



// Chords4

Chord4[1].tipo = 1;
Chord4[1].fund = 1;
Chord4[1].di1  = 4;
Chord4[1].di2  = 3;
Chord4[1].di3  = 4;
strcpy(Chord4[1].Nom,"Maj7");

Chord4[2].tipo = 3;
Chord4[2].fund = 1;
Chord4[2].di1  = 3;
Chord4[2].di2  = 4;
Chord4[2].di3  = 3;
strcpy(Chord4[2].Nom,"m7");

Chord4[3].tipo = 2;
Chord4[3].fund = 1;
Chord4[3].di1  = 4;
Chord4[3].di2  = 3;
Chord4[3].di3  = 3;
strcpy(Chord4[3].Nom,"7");

Chord4[4].tipo = 4;
Chord4[4].fund = 1;
Chord4[4].di1  = 3;
Chord4[4].di2  = 3;
Chord4[4].di3  = 4;
strcpy(Chord4[4].Nom,"m7(b5)");

Chord4[5].tipo = 5;
Chord4[5].fund = 1;
Chord4[5].di1  = 3;
Chord4[5].di2  = 3;
Chord4[5].di3  = 3;
strcpy(Chord4[5].Nom,"°7");

Chord4[6].tipo = 6;
Chord4[6].fund = 1;
Chord4[6].di1  = 4;
Chord4[6].di2  = 4;
Chord4[6].di3  = 2;
strcpy(Chord4[6].Nom,"+7");

Chord4[7].tipo = 1;
Chord4[7].fund = 1;
Chord4[7].di1  = 4;
Chord4[7].di2  = 3;
Chord4[7].di3  = 5;
strcpy(Chord4[7].Nom,"");

Chord4[8].tipo = 1;
Chord4[8].fund = 1;
Chord4[8].di1  = 4;
Chord4[8].di2  = 3;
Chord4[8].di3  = 2;
strcpy(Chord4[8].Nom,"6");

Chord4[9].tipo = 7;
Chord4[9].fund = 1;
Chord4[9].di1  = 5;
Chord4[9].di2  = 2;
Chord4[9].di3  = 3;
strcpy(Chord4[9].Nom,"7(Sus4)");

Chord4[10].tipo = 3;
Chord4[10].fund = 1;
Chord4[10].di1  = 3;
Chord4[10].di2  = 4;
Chord4[10].di3  = 4;
strcpy(Chord4[10].Nom,"m(Maj7)");

Chord4[11].tipo = 3;
Chord4[11].fund = 1;
Chord4[11].di1  = 3;
Chord4[11].di2  = 4;
Chord4[11].di3  = 2;
strcpy(Chord4[11].Nom,"m6");

Chord4[12].tipo = 6;
Chord4[12].fund = 1;
Chord4[12].di1  = 4;
Chord4[12].di2  = 4;
Chord4[12].di3  = 4;
strcpy(Chord4[12].Nom,"+(Maj7)");

Chord4[13].tipo = 1;
Chord4[13].fund = 1;
Chord4[13].di1  = 2;
Chord4[13].di2  = 4;
Chord4[13].di3  = 3;
strcpy(Chord4[13].Nom,"lyd");

Chord4[14].tipo = 1;
Chord4[14].fund = 4;
Chord4[14].di1  = 3;
Chord4[14].di2  = 4;
Chord4[14].di3  = 1;
strcpy(Chord4[14].Nom,"Maj7");

Chord4[15].tipo = 1;
Chord4[15].fund = 4;
Chord4[15].di1  = 3;
Chord4[15].di2  = 3;
Chord4[15].di3  = 2;
strcpy(Chord4[15].Nom,"7");

Chord4[16].tipo = 6;
Chord4[16].fund = 4;
Chord4[16].di1  = 4;
Chord4[16].di2  = 2;
Chord4[16].di3  = 2;
strcpy(Chord4[16].Nom,"+7");

Chord4[17].tipo = 1;
Chord4[17].fund = 3;
Chord4[17].di1  = 3;
Chord4[17].di2  = 5;
Chord4[17].di3  = 4;
strcpy(Chord4[17].Nom,"");

Chord4[18].tipo = 7;
Chord4[18].fund = 4;
Chord4[18].di1  = 2;
Chord4[18].di2  = 3;
Chord4[18].di3  = 2;
strcpy(Chord4[18].Nom,"7(Sus4)");


Chord4[19].tipo = 3;
Chord4[19].fund = 4;
Chord4[19].di1  = 4;
Chord4[19].di2  = 4;
Chord4[19].di3  = 1;
strcpy(Chord4[19].Nom,"m(Maj7)");

Chord4[20].tipo = 6;
Chord4[20].fund = 4;
Chord4[20].di1  = 4;
Chord4[20].di2  = 4;
Chord4[20].di3  = 1;
strcpy(Chord4[20].Nom,"+(Maj7)");

Chord4[21].tipo = 1;
Chord4[21].fund = 3;
Chord4[21].di1  = 4;
Chord4[21].di2  = 1;
Chord4[21].di3  = 4;
strcpy(Chord4[21].Nom,"Maj7");

Chord4[22].tipo = 3;
Chord4[22].fund = 3;
Chord4[22].di1  = 3;
Chord4[22].di2  = 2;
Chord4[22].di3  = 3;
strcpy(Chord4[22].Nom,"m7");

Chord4[23].tipo = 2;
Chord4[23].fund = 3;
Chord4[23].di1  = 3;
Chord4[23].di2  = 2;
Chord4[23].di3  = 4;
strcpy(Chord4[23].Nom,"7");

Chord4[24].tipo = 4;
Chord4[24].fund = 3;
Chord4[24].di1  = 4;
Chord4[24].di2  = 2;
Chord4[24].di3  = 3;
strcpy(Chord4[24].Nom,"m7(b5)");

Chord4[26].tipo = 6;
Chord4[25].fund = 3;
Chord4[25].di1  = 2;
Chord4[25].di2  = 2;
Chord4[25].di3  = 4;
strcpy(Chord4[25].Nom,"+7");

Chord4[26].tipo = 1;
Chord4[26].fund = 2;
Chord4[26].di1  = 5;
Chord4[26].di2  = 4;
Chord4[26].di3  = 3;
strcpy(Chord4[26].Nom,"");

Chord4[27].tipo = 7;
Chord4[27].fund = 3;
Chord4[27].di1  = 3;
Chord4[27].di2  = 2;
Chord4[27].di3  = 5;
strcpy(Chord4[27].Nom,"7(Sus4)");

Chord4[28].tipo = 2;
Chord4[28].fund = 3;
Chord4[28].di1  = 4;
Chord4[28].di2  = 2;
Chord4[28].di3  = 3;
strcpy(Chord4[28].Nom,"m(Maj7)");

Chord4[29].tipo = 6;
Chord4[29].fund = 3;
Chord4[29].di1  = 3;
Chord4[29].di2  = 1;
Chord4[29].di3  = 4;
strcpy(Chord4[29].Nom,"+(Maj7)");

Chord4[30].tipo = 1;
Chord4[30].fund = 2;
Chord4[30].di1  = 1;
Chord4[30].di2  = 4;
Chord4[30].di3  = 3;
strcpy(Chord4[30].Nom,"Maj7");

Chord4[31].tipo = 3;
Chord4[31].fund = 2;
Chord4[31].di1  = 2;
Chord4[31].di2  = 3;
Chord4[31].di3  = 4;
strcpy(Chord4[31].Nom,"m7");

Chord4[32].tipo = 4;
Chord4[32].fund = 2;
Chord4[32].di1  = 2;
Chord4[32].di2  = 3;
Chord4[32].di3  = 3;
strcpy(Chord4[32].Nom,"m7(b5)");

Chord4[33].tipo = 6;
Chord4[33].fund = 2;
Chord4[33].di1  = 2;
Chord4[33].di2  = 4;
Chord4[33].di3  = 4;
strcpy(Chord4[33].Nom,"+7");

Chord4[34].tipo = 2;
Chord4[34].fund = 4;
Chord4[34].di1  = 6;
Chord4[34].di2  = 3;
Chord4[34].di3  = 5;
strcpy(Chord4[34].Nom,"7");

Chord4[35].tipo = 7;
Chord4[35].fund = 2;
Chord4[35].di1  = 2;
Chord4[35].di2  = 5;
Chord4[35].di3  = 2;
strcpy(Chord4[35].Nom,"7(Sus4");

Chord4[36].tipo = 3;
Chord4[36].fund = 2;
Chord4[36].di1  = 1;
Chord4[36].di2  = 3;
Chord4[36].di3  = 4;
strcpy(Chord4[36].Nom,"m(Maj7)");

Chord4[37].tipo = 6;
Chord4[37].fund = 2;
Chord4[37].di1  = 1;
Chord4[37].di2  = 4;
Chord4[37].di3  = 4;
strcpy(Chord4[37].Nom,"+(Maj7)");

Chord4[38].tipo = 3;
Chord4[38].fund = 1;
Chord4[38].di1  = 3;
Chord4[38].di2  = 4;
Chord4[38].di3  = 5;
strcpy(Chord4[38].Nom,"m");

Chord4[39].tipo = 3;
Chord4[39].fund = 3;
Chord4[39].di1  = 4;
Chord4[39].di2  = 5;
Chord4[39].di3  = 3;
strcpy(Chord4[39].Nom,"m");

Chord4[40].tipo = 3;
Chord4[40].fund = 2;
Chord4[40].di1  = 5;
Chord4[40].di2  = 3;
Chord4[40].di3  = 4;
strcpy(Chord4[40].Nom,"m");

Chord4[41].tipo = 1;
Chord4[41].fund = 1;
Chord4[41].di1  = 2;
Chord4[41].di2  = 2;
Chord4[41].di3  = 3;
strcpy(Chord4[41].Nom,"9");

Chord4[42].tipo = 1;
Chord4[42].fund = 4;
Chord4[42].di1  = 2;
Chord4[42].di2  = 3;
Chord4[42].di3  = 5;
strcpy(Chord4[42].Nom,"9");

Chord4[43].tipo = 1;
Chord4[43].fund = 3;
Chord4[43].di1  = 3;
Chord4[43].di2  = 5;
Chord4[43].di3  = 2;
strcpy(Chord4[43].Nom,"9");


Chord4[44].tipo = 1;
Chord4[44].fund = 2;
Chord4[44].di1  = 5;
Chord4[44].di2  = 2;
Chord4[44].di3  = 2;
strcpy(Chord4[44].Nom,"9");

Chord4[45].tipo = 4;
Chord4[45].fund = 1;
Chord4[45].di1  = 3;
Chord4[45].di2  = 3;
Chord4[45].di3  = 5;
strcpy(Chord4[45].Nom,"m(Maj7)(b5)");

Chord4[46].tipo = 3;
Chord4[46].fund = 1;
Chord4[46].di1  = 2;
Chord4[46].di2  = 1;
Chord4[46].di3  = 4;
strcpy(Chord4[46].Nom,"m7");



// Chord 5

Chord5[1].tipo = 1;
Chord5[1].fund = 1;
Chord5[1].di1  = 2;
Chord5[1].di2  = 2;
Chord5[1].di3  = 3;
Chord5[1].di4   = 4;
strcpy(Chord5[1].Nom,"Maj7/9");

Chord5[2].tipo = 7;
Chord5[2].fund = 3;
Chord5[2].di1  = 3;
Chord5[2].di2  = 2;
Chord5[2].di3  = 2;
Chord5[2].di4   = 3;
strcpy(Chord5[2].Nom,"7(Sus4)");

Chord5[3].tipo = 7;
Chord5[3].fund = 1;
Chord5[3].di1  = 5;
Chord5[3].di2  = 2;
Chord5[3].di3  = 3;
Chord5[3].di4   = 2;
strcpy(Chord5[3].Nom,"7(Sus4)");

Chord5[4].tipo = 2;
Chord5[4].fund = 3;
Chord5[4].di1  = 3;
Chord5[4].di2  = 2;
Chord5[4].di3  = 2;
Chord5[4].di4   = 2;
strcpy(Chord5[4].Nom,"7");

Chord5[5].tipo = 1;
Chord5[5].fund = 3;
Chord5[5].di1  = 4;
Chord5[5].di2  = 1;
Chord5[5].di3  = 2;
Chord5[5].di4   = 2;
strcpy(Chord5[5].Nom,"Maj7");

Chord5[6].tipo = 7;
Chord5[6].fund = 1;
Chord5[6].di1  = 2;
Chord5[6].di2  = 3;
Chord5[6].di3  = 2;
Chord5[6].di4   = 3;
strcpy(Chord5[6].Nom,"7(Sus4)");

Chord5[7].tipo = 7;
Chord5[7].fund = 1;
Chord5[7].di1  = 2;
Chord5[7].di2  = 3;
Chord5[7].di3  = 2;
Chord5[7].di4   = 5;
strcpy(Chord5[7].Nom,"7(Sus4)");

Chord5[8].tipo = 4;
Chord5[8].fund = 1;
Chord5[8].di1  = 3;
Chord5[8].di2  = 2;
Chord5[8].di3  = 1;
Chord5[8].di4   = 4;
strcpy(Chord5[8].Nom,"m7(b5)");

Chord5[9].tipo = 3;
Chord5[9].fund = 1;
Chord5[9].di1  = 2;
Chord5[9].di2  = 1;
Chord5[9].di3  = 4;
Chord5[9].di4   = 3;
strcpy(Chord5[9].Nom,"m7");






//Inicia Ritmos


for (j = 1; j<= 20; j++)

{ 
   strcpy(Rt[j].Nom,"Emty");
   strcpy(Rt[j].Nfile,"Emty");
   Rt[j].bars = 0;
   Rt[j].blackn = 0;
   for (i=0; i<=64; i++)
   {
    Rt[j].linb[i] = 0;
    Rt[j].linbv[i]= 0;
   }
}


// Inicia Banco


  for (j = 1; j <= 32; j++)
    {
      for (i = 1; i <= 20; i++)
	{
	  Banco[j].Operator[i].harmonic = Operator[i].harmonic;
	  Banco[j].Operator[i].harmonic_fine = 0.0;
	  Banco[j].Operator[i].volumen = 0.0;
	}


      Banco[j].echoon = 0;
      Banco[j].echodelay = 0;
      Banco[j].echovol = 0;
      Banco[j].PLFOspeed = 0;
      Banco[j].PLFOdelay = 0;
      Banco[j].LFOspeed = 0;
      Banco[j].LFOpitch = 0;
      Banco[j].rota = 0;
      Banco[j].modulation = 0;
      Banco[j].transpose = 0;
      Banco[j].master = 0.70;
      Banco[j].attack = 0.02;
      Banco[j].detune = 0;
      Banco[j].choron = 0;
      Banco[j].split = 0;
      Banco[j].ELFOamplitude = 0;
      Banco[j].ELFOspeed = 0;
      Banco[j].popo = 0;
      Banco[j].ganmod = 1;
      Banco[j].revon = 0;
      Banco[j].chorvol = 0.60;


    }



//  Inicia Undo
  for (j = 0; j <= 100; j++)
    {

      for (i = 1; i <= 20; i++)
	{
	  Undo[j].Operator[i].harmonic = Operator[i].harmonic;
	  Undo[j].Operator[i].harmonic_fine = 0.0;
	  Undo[j].Operator[i].volumen = 0.0;

	}

      Undo[j].echoon = 0;
      Undo[j].echodelay = 0;
      Undo[j].echovol = 0;
      Undo[j].PLFOspeed = 0;
      Undo[j].PLFOdelay = 0;
      Undo[j].LFOspeed = 0;
      Undo[j].LFOpitch = 0;
      Undo[j].rota = 0;
      Undo[j].modulation = 0;
      Undo[j].transpose = 0;
      Undo[j].master = 0.70;
      Undo[j].attack = 0.02;
      Undo[j].detune = 0;
      Undo[j].choron = 0;
      Undo[j].split = 0;
      Undo[j].ELFOamplitude = 0;
      Undo[j].ELFOspeed = 0;
      Undo[j].popo = 0;
      Undo[j].ganmod = 1;
      Undo[j].revon = 0;
      Undo[j].chorvol = 0.60;


    }


// Inicia Prim

  for (j = 0; j <= 3; j++)
    {

      for (i = 1; i <= 20; i++)
	{
	  Prim[j].Operator[i].harmonic = Operator[i].harmonic;
	  Prim[j].Operator[i].harmonic_fine = 0.0;
	  Prim[j].Operator[i].volumen = 0.0;
	}



      Prim[j].echoon = 0;
      Prim[j].echodelay = 0;
      Prim[j].echovol = 0;
      Prim[j].PLFOspeed = 0;
      Prim[j].PLFOdelay = 0;
      Prim[j].LFOspeed = 0;
      Prim[j].LFOpitch = 0;
      Prim[j].rota = 0;
      Prim[j].modulation = 0;
      Prim[j].transpose = 0;
      Prim[j].master = 0.70;
      Prim[j].attack = 0.02;
      Prim[j].detune = 0;
      Prim[j].choron = 0;
      Prim[j].split = 0;
      Prim[j].ELFOamplitude = 0;
      Prim[j].ELFOspeed = 0;
      Prim[j].popo = 0;
      Prim[j].ganmod = 1;
      Prim[j].revon = 0;
      Prim[j].chorvol = 0.30;





    }



  //ALSA init
  snd_seq_open (&MidiInPuerto[1].midi_in, "default", SND_SEQ_OPEN_INPUT, 0);


  int alsaport = 0;
  char portname[50];

  sprintf (portname, "Horgand IN");

  alsaport = snd_seq_create_simple_port (MidiInPuerto[1].midi_in, portname,
					 SND_SEQ_PORT_CAP_WRITE |
					 SND_SEQ_PORT_CAP_SUBS_WRITE,
					 SND_SEQ_PORT_TYPE_SYNTH);




  lsin = (float *) malloc (sizeof (float) * 8000);
  nsin = (float *) malloc (sizeof (float) * 8000);
  memset (lsin, 0, 8000);
  memset (nsin, 0, 8000);



  float pepin;

  for (i = 0; i <= 7000; i++)

    {
      pepin = (float) (i / 1000.0);
      lsin[i] = sin (pepin);
      nsin[i] = sin (-1 * pepin);
    }


  for (i = 0; i < POLY; i++)
    {
      note_active[i] = 0;
      env_time[i] = 0;
    }


  for (i = 1; i <= 168; i++)
    {
      h[i].f1 = 8.1757989156 * exp ((float) (i - 2) * log (2.0) / 12.0);
      h[i].f2 = 8.1757989156 * exp ((float) (i) * log (2.0) / 12.0);
      h[i].f3 = 8.1757989156 * exp ((float) (i + 2) * log (2.0) / 12.0);
    }


  wbuf = (short *) malloc (2 * sizeof (short) * BUFSIZE);
  rbuf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  bbuf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  buf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  history = (float *) malloc (2 * sizeof (float) * BUFSIZE * 1024);
  rhistory = (float *) malloc (2 * sizeof (float) * BUFSIZE * 1024);
  ehistoryl = (float *) malloc (2 * sizeof (float) * BUFSIZE * 128);
  ehistoryr = (float *) malloc (2 * sizeof (float) * BUFSIZE * 128);

  memset (history, 0, BUFSIZE * 1024);
  memset (rhistory, 0, BUFSIZE * 1024);
  memset (ehistoryl, 0, BUFSIZE * 128);
  memset (ehistoryr, 0, BUFSIZE * 128);




  FILE *fs;
  char temp[512];
  char nomfile[256];
  char nomfile1[256];
  sprintf (nomfile, "%s%s", getenv ("HOME"), "/.Horgand");
  if ((fs = fopen (nomfile, "r")) != NULL)
    {
      fgets (temp, sizeof temp, fs);
      for (i = 0; i <= (int) strlen(temp) - 2; i++)
      MidiInPuerto[1].SetMidiIn[i] = temp[i];
      MidiInPuerto[1].SMidiIn = MidiInPuerto[1].SetMidiIn;
      
            
      bzero (temp, sizeof (temp));
      fgets (temp, sizeof temp, fs);
      if (strstr (temp, "OSS") != NULL)
	{
	  Salida = 1;
	  ossaudioprepare ();
	}
      if (strstr (temp, "Alsa") != NULL)
	{
	  Salida = 2;
	  alsaaudioprepare ();
	}
      if (strstr (temp, "Jack") != NULL)
	{
	  Salida = 3;
	  jackaudioprepare ();
	}

      bzero(BankFilename, sizeof (BankFilename));
      bzero (temp, sizeof (temp));
      fgets (temp, sizeof temp, fs);
      if (strlen(temp)>2)
               {
                for (i = 0; i <= (int) strlen(temp) - 2; i++) BankFilename[i] = temp[i];
                loadbank(BankFilename);
               } 



    }


   bzero(nomfile, sizeof(nomfile));
   strcpy(nomfile, "/usr/share/horgand/RithmList.txt");
   bzero(nomfile1, sizeof(nomfile1));
   strcpy(nomfile1, "/usr/local/share/horgand/RithmList.txt");
   if ((fs = fopen (nomfile, "r")) != NULL)  solucion = 1;
   if ((fs = fopen (nomfile1, "r")) != NULL) solucion = 2;
   if (solucion == 2 ) strcpy(nomfile, nomfile1); 
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (nomfile, "r")) != NULL)
   {
         int linea = 0;
         NumRit= 1;
         int w;    
      while (fgets(temp, sizeof temp, fs) != NULL)
          {
             linea++;
             switch (linea)
           { 
             case 1:
              bzero(Rt[NumRit].Nom, sizeof(Rt[NumRit].Nom));
              for (i=0;  i<=(int) strlen(temp) -2; i++) Rt[NumRit].Nom[i] = temp[i];                   
              break; 
             case 2:
              bzero(Rt[NumRit].Nfile, sizeof(Rt[NumRit].Nfile)); 
              for (i=0;  i<=(int) strlen(temp) -2; i++) Rt[NumRit].Nfile[i] = temp[i];
              break;
             case 3:
              sscanf (temp,"%d", &Rt[NumRit].bars);
              break;
             case 4:
              sscanf (temp,"%d", &Rt[NumRit].blackn);
              break;
             case 5: 
             sscanf(temp,"%d,%d,%d,%d",&Rt[NumRit].linb[1],&Rt[NumRit].linb[2],&Rt[NumRit].linb[3],&Rt[NumRit].linb[4]);
             for (i=1; i<Rt[NumRit].bars*Rt[NumRit].blackn; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              fgets(temp, sizeof temp, fs);
              sscanf(temp,"%d,%d,%d,%d",&Rt[NumRit].linb[w+1],&Rt[NumRit].linb[w+2],&Rt[NumRit].linb[w+3],&Rt[NumRit].linb[w+4]);
             } 
             bzero(temp,sizeof(temp));
             fgets(temp, sizeof temp, fs);
             sscanf(temp,"%d,%d,%d,%d",&Rt[NumRit].linbv[1],&Rt[NumRit].linbv[2],&Rt[NumRit].linbv[3],&Rt[NumRit].linbv[4]);
             for (i=1; i<Rt[NumRit].bars*Rt[NumRit].blackn; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              fgets(temp, sizeof temp, fs);
              sscanf(temp,"%d,%d,%d,%d",&Rt[NumRit].linbv[w+1],&Rt[NumRit].linbv[w+2],&Rt[NumRit].linbv[w+3],&Rt[NumRit].linbv[w+4]);
             }
              break;
              case 6:
              break;
              case 7:
              break;
              case 8:
              break;
              case 9:
              break;
              case 10:
              break;
              case 11:
              linea = 0;
              NumRit++;
              break;
          }
 


         }
       }


  
  memset (buf, 0, PERIOD8);
  memset (wbuf, 0, PERIOD8);
  memset (rbuf, 0, PERIOD8);  
  memset (bbuf, 0, PERIOD8);

  espera = 1;

};


HOR::~HOR ()
{
  snd_seq_close (MidiInPuerto[1].midi_in);

};

float
HOR::ELFO (float *kx)
{

  float out;

  *kx += incre * ELFOspeed;

  if (*kx > 1)
    *kx = 0;

  out = Fsin (*kx * D_PI);

  if (out < -1.0)
    out = -1.0;
  else if (out > 1.0)
    out = 1.0;
    out *=efreqlfo;
  return ((1+out)*0.5 );
  


};


float
HOR::pitchOp (int i, int note)
{

  return ((lasfreq[(int) Operator[i].harmonic] +
	   Operator[i].harmonic_fine) * aplfo);

};


void
HOR::volumeOpC (int i, int l2)
{


  Operator[i].con1 =
    Operator[i].volumen * alfo / (2 * lasfreq[Operator[i].harmonic]);
};


void

HOR::miraalfo(int nota)
{
alfo = velocity[nota] * envi[nota] * (1 -((120 - note[nota]) / 120.0));
};



void
HOR::panico ()
{
  int i;
  for (i = 0; i < POLY; i++)
    {
      note_active[i] = 0;
      env_time[i] = 0;
    }

};


void
HOR::Jenvelope (int *note_active, int gate, float t, int nota)
{


  if (gate)
    {

      if (t > attack )
	{
	  envi[nota] = sustain;
	  return;
	}
      envi[nota] = t / (attack + 0.0001);
      return;
    }
  else
    {
      if ((t > release) && (pedal == 0))
	{
	  if (note_active)
	    *note_active = 0;
             
	  return;
	}
      if ((pedal == 0) && (envi[nota] > 0))
	{
	  envi[nota] *= (1.0 - (t / release));
	  if ((note_active) && (envi[nota] < 0.01))
	    *note_active = 0;
             
	}

    }


};



float
HOR::PLFO (float t)
{

  float x, out;

  if (t * 20 < PLFOdelay)
    return (0.5);

  x = (t - floor (t));
  x *= PLFOspeed;
  x -= floor (x);


  out = Fsin (x * D_PI);


  if (out < -1.0)
    out = -1.0;
  else if (out > 1.0)
    out = 1.0;
  out *= freqplfo;
  return ((1 + out) * 0.5);

}


float
HOR::LFO (float t)
{

  float out;


  xx += LFOspeed * incre;

  if (xx > 1)
    xx = 0;

  out = Fsin (xx * D_PI);

  if (out < -1.0)
    out = -1.0;
  else if (out > 1.0)
    out = 1.0;
    return(out *= freqlfo);

      
};






void
HOR::MiraNota (int nota)
{
  int l;

  l = note[nota] + transpose + 12;
  freq_note =
    (pitch >
     0) ? h[l].f2 + (h[l].f3 - h[l].f2) * pitch : h[l].f2 + (h[l].f2 -
							     h[l].f1) * pitch;

  partial = mastertune * freq_note * lalapi;

};


void
HOR::Alg1s (int nframes, void *)
{
 
  int l1, l2, i, kk = 0;
  float soundr,soundl = 0;

  memset (buf, 0, PERIOD8);

  freqplfo = modulation * LFOpitch * lalapi;




  for (l2 = 0; l2 < POLY; l2++)
    {

      if (note_active[l2])
	{
	  MiraNota (l2);

	  Jenvelope (&note_active[l2], gate[l2], env_time[l2], l2);
	  aplfo = PLFO (env_time[l2]);
          miraalfo(l2); 
          
	  for (i = 1; i <= 20; i++)
	    {
	      volumeOpC (i, l2);
              f[i].dphi = partial * pitchOp (i, l2);
	      if (f[i].dphi > D_PI) f[i].dphi -= D_PI;
              
	    }



	  for (l1 = 0; l1 < PERIOD2; l1+= 2)
	    {

	      soundl = 0;
              soundr = 0;

	      for (i = 1; i <= 20; i++)
		{

               if (Operator[i].con1 > 0)
                 {
		  f[i].phi[l2] += f[i].dphi;
		  if (f[i].phi[l2] > D_PI) f[i].phi[l2] -= D_PI;
		  if (i<11) soundl += Operator[i].con1 * Fsin (f[i].phi[l2]);
                  else soundr += Operator[i].con1 * Fsin (f[i].phi[l2]);                
		 }
                }
	      buf[l1] += soundl*master;
              buf[l1+1] += soundr*master;
	      env_time[l2] += incre;
	    }

	}


    }

  if (choron == 1)
    bchorus ();
  if (rota == 1)
    rotary ();
  if (echoon == 1)
    procesa ();
  if (revon == 1)
    reverb();
  if (riton == 1) 
   CogeRitmo();
  



Salidafinal();



  switch (Salida)
    {
    case 1:
      write (snd_handle, wbuf, PERIOD8);
      break;
    case 2:
      kk = snd_pcm_writei (playback_handle, wbuf, PERIOD2);
      if (kk < (PERIOD2))
	snd_pcm_prepare (playback_handle);
      break;
    }


   return;
};


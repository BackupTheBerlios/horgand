#include "Holrgan.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>


pthread_mutex_t mutex;
int l1, i, j, k, Pexitprogram, vum, vumvum, espera,
UndoCount,programa,vavi,pr,pr1,tum,cambialo;
char NombreAcorde[16];
int solucion,Rit;
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



  for (i = 1; i <= 6; i++)
    {
      Operator[i].harmonic_fine = 0.0;
      Operator[i].volumen = 0.0;
    }

  Operator[1].harmonic = 3;
  Operator[2].harmonic = 5;
  Operator[3].harmonic = 8;
  Operator[4].harmonic = 11;
  Operator[5].harmonic = 14;
  Operator[6].harmonic = 22;


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
      for (i = 1; i <= 6; i++)
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

      for (i = 1; i <= 6; i++)
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

      for (i = 1; i <= 6; i++)
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




  lsin = (float *) malloc (sizeof (float) * 10000);
  nsin = (float *) malloc (sizeof (float) * 10000);
  memset (lsin, 0, 10000);
  memset (nsin, 0, 10000);



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


  for (i = 1; i <= 140; i++)
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


void 

HOR::MiraChord()
{
int i,j;
int anote[POLY];
int onote[POLY];
int nnotes=0;
int posi = 0;
int baja,ubaja;
int pafuera=0;
int busca=0;
int di1,di2,di3,di4;
char AName[16];


chord = 0;
for (i=0; i<=POLY; i++) 
	{
	if (( note_active[i] == 1) && (rnote[i] < 60))
		{
 		anote[nnotes] = rnote[i];
 		nnotes++;
		}
	}



if ((nnotes < 3) || (nnotes > 5) ) return;

while(posi<nnotes)
{
        baja=400;

	for (i=0; i<nnotes; i++)
	{
 	if (anote[i] <= baja)
		{ 
		onote[posi] = anote[i];
                ubaja=baja;	
        	baja = anote[i];
                pafuera = i;
                }
        }
        baja = ubaja;
        anote[pafuera]= 1000;
        posi++;
}


if (nnotes == 3)
   {

	di1=onote[1] - onote[0];
	di2=onote[2] - onote[1];

	j =0;

 	while(busca==0)

	{
	j++;
	if ((Chord3[j].di1 == di1) && (Chord3[j].di2 == di2))
		{ 
    			busca = 1;
    			chord = j;
                        ctipo = Chord3[j].tipo;
                        break;
		}    
 
        if (j > 14 ) break;
	}

	if (chord != 0)
	{
	
   	        int elke = onote[Chord3[chord].fund-1];
                fundi = elke % 12;
		sprintf(AName,"%s%s",NC[fundi].Nom,Chord3[chord].Nom);
                
                if (strcmp(AName, NombreAcorde) != 0)
                { 
                strcpy(NombreAcorde,AName);
                cambialo = 1;
		}
	}
     return;
   }

if (nnotes == 4)
   {

        di1=onote[1] - onote[0];
        di2=onote[2] - onote[1];
        di3=onote[3] - onote[2];
        j =0;

        while(busca==0)

        {
        j++;
        if ((Chord4[j].di1 == di1) && (Chord4[j].di2 == di2) && (Chord4[j].di3 == di3))
                {
                        busca = 1;
                        chord = j;
                        ctipo = Chord4[j].tipo;
                        break;
                }

        if (j > 46 ) break;
        }

        if (chord != 0)
        {
                int elke = onote[Chord4[chord].fund-1];
                fundi = elke % 12;
                sprintf(AName,"%s%s",NC[fundi].Nom,Chord4[chord].Nom);
                if (strcmp(AName, NombreAcorde) != 0)
                {
                strcpy(NombreAcorde,AName);
                cambialo = 1;
                }

                
        }
        return;

   }

if (nnotes == 5)
   {

        di1=onote[1] - onote[0];
        di2=onote[2] - onote[1];
        di3=onote[3] - onote[2];
        di4=onote[4] - onote[3];
        j =0;

        while(busca==0)

        {
        j++;
        if ((Chord5[j].di1 == di1) && (Chord5[j].di2 == di2) && (Chord5[j].di3 == di3) && (Chord5[j].di4 == di4))
                {
                        busca = 1;
                        chord = j;
                        ctipo = Chord5[j].tipo;
                        break;
                }

        if (j > 9 ) break;
        }

        if (chord != 0)
        {
                int elke = onote[Chord5[chord].fund-1];
                fundi = elke % 12;
                sprintf(AName,"%s%s",NC[fundi].Nom,Chord5[chord].Nom);
                if (strcmp(AName, NombreAcorde) != 0)
                {
                strcpy(NombreAcorde,AName);
                cambialo = 1;
                }

                
        }

   }




};

void 
HOR::MiraTempo()

{

int i;

pos = (int) ((tempo * cuenta) / fracpos) + 1;
if (pos == 1)  tum = 127; else tum = 0;
for (i=1; i<=bars; i++) if (pos== 4*blackn) tum = 127;


};


void 

HOR:: MiraLinea()
{

int readcounts,lanota;

  
  if ((linb[pos] == 0) && (basspending == 0)) return; 

  if ( pos != lpos)
	{
        lpos = pos;
        if (linb[pos] != 0)
        {
        if (split == 1) MiraChord();
        lanota = linb[pos];
        if (lanota == 5 ) lanota += TCh[ctipo].ter;
        if (lanota == 8 ) lanota += TCh[ctipo].qui;
        if (lanota == 12 ) lanota += TCh[ctipo].sep;
 
	bnote = btrans + lanota - 1 + fundi;
        velobass = linbv[pos] / 100.0;
        if (bnote > 11) bnote -= 12;
        if (bnote < 0 ) bnote += 12;
        afina = AB[bnote].afin+AB[bnote].bmt;
        readcounts = sf_seek (infileb, 0, SEEK_SET);
        basspending = 1;
	CogeBass();
        }
	}
  if (basspending == 1 ) CogeBass();

};





int

HOR::SelectRitmo(char *nomrit)
{

   
   if (! (infile = sf_open (nomrit, SFM_READ, &sfinfo)))
{
        printf ("Not able to open input file %s.\n", nomrit);
        fe = 0;
        return(1);
}
fe = 1;       
return(0);
};

void

HOR::SelectBass(char *nombass)
{

   
   if (! (infileb = sf_open (nombass, SFM_READ, &sfinfob)))
        printf ("Not able to open input file %s.\n", nombass) ;
        
      

};


void
HOR::ponpe ()
{
  PERIOD2 = PERIOD * 2;
  PERIOD4 = PERIOD * 4;
  PERIOD8 = PERIOD * 8;
};



void
HOR::CogeBass()
{
float l, r, rl, rr;
int j,readcounts,readcountr;
int longi;

memset (bbuf, 0, PERIOD8);


longi  = (int) (afina * PERIOD);

readcounts = sf_seek (infileb, 0, SEEK_CUR); 
readcountr = sf_readf_float (infileb, bbuf, longi);

if ((readcounts + longi ) < framesbass) 

basspending = 1; 

else basspending = 0; 


 for (i = 0; i < PERIOD2; i +=2)
    {

      j = (int) (i * afina);
      if (j % 2 != 0) j++;

      l = buf[i];
      r = buf[i+1];

       if (l < -1.0)
        l = -1.0;
      else if (l > 1.0)
        l = 1.0;
      if (r < -1.0)
        r = -1.0;
      else if (r > 1.0)
        r = 1.0;
     

      rl = bbuf[j];
      rr = bbuf[j+1];     
 
      if (rl < -1.0)
        rl = -1.0;
      else if (rl > 1.0)
        rl = 1.0;
 
       if (rl < -1.0)
        rl = -1.0;
      else if (rl > 1.0)
        rl = 1.0;
     

     buf[i] =  l  + (rl * bassvol * velobass);
     buf[i+1] =  r  + (rr * bassvol * velobass);


      }


};



void HOR::CogeRitmo() { float l, r, rl, rr; 
int j,readcountr,falta; 
int ftempo;

memset (rbuf, 0, PERIOD8);


ftempo  = (int) (tempo * PERIOD);

MiraTempo();
if (basson == 1 ) MiraLinea();

cuenta  = sf_seek (infile, 0, SEEK_CUR);
readcountr = sf_readf_float (infile, rbuf, ftempo);

if (readcountr < ftempo)

{

falta = ftempo - readcountr;
cuenta = sf_seek (infile, 0, SEEK_SET);
readcountr = sf_readf_float (infile, rbuf, falta);

}


 for (i = 0; i < PERIOD2; i += 2)
    {

      j = (int) (i * tempo);
      if (j % 2 != 0) j++; 
     
      l = buf[i];
      r = buf[i+1];
      
       if (l < -1.0)
        l = -1.0;
      else if (l > 1.0)
        l = 1.0;
      if (r < -1.0)
        r = -1.0;
      else if (r > 1.0)
        r = 1.0;

 
      rl = rbuf[j];
      rr = rbuf[j+1];     
 
      if (rl < -1.0)
        rl = -1.0;
      else if (rl > 1.0)
        rl = 1.0;
      if (rr < -1.0)
        rr = -1.0;
      else if (rr > 1.0)
        rr = 1.0;
     

     buf[i] =  (l  + (rl * ritvol)) * 0.5;
     buf[i+1] =  (r + (rr * ritvol)) * 0.5;

      }

};


void
HOR::Salidafinal ()
{
  int j;
  float l, r;
  short sl, sr;
  memset (wbuf, 0, PERIOD8);
  
  
  for (i = 0; i < PERIOD2; i += 2)
    {

      j = 2 * i;
            
      l = buf[i];
      r = buf[i+1];
      
      sl = (short) (l * 32767.0);
      sr = (short) (r * 32767.0);

      wbuf[j] = sl;
      wbuf[j + 1] = sr;
      wbuf[j + 2] = sl;
      wbuf[j + 3] = sr;

    }
};



// OSS AUDIO OUT

void
HOR::ossaudioprepare ()
{

  int snd_bitsize = 16;
  snd_fragment = 0x00080009;
  snd_stereo = 1;
  snd_format = AFMT_S16_LE;
  snd_samplerate = SAMPLE_RATE;
  PERIOD = MPERIOD;
  ponpe ();
  snd_handle = open ("/dev/dsp", O_WRONLY, 0);
  if (snd_handle == -1)
    {
      fprintf (stderr, "ERROR - I can't open  /dev/dsp \n");
      return;
    };
  ioctl (snd_handle, SNDCTL_DSP_RESET, NULL);

  ioctl (snd_handle, SNDCTL_DSP_SETFMT, &snd_format);
  ioctl (snd_handle, SNDCTL_DSP_STEREO, &snd_stereo);
  ioctl (snd_handle, SNDCTL_DSP_SPEED, &snd_samplerate);
  ioctl (snd_handle, SNDCTL_DSP_SAMPLESIZE, &snd_bitsize);
  ioctl (snd_handle, SNDCTL_DSP_SETFRAGMENT, &snd_fragment);


};

// ALSA AUDIO OUT

void
HOR::alsaaudioprepare ()
{
  char pcm_name[50];
  sprintf (pcm_name, "plughw:0,0");


  if (snd_pcm_open (&playback_handle, pcm_name, SND_PCM_STREAM_PLAYBACK, 0) <
      0)
    {
      fprintf (stderr, "cannot open audio device %s\n", pcm_name);
      exit (1);
    }
  PERIOD = MPERIOD;
  ponpe ();
  snd_pcm_hw_params_alloca (&hw_params);
  snd_pcm_hw_params_any (playback_handle, hw_params);
  snd_pcm_hw_params_set_access (playback_handle, hw_params,
				SND_PCM_ACCESS_RW_INTERLEAVED);
  snd_pcm_hw_params_set_format (playback_handle, hw_params,
				SND_PCM_FORMAT_S16_LE);
  snd_pcm_hw_params_set_rate (playback_handle, hw_params, SAMPLE_RATE, 0);
  snd_pcm_hw_params_set_channels (playback_handle, hw_params, 2);

  snd_pcm_hw_params_set_periods (playback_handle, hw_params, 2, 0);
  snd_pcm_hw_params_set_period_size (playback_handle, hw_params, PERIOD2, 0);
  snd_pcm_hw_params (playback_handle, hw_params);
  snd_pcm_sw_params_alloca (&sw_params);
  snd_pcm_sw_params_current (playback_handle, sw_params);
  snd_pcm_sw_params_set_avail_min (playback_handle, sw_params, PERIOD2);
  snd_pcm_sw_params (playback_handle, sw_params);


};

// JACK Audio


void
HOR::jackaudioprepare ()
{

  jackclient = jack_client_new ("Horgand");
  if (jackclient == 0)
    {
      fprintf (stderr, "Cannot make a jack client\n");
      exit (1);
    };
  fprintf (stderr, "Internal SampleRate   = %d\nJack Output SampleRate= %d\n",
	   SAMPLE_RATE, jack_get_sample_rate (jackclient));
  if ((unsigned int) jack_get_sample_rate (jackclient) !=
      (unsigned int) SAMPLE_RATE)
    fprintf (stderr,
	     "It is recomanded that the both samplerates to be equal.\n");



  jack_set_process_callback (jackclient, jackprocess, 0);
  PERIOD = jack_get_buffer_size (jackclient);
  PERIOD /= 2;
  ponpe ();
  outport_left = jack_port_register (jackclient, "out_1",
				     JACK_DEFAULT_AUDIO_TYPE,
				     JackPortIsOutput | JackPortIsTerminal,
				     0);
  outport_right =
    jack_port_register (jackclient, "out_2", JACK_DEFAULT_AUDIO_TYPE,
			JackPortIsOutput | JackPortIsTerminal, 0);

  if (jack_activate (jackclient))
    {
      fprintf (stderr, "Cannot activate jack client\n");
      exit (1);
    };


  jack_connect (jackclient, jack_port_name (outport_left),
		"alsa_pcm:playback_1");
  jack_connect (jackclient, jack_port_name (outport_right),
		"alsa_pcm:playback_2");

};



float
HOR::fastabs (float f)
{
  int i = ((*(int *) &f) & 0x7fffffff);
  return (*(float *) &i);

};


float
HOR::Fsin (float x)
{

  if (x >= 0) return (lsin[(int) (x * 1000)]); else return (nsin[(int) (x * 1000)]);

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


void
HOR::bchorus ()
{

  long elkel, elker, elkel2, elker2;
  float valorl, valorr;
  float dll1, dlr1;
  float dell, delr;
  float dllo;
  long aeperhis;
  int j;

  efreqlfo = 8 * modulation * ELFOamplitude * lalapi;



  for (i = 0; i < PERIOD2; i +=2)
    {
      ehistoryl[eperhis] = buf[i];
      ehistoryr[eperhis] = buf[i + 1];
      if (++eperhis > 32800)
	eperhis = 0;
    }

  aeperhis = eperhis - PERIOD;

  for (i = 0; i < PERIOD; i++)

    {
      j = 2 * i;

      ldelay1 = ldelay;
      rdelay1 = rdelay;

      dll1 = ELFO (&xel);
      dlr1 = ELFO (&xer);


      ldelay = PERIOD2 + (dll1 * popo);
      rdelay = PERIOD2 + (dlr1 * popo);
      dell = (ldelay1 * (PERIOD - i) + ldelay * i) / PERIOD;
      delr = (rdelay1 * (PERIOD - i) + rdelay * i) / PERIOD;


      dllo = 1.0 - fmod (dell, 1.0);

      elkel = (long) (aeperhis + i - dell);
      
      if (elkel < 0)
	elkel += 32800;
      if (elkel > 32800)
	elkel -= 32800;
      elkel2 = elkel - 1;
      if (elkel2 < 0)
	elkel2 += 32800;
      if (elkel2 > 32800)
	elkel2 -= 32800;
      valorl = ehistoryl[elkel] * dllo + ehistoryl[elkel2] * (1 - dllo);
      buf[j] = (buf[j] * (1 - chorvol)) + (valorl * chorvol);

      dllo = 1.0 - fmod (delr, 1.0);
   
      elker = (long) (aeperhis + i - delr);
      if (elker < 0)
	elker += 32800;
      if (elker > 32800)
	elker -= 32800;
      elker2 = elker - 1;
      if (elker2 < 0)
	elker2 += 32800;
      if (elker2 > 32800)
	elker2 -= 32800;
      valorr = ehistoryr[elker] * dllo + ehistoryr[elker2] * (1 - dllo);
      buf[j + 1] = (buf[j + 1] * (1 - chorvol)) + (valorr * chorvol);


    }
};


void
HOR::rotary ()
{
  
  float a, l, r;
  freqlfo = 8 * modulation * LFOamplitude * lalapi;

  for (i = 0; i <PERIOD2; i +=2)
    {

      a = LFO (xx) / 3.0;

      l = buf[i];
      r = buf[i + 1];


      buf[i] -= l * a;
      buf[i + 1] += r * a;


    }
};


void
HOR::reverb ()

{
  
  long elke, elke1;
  float tmp=0;
  float tmprvol=0;
  float tmprvol1=0;
  float bufl;
  float bufr;
  float efxoutl;
  float efxoutr;
  float stmp; 
  
    
  
  for (i = 0; i <PERIOD2; i +=2)

    {

  bufl = buf[i];
  bufr = buf[i+1];
  efxoutl = 0;
  efxoutr = 0;
  stmp = 0;

  for (j = 0; j<=15; j++)
    {
 
   
      elke = rperhis - ((long) (combl[j] * rtime));
      if (elke % 2 != 0) elke = elke + 1;
      if (elke < 0) elke = 524800 + elke;

      elke1 = rperhis  - ((long) (combr[j]  * rtime));
      if (elke1 % 2 == 0) elke1 = elke1 + 1; 
      if (elke1 < 0) elke1 = 524800 + elke1;
 
      tmp = diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 7 ) capsg = 0;
      efxoutl += rhistory[elke] * stmp;

      tmp = diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 7 ) capsg = 0;
      efxoutr += rhistory[elke1] * stmp;
 
     }
      
      tmprvol =  stmp * revvol;
      tmprvol1 = 1 - tmprvol;
         
  
      buf[i] = (bufl * tmprvol1) + (efxoutl * tmprvol);
      rhistory[rperhis] = buf[i];
      if (++rperhis > 524800) rperhis = 0;
      buf[i + 1] = (bufr * tmprvol1) + (efxoutr * tmprvol);
      rhistory[rperhis] = buf[i + 1]; 
      if (++rperhis > 524800) rperhis = 0;

     }
};



void
HOR::procesa ()
{
  
  long elke, elke1;
  long delay = (long) echodelay;
  float voll, volr;
  float echovolr, echovoll;

  voll = 1 - lado;
  volr = 1 - voll;
  echovoll = voll * echovol;
  echovolr = volr * echovol;


  for (i = 0; i <PERIOD2; i +=2)

    {
      
      elke = perhis - delay;
      if (elke % 2 != 0) elke = elke + 1;
      if (elke < 0)
	elke = 524800 + elke;
      elke1 = elke + 1;
      if (elke1 < 0)
	elke1 = 524800 + elke1;

      buf[i] = (buf[i] * (1 - echovoll)) + (history[elke] * echovoll);
      history[perhis] = buf[i];
      if (++perhis > 524800)
	perhis = 0;

      buf[i + 1] =
	(buf[i + 1] * (1 - echovolr)) + (history[elke1] * echovolr);
      history[perhis] = buf[i+1];
      if (++perhis > 524800)
	perhis = 0;
    }

  switch (hacia)
    {
    case 0:
      lado += 0.01;
      if (lado > 1)
	hacia = 1;
      break;
    case 1:
      lado -= 0.01;
      if (lado < 0)
	hacia = 0;
      break;
    }
    
};

void
HOR::rclean()
{

memset (rhistory, 0, BUFSIZE * 1024);

};


void
HOR::procesaclean ()
{
  memset (history, 0, BUFSIZE * 1024);

};

void
HOR::chorusclean ()
{
  memset (ehistoryl, 0, BUFSIZE * 128);
  memset (ehistoryr, 0, BUFSIZE * 128);

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
HOR::midievents (int keIN)
{


  snd_seq_event_t *midievent;

  midievent = NULL;
  snd_seq_event_input (MidiInPuerto[keIN].midi_in, &midievent);
  if (midievent == NULL)
    return;


  switch (midievent->type)
    {
    case SND_SEQ_EVENT_PITCHBEND:
      pitch = (float) midievent->data.control.value / 8192.0;
      break;

    case SND_SEQ_EVENT_PGMCHANGE:


      if ((midievent->data.control.value > 0)
	  && (midievent->data.control.value < 33))
	programa = midievent->data.control.value;


      break;


    case SND_SEQ_EVENT_CONTROLLER:

      if (midievent->data.control.param == 1)
	modulation = (float) midievent->data.control.value / 12.7;

      if (midievent->data.control.param == 7)
	master = (float) midievent->data.control.value / 127.0;

      if (midievent->data.control.param == 64)
	{
	  if (midievent->data.control.value < 64)
	    pedal = 0;
	  if (midievent->data.control.value > 63)
	    pedal = 1;
	}



      break;




    case SND_SEQ_EVENT_NOTEON:

      if (midievent->data.note.velocity != 0)
	{
	  for (l1 = 0; l1 < POLY; l1++)
	    {
	      if (!note_active[l1])
		{
		  rnote[l1] = midievent->data.note.note;
		  note[l1] = rnote[l1];
		  vumvum = vum;
		  vum = midievent->data.note.velocity;
		  velocity[l1] = midievent->data.note.velocity / 127.0;

		  if ((split == 1) && (rnote[l1] < 60))
		    {
                     
		      note[l1] += 24;
		      velocity[l1] /= 2;
		    }

		  env_time[l1] = 0;
		  gate[l1] = 1;
		  note_active[l1] = 1;
                  MiraChord();
                  break;
		}
	    }
	  break;
	}
      else
	{
	  vumvum = vum;
	  vum = 0;
	  for (l1 = 0; l1 < POLY; l1++)
	    {

	      if (gate[l1] && note_active[l1]
		  && (rnote[l1] == midievent->data.note.note))
		{
		  env_time[l1] = 0;
		  gate[l1] = 0;
                  MiraChord();
		}

	    }
	}
      break;

    case SND_SEQ_EVENT_NOTEOFF:

      vumvum = vum;
      vum = 0;
      for (l1 = 0; l1 < POLY; l1++)
	{

	  if (gate[l1] && note_active[l1]
	      && (rnote[l1] == midievent->data.note.note))
	    {
	      env_time[l1] = 0;
	      gate[l1] = 0;
              MiraChord();
	    }

	}
      break;
    }

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
	  envi[nota] *= (1.0 - t / release);
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

  l = note[nota] + transpose;

  freq_note =
    (pitch >
     0) ? h[l].f2 + (h[l].f3 - h[l].f2) * pitch : h[l].f2 + (h[l].f2 -
							     h[l].f1) * pitch;

  partial = mastertune * freq_note * lalapi;

};



void
HOR::savefile (char *filename)
{


  FILE *fn;
  char buf[2048];
  fn = fopen (filename, "w");
  for (i = 1; i <= 6; i++)
    {

      bzero (buf, sizeof (buf));
      sprintf (buf, "%d,%f,%f\n", Operator[i].harmonic,
	       Operator[i].harmonic_fine, Operator[i].volumen);



      fputs (buf, fn);
    }

  bzero (buf, sizeof (buf));
  sprintf (buf, "%f,%d,%f,%f,%f,%d,%f,%f\n",
	   master, transpose, PLFOspeed, PLFOdelay, LFOspeed, rota, LFOpitch,
	   modulation);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  sprintf (buf, "%f,%f,%f,%d,%f,%f\n", attack, revon, detune, echoon,
	   echodelay, echovol);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  sprintf (buf, "%d,%d,%f,%f,%f,%f,%f\n", split, choron, popo, ganmod,
	   ELFOspeed, ELFOamplitude, chorvol);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  fputs (nombre, fn);
  fputs ("\n", fn);
  fclose (fn);

};

void
HOR::loadfile (char *filename)
{

  int i;
  FILE *fn;
  char buf[2048];

  if ((fn = fopen (filename, "r")) == NULL)
    return;


  for (i = 1; i <= 6; i++)
    {

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf, "%d,%f,%f", &Operator[i].harmonic,
	      &Operator[i].harmonic_fine, &Operator[i].volumen);




    }

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf (buf,
	  "%f,%d,%f,%f,%f,%d,%f,%f", &master, &transpose, &PLFOspeed,
	  &PLFOdelay, &LFOspeed, &rota, &LFOpitch, &modulation);

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf (buf, "%f,%f,%f,%d,%f,%f", &attack, &revon, &detune, &echoon,
	  &echodelay, &echovol);

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf
    (buf, "%d,%d,%f,%f,%f,%f,%f\n", &split, &choron, &popo, &ganmod,
     &ELFOspeed, &ELFOamplitude, &chorvol);

  bzero (buf, sizeof (buf));
  bzero (Name, sizeof (Name));
  fgets (buf, sizeof buf, fn);
  for (i = 0; i <= 24; i++)
    if (buf[i] > 20)
      Name[i] = buf[i];
  nombre = Name;
  fclose (fn);

};

void
HOR::savebank (char *filename)
{

  FILE *fn;
  char buf[2048];
  fn = fopen (filename, "w");

  for (j = 1; j <= 32; j++)
    {


      for (i = 1; i <= 6; i++)
	{

	  bzero (buf, sizeof (buf));
	  sprintf (buf, "%d,%f,%f\n",
		   Banco[j].Operator[i].harmonic,
		   Banco[j].Operator[i].harmonic_fine,
		   Banco[j].Operator[i].volumen);


	  fputs (buf, fn);
	}

      bzero (buf, sizeof (buf));
      sprintf (buf, "%f,%d,%f,%f,%f,%d,%f,%f\n",
	       Banco[j].master, Banco[j].transpose, Banco[j].PLFOspeed,
	       Banco[j].PLFOdelay, Banco[j].LFOspeed, Banco[j].rota,
	       Banco[j].LFOpitch, Banco[j].modulation);


      fputs (buf, fn);
      bzero (buf, sizeof (buf));
      sprintf (buf, "%f,%f,%f,%d,%f,%f\n", Banco[j].attack, Banco[j].revon,
	       Banco[j].detune, Banco[j].echoon, Banco[j].echodelay,
	       Banco[j].echovol);
      fputs (buf, fn);
      bzero (buf, sizeof (buf));
      sprintf
	(buf, "%d,%d,%f,%f,%f,%f,%f\n", Banco[j].split, Banco[j].choron,
	 Banco[j].popo, Banco[j].ganmod, Banco[j].ELFOspeed,
	 Banco[j].ELFOamplitude, Banco[j].chorvol);
      fputs (buf, fn);


      bzero (buf, sizeof (buf));
      for (i = 0; i <= 24; i++)
	buf[i] = Banco[j].Name[i];
      fputs (buf, fn);
      fputs ("\n", fn);
      fputs ("---\n", fn);
    }
  fclose (fn);

};


void
HOR::loadbank (char *filename)
{

  int i;
  FILE *fn;
  char buf[2048];

  if ((fn = fopen (filename, "r")) == NULL)
    return;
  for (j = 1; j <= 32; j++)
    {

      for (i = 1; i <= 6; i++)
	{

	  bzero (buf, sizeof (buf));
	  fgets (buf, sizeof buf, fn);

	  sscanf (buf, "%d,%f,%f",
		  &Banco[j].Operator[i].harmonic,
		  &Banco[j].Operator[i].harmonic_fine,
		  &Banco[j].Operator[i].volumen);

	}

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf,
	      "%f,%d,%f,%f,%f,%d,%f,%f", &Banco[j].master,
	      &Banco[j].transpose, &Banco[j].PLFOspeed, &Banco[j].PLFOdelay,
	      &Banco[j].LFOspeed, &Banco[j].rota, &Banco[j].LFOpitch,
	      &Banco[j].modulation);

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf,
	      "%f,%f,%f,%d,%f,%f", &Banco[j].attack, &Banco[j].revon,
	      &Banco[j].detune, &Banco[j].echoon, &Banco[j].echodelay,
	      &Banco[j].echovol);

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf
	(buf, "%d,%d,%f,%f,%f,%f,%f\n", &Banco[j].split, &Banco[j].choron,
	 &Banco[j].popo, &Banco[j].ganmod, &Banco[j].ELFOspeed,
	 &Banco[j].ELFOamplitude, &Banco[j].chorvol);




      bzero (buf, sizeof (buf));
      bzero (Banco[j].Name, sizeof (Banco[j].Name));
      fgets (buf, sizeof buf, fn);
      for (i = 0; i <= 24; i++)
	if (buf[i] > 20)
	  Banco[j].Name[i] = buf[i];
      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);

    }

  fclose (fn);
};


void
HOR::loadrhyt(char *filename)
{
   
   FILE *fs;
   char temp[1024];
   
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (filename, "r")) != NULL)
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
              for (i = 0; i <= (int) strlen(temp) - 2; i++) Rt[NumRit].Nom[i] = temp[i];                   
              break; 
             case 2:
              for (i = 0; i <= (int) strlen(temp) - 2; i++) Rt[NumRit].Nfile[i] = temp[i];
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




};


void
HOR::saverhyt(char *filename)
{
   
   FILE *fs;
   char temp[1024];
   int w=0;   
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (filename, "w")) != NULL)
   {     
     for(NumRit=1; NumRit<=20; NumRit++)
       {    
         bzero(temp,sizeof(temp));
         sprintf(temp,"%s\n",Rt[NumRit].Nom);
         fputs (temp, fs);        
         bzero(temp,sizeof(temp));           
         sprintf(temp,"%s\n",Rt[NumRit].Nfile);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf (temp,"%d\n", Rt[NumRit].bars);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf (temp,"%d\n", Rt[NumRit].blackn);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf(temp,"%d,%d,%d,%d\n",Rt[NumRit].linb[1],Rt[NumRit].linb[2],Rt[NumRit].linb[3],Rt[NumRit].linb[4]);
         fputs (temp, fs);
         for (i=1; i<Rt[NumRit].bars*Rt[NumRit].blackn; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              sprintf(temp,"%d,%d,%d,%d\n",Rt[NumRit].linb[w+1],Rt[NumRit].linb[w+2],Rt[NumRit].linb[w+3],Rt[NumRit].linb[w+4]);
              fputs (temp, fs);
             } 
             bzero(temp,sizeof(temp));
             sprintf(temp,"%d,%d,%d,%d\n",Rt[NumRit].linbv[1],Rt[NumRit].linbv[2],Rt[NumRit].linbv[3],Rt[NumRit].linbv[4]);
             fputs (temp, fs);

             for (i=1; i<Rt[NumRit].bars*Rt[NumRit].blackn; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              sprintf(temp,"%d,%d,%d,%d\n",Rt[NumRit].linbv[w+1],Rt[NumRit].linbv[w+2],Rt[NumRit].linbv[w+3],Rt[NumRit].linbv[w+4]);
              fputs (temp, fs);
             }
              for (j=1; j<=6; j++)
              {
              bzero(temp, sizeof(temp));
              sprintf(temp, "0\n");
              fputs(temp,fs);
              }
          }
     fclose(fs);
  }
};









void
HOR::New ()
{

  for (i = 1; i <= 6; i++)
    {

      Operator[i].harmonic_fine = 0.0;
      Operator[i].volumen = 0.0;

    }

  Operator[1].harmonic = 3;
  Operator[2].harmonic = 5;
  Operator[3].harmonic = 8;
  Operator[4].harmonic = 11;
  Operator[5].harmonic = 14;
  Operator[6].harmonic = 22;

  attack = 0.02;
  decay = 0.00;
  echoon = 0;
  echodelay = 0;
  echovol = 0;
  PLFOspeed = 0;
  PLFOdelay = 0;
  LFOspeed = 0;
  LFOpitch = 0;
  modulation = 10;
  transpose = 0;
  rota = 0;
  pitch = 0;
  pedal = 0;
  master = 0.70;
  detune = 0;
  split = 0;
  chorvol = 0.60;
  choron = 0;
  ELFOspeed = 0;
  ELFOamplitude = 0;
  popo = 0;
  ganmod = 1;
  revon = 0;
  bzero (Name, sizeof (Name));
  nombre = Name;
}


void
HOR::Alg1s (int nframes, void *)
{

  int l1, l2, i, kk = 0;

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
          
	  for (i = 1; i <= 6; i++)
	    {
	      volumeOpC (i, l2);
             
              if (Operator[i].con1 > 0)
              {
	      f[i].dphi = partial * pitchOp (i, l2);
	      if (f[i].dphi > D_PI)
		f[i].dphi -= D_PI;
            }
	    }



	  for (l1 = 0; l1 < PERIOD2; l1++)
	    {

	      sound = 0;

	      for (i = 1; i <= 6; i++)
		{

               if (Operator[i].con1 > 0)
                 {
		  f[i].phi[l2] += f[i].dphi;
		  if (f[i].phi[l2] > D_PI)
		    f[i].phi[l2] -= D_PI;
		   sound += Operator[i].con1 * Fsin (f[i].phi[l2]);
		 }
                }
	      buf[l1] += sound * master;

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


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
int l1, i, j, k, Pexitprogram, MidiInLevel, LastMidiInLevel, waitforGUI,
UndoCount,preset,Signal_for_Cb_Sliders,BarLead,changeNameChord;
char NameChord[16];
int prefix_trick,Selected_Rhythm,commandline;
const char *FilePreset;


HOR::HOR ()
{

  //Init de vars
  
  Selected_Rhythm = 0;
  waitforGUI = 0;
  rperhis = 130000;
  ldelay=0;
  rdelay=0;
  capsg=0;
  Master_Volume = 0.70;
  Organ_Master_Volume = 0.70;
  pattern_bars = 1;
  ae = 1;
  file_ok = 0;  
  cpreset=1;

// FM Operator frequencys

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



// Init FM Operators 

  for (i = 1; i <= 10; i++)
    {
      Operator[i].harmonic_fine = 0.0;
      Operator[i].volumen = 0.0;
      Operator[i].marimba = 0;
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
  

  prefix_trick = 0;
  mastertune = 1;
  attack = 0.001;
  decay = 0.20;
  sustain = 0.8;
  release = 0.12;
  E_Delay_On = 0;
  Delay_Delay = 0;
  Delay_Volume = 0;
  Rotary_LFO_Speed = 0;
  Pitch_LFO_Speed = 0;
  Pitch_LFO_Delay = 0;
  LFOpitch = 0;
  Rotary_LFO_Amplitude = 99;
  Keyb_Level_Scaling=1;
  modulation = 10;
  transpose = 0;
  pitch = 0;
  pedal = 0;
  UndoCount = 0;
  Stereo_Side = 0;
  To_Stereo_Side = 0;
  Rotary_X = 0;
  Chorus_X_L = 0.0;
  Chorus_X_L = 0.25;
  Chorus_LFO_Speed = 0;
  Chorus_Volume = 0.60;
  split = 0;
  Reverb_Preset = 1;
  E_Reverb_On = 0;
  Reverb_Time = 1.0;
  Reverb_Diffussion = 0.1;
  Reverb_Volume = 0.20;
  tempo = 2;
  Rhythm_Volume = 0.5;
  Bass_Volume = 0.5;
  basspending = 0;
  lpos = 100;
  length_bass_note = 2.0;
  changeNameChord = 0;

// Init Reverb Taps 

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


// Init Chord Names


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


//Init bass offsets to tune sample notes

AB[0].tune = 2.0;
AB[1].tune = 2.119;
AB[2].tune = 2.245;
AB[3].tune = 2.3785;
AB[4].tune = 2.519877;
AB[5].tune = 2.669724;
AB[6].tune = 2.828746;
AB[7].tune = 1.49847;
AB[8].tune = 1.587767;
AB[9].tune = 1.681957;
AB[10].tune = 1.782262;
AB[11].tune = 1.888073;



// Init Chord Types



//Maj7

TCh[1].third = 0;
TCh[1].five_th = 0;
TCh[1].seven_th = 0;

//7

TCh[2].third = 0;
TCh[2].five_th = 0;
TCh[2].seven_th = -1;

//-7

TCh[3].third = -1;
TCh[3].five_th = 0;
TCh[3].seven_th = -1;

//-7(b5)

TCh[4].third = -1;
TCh[4].five_th = -1;
TCh[4].seven_th = -1;

//dis

TCh[5].third = -1;
TCh[5].five_th = -1;
TCh[5].seven_th = -2;

//aug7

TCh[6].third = 0;
TCh[6].five_th = +1;
TCh[6].seven_th = -1;


//7Sus4

TCh[7].third = +1;
TCh[7].five_th = 0;
TCh[7].seven_th = -1;



// Init Chords (Distances between notes, type, Names)

// 3 Notes Chords

Chord3[1].type = 1;
Chord3[1].fund = 1;
Chord3[1].dist1  = 4;
Chord3[1].dist2  = 3;
strcpy(Chord3[1].Nom,"");

Chord3[2].type = 1;
Chord3[2].fund = 3;
Chord3[2].dist1  = 3;
Chord3[2].dist2  = 5;
strcpy(Chord3[2].Nom,"");

Chord3[3].type = 1;
Chord3[3].fund = 2;
Chord3[3].dist1  = 5;
Chord3[3].dist2  = 4;
strcpy(Chord3[3].Nom,"");

Chord3[4].type = 3;
Chord3[4].fund = 1;
Chord3[4].dist1  = 3;
Chord3[4].dist2  = 4;
strcpy(Chord3[4].Nom,"m");

Chord3[5].type = 3;
Chord3[5].fund = 3;
Chord3[5].dist1  = 4;
Chord3[5].dist2  = 5;
strcpy(Chord3[5].Nom,"m");

Chord3[6].type = 3;
Chord3[6].fund = 2;
Chord3[6].dist1  = 5;
Chord3[6].dist2  = 3;
strcpy(Chord3[6].Nom,"m");

Chord3[7].type = 5;
Chord3[7].fund = 1;
Chord3[7].dist1  = 3;
Chord3[7].dist2  = 3;
strcpy(Chord3[7].Nom,"°");

Chord3[8].type = 6;
Chord3[8].fund = 1;
Chord3[8].dist1  = 4;
Chord3[8].dist2  = 4;
strcpy(Chord3[8].Nom,"+");

Chord3[9].type = 1;
Chord3[9].fund = 1;
Chord3[9].dist1  = 2;
Chord3[9].dist2  = 5;
strcpy(Chord3[9].Nom,"2");

Chord3[10].type = 1;
Chord3[10].fund = 3;
Chord3[10].dist1  = 3;
Chord3[10].dist2  = 2;
strcpy(Chord3[10].Nom,"");

Chord3[11].type = 4;
Chord3[11].fund = 2;
Chord3[11].dist1  = 6;
Chord3[11].dist2  = 3;
strcpy(Chord3[11].Nom,"m(b5)");


Chord3[12].type = 2;
Chord3[12].fund = 1;
Chord3[12].dist1  = 4;
Chord3[12].dist2  = 6;
strcpy(Chord3[12].Nom,"7");

Chord3[13].type = 3;
Chord3[13].fund = 1;
Chord3[13].dist1  = 3;
Chord3[13].dist2  = 7;
strcpy(Chord3[13].Nom,"m7");

Chord3[14].type = 3;
Chord3[14].fund = 1;
Chord3[14].dist1  = 3;
Chord3[14].dist2  = 6;
strcpy(Chord3[14].Nom,"m6");



// 4 Notes Chords

Chord4[1].type = 1;
Chord4[1].fund = 1;
Chord4[1].dist1  = 4;
Chord4[1].dist2  = 3;
Chord4[1].dist3  = 4;
strcpy(Chord4[1].Nom,"Maj7");

Chord4[2].type = 3;
Chord4[2].fund = 1;
Chord4[2].dist1  = 3;
Chord4[2].dist2  = 4;
Chord4[2].dist3  = 3;
strcpy(Chord4[2].Nom,"m7");

Chord4[3].type = 2;
Chord4[3].fund = 1;
Chord4[3].dist1  = 4;
Chord4[3].dist2  = 3;
Chord4[3].dist3  = 3;
strcpy(Chord4[3].Nom,"7");

Chord4[4].type = 4;
Chord4[4].fund = 1;
Chord4[4].dist1  = 3;
Chord4[4].dist2  = 3;
Chord4[4].dist3  = 4;
strcpy(Chord4[4].Nom,"m7(b5)");

Chord4[5].type = 5;
Chord4[5].fund = 1;
Chord4[5].dist1  = 3;
Chord4[5].dist2  = 3;
Chord4[5].dist3  = 3;
strcpy(Chord4[5].Nom,"°7");

Chord4[6].type = 6;
Chord4[6].fund = 1;
Chord4[6].dist1  = 4;
Chord4[6].dist2  = 4;
Chord4[6].dist3  = 2;
strcpy(Chord4[6].Nom,"+7");

Chord4[7].type = 1;
Chord4[7].fund = 1;
Chord4[7].dist1  = 4;
Chord4[7].dist2  = 3;
Chord4[7].dist3  = 5;
strcpy(Chord4[7].Nom,"");

Chord4[8].type = 1;
Chord4[8].fund = 1;
Chord4[8].dist1  = 4;
Chord4[8].dist2  = 3;
Chord4[8].dist3  = 2;
strcpy(Chord4[8].Nom,"6");

Chord4[9].type = 7;
Chord4[9].fund = 1;
Chord4[9].dist1  = 5;
Chord4[9].dist2  = 2;
Chord4[9].dist3  = 3;
strcpy(Chord4[9].Nom,"7(Sus4)");

Chord4[10].type = 3;
Chord4[10].fund = 1;
Chord4[10].dist1  = 3;
Chord4[10].dist2  = 4;
Chord4[10].dist3  = 4;
strcpy(Chord4[10].Nom,"m(Maj7)");

Chord4[11].type = 3;
Chord4[11].fund = 1;
Chord4[11].dist1  = 3;
Chord4[11].dist2  = 4;
Chord4[11].dist3  = 2;
strcpy(Chord4[11].Nom,"m6");

Chord4[12].type = 6;
Chord4[12].fund = 1;
Chord4[12].dist1  = 4;
Chord4[12].dist2  = 4;
Chord4[12].dist3  = 4;
strcpy(Chord4[12].Nom,"+(Maj7)");

Chord4[13].type = 1;
Chord4[13].fund = 1;
Chord4[13].dist1  = 2;
Chord4[13].dist2  = 4;
Chord4[13].dist3  = 3;
strcpy(Chord4[13].Nom,"lyd");

Chord4[14].type = 1;
Chord4[14].fund = 4;
Chord4[14].dist1  = 3;
Chord4[14].dist2  = 4;
Chord4[14].dist3  = 1;
strcpy(Chord4[14].Nom,"Maj7");

Chord4[15].type = 1;
Chord4[15].fund = 4;
Chord4[15].dist1  = 3;
Chord4[15].dist2  = 3;
Chord4[15].dist3  = 2;
strcpy(Chord4[15].Nom,"7");

Chord4[16].type = 6;
Chord4[16].fund = 4;
Chord4[16].dist1  = 4;
Chord4[16].dist2  = 2;
Chord4[16].dist3  = 2;
strcpy(Chord4[16].Nom,"+7");

Chord4[17].type = 1;
Chord4[17].fund = 3;
Chord4[17].dist1  = 3;
Chord4[17].dist2  = 5;
Chord4[17].dist3  = 4;
strcpy(Chord4[17].Nom,"");

Chord4[18].type = 7;
Chord4[18].fund = 4;
Chord4[18].dist1  = 2;
Chord4[18].dist2  = 3;
Chord4[18].dist3  = 2;
strcpy(Chord4[18].Nom,"7(Sus4)");


Chord4[19].type = 3;
Chord4[19].fund = 4;
Chord4[19].dist1  = 4;
Chord4[19].dist2  = 4;
Chord4[19].dist3  = 1;
strcpy(Chord4[19].Nom,"m(Maj7)");

Chord4[20].type = 6;
Chord4[20].fund = 4;
Chord4[20].dist1  = 4;
Chord4[20].dist2  = 4;
Chord4[20].dist3  = 1;
strcpy(Chord4[20].Nom,"+(Maj7)");

Chord4[21].type = 1;
Chord4[21].fund = 3;
Chord4[21].dist1  = 4;
Chord4[21].dist2  = 1;
Chord4[21].dist3  = 4;
strcpy(Chord4[21].Nom,"Maj7");

Chord4[22].type = 3;
Chord4[22].fund = 3;
Chord4[22].dist1  = 3;
Chord4[22].dist2  = 2;
Chord4[22].dist3  = 3;
strcpy(Chord4[22].Nom,"m7");

Chord4[23].type = 2;
Chord4[23].fund = 3;
Chord4[23].dist1  = 3;
Chord4[23].dist2  = 2;
Chord4[23].dist3  = 4;
strcpy(Chord4[23].Nom,"7");

Chord4[24].type = 4;
Chord4[24].fund = 3;
Chord4[24].dist1  = 4;
Chord4[24].dist2  = 2;
Chord4[24].dist3  = 3;
strcpy(Chord4[24].Nom,"m7(b5)");

Chord4[26].type = 6;
Chord4[25].fund = 3;
Chord4[25].dist1  = 2;
Chord4[25].dist2  = 2;
Chord4[25].dist3  = 4;
strcpy(Chord4[25].Nom,"+7");

Chord4[26].type = 1;
Chord4[26].fund = 2;
Chord4[26].dist1  = 5;
Chord4[26].dist2  = 4;
Chord4[26].dist3  = 3;
strcpy(Chord4[26].Nom,"");

Chord4[27].type = 7;
Chord4[27].fund = 3;
Chord4[27].dist1  = 3;
Chord4[27].dist2  = 2;
Chord4[27].dist3  = 5;
strcpy(Chord4[27].Nom,"7(Sus4)");

Chord4[28].type = 2;
Chord4[28].fund = 3;
Chord4[28].dist1  = 4;
Chord4[28].dist2  = 2;
Chord4[28].dist3  = 3;
strcpy(Chord4[28].Nom,"m(Maj7)");

Chord4[29].type = 6;
Chord4[29].fund = 3;
Chord4[29].dist1  = 3;
Chord4[29].dist2  = 1;
Chord4[29].dist3  = 4;
strcpy(Chord4[29].Nom,"+(Maj7)");

Chord4[30].type = 1;
Chord4[30].fund = 2;
Chord4[30].dist1  = 1;
Chord4[30].dist2  = 4;
Chord4[30].dist3  = 3;
strcpy(Chord4[30].Nom,"Maj7");

Chord4[31].type = 3;
Chord4[31].fund = 2;
Chord4[31].dist1  = 2;
Chord4[31].dist2  = 3;
Chord4[31].dist3  = 4;
strcpy(Chord4[31].Nom,"m7");

Chord4[32].type = 4;
Chord4[32].fund = 2;
Chord4[32].dist1  = 2;
Chord4[32].dist2  = 3;
Chord4[32].dist3  = 3;
strcpy(Chord4[32].Nom,"m7(b5)");

Chord4[33].type = 6;
Chord4[33].fund = 2;
Chord4[33].dist1  = 2;
Chord4[33].dist2  = 4;
Chord4[33].dist3  = 4;
strcpy(Chord4[33].Nom,"+7");

Chord4[34].type = 2;
Chord4[34].fund = 4;
Chord4[34].dist1  = 6;
Chord4[34].dist2  = 3;
Chord4[34].dist3  = 5;
strcpy(Chord4[34].Nom,"7");

Chord4[35].type = 7;
Chord4[35].fund = 2;
Chord4[35].dist1  = 2;
Chord4[35].dist2  = 5;
Chord4[35].dist3  = 2;
strcpy(Chord4[35].Nom,"7(Sus4");

Chord4[36].type = 3;
Chord4[36].fund = 2;
Chord4[36].dist1  = 1;
Chord4[36].dist2  = 3;
Chord4[36].dist3  = 4;
strcpy(Chord4[36].Nom,"m(Maj7)");

Chord4[37].type = 6;
Chord4[37].fund = 2;
Chord4[37].dist1  = 1;
Chord4[37].dist2  = 4;
Chord4[37].dist3  = 4;
strcpy(Chord4[37].Nom,"+(Maj7)");

Chord4[38].type = 3;
Chord4[38].fund = 1;
Chord4[38].dist1  = 3;
Chord4[38].dist2  = 4;
Chord4[38].dist3  = 5;
strcpy(Chord4[38].Nom,"m");

Chord4[39].type = 3;
Chord4[39].fund = 3;
Chord4[39].dist1  = 4;
Chord4[39].dist2  = 5;
Chord4[39].dist3  = 3;
strcpy(Chord4[39].Nom,"m");

Chord4[40].type = 3;
Chord4[40].fund = 2;
Chord4[40].dist1  = 5;
Chord4[40].dist2  = 3;
Chord4[40].dist3  = 4;
strcpy(Chord4[40].Nom,"m");

Chord4[41].type = 1;
Chord4[41].fund = 1;
Chord4[41].dist1  = 2;
Chord4[41].dist2  = 2;
Chord4[41].dist3  = 3;
strcpy(Chord4[41].Nom,"9");

Chord4[42].type = 1;
Chord4[42].fund = 4;
Chord4[42].dist1  = 2;
Chord4[42].dist2  = 3;
Chord4[42].dist3  = 5;
strcpy(Chord4[42].Nom,"9");

Chord4[43].type = 1;
Chord4[43].fund = 3;
Chord4[43].dist1  = 3;
Chord4[43].dist2  = 5;
Chord4[43].dist3  = 2;
strcpy(Chord4[43].Nom,"9");


Chord4[44].type = 1;
Chord4[44].fund = 2;
Chord4[44].dist1  = 5;
Chord4[44].dist2  = 2;
Chord4[44].dist3  = 2;
strcpy(Chord4[44].Nom,"9");

Chord4[45].type = 4;
Chord4[45].fund = 1;
Chord4[45].dist1  = 3;
Chord4[45].dist2  = 3;
Chord4[45].dist3  = 5;
strcpy(Chord4[45].Nom,"m(Maj7)(b5)");

Chord4[46].type = 3;
Chord4[46].fund = 1;
Chord4[46].dist1  = 2;
Chord4[46].dist2  = 1;
Chord4[46].dist3  = 4;
strcpy(Chord4[46].Nom,"m7");



// 5 Notes Chords

Chord5[1].type = 1;
Chord5[1].fund = 1;
Chord5[1].dist1  = 2;
Chord5[1].dist2  = 2;
Chord5[1].dist3  = 3;
Chord5[1].dist4   = 4;
strcpy(Chord5[1].Nom,"Maj7/9");

Chord5[2].type = 7;
Chord5[2].fund = 3;
Chord5[2].dist1  = 3;
Chord5[2].dist2  = 2;
Chord5[2].dist3  = 2;
Chord5[2].dist4   = 3;
strcpy(Chord5[2].Nom,"7(Sus4)");

Chord5[3].type = 7;
Chord5[3].fund = 1;
Chord5[3].dist1  = 5;
Chord5[3].dist2  = 2;
Chord5[3].dist3  = 3;
Chord5[3].dist4   = 2;
strcpy(Chord5[3].Nom,"7(Sus4)");

Chord5[4].type = 2;
Chord5[4].fund = 3;
Chord5[4].dist1  = 3;
Chord5[4].dist2  = 2;
Chord5[4].dist3  = 2;
Chord5[4].dist4   = 2;
strcpy(Chord5[4].Nom,"7");

Chord5[5].type = 1;
Chord5[5].fund = 3;
Chord5[5].dist1  = 4;
Chord5[5].dist2  = 1;
Chord5[5].dist3  = 2;
Chord5[5].dist4   = 2;
strcpy(Chord5[5].Nom,"Maj7");

Chord5[6].type = 7;
Chord5[6].fund = 1;
Chord5[6].dist1  = 2;
Chord5[6].dist2  = 3;
Chord5[6].dist3  = 2;
Chord5[6].dist4   = 3;
strcpy(Chord5[6].Nom,"7(Sus4)");

Chord5[7].type = 7;
Chord5[7].fund = 1;
Chord5[7].dist1  = 2;
Chord5[7].dist2  = 3;
Chord5[7].dist3  = 2;
Chord5[7].dist4   = 5;
strcpy(Chord5[7].Nom,"7(Sus4)");

Chord5[8].type = 4;
Chord5[8].fund = 1;
Chord5[8].dist1  = 3;
Chord5[8].dist2  = 2;
Chord5[8].dist3  = 1;
Chord5[8].dist4   = 4;
strcpy(Chord5[8].Nom,"m7(b5)");

Chord5[9].type = 3;
Chord5[9].fund = 1;
Chord5[9].dist1  = 2;
Chord5[9].dist2  = 1;
Chord5[9].dist3  = 4;
Chord5[9].dist4   = 3;
strcpy(Chord5[9].Nom,"m7");






//Init Rhythm


for (j = 1; j<= 20; j++)

{ 
   strcpy(Rt[j].Nom,"Empty");
   strcpy(Rt[j].Nfile,"Empty");
   Rt[j].bars = 0;
   Rt[j].quarter_note = 0;
   for (i=0; i<=64; i++)
   {
    Rt[j].Line_Bass_Note[i] = 0;
    Rt[j].Line_Bass_Velocity[i]= 0;
   }
}


// Init Bank


  for (j = 1; j <= 32; j++)
    {
      for (i = 1; i <= 10; i++)
	{
	  Banco[j].Operator[i].harmonic = Operator[i].harmonic;
	  Banco[j].Operator[i].harmonic_fine = 0.0;
	  Banco[j].Operator[i].volumen = 0.0;
	}


      Banco[j].E_Delay_On = 0;
      Banco[j].Delay_Delay = 0;
      Banco[j].Delay_Volume = 0;
      Banco[j].Pitch_LFO_Speed = 0;
      Banco[j].Pitch_LFO_Delay = 0;
      Banco[j].Rotary_LFO_Speed = 0;
      Banco[j].LFOpitch = 0;
      Banco[j].E_Rotary_On = 0;
      Banco[j].modulation = 0;
      Banco[j].transpose = 0;
      Banco[j].Organ_Master_Volume = 0.70;
      Banco[j].attack = attack;
      Banco[j].detune = 0;
      Banco[j].E_Chorus_On = 0;
      Banco[j].split = 0;
      Banco[j].Chorus_LFO_Amplitude = 0;
      Banco[j].Chorus_LFO_Speed = 0;
      Banco[j].Chorus_Delay = 0;
      Banco[j].Reverb_Preset = 1;
      Banco[j].E_Reverb_On = 0;
      Banco[j].Chorus_Volume = 0.60;


    }



//  Init Undo/Redo

  for (j = 0; j <= 100; j++)
    {

      for (i = 1; i <= 10; i++)
	{
	  Undo[j].Operator[i].harmonic = Operator[i].harmonic;
	  Undo[j].Operator[i].harmonic_fine = 0.0;
	  Undo[j].Operator[i].volumen = 0.0;

	}

      Undo[j].E_Delay_On = 0;
      Undo[j].Delay_Delay = 0;
      Undo[j].Delay_Volume = 0;
      Undo[j].Pitch_LFO_Speed = 0;
      Undo[j].Pitch_LFO_Delay = 0;
      Undo[j].Rotary_LFO_Speed = 0;
      Undo[j].LFOpitch = 0;
      Undo[j].E_Rotary_On = 0;
      Undo[j].modulation = 0;
      Undo[j].transpose = 0;
      Undo[j].Organ_Master_Volume = 0.70;
      Undo[j].attack = attack;
      Undo[j].detune = 0;
      Undo[j].E_Chorus_On = 0;
      Undo[j].split = 0;
      Undo[j].Chorus_LFO_Amplitude = 0;
      Undo[j].Chorus_LFO_Speed = 0;
      Undo[j].Chorus_Delay = 0;
      Undo[j].Reverb_Preset = 1;
      Undo[j].E_Reverb_On = 0;
      Undo[j].Chorus_Volume = 0.60;


    }


// Init Initial state of Undo/Redo buffer

  for (j = 0; j <= 3; j++)
    {

      for (i = 1; i <= 10; i++)
	{
	  Prim[j].Operator[i].harmonic = Operator[i].harmonic;
	  Prim[j].Operator[i].harmonic_fine = 0.0;
	  Prim[j].Operator[i].volumen = 0.0;
	}



      Prim[j].E_Delay_On = 0;
      Prim[j].Delay_Delay = 0;
      Prim[j].Delay_Volume = 0;
      Prim[j].Pitch_LFO_Speed = 0;
      Prim[j].Pitch_LFO_Delay = 0;
      Prim[j].Rotary_LFO_Speed = 0;
      Prim[j].LFOpitch = 0;
      Prim[j].E_Rotary_On = 0;
      Prim[j].modulation = 0;
      Prim[j].transpose = 0;
      Prim[j].Organ_Master_Volume = 0.70;
      Prim[j].attack = attack;
      Prim[j].detune = 0;
      Prim[j].E_Chorus_On = 0;
      Prim[j].split = 0;
      Prim[j].Chorus_LFO_Amplitude = 0;
      Prim[j].Chorus_LFO_Speed = 0;
      Prim[j].Chorus_Delay = 0;
      Prim[j].Reverb_Preset = 1;
      Prim[j].E_Reverb_On = 0;
      Prim[j].Chorus_Volume = 0.30;





    }



  //ALSA init
  
  // Open Alsa Seq 
 
  snd_seq_open (&MidiInPuerto[1].midi_in, "default", SND_SEQ_OPEN_INPUT, 0);
  int alsaport = 0;
  char portname[50];

  // Create Alsa Seq Client
  
  sprintf (portname, "Horgand IN");
  alsaport = snd_seq_create_simple_port (MidiInPuerto[1].midi_in, portname,
					 SND_SEQ_PORT_CAP_WRITE |
					 SND_SEQ_PORT_CAP_SUBS_WRITE,
					 SND_SEQ_PORT_TYPE_SYNTH);



  // Init gated notes

  for (i = 0; i < POLY; i++)
    {
      note_active[i] = 0;
      env_time[i] = 0;
    }

  // Init frequency Notes 


  for (i = 1; i <= 192; i++)
    {
      h[i].f1 = 8.1757989156 * exp ((float) (i - 2) * log (2.0) / 12.0);
      h[i].f2 = 8.1757989156 * exp ((float) (i) * log (2.0) / 12.0);
      h[i].f3 = 8.1757989156 * exp ((float) (i + 2) * log (2.0) / 12.0);
    }


  // Allocate memory for calculated sins

  size_t sizesin = (size_t) (D_PI * 1000); 

  lsin = (float *) malloc (sizeof (float) * (sizesin + 4));

  memset (lsin, 0, sizesin);


   float x_sin;

   for (i = 0; i < (int) sizesin; i++)

    {
      x_sin = (float) ( i * D_PI / sizesin);
      lsin[i] = sin (x_sin);
      if( i > 0) lsin[i-1] = (lsin[i-1] *  ( 1.0 +  lsin[i] - lsin[i-1]));
      if( i > 1) lsin[i-2] = (lsin[i-2] *  ( 1.0 +  lsin[i-1] - lsin[i-2]));
      if( i > 2) lsin[i-3] = (lsin[i-3] *  ( 1.0 +  lsin[i-2] - lsin[i-3]));
      if( i > 3) lsin[i-4] = (lsin[i-4] *  ( 1.0 +  lsin[i-3] - lsin[i-4]));
      if( i > 4) lsin[i-5] = (lsin[i-5] *  ( 1.0 +  lsin[i-4] - lsin[i-5]));
      if( i > 5) lsin[i-6] = (lsin[i-6] *  ( 1.0 +  lsin[i-5] - lsin[i-6]));
      if( i > 6) lsin[i-7] = (lsin[i-7] *  ( 1.0 +  lsin[i-6] - lsin[i-7]));
      if( i > 7) lsin[i-8] = (lsin[i-8] *  ( 1.0 +  lsin[i-7] - lsin[i-8]));


    }


  // Init Sound and effect buffers


  wbuf = (short *) malloc (2 * sizeof (short) * BUFSIZE);
  rbuf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  bbuf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  buf = (float *) malloc (2 * sizeof (float) * BUFSIZE);
  history = (float *) malloc (2 * sizeof (float) * BUFSIZE * 512);

  memset (history, 0, BUFSIZE * 1024);


// Get config settings and init settings 

  FILE *fs;
  char temp[512];
  char nomfile[256];
  char nomfile1[256];
  sprintf (nomfile, "%s%s", getenv ("HOME"), "/.Horgand");
  if ((fs = fopen (nomfile, "r")) != NULL)
    {
      fgets (temp, sizeof temp, fs);
      
// Get MIDI IN Setting      
      
      for (i = 0; i <= (int) strlen(temp) - 2; i++)
      MidiInPuerto[1].SetMidiIn[i] = temp[i];
      MidiInPuerto[1].SMidiIn = MidiInPuerto[1].SetMidiIn;
      
// Get Audio Out Setting      
            
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

// Adjust some vars depend on Audio OUT

       increment = .5 / SAMPLE_RATE;
       D_PI_to_SAMPLE_RATE = D_PI / SAMPLE_RATE;

// Load Preset Bank File

      bzero(BankFilename, sizeof (BankFilename));
      bzero (temp, sizeof (temp));
      fgets (temp, sizeof temp, fs);
      if (strlen(temp)>2)
               {
                for (i = 0; i <= (int) strlen(temp) - 2; i++) BankFilename[i] = temp[i];
                loadbank(BankFilename);
               } 



    }


// Load Rhythm File

   bzero(nomfile, sizeof(nomfile));
   strcpy(nomfile, "/usr/share/horgand/Rhythm_List.txt");
   bzero(nomfile1, sizeof(nomfile1));
   strcpy(nomfile1, "/usr/local/share/horgand/Rhythm_List.txt");
   if ((fs = fopen (nomfile, "r")) != NULL)  prefix_trick = 1;
   if ((fs = fopen (nomfile1, "r")) != NULL) prefix_trick = 2;
   if (prefix_trick == 2 ) strcpy(nomfile, nomfile1); 
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (nomfile, "r")) != NULL)
   {
         int linea = 0;
         Num_Rhythm= 1;
         int w;    
      while (fgets(temp, sizeof temp, fs) != NULL)
          {
             linea++;
             switch (linea)
           { 
             case 1:
              bzero(Rt[Num_Rhythm].Nom, sizeof(Rt[Num_Rhythm].Nom));
              for (i=0;  i<=(int) strlen(temp) -2; i++) Rt[Num_Rhythm].Nom[i] = temp[i];                   
              break; 
             case 2:
              bzero(Rt[Num_Rhythm].Nfile, sizeof(Rt[Num_Rhythm].Nfile)); 
              for (i=0;  i<=(int) strlen(temp) -2; i++) Rt[Num_Rhythm].Nfile[i] = temp[i];
              break;
             case 3:
              sscanf (temp,"%d", &Rt[Num_Rhythm].bars);
              break;
             case 4:
              sscanf (temp,"%d", &Rt[Num_Rhythm].quarter_note);
              break;
             case 5: 
             sscanf(temp,"%d,%d,%d,%d",&Rt[Num_Rhythm].Line_Bass_Note[1],&Rt[Num_Rhythm].Line_Bass_Note[2],&Rt[Num_Rhythm].Line_Bass_Note[3],&Rt[Num_Rhythm].Line_Bass_Note[4]);
             for (i=1; i<Rt[Num_Rhythm].bars*Rt[Num_Rhythm].quarter_note; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              fgets(temp, sizeof temp, fs);
              sscanf(temp,"%d,%d,%d,%d",&Rt[Num_Rhythm].Line_Bass_Note[w+1],&Rt[Num_Rhythm].Line_Bass_Note[w+2],&Rt[Num_Rhythm].Line_Bass_Note[w+3],&Rt[Num_Rhythm].Line_Bass_Note[w+4]);
             } 
             bzero(temp,sizeof(temp));
             fgets(temp, sizeof temp, fs);
             sscanf(temp,"%d,%d,%d,%d",&Rt[Num_Rhythm].Line_Bass_Velocity[1],&Rt[Num_Rhythm].Line_Bass_Velocity[2],&Rt[Num_Rhythm].Line_Bass_Velocity[3],&Rt[Num_Rhythm].Line_Bass_Velocity[4]);
             for (i=1; i<Rt[Num_Rhythm].bars*Rt[Num_Rhythm].quarter_note; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              fgets(temp, sizeof temp, fs);
              sscanf(temp,"%d,%d,%d,%d",&Rt[Num_Rhythm].Line_Bass_Velocity[w+1],&Rt[Num_Rhythm].Line_Bass_Velocity[w+2],&Rt[Num_Rhythm].Line_Bass_Velocity[w+3],&Rt[Num_Rhythm].Line_Bass_Velocity[w+4]);
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
              Num_Rhythm++;
              break;
          }
 


         }
       }


  
  // Init buffers
  
  memset (buf, 0, PERIOD4);
  memset (wbuf, 0, PERIOD4);
  memset (rbuf, 0, PERIOD4);  
  memset (bbuf, 0, PERIOD4);
   
 // Send Signal to GUI  -> "All OK"

  waitforGUI = 1;

};


HOR::~HOR ()
{
  snd_seq_close (MidiInPuerto[1].midi_in);

};


// Returns the FM Operator Pitch (Frequency + LFO)

float
HOR::pitch_Operator (int i, int note)
{
  
return ((lasfreq[(int) Operator[i].harmonic] + Operator[i].harmonic_fine) + LFO_Volume);

}
                 

// Returns The FM Operator Volume 

void
HOR::volume_Operator (int i, int l2)
{
  Operator[i].con1 = Operator[i].volumen * Envelope_Volume[l2] * Keyb_Level_Scaling / lasfreq[Operator[i].harmonic];
   
};



// Return Keyboard Level Scaling (High Note ...less volume)

float
HOR::Get_Keyb_Level_Scaling(int nota)
{
return(velocity[nota] * (1 - ((120 - note[nota]+transpose) / 240.0)));
};


// Turn Off all the sound


void
HOR::panic()
{
  int i;
  for (i = 0; i < POLY; i++)
    {
      note_active[i] = 0;
      env_time[i] = 0;
    }

};

// The fucking ADSR


float
HOR::Jenvelope (int *note_active, int gate, float t, int nota)
{

  float Env = 0;

    
    if (gate)
    {
       if (t > attack + decay )  return (sustain);
       if (t > attack) return(1.0 - (1.0 - sustain) * (t - attack) / decay);
       
       return(t / attack);
    }
  else
    {

      if (pedal == 0)
      {  
          if (release>t)
          {
          Env = Envelope_Volume[nota] * (1.0 -  t / release);
          if (Env < 0.000015)
             {
               if (*note_active) *note_active=0;
                env_time[nota] = 0;
                return(0);
              }
              
             else                           
             return (Env);
          }
          else
          {
          if (*note_active) *note_active=0;
          env_time[nota] = 0;
          return(0);
          }
       }
       
      else
        {
        return(sustain);
        }
     }     

     return(Env);
};



// Returns Pitch LFO 


float
HOR::Pitch_LFO (float t)
{

  float x, out;
  
  if (t * 20 < Pitch_LFO_Delay)
    return (0);

  

  x = fmod(Pitch_LFO_Speed * t, 1.0);

  out = Fsin (x * D_PI) * LFO_Frequency;
     
  return (out);

}


// Return Played Note Frequency

float
HOR::Get_Partial (int nota)
{
  int l;
  float partial=0;
  float freq_note=0; 
  
  l = note[nota] + transpose + 12;
  freq_note=(pitch >0) ? h[l].f2 + (h[l].f3 - h[l].f2) * pitch : h[l].f2 + (h[l].f2 - h[l].f1) * pitch;
  partial = mastertune * freq_note * D_PI_to_SAMPLE_RATE;
  if (partial > D_PI) partial=fmod(partial,D_PI);
  return(partial);
  

};


float
HOR::Fsin (float x)
{

if ( x > D_PI) x = fmod(x,D_PI);  
return(lsin[(int)(x * 1000)]);

};



void
HOR::Calc_LFO_Frequency()
{
LFO_Frequency =  modulation * LFOpitch * D_PI_to_SAMPLE_RATE;

};  





// Main Audio thread

void
HOR::Alg1s (int nframes, void *)
{

  pthread_mutex_lock(&mutex); 

  int l1, l2, i, kk = 0;
  float sound = 0;
  float m_partial;
  int output_yes = 0;
  memset (buf, 0, PERIOD4);
  


    for (l2 = 0; l2 < POLY; l2++)
    {

      if (note_active[l2])
	{
	  output_yes=1;
	  m_partial=Get_Partial(l2);
          Keyb_Level_Scaling=Get_Keyb_Level_Scaling(l2);
          LFO_Volume = Pitch_LFO (env_time[l2]);

          
          for (l1 = 0; l1 < PERIOD; l1 +=2)
          {
     	    sound=0;

            Envelope_Volume[l2] = (Jenvelope (&note_active[l2], gate[l2], env_time[l2], l2));        
      
            

     	    for (i = 1; i <= 10; i++)
	      {
                
                volume_Operator(i, l2);
                if (Operator[i].con1 > 0)
                   {
                     f[i].dphi = m_partial * pitch_Operator (i, l2);
                     if (f[i].dphi > D_PI) f[i].dphi = fmod(f[i].dphi,D_PI);
                     f[i].phi[l2] += f[i].dphi;
                     if (f[i].phi[l2] > D_PI) f[i].phi[l2]=fmod(f[i].phi[l2],D_PI);
                     sound +=  Operator[i].con1 * Fsin(f[i].phi[l2]);

                   }                
 
              }  
 
                buf[l1] += (sound * Organ_Master_Volume * .5);
                buf[l1+1] =buf[l1];
                env_time[l2] +=increment;                
              
                      
           }
              
	}

    }
     



if(output_yes)
  {
  if (E_Chorus_On == 1)
    Effect_Chorus ();
  if (E_Rotary_On == 1)
    Effect_Rotary ();
  }

  if (E_Delay_On == 1)
    Effect_Delay();
  if (E_Reverb_On == 1)
    Effect_Reverb();

Write_Buffer_Effects();

  if (Rhythm_On == 1) 
   Get_Rhythm();


  


Final_Output();



  switch (Salida)
    {
    case 1:
      write (snd_handle, wbuf, PERIOD4);
      break;
    case 2:
      kk = snd_pcm_writei (playback_handle, wbuf, PERIOD);
      if (kk < PERIOD)
        {
        printf("xrun!\n");
	snd_pcm_prepare (playback_handle);
	}
      break;
    }
   pthread_mutex_unlock(&mutex);
   return;
};

  

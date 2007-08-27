/*
  horgand - a organ software

 organvarios.C  -  miscelaneous functions
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
#include <math.h>
// Identify Chords


void 
HOR::Get_Chord()
{
int i,j;
int anote[POLY];
int onote[POLY];
int nnotes=0;
int posi = 0;
int baja,ubaja;
int pafuera=0;
int busca=0;
int dist1,dist2,dist3,dist4;
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



if ((nnotes > 5) || (nnotes < 3)) return;

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

	dist1=onote[1] - onote[0];
	dist2=onote[2] - onote[1];

	j =0;

 	while(busca==0)

	{
	j++;
	if ((Chord3[j].dist1 == dist1) && (Chord3[j].dist2 == dist2))
		{ 
    			busca = 1;
    			chord = j;
                        chord_type = Chord3[j].type;
                        break;
		}    
 
        if (j > 14 ) break;
	}

	if (chord != 0)
	{
	
   	        int elke = onote[Chord3[chord].fund-1];
                fundamental = elke % 12;
		sprintf(AName,"%s%s",NC[fundamental].Nom,Chord3[chord].Nom);
                
                if (strcmp(AName, NameChord) != 0)
                { 
                strcpy(NameChord,AName);
                changeNameChord = 1;
		}
	}
     return;
   }

if (nnotes == 4)
   {

        dist1=onote[1] - onote[0];
        dist2=onote[2] - onote[1];
        dist3=onote[3] - onote[2];
        j =0;

        while(busca==0)

        {
        j++;
        if ((Chord4[j].dist1 == dist1) && (Chord4[j].dist2 == dist2) && (Chord4[j].dist3 == dist3))
                {
                        busca = 1;
                        chord = j;
                        chord_type = Chord4[j].type;
                        break;
                }

        if (j > 46 ) break;
        }

        if (chord != 0)
        {
                int elke = onote[Chord4[chord].fund-1];
                fundamental = elke % 12;
                sprintf(AName,"%s%s",NC[fundamental].Nom,Chord4[chord].Nom);
                if (strcmp(AName, NameChord) != 0)
                {
                strcpy(NameChord,AName);
                changeNameChord = 1;
                }

                
        }
        return;

   }

if (nnotes == 5)
   {

        dist1=onote[1] - onote[0];
        dist2=onote[2] - onote[1];
        dist3=onote[3] - onote[2];
        dist4=onote[4] - onote[3];
        j =0;

        while(busca==0)

        {
        j++;
        if ((Chord5[j].dist1 == dist1) && (Chord5[j].dist2 == dist2) && (Chord5[j].dist3 == dist3) && (Chord5[j].dist4 == dist4))
                {
                        busca = 1;
                        chord = j;
                        chord_type = Chord5[j].type;
                        break;
                }

        if (j > 9 ) break;
        }

        if (chord != 0)
        {
                int elke = onote[Chord5[chord].fund-1];
                fundamental = elke % 12;
                sprintf(AName,"%s%s",NC[fundamental].Nom,Chord5[chord].Nom);
                if (strcmp(AName, NameChord) != 0)
                {
                strcpy(NameChord,AName);
                changeNameChord = 1;
                }

                
        }

   }




};

// Init Some Vars

void
HOR::Put_Period()
{
  PERIOD2 = PERIOD * 2;
  PERIOD4 = PERIOD * 4;
  PERIOD8 = PERIOD * 8;
};


// Reset vars to New Preset

void
HOR::New ()
{
  int i;

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


  E_Delay_On = 0;
  Delay_Delay = 0;
  Delay_Volume = 0;
  Pitch_LFO_Speed = 0;
  Pitch_LFO_Delay = 0;
  Rotary_LFO_Speed = 0;
  LFOpitch = 0;
  modulation = .99;
  organ_transpose = 0;
  E_Rotary_On = 0;
  pitch = 0;
  pedal = 0;
  Master_Volume = 0.70;
  Organ_Master_Volume = 0.70;
  detune = 0;
  split = 0;
  Chorus_Volume = 0.60;
  E_Chorus_On = 0;
  Chorus_LFO_Speed = 0;
  Chorus_LFO_Amplitude = 0;
  Chorus_Delay = 0;
  Reverb_Preset = 1;
  E_Reverb_On=0;
  bzero (Name, sizeof (Name));
  c_name = Name;
  Normalize[1] = 1.0;
  Normalize[2] = 1.0;
  Normalize[3] = 1.0;
  Normalize[4] = .66;
  Normalize[5] = .5;
  Normalize[6] = .4;
  Normalize[7] = .3;
  Normalize[8] = .25;
  Normalize[9] = .22;
  Normalize[10] = .2;
  Normalize[11] = .166;
  Normalize[12] = .142;
  Normalize[13] = .133;
  Normalize[14] = .125;
  Normalize[15] = .111;
  Normalize[16] = .1;
  Normalize[17] = 0.095;
  Normalize[18] = 0.090;
  Normalize[19] = 0.083;
  Normalize[20] = 0.076;
  Normalize[21] = 0.071;
  Normalize[22] = .066;
  attack = 0.001;
  u_attack = 1.0 /attack;
  decay = 0.20;
  u_decay = 1.0 / decay;
  sustain = 0.8;
  p_attack= 0.0001;
  u_p_attack = 1.0 / p_attack;
  p_decay = 0.24;
  u_p_decay = 1.0 / p_decay;
  p_sustain=0.00;
  p_release=0.12;
  u_p_release = 1.0 / p_release;
  Rotary_LFO_Amplitude = 9980;



}


// Puts Undo

void
HOR::MUndo()
{
UndoCount=UndoCount-1;
if (UndoCount == -1) UndoCount = 95;
PonDATA_Undo(UndoCount);
};

void
HOR::PonDATA_Undo(int UndoCount)
{
int k;
for (k=1; k<=10; k++)
{
Operator[k].volumen =Undo[UndoCount].Operator[k].volumen;
Operator[k].harmonic_fine=Undo[UndoCount].Operator[k].harmonic_fine;
Operator[k].harmonic =Undo[UndoCount].Operator[k].harmonic;
Operator[k].marimba=Undo[UndoCount].Operator[k].marimba;
}

E_Delay_On = Undo[UndoCount].E_Delay_On;
Delay_Volume = Undo[UndoCount].Delay_Volume;
Delay_Delay = Undo[UndoCount].Delay_Delay;
Pitch_LFO_Speed = Undo[UndoCount].Pitch_LFO_Speed;
Pitch_LFO_Delay = Undo[UndoCount].Pitch_LFO_Delay;
Rotary_LFO_Speed = Undo[UndoCount].Rotary_LFO_Speed;
LFOpitch = Undo[UndoCount].LFOpitch;
E_Rotary_On = Undo[UndoCount].E_Rotary_On;
modulation = Undo[UndoCount].modulation;
organ_transpose = Undo[UndoCount].organ_transpose;
Organ_Master_Volume = Undo[UndoCount].Organ_Master_Volume;

for (k=0; k<=24; k++) Name[k]=Undo[UndoCount].Name[k];
c_name = Name;

E_Reverb_On=Undo[UndoCount].E_Reverb_On;
detune = Undo[UndoCount].detune;
split=Undo[UndoCount].split;
Reverb_Preset=Undo[UndoCount].Reverb_Preset;
E_Chorus_On=Undo[UndoCount].E_Chorus_On;
Chorus_LFO_Amplitude=Undo[UndoCount].Chorus_LFO_Amplitude;
Chorus_Delay=Undo[UndoCount].Chorus_Delay;
Chorus_LFO_Speed=Undo[UndoCount].Chorus_LFO_Speed;
Chorus_Volume=Undo[UndoCount].Chorus_Volume;
attack=Undo[UndoCount].attack;
decay=Undo[UndoCount].decay;
sustain=Undo[UndoCount].sustain;
p_attack=Undo[UndoCount].p_attack;
p_decay=Undo[UndoCount].p_decay;
for (k=1;k<=22;k++) Normalize[k]=Undo[UndoCount].Normalize[k];
Rotary_LFO_Amplitude=Undo[UndoCount].Rotary_LFO_Amplitude;



};


//Puts Redo

void
HOR::MRedo()
{
UndoCount = UndoCount + 1;
if (UndoCount == 95 ) UndoCount = 0;
PonDATA_Undo(UndoCount);

};


// Refresh Undo/Redo Buffer when something is edited

void
HOR::MActu()
{

int k;

UndoCount++;
if (UndoCount == 95) UndoCount = 0;

for (k=1; k<=10; k++)
{
Undo[UndoCount].Operator[k].volumen=Operator[k].volumen;
Undo[UndoCount].Operator[k].harmonic_fine=Operator[k].harmonic_fine;
Undo[UndoCount].Operator[k].harmonic=Operator[k].harmonic;
Undo[UndoCount].Operator[k].marimba=Operator[k].marimba;
}


Undo[UndoCount].E_Delay_On=E_Delay_On;
Undo[UndoCount].Delay_Volume=Delay_Volume;
Undo[UndoCount].Delay_Delay=Delay_Delay;
Undo[UndoCount].Pitch_LFO_Speed=Pitch_LFO_Speed;
Undo[UndoCount].Pitch_LFO_Delay=Pitch_LFO_Delay;
Undo[UndoCount].Rotary_LFO_Speed=Rotary_LFO_Speed;
Undo[UndoCount].LFOpitch=LFOpitch;
Undo[UndoCount].E_Rotary_On=E_Rotary_On;
Undo[UndoCount].modulation=modulation;
Undo[UndoCount].organ_transpose=organ_transpose;
Undo[UndoCount].Organ_Master_Volume=Organ_Master_Volume;

for (k=0; k<=24; k++) Undo[UndoCount].Name[k]=Name[k];
c_name = Name;
Undo[UndoCount].detune=detune;
Undo[UndoCount].E_Reverb_On=E_Reverb_On;
Undo[UndoCount].split=split;
Undo[UndoCount].Reverb_Preset =Reverb_Preset;
Undo[UndoCount].E_Chorus_On=E_Chorus_On;
Undo[UndoCount].Chorus_LFO_Amplitude=Chorus_LFO_Amplitude;
Undo[UndoCount].Chorus_Delay=Chorus_Delay;
Undo[UndoCount].Chorus_LFO_Speed=Chorus_LFO_Speed;
Undo[UndoCount].Chorus_Volume=Chorus_Volume;
Undo[UndoCount].attack=attack;
Undo[UndoCount].decay=decay;
Undo[UndoCount].sustain=sustain;
Undo[UndoCount].p_attack=p_attack;
Undo[UndoCount].p_decay=p_decay;
for (k=0; k<=22; k++) Undo[UndoCount].Normalize[k]=Normalize[k];
Undo[UndoCount].Rotary_LFO_Amplitude=Rotary_LFO_Amplitude;



};


// Put Undo/Redo buffers on Loaded Preset State for Compare 

void
HOR::PutPrim()
{

int k;
for (k=1; k<=10; k++)
{
Prim[1].Operator[k].volumen=Operator[k].volumen;
Prim[1].Operator[k].harmonic_fine=Operator[k].harmonic_fine;
Prim[1].Operator[k].harmonic=Operator[k].harmonic;
Prim[1].Operator[k].marimba=Operator[k].marimba;
}

Prim[1].E_Delay_On=E_Delay_On;
Prim[1].Delay_Volume=Delay_Volume;
Prim[1].Delay_Delay=Delay_Delay;

Prim[1].Pitch_LFO_Speed=Pitch_LFO_Speed;
Prim[1].Pitch_LFO_Delay=Pitch_LFO_Delay;
Prim[1].Rotary_LFO_Speed=Rotary_LFO_Speed;
Prim[1].LFOpitch=LFOpitch;
Prim[1].E_Rotary_On=E_Rotary_On;
Prim[1].modulation=modulation;
Prim[1].organ_transpose=organ_transpose;
Prim[1].Organ_Master_Volume=Organ_Master_Volume;

for (k=0; k<=24; k++) Prim[1].Name[k]=Name[k];

Prim[1].detune=detune;
Prim[1].E_Reverb_On=E_Reverb_On;

Prim[1].split=split;
Prim[1].Reverb_Preset =Reverb_Preset;
Prim[1].E_Chorus_On=E_Chorus_On;
Prim[1].Chorus_LFO_Amplitude=Chorus_LFO_Amplitude;
Prim[1].Chorus_Delay=Chorus_Delay;
Prim[1].Chorus_LFO_Speed=Chorus_LFO_Speed;
Prim[1].Chorus_Volume=Chorus_Volume;
Prim[1].attack=attack;
Prim[1].decay=decay;
Prim[1].sustain=sustain;
Prim[1].p_attack=p_attack;
Prim[1].p_decay=p_decay;
for (k=0; k<=22; k++) Prim[1].Normalize[k]=Normalize[k];
Prim[1].Rotary_LFO_Amplitude=Rotary_LFO_Amplitude;




};


// Put the Loaded Preset for Compare


void
HOR::MGetPrim()
{

int k;
for (k=1; k<=10; k++)
{
Operator[k].volumen =Prim[1].Operator[k].volumen;
Operator[k].harmonic_fine =Prim[1].Operator[k].harmonic_fine;
Operator[k].harmonic =Prim[1].Operator[k].harmonic;
Operator[k].marimba = Prim[1].Operator[k].marimba;
}

E_Delay_On = Prim[1].E_Delay_On;
Delay_Volume = Prim[1].Delay_Volume;
Delay_Delay = Prim[1].Delay_Delay;
Pitch_LFO_Speed = Prim[1].Pitch_LFO_Speed;
Pitch_LFO_Delay = Prim[1].Pitch_LFO_Delay;
Rotary_LFO_Speed = Prim[1].Rotary_LFO_Speed;
LFOpitch = Prim[1].LFOpitch;
E_Rotary_On = Prim[1].E_Rotary_On;
modulation = Prim[1].modulation;
organ_transpose = Prim[1].organ_transpose;
Organ_Master_Volume = Prim[1].Organ_Master_Volume;
bzero(Name,sizeof(Name));
for (k=0; k<=24; k++) Name[k]=Prim[1].Name[k];
c_name = Name;
detune = Prim[1].detune;
E_Reverb_On = Prim[1].E_Reverb_On;
split=Prim[1].split;
Reverb_Preset=Prim[1].Reverb_Preset;
E_Chorus_On=Prim[1].E_Chorus_On;
Chorus_LFO_Amplitude=Prim[1].Chorus_LFO_Amplitude;
Chorus_Delay=Prim[1].Chorus_Delay;
Chorus_LFO_Speed=Prim[1].Chorus_LFO_Speed;
Chorus_Volume=Prim[1].Chorus_Volume;
attack=Prim[1].attack;
decay=Prim[1].decay;
sustain=Prim[1].sustain;
p_attack=Prim[1].p_attack;
p_decay=Prim[1].p_decay;
for (k=1;k<=22;k++) Normalize[k]=Prim[1].Normalize[k];
Rotary_LFO_Amplitude=Prim[1].Rotary_LFO_Amplitude;


};


void
HOR::Get_Combi_t(int i)
{
int k;
for (k=1; k<=10; k++)
{
Banco[i].Operator[k].volumen=Operator[k].volumen;
Banco[i].Operator[k].harmonic_fine=Operator[k].harmonic_fine;
Banco[i].Operator[k].harmonic=Operator[k].harmonic;
Banco[i].Operator[k].marimba=Operator[k].marimba;
}
Banco[i].E_Delay_On=E_Delay_On;
Banco[i].Delay_Delay=Delay_Delay;
Banco[i].Delay_Volume=Delay_Volume;
Banco[i].Pitch_LFO_Speed=Pitch_LFO_Speed;
Banco[i].Pitch_LFO_Delay=Pitch_LFO_Delay;
Banco[i].Rotary_LFO_Speed=Rotary_LFO_Speed;
Banco[i].LFOpitch=LFOpitch;
Banco[i].E_Rotary_On=E_Rotary_On;
Banco[i].modulation=modulation;
Banco[i].organ_transpose=organ_transpose;
Banco[i].Organ_Master_Volume=Organ_Master_Volume;

for (k=0; k<=24; k++) Banco[i].Name[k]=Name[k];

Banco[i].detune=detune;
Banco[i].E_Reverb_On=E_Reverb_On;
Banco[i].split=split;
Banco[i].Reverb_Preset =Reverb_Preset;
Banco[i].E_Chorus_On=E_Chorus_On;
Banco[i].Chorus_LFO_Amplitude=Chorus_LFO_Amplitude;
Banco[i].Chorus_Delay=Chorus_Delay;
Banco[i].Chorus_LFO_Speed=Chorus_LFO_Speed;
Banco[i].Chorus_Volume=Chorus_Volume;
Banco[i].attack=attack;
Banco[i].decay=decay;
Banco[i].sustain=sustain;
Banco[i].p_attack=p_attack;
Banco[i].p_decay=p_decay;
for (k=0; k<=22; k++) Banco[i].Normalize[k]=Normalize[k];
Banco[i].Rotary_LFO_Amplitude=Rotary_LFO_Amplitude;



};


void
HOR::Put_Combi_t(int i)
{
int k;
for (k=1; k<=10; k++)
{
Operator[k].volumen =Banco[i].Operator[k].volumen;
Operator[k].harmonic_fine =Banco[i].Operator[k].harmonic_fine;
Operator[k].harmonic =Banco[i].Operator[k].harmonic;
Operator[k].marimba=Banco[i].Operator[k].marimba;
}

E_Delay_On = Banco[i].E_Delay_On;
Delay_Volume = Banco[i].Delay_Volume;
Delay_Delay = Banco[i].Delay_Delay;
Pitch_LFO_Speed = Banco[i].Pitch_LFO_Speed;
Pitch_LFO_Delay = Banco[i].Pitch_LFO_Delay;
Rotary_LFO_Speed = Banco[i].Rotary_LFO_Speed;
LFOpitch = Banco[i].LFOpitch;
E_Rotary_On = Banco[i].E_Rotary_On;
modulation = Banco[i].modulation;
organ_transpose = Banco[i].organ_transpose;
Organ_Master_Volume = Banco[i].Organ_Master_Volume;
bzero(Name, sizeof(Name));
for (k=0; k<=24; k++) Name[k]=Banco[i].Name[k];
c_name = Name;
E_Reverb_On = Banco[i].E_Reverb_On;
detune = Banco[i].detune;
if (Rhythm_On != 1) split=Banco[i].split;
Reverb_Preset=Banco[i].Reverb_Preset;
E_Chorus_On=Banco[i].E_Chorus_On;
Chorus_LFO_Amplitude=Banco[i].Chorus_LFO_Amplitude;
Chorus_Delay=Banco[i].Chorus_Delay;
Chorus_LFO_Speed=Banco[i].Chorus_LFO_Speed;
Chorus_Volume=Banco[i].Chorus_Volume;
attack=Banco[i].attack;
decay=Banco[i].decay;
sustain=Banco[i].sustain;
p_attack=Banco[i].p_attack;
p_decay=Banco[i].p_decay;
for (k=1;k<=22;k++) Normalize[k]=Banco[i].Normalize[k];
Rotary_LFO_Amplitude=Banco[i].Rotary_LFO_Amplitude;

Prim[1] = Banco[i];

};


void
HOR::syncadsr()
{


 memset(f ,0, sizeof f);

 
 u_attack = 1.0 /attack;
 u_decay = 1.0 / decay;
 u_p_attack = 1.0 / p_attack;
 u_p_decay = 1.0 / p_decay;

 
};


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

// Init some Reverb Vars

float
HOR::fastabs (float f)
{
  int i = ((*(int *) &f) & 0x7fffffff);
  return (*(float *) &i);

};

// Return previous calculated Sins

float
HOR::Fsin (float x)
{

  x = fmod(x,D_PI);  
 return ((x >= 0) ? lsin[(int) (x * 1000)] : -1 * lsin[(int) (x * 1000)]);

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


  attack = 0.02;
  decay = 0.00;
  E_Delay_On = 0;
  Delay_Delay = 0;
  Delay_Volume = 0;
  Pitch_LFO_Speed = 0;
  Pitch_LFO_Delay = 0;
  Rotary_LFO_Speed = 0;
  LFOpitch = 0;
  modulation = 10;
  transpose = 0;
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
}


// Puts Undo

void
HOR::MUndo()
{

int k;

UndoCount = UndoCount -1;
if (UndoCount == -1) UndoCount = 95;
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
transpose = Undo[UndoCount].transpose;
Organ_Master_Volume = Undo[UndoCount].Organ_Master_Volume;

for (k=0; k<=24; k++) Name[k]=Undo[UndoCount].Name[k];
c_name = Name;

E_Reverb_On=Undo[UndoCount].E_Reverb_On;
attack= Undo[UndoCount].attack;
detune = Undo[UndoCount].detune;
split=Undo[UndoCount].split;
Reverb_Preset=Undo[UndoCount].Reverb_Preset;
E_Chorus_On=Undo[UndoCount].E_Chorus_On;
Chorus_LFO_Amplitude=Undo[UndoCount].Chorus_LFO_Amplitude;
Chorus_Delay=Undo[UndoCount].Chorus_Delay;
Chorus_LFO_Speed=Undo[UndoCount].Chorus_LFO_Speed;
Chorus_Volume=Undo[UndoCount].Chorus_Volume;

};


//Puts Redo

void
HOR::MRedo()
{

int k;


UndoCount = UndoCount + 1;
if (UndoCount == 95 ) UndoCount = 0;

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
transpose = Undo[UndoCount].transpose;
Organ_Master_Volume = Undo[UndoCount].Organ_Master_Volume;

for (k=0; k<=24; k++) Name[k]=Undo[UndoCount].Name[k];
c_name = Name;

attack = Undo[UndoCount].attack;
detune = Undo[UndoCount].detune;

E_Reverb_On=Undo[UndoCount].E_Reverb_On;
split=Undo[UndoCount].split;
Reverb_Preset=Undo[UndoCount].Reverb_Preset;
E_Chorus_On=Undo[UndoCount].E_Chorus_On;
Chorus_LFO_Amplitude=Undo[UndoCount].Chorus_LFO_Amplitude;
Chorus_Delay=Undo[UndoCount].Chorus_Delay;
Chorus_LFO_Speed=Undo[UndoCount].Chorus_LFO_Speed;
Chorus_Volume=Undo[UndoCount].Chorus_Volume;

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
Undo[UndoCount].transpose=transpose;
Undo[UndoCount].Organ_Master_Volume=Organ_Master_Volume;

for (k=0; k<=24; k++) Undo[UndoCount].Name[k]=Name[k];
c_name = Name;
Undo[UndoCount].attack=attack;
Undo[UndoCount].detune=detune;
Undo[UndoCount].E_Reverb_On=E_Reverb_On;
Undo[UndoCount].split=split;
Undo[UndoCount].Reverb_Preset =Reverb_Preset;
Undo[UndoCount].E_Chorus_On=E_Chorus_On;
Undo[UndoCount].Chorus_LFO_Amplitude=Chorus_LFO_Amplitude;
Undo[UndoCount].Chorus_Delay=Chorus_Delay;
Undo[UndoCount].Chorus_LFO_Speed=Chorus_LFO_Speed;
Undo[UndoCount].Chorus_Volume=Chorus_Volume;


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
Prim[1].transpose=transpose;
Prim[1].Organ_Master_Volume=Organ_Master_Volume;

for (k=0; k<=24; k++) Prim[1].Name[k]=Name[k];

Prim[1].attack=attack;
Prim[1].detune=detune;
Prim[1].E_Reverb_On=E_Reverb_On;

Prim[1].split=split;
Prim[1].Reverb_Preset =Reverb_Preset;
Prim[1].E_Chorus_On=E_Chorus_On;
Prim[1].Chorus_LFO_Amplitude=Chorus_LFO_Amplitude;
Prim[1].Chorus_Delay=Chorus_Delay;
Prim[1].Chorus_LFO_Speed=Chorus_LFO_Speed;
Prim[1].Chorus_Volume=Chorus_Volume;

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
transpose = Prim[1].transpose;
Organ_Master_Volume = Prim[1].Organ_Master_Volume;
bzero(Name,sizeof(Name));
for (k=0; k<=24; k++) Name[k]=Prim[1].Name[k];
c_name = Name;
attack = Prim[1].attack;
detune = Prim[1].detune;
E_Reverb_On = Prim[1].E_Reverb_On;
split=Prim[1].split;
Reverb_Preset=Prim[1].Reverb_Preset;
E_Chorus_On=Prim[1].E_Chorus_On;
Chorus_LFO_Amplitude=Prim[1].Chorus_LFO_Amplitude;
Chorus_Delay=Prim[1].Chorus_Delay;
Chorus_LFO_Speed=Prim[1].Chorus_LFO_Speed;
Chorus_Volume=Prim[1].Chorus_Volume;


};






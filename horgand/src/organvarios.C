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
HOR::ponpe ()
{
  PERIOD2 = PERIOD * 2;
  PERIOD4 = PERIOD * 4;
  PERIOD8 = PERIOD * 8;
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



void
HOR::New ()
{
  int i;

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


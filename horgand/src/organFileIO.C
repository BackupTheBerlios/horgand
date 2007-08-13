/*
  horgand - a organ software

 organ.FileIO.C  -  File Input/Output functions
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
HOR::savefile (char *filename)
{

  int i;
  FILE *fn;
  char buf[2048];
  fn = fopen (filename, "w");
  for (i = 1; i <= 10; i++)
    {

      bzero (buf, sizeof (buf));
      sprintf (buf, "%d,%f,%f,%d\n", Operator[i].harmonic,
	       Operator[i].harmonic_fine,Operator[i].volumen,Operator[i].marimba);



      fputs (buf, fn);
    }

  bzero (buf, sizeof (buf));
  sprintf (buf, "%f,%d,%f,%f,%f,%d,%f,%f\n",
	   Organ_Master_Volume, transpose, Pitch_LFO_Speed, Pitch_LFO_Delay, Rotary_LFO_Speed, E_Rotary_On, LFOpitch,
	   modulation);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  sprintf (buf, "%f,%d,%f,%d,%f,%f\n", attack, E_Reverb_On, detune, E_Delay_On,
	   Delay_Delay, Delay_Volume);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  sprintf (buf, "%d,%d,%f,%d,%f,%f,%f\n", split, E_Chorus_On, Chorus_Delay, Reverb_Preset,
	   Chorus_LFO_Speed, Chorus_LFO_Amplitude, Chorus_Volume);
  fputs (buf, fn);
  bzero (buf, sizeof (buf));
  fputs (c_name, fn);
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


  for (i = 1; i <= 10; i++)
    {

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf, "%d,%f,%f,%d", &Operator[i].harmonic,
	      &Operator[i].harmonic_fine,&Operator[i].volumen,&Operator[i].marimba);




    }

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf (buf,
	  "%f,%d,%f,%f,%f,%d,%f,%f", &Organ_Master_Volume, &transpose, &Pitch_LFO_Speed,
	  &Pitch_LFO_Delay, &Rotary_LFO_Speed, &E_Rotary_On, &LFOpitch, &modulation);

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf (buf, "%f,%d,%f,%d,%f,%f", &attack, &E_Reverb_On, &detune, &E_Delay_On,
	  &Delay_Delay, &Delay_Volume);

  bzero (buf, sizeof (buf));
  fgets (buf, sizeof buf, fn);
  sscanf
    (buf, "%d,%d,%f,%d,%f,%f,%f\n", &split, &E_Chorus_On, &Chorus_Delay, &Reverb_Preset,
     &Chorus_LFO_Speed, &Chorus_LFO_Amplitude, &Chorus_Volume);

  bzero (buf, sizeof (buf));
  bzero (Name, sizeof (Name));
  fgets (buf, sizeof buf, fn);
  for (i = 0; i <= 24; i++)
    if (buf[i] > 20)
      Name[i] = buf[i];
  c_name = Name;
  fclose (fn);

};

void
HOR::savebank (char *filename)
{
  int i,j;
  FILE *fn;
  char buf[2048];
  fn = fopen (filename, "w");

  for (j = 1; j <= 32; j++)
    {


      for (i = 1; i <= 10; i++)
	{

	  bzero (buf, sizeof (buf));
	  sprintf (buf, "%d,%f,%f,%d\n",
		   Banco[j].Operator[i].harmonic,
		   Banco[j].Operator[i].harmonic_fine,
		   Banco[j].Operator[i].volumen,Banco[j].Operator[i].marimba);


	  fputs (buf, fn);
	}

      bzero (buf, sizeof (buf));
      sprintf (buf, "%f,%d,%f,%f,%f,%d,%f,%f\n",
	       Banco[j].Organ_Master_Volume, Banco[j].transpose, Banco[j].Pitch_LFO_Speed,
	       Banco[j].Pitch_LFO_Delay, Banco[j].Rotary_LFO_Speed, Banco[j].E_Rotary_On,
	       Banco[j].LFOpitch, Banco[j].modulation);


      fputs (buf, fn);
      bzero (buf, sizeof (buf));
      sprintf (buf, "%f,%d,%f,%d,%f,%f\n", Banco[j].attack, Banco[j].E_Reverb_On,
	       Banco[j].detune, Banco[j].E_Delay_On, Banco[j].Delay_Delay,
	       Banco[j].Delay_Volume);
      fputs (buf, fn);
      bzero (buf, sizeof (buf));
      sprintf
	(buf, "%d,%d,%f,%d,%f,%f,%f\n", Banco[j].split, Banco[j].E_Chorus_On,
	 Banco[j].Chorus_Delay, Banco[j].Reverb_Preset, Banco[j].Chorus_LFO_Speed,
	 Banco[j].Chorus_LFO_Amplitude, Banco[j].Chorus_Volume);
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

  int i,j;
  FILE *fn;
  char buf[2048];

  if ((fn = fopen (filename, "r")) == NULL)
    return;
  for (j = 1; j <= 32; j++)
    {

      for (i = 1; i <= 10; i++)
	{

	  bzero (buf, sizeof (buf));
	  fgets (buf, sizeof buf, fn);

	  sscanf (buf, "%d,%f,%f,%d",
		  &Banco[j].Operator[i].harmonic,
		  &Banco[j].Operator[i].harmonic_fine,
		  &Banco[j].Operator[i].volumen,&Banco[j].Operator[i].marimba);
 
	}

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf,
	      "%f,%d,%f,%f,%f,%d,%f,%f", &Banco[j].Organ_Master_Volume,
	      &Banco[j].transpose, &Banco[j].Pitch_LFO_Speed, &Banco[j].Pitch_LFO_Delay,
	      &Banco[j].Rotary_LFO_Speed, &Banco[j].E_Rotary_On, &Banco[j].LFOpitch,
	      &Banco[j].modulation);

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf (buf,
	      "%f,%d,%f,%d,%f,%f", &Banco[j].attack, &Banco[j].E_Reverb_On,
	      &Banco[j].detune, &Banco[j].E_Delay_On, &Banco[j].Delay_Delay,
	      &Banco[j].Delay_Volume);

      bzero (buf, sizeof (buf));
      fgets (buf, sizeof buf, fn);
      sscanf
	(buf, "%d,%d,%f,%d,%f,%f,%f\n", &Banco[j].split, &Banco[j].E_Chorus_On,
	 &Banco[j].Chorus_Delay, &Banco[j].Reverb_Preset, &Banco[j].Chorus_LFO_Speed,
	 &Banco[j].Chorus_LFO_Amplitude, &Banco[j].Chorus_Volume);




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
   int i;
   FILE *fs;
   char temp[1024];
   
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (filename, "r")) != NULL)
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
              bzero(Rt[Num_Rhythm].Nom,sizeof(Rt[Num_Rhythm].Nom));
              for (i = 0; i <= (int) strlen(temp) - 2; i++) Rt[Num_Rhythm].Nom[i] = temp[i];                   
              break; 
             case 2:
              bzero(Rt[Num_Rhythm].Nfile,sizeof(Rt[Num_Rhythm].Nfile));
              for (i = 0; i <= (int) strlen(temp) - 2; i++) Rt[Num_Rhythm].Nfile[i] = temp[i];
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




};


void
HOR::saverhyt(char *filename)
{
   int i,j;
   FILE *fs;
   char temp[1024];
   int w=0;   
   bzero(temp,sizeof(temp));
 
  if ((fs = fopen (filename, "w")) != NULL)
   {     
     for(Num_Rhythm=1; Num_Rhythm<=20; Num_Rhythm++)
       {    
         bzero(temp,sizeof(temp));
         sprintf(temp,"%s\n",Rt[Num_Rhythm].Nom);
         fputs (temp, fs);        
         bzero(temp,sizeof(temp));           
         sprintf(temp,"%s\n",Rt[Num_Rhythm].Nfile);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf (temp,"%d\n", Rt[Num_Rhythm].bars);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf (temp,"%d\n", Rt[Num_Rhythm].quarter_note);
         fputs (temp, fs);
         bzero(temp,sizeof(temp));
         sprintf(temp,"%d,%d,%d,%d\n",Rt[Num_Rhythm].Line_Bass_Note[1],Rt[Num_Rhythm].Line_Bass_Note[2],Rt[Num_Rhythm].Line_Bass_Note[3],Rt[Num_Rhythm].Line_Bass_Note[4]);
         fputs (temp, fs);
         for (i=1; i<Rt[Num_Rhythm].bars*Rt[Num_Rhythm].quarter_note; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              sprintf(temp,"%d,%d,%d,%d\n",Rt[Num_Rhythm].Line_Bass_Note[w+1],Rt[Num_Rhythm].Line_Bass_Note[w+2],Rt[Num_Rhythm].Line_Bass_Note[w+3],Rt[Num_Rhythm].Line_Bass_Note[w+4]);
              fputs (temp, fs);
             } 
             bzero(temp,sizeof(temp));
             sprintf(temp,"%d,%d,%d,%d\n",Rt[Num_Rhythm].Line_Bass_Velocity[1],Rt[Num_Rhythm].Line_Bass_Velocity[2],Rt[Num_Rhythm].Line_Bass_Velocity[3],Rt[Num_Rhythm].Line_Bass_Velocity[4]);
             fputs (temp, fs);

             for (i=1; i<Rt[Num_Rhythm].bars*Rt[Num_Rhythm].quarter_note; i++)
             {
              w = i*4;
              bzero(temp,sizeof(temp));
              sprintf(temp,"%d,%d,%d,%d\n",Rt[Num_Rhythm].Line_Bass_Velocity[w+1],Rt[Num_Rhythm].Line_Bass_Velocity[w+2],Rt[Num_Rhythm].Line_Bass_Velocity[w+3],Rt[Num_Rhythm].Line_Bass_Velocity[w+4]);
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





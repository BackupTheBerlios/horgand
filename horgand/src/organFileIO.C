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
  for (i = 1; i <= 20; i++)
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


  for (i = 1; i <= 20; i++)
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
  int i,j;
  FILE *fn;
  char buf[2048];
  fn = fopen (filename, "w");

  for (j = 1; j <= 32; j++)
    {


      for (i = 1; i <= 20; i++)
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

  int i,j;
  FILE *fn;
  char buf[2048];

  if ((fn = fopen (filename, "r")) == NULL)
    return;
  for (j = 1; j <= 32; j++)
    {

      for (i = 1; i <= 20; i++)
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
   int i;
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
   int i,j;
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





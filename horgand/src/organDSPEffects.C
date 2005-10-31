/*
  horgand - a organ software

 organDSPEffects.C  -  DSP Effects functions
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



void
HOR::bchorus ()
{

  long elkel, elker, elkel2, elker2;
  float valorl, valorr;
  float dll1, dlr1;
  float dell, delr;
  float dllo;
  long aeperhis;
  int i,j;

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
  int i;
  float a ,l, r;
  freqlfo = 4 * modulation * LFOamplitude * lalapi;

  for (i = 0; i <PERIOD2; i +=2)
    {

      a = LFO (xx);

      l =  buf[i];
      r =  buf[i + 1];


      buf[i] -= (l * a) / 2.0;
      buf[i + 1] += (r * a) / 2.0;
      
                         


    }
};


void
HOR::reverb ()

{
  int i,j;
  long elke, elke1;
  float tmp=0;
  float tmprvol=0;
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
    
      
      elke = rperhis - ((long) (combl[j] * rtime))+10000;
      if (elke % 2 != 0) elke = elke + 1;
      if (elke < 0) elke = 524800 + elke;

      elke1 = rperhis  - ((long) (combr[j] * rtime))+10000;
      if (elke1 % 2 == 0) elke1 = elke1 + 1; 
      if (elke1 < 0) elke1 = 524800 + elke1;
 
      tmp = diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 15 ) capsg = 0;
      efxoutl += rhistory[elke] * stmp;
                  
      tmp = diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 15 ) capsg = 0;
      efxoutr += rhistory[elke1] * stmp;
             
     }
       
        
      tmprvol =  stmp * revvol;
       
    
      buf[i] = bufl + ((efxoutl * tmprvol) / 2.0 );
      rhistory[rperhis] = buf[i];
      if (++rperhis > 524800) rperhis = 0;
      buf[i + 1] = bufr + ((efxoutr * tmprvol) / 2.0 );
      rhistory[rperhis] = buf[i+1];
      if (++rperhis > 524800) rperhis = 0;
                                                   
      if (++hrperhis > 524800) hrperhis = 0;
      rhistory[hrperhis] = 0;
      if (++hrperhis > 524800) hrperhis = 0;
      rhistory[hrperhis] = 0;
            

    }
};



void
HOR::procesa ()
{
  int i;  
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

memset (rhistory, 0, 2 * sizeof (float) * BUFSIZE * 1024);

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


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

// LFO for chorus

float
HOR::Chorus_LFO (float *Chorus_X)
{

  float out;

  *Chorus_X += increment * Chorus_LFO_Speed;

  if (*Chorus_X > 1)
   *Chorus_X = 0;

  ;

  out = Fsin (*Chorus_X * D_PI);

  if (out < -1.0)
    out = -1.0;
  else if (out > 1.0)
    out = 1.0;
   out *= Chorus_LFO_Frequency;
 return (out);
  
};


// Chorus Effect

void
HOR::Effect_Chorus()
{

  long elkel, elker, elkel2, elker2;
  float valorl, valorr;
  float dll1, dlr1;
  float dell, delr;
  float dllo;
  long aeperhis;
  int i,j;

  Chorus_LFO_Frequency = 8 * modulation * Chorus_LFO_Amplitude * D_PI_to_SAMPLE_RATE ;
  while (Chorus_LFO_Frequency > D_PI ) Chorus_LFO_Frequency -=D_PI;
  
  


  for (i = 0; i < PERIOD2; i +=2)
    {
      ehistoryl[eperhis] = buf[i];
      ehistoryr[eperhis] = buf[i + 1];
      if (++eperhis >= 32800)
	eperhis = 0;
    }

  aeperhis = eperhis - PERIOD;

  for (i = 0; i < PERIOD; i++)

    {
      j = 2 * i;

      ldelay1 = ldelay;
      rdelay1 = rdelay;

      dll1 = Chorus_LFO (&Chorus_X_L);
      dlr1 = Chorus_LFO (&Chorus_X_R);



      ldelay = PERIOD2 + (dll1 * Chorus_Delay);
      rdelay = PERIOD2 + (dlr1 * Chorus_Delay);
      

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
      
      buf[j] = (buf[j] * (1 - Chorus_Volume)) + (valorl * Chorus_Volume);

      dllo = 1.0 - fmod (delr, 1.0);
      
      
      
      
      elker = (long) (aeperhis + i  - delr);

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
      
      
      buf[j + 1] = (buf[j + 1] * (1 - Chorus_Volume)) + (valorr * Chorus_Volume);


    }
};


// LFO for Rotary


float
HOR::Rotary_LFO (float t)
{

  float out;


  Rotary_X += Rotary_LFO_Speed * increment;

  if (Rotary_X > 1)
    Rotary_X = 0;

  out = Fsin (Rotary_X * D_PI);

  if (out < -1.0)
    out = -1.0;
  else if (out > 1.0)
    out = 1.0;
   out *= Rotary_LFO_Frequency;
   return (out);
  
};


// Rotary Effect


void
HOR::Effect_Rotary ()
{
  int i;
  float a ,l, r;
  Rotary_LFO_Frequency = 8 * modulation * Rotary_LFO_Amplitude * D_PI_to_SAMPLE_RATE;
  while (Rotary_LFO_Frequency > D_PI ) Rotary_LFO_Frequency -=D_PI;


  for (i = 0; i <PERIOD2; i +=2)
    {

      a = Rotary_LFO (Rotary_X);
      l =  buf[i];
      r =  buf[i + 1];


      buf[i] -= (l * a) / 2.0;
      buf[i + 1] += (r * a) / 2.0;
      
                         


    }
};


// Reverb Effect

void
HOR::Effect_Reverb ()

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
    
      
      elke = rperhis - ((long) (combl[j] * Reverb_Time))+10000;
      if (elke % 2 != 0) elke = elke + 1;
      if (elke < 0) elke = 524800 + elke;

      elke1 = rperhis  - ((long) (combr[j] * Reverb_Time))+10000;
      if (elke1 % 2 == 0) elke1 = elke1 + 1; 
      if (elke1 < 0) elke1 = 524800 + elke1;
 
      tmp = Reverb_Diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 15 ) capsg = 0;
      efxoutl += rhistory[elke] * stmp;
                  
      tmp = Reverb_Diffussion * apsg[capsg] / apss;
      stmp += tmp;
      if (++capsg > 15 ) capsg = 0;
      efxoutr += rhistory[elke1] * stmp;
             
     }
       
        
      tmprvol =  stmp * Reverb_Volume;
       
    
      buf[i] = bufl + ((efxoutl * tmprvol));
      rhistory[rperhis] = buf[i];
      if (++rperhis > 524800) rperhis = 0;
      buf[i + 1] = bufr + ((efxoutr * tmprvol));
      rhistory[rperhis] = buf[i+1];
      if (++rperhis > 524800) rperhis = 0;
                                                   
      if (++hrperhis > 524800) hrperhis = 0;
      rhistory[hrperhis] = 0;
      if (++hrperhis > 524800) hrperhis = 0;
      rhistory[hrperhis] = 0;
            

    }
};


// Delay Effect

void
HOR::Effect_Delay()
{
  int i;  
  long elke, elke1;
  long delay = (long) Delay_Delay;
  float voll, volr;
  float Delay_Volumer, Delay_Volumel;

  voll = 1 - Stereo_Side;
  volr = 1 - voll;
  Delay_Volumel = voll * Delay_Volume;
  Delay_Volumer = volr * Delay_Volume;


  for (i = 0; i <PERIOD2; i +=2)

    {
      
      elke = perhis - delay;
      if (elke % 2 != 0) elke = elke + 1;
      if (elke < 0)
	elke = 524800 + elke;
      elke1 = elke + 1;
      if (elke1 < 0)
	elke1 = 524800 + elke1;

      buf[i] = (buf[i] * (1 - Delay_Volumel)) + (history[elke] * Delay_Volumel);
      history[perhis] = buf[i];
      if (++perhis > 524800)
	perhis = 0;

      buf[i + 1] =
	(buf[i + 1] * (1 - Delay_Volumer)) + (history[elke1] * Delay_Volumer);
      history[perhis] = buf[i+1];
      if (++perhis > 524800)
	perhis = 0;
    }

  switch (To_Stereo_Side)
    {
    case 0:
      Stereo_Side += 0.01;
      if (Stereo_Side > 1)
	To_Stereo_Side = 1;
      break;
    case 1:
      Stereo_Side -= 0.01;
      if (Stereo_Side < 0)
	To_Stereo_Side = 0;
      break;
    }
    
};


// Reverb Clean Buffers

void
HOR::reverbclean()
{

memset (rhistory, 0, 2 * sizeof (float) * BUFSIZE * 1024);

};

// Delay Clean Buffers

void
HOR::delayclean ()
{
  memset (history, 0, BUFSIZE * 1024);

};

// Chorus Clean Buffers

void
HOR::chorusclean ()
{
  memset (ehistoryl, 0, BUFSIZE * 128);
  memset (ehistoryr, 0, BUFSIZE * 128);

};


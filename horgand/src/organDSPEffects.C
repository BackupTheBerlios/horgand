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

  *Chorus_X += a[0].Chorus_LFO_Speed * increment;

  if (*Chorus_X > 1) *Chorus_X =0.0f;

  out=Fsin(*Chorus_X*D_PI)*Chorus_LFO_Frequency;
  
  return (out);
  
  
};


// Chorus Effect

void 
HOR::Calc_Chorus_LFO_Frequency()

{
Chorus_LFO_Frequency = a[0].modulation*a[0].Chorus_LFO_Amplitude;

};



void
HOR::Effect_Chorus()
{

  int elkel,elkel2;
  float ch_delay= a[0].Chorus_Delay*SAMPLE_RATE/10000.0*3.0;
  float ldelay1,rdelay1,dell,valorl;
  int i;
  float chor_vol=a[0].Chorus_Volume*.5;
  float ms=SAMPLE_RATE/1000.0;
  float dllo;
    
    
  for (i = 0; i < PERIOD; i +=2)

    {
      
      ldelay1=ldelay;
      rdelay1=rdelay;

      // L Channel

      ldelay=ms+ch_delay+Chorus_LFO(&Chorus_X_L);
      dell=(ldelay1*(PERIOD-i)+ldelay*i)/PERIOD;
      elkel=cl_counter-(int)ceil(dell-1.0);
      if (elkel<0) elkel +=8192;
      if (elkel>=8192) elkel -=8192;
      elkel2=elkel-1;
      if (elkel2<0) elkel2 +=8192;
      if (elkel2>=8192) elkel2 -=8192;
      dllo=1.0-fmod(dell,1.0);
      valorl=(dllo*cldelay[elkel])+(cldelay[elkel2]*(1-dllo));
      buf[i]+=valorl*chor_vol;
      cldelay[cl_counter]=buf[i];
      
          
      
      // R Channel
      rdelay=ms+ch_delay+Chorus_LFO(&Chorus_X_R);
      dell=(rdelay1*(PERIOD-i)+rdelay*i)/PERIOD;
      elkel=cl_counter-(int)ceil(dell-1.0);
      if (elkel<0) elkel +=8192;
      if (elkel>=8192) elkel -=8192;
      elkel2=elkel-1;
      if (elkel2<0) elkel2 +=8192;
      if (elkel2>=8192) elkel2 -=8192;
      dllo=1.0-fmod(dell,1.0);
      valorl=(dllo*crdelay[elkel])+(crdelay[elkel2]*(1-dllo));
      buf[i+1]+=valorl*chor_vol;
      crdelay[cl_counter]=buf[i+1];      
      
      if (++cl_counter>=8192) cl_counter=0;
      
 
    }


};


// LFO for Rotary


float
HOR::Rotary_LFO (float t)
{

  float out;

  Rotary_X += a[0].Rotary_LFO_Speed * increment;

  if (Rotary_X > 1) Rotary_X =0.0f;

  out = Fsin (Rotary_X * D_PI) * Rotary_LFO_Frequency;

  return (out);
  
};


// Rotary Effect


void
HOR::Effect_Rotary ()
{
  int i;
  float val ,l, r;

  Rotary_LFO_Frequency = a[0].modulation * a[0].Rotary_LFO_Amplitude * D_PI_to_SAMPLE_RATE;


  for (i = 0; i <PERIOD; i +=2)
    {

      val = Rotary_LFO (Rotary_X)*.5;

         l = buf[i];
         r =  buf[i + 1];
        
      buf[i] -= (l * val);
      buf[i + 1] += (r * val);
      
       
       
    }
};


// Reverb Effect

void
HOR::Effect_Reverb ()

{
  int i,j;
  int elke, elke1;
  float efxoutl;
  float efxoutr;
  float stmp; 
  float tmprvol;
  int a_rperhis=rperhis;
  float rev_vol = Reverb_Volume*.42;
  
    
  for (i = 0; i <PERIOD; i +=2)

    {

     efxoutl = 0.0f;
     efxoutr = 0.0f;
     stmp = 0.0f;
     
     for (j = 0; j<16; j++)
        {
         elke = a_rperhis-a_combl[j];
         if (elke < 0) elke += 262400;
         elke1 =  a_rperhis-a_combr[j];
         if (elke1<0) elke1 +=262400;

         stmp += Reverb_Diffussion*ready_apsg[capsg];
         if (++capsg >15) capsg =0;
         efxoutl += history[elke]*stmp;
         stmp += Reverb_Diffussion*ready_apsg[capsg];
         if (++capsg >15) capsg =0;
         efxoutr += history[elke1]*stmp;
         }
       
                 
      tmprvol = stmp * rev_vol;
       
    
      buf[i] +=  (efxoutl * tmprvol);
      buf[i + 1] += (efxoutr * tmprvol);
                                                   
      a_rperhis +=2;
      if (a_rperhis >262400) a_rperhis -=262400;
    }
};


// Delay Effect

void
HOR::Effect_Delay()
{
  int i;  
  int elke, elke1;
  int delay = (int) a[0].Delay_Delay;
  float voll, volr;
  float Delay_Volumer, Delay_Volumel;
  int a_rperhis=rperhis;


  voll = 1 - Stereo_Side;
  volr = 1 - voll;
  Delay_Volumel = voll * a[0].Delay_Volume;
  Delay_Volumer = volr * a[0].Delay_Volume;


  
  for (i = 0; i <PERIOD; i +=2)

    {
      elke = a_rperhis - delay;    
      if (elke % 2 != 0) elke++;
      if (elke < 0)
	elke = 262400 + elke;
      elke1 = elke + 1;
      if (elke1 < 0)
	elke1 = 262400 + elke1;

      buf[i] +=  (history[elke] * Delay_Volumel * .5);
      buf[i + 1] +=(history[elke1] * Delay_Volumer * .5);
      a_rperhis +=2;
      if (a_rperhis > 262400) a_rperhis -= 262400; 

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
HOR::Clean_Buffer_Effects()
{
memset (history, 0, BUFSIZE * 1024);
memset (cldelay,0,BUFSIZE * 8);
memset (crdelay,0,BUFSIZE * 8);
};


void 
HOR::Write_Buffer_Effects()
{

int i;

      for (i=0; i< PERIOD; i++) 
       {
         history[rperhis] = buf[i];
         if (++rperhis > 262400) rperhis = 0;
       }


};




/*
  horgand - a organ software

 organAccompaniment.C  -  organ accompaniment functions
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
HOR::CogeBass()
{
float l, r, rl, rr;
int i,j,readcounts,readcountr;
int longi;

memset (bbuf, 0, PERIOD8);


longi  = (int) (afina * PERIOD);

readcounts = sf_seek (infileb, 0, SEEK_CUR); 
readcountr = sf_readf_float (infileb, bbuf, longi);

if ((readcounts + longi ) < framesbass) basspending = 1; 

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
int i,j,readcountr,falta; 
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

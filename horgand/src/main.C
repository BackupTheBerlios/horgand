/*
  horgand - a organ software

  main.C  -  Main file of the organ
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
(version2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/





#include <getopt.h>
#include <sched.h>
#include <sys/mman.h>
#include <pthread.h>
#include "Holrgan.h"
#include "HORGAN.h"
#include <math.h>
pthread_t thr1, thr2;
int kk;
HOR hor;


void pon_realtime()

{
    sched_param scprior;

    scprior.sched_priority=50;
    int prior=sched_setscheduler(0,SCHED_FIFO,&scprior);
    if (prior==0) printf("SCHED_FIFO\n");

};


void *
thread1 (void *arg)
{
   pon_realtime();
  while (Pexitprogram ==0)  hor.midievents(1);
  return (0);
};

void *
thread2 (void *arg)
{
    
    pon_realtime();
    while (Pexitprogram ==0)  hor.Alg1s(hor.PERIOD,0);
    return(0);

};


int main(int argc, char *argv[])

{

  fprintf (stderr,
	   "horgand v1.08 - Copyright (c) 2003-2004 Josep Andreu (Holborn)\n");
  if (argc == 1)
    fprintf (stderr, "Try 'horgand --help' for command-line options.\n");


  struct option opts[] = {
    {"load", 1, NULL, 'l'},
    {"bank", 1, NULL, 'b'},
    {"rhyt", 1, NULL, 'r'},
    {"help", 0, NULL, 'h'},
    {0, 0, 0, 0}
  };

  
  Pexitprogram = 0;
  commandline = 0;


  opterr = 0;
  int option_index = 0, opt, exitwithhelp = 0;
  while (1)
    {
      opt = getopt_long (argc, argv, "l:b:r:h", opts, &option_index);
      char *optarguments = optarg;
      
      if (opt == -1)
	break;


      switch (opt)
	{
	case 'h':
	  exitwithhelp = 1;
	  break;
                                          
	case 'l':
	  if (optarguments != NULL)
	    {
              commandline = 1;
	      hor.loadfile (optarguments);
	      break;
	    }
        case 'r' :
            if (optarguments != NULL)
            {
              hor.loadrhyt (optarguments);
              break;
            }

	case 'b':
	  if (optarguments != NULL)
	    {
	      hor.loadbank (optarguments);

	      break;
	    }


	};
    };

  if (exitwithhelp != 0)
    {
      fprintf (stderr, "Usage: Horgand [OPTION]\n\n");
      fprintf (stderr, "  -h ,     --help \t\t\t display command-line help and exit\n");
      fprintf (stderr, "  -l File, --load=File \t\t\t loads sound\n");
      fprintf (stderr, "  -b File, --bank=File \t\t\t loads bank\n");
      fprintf (stderr, "  -r File, --rhyt=File \t\t\t loads rhythm\n");

      fprintf (stderr, "\n\n");
      return (0);
    };

  mlockall(MCL_CURRENT | MCL_FUTURE);
  
  HORGAN *horUI = new HORGAN(&hor);


  pthread_mutex_init (&mutex, NULL);
  pthread_create (&thr1, NULL, thread1, NULL);
  if (hor.Salida < 3)  pthread_create (&thr2, NULL, thread2, NULL);
 
  

  while (Pexitprogram == 0)
    { 
      Fl::wait();
      if (vumvum != vum) horUI->VUI1->value(vum);
      
      if (hor.riton != 0) if (tum != horUI->VUI2->value()) horUI->VUI2->value(tum);
      if (cambialo == 1) 
      {
       horUI->ACI->label(NombreAcorde);
       cambialo = 0;
      }

      if (programa != 0)
	{ 
          
 	  horUI->PutCombi (programa);
	  programa = 0;
	}

         
    }

if (hor.Salida == 3)  jack_client_close(hor.jackclient);
if (hor.Salida == 2)  snd_pcm_close (hor.playback_handle);
if (hor.Salida == 1)  close(hor.snd_handle);


  free(hor.nsin);
  free(hor.lsin);    
  free(hor.history);
  free(hor.buf);
  free(hor.wbuf);
  pthread_mutex_destroy (&mutex);
  delete horUI;

};


int jackprocess(jack_nframes_t nframes,void *arg)

{

pthread_mutex_lock(&mutex);


  int l1, l2, i,j;
  float sound = 0;
  float enve0, enve1 = 0;

   jack_default_audio_sample_t *outl = (jack_default_audio_sample_t*)
   jack_port_get_buffer(hor.outport_left, nframes);
   jack_default_audio_sample_t *outr = (jack_default_audio_sample_t*)
   jack_port_get_buffer(hor.outport_right, nframes);


   memset(outl, 0, hor.PERIOD2 * sizeof(jack_default_audio_sample_t));
   memset(outr, 0, hor.PERIOD2 * sizeof(jack_default_audio_sample_t));
   memset (hor.buf, 0, hor.PERIOD8);

   hor.freqplfo =  hor.modulation * hor.LFOpitch * hor.lalapi;




  for (l2 = 0; l2 < POLY; l2++)
    {

      if (hor.note_active[l2])
        {
          hor.MiraNota(l2);

          hor.aplfo = hor.PLFO(hor.env_time[l2]);

          hor.decay = 0.0;
          hor.sustain = 0.99;          
          enve0 = hor.Jenvelope (&hor.note_active[l2], hor.gate[l2], hor.env_time[l2], l2);
          hor.decay = 0.30;
          hor.sustain = 0.0;        
          enve1 = hor.Jenvelope (&hor.note_active[l2], hor.gate[l2], hor.env_time[l2], l2); 

          hor.miraalfo(l2);
          


          for (i=1; i<=10; i++)
            {
             if (hor.Operator[i].mar) hor.envi[l2]=enve1; else hor.envi[l2]=enve0;
             hor.volumeOpC(i,l2);
             if (hor.Operator[i].con1 > 0)
             {
             hor.f[i].dphi =  hor.partial * hor.pitchOp(i,l2);
            if (hor.f[i].dphi > D_PI) hor.f[i].dphi -= D_PI;
             }
             }



          for (l1 = 0; l1 <hor.PERIOD2; l1 += 2)
            {

              sound=0;
              
              for (i=1; i<=10; i++)
              {
              hor.f[i].phi[l2] += hor.f[i].dphi;
              if (hor.f[i].phi[l2] > D_PI) hor.f[i].phi[l2] -= D_PI;
              sound += hor.Operator[i].con1 * hor.Fsin(hor.f[i].phi[l2]);
              }

              hor.buf[l1] += sound * hor.omaster;
              hor.buf[l1+1] += sound * hor.omaster;
              hor.env_time[l2] += hor.incre;
             }

        }


    }

if (hor.choron == 1 ) hor.bchorus();
if (hor.rota == 1 )  hor.rotary();
if (hor.echoon == 1) hor.procesa();
if (hor.revon == 1)  hor.reverb();
if (hor.riton == 1)  hor.CogeRitmo();


for (i=0; i<hor.PERIOD; i++)
{
 j = 2 * i;
 outl[j]=hor.buf[j] * hor.master;
 outr[j]=hor.buf[j+1] * hor.master;
 outl[j+1]=hor.buf[j] * hor.master;
 outr[j+1]=hor.buf[j+1] * hor.master;
}

pthread_mutex_unlock(&mutex);
return(0);

};


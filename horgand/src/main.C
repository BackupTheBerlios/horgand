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
HOR hor;



// Put Kernel RT priority to a thread

void pon_realtime()

{
    sched_param scprior;

    scprior.sched_priority=50;
    int prior=sched_setscheduler(0,SCHED_FIFO,&scprior);
    if (prior==0) printf("SCHED_FIFO\n");
};


// MIDI Input thread ( Read MIDI incoming messages)

void *
thread1 (void *arg)
{
  pon_realtime();
  while (Pexitprogram ==0)  hor.midievents(1);

  return (0);
};


// Audio thread

void *
thread2 (void *arg)
{
    pon_realtime();
    while (Pexitprogram ==0)  hor.Alg1s(hor.PERIOD,0);

    return(0);

};


int main(int argc, char *argv[])

{

// Read command Line

  fprintf (stderr,
	   "horgand v1.09 - Copyright (c) 2003-2007 Josep Andreu (Holborn)\n");
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
    
    
  //Locks memory

  mlockall(MCL_CURRENT | MCL_FUTURE);
  
  // Launch GUI

  HORGAN *horUI = new HORGAN(&hor);


  pthread_mutex_init (&mutex, NULL);

  // Launch MIDI thread

  pthread_create (&thr1, NULL, thread1, NULL);

  // Launch AUDIO thread for ALSA and OSS, not for JACK
  
  if (hor.Salida < 3)  pthread_create (&thr2, NULL, thread2, NULL);
 
  
  // Main  

  while (Pexitprogram == 0)
    { 
 
      // Refresh GUI
      Fl::wait();
      
      // Refresh MIDI Input Level on GUI
      if (LastMidiInLevel != MidiInLevel) horUI->VUI1->value(MidiInLevel);
      
      // Refresh Bar Lead of Drum Loops
      if (hor.Rhythm_On != 0) if (BarLead != horUI->VUI2->value()) horUI->VUI2->value(BarLead);

      // Refresh Chord Names

      if (changeNameChord == 1) 
      {
       horUI->ACI->label(NameChord);
       changeNameChord = 0;
      }
      // If MIDI Program Change Message arrives change preset

      if (preset != 0)
	{ 
          
 	  horUI->PutCombi (preset);
	  preset = 0;
	}

         
    }


    // Exit  Close Audio devices

if (hor.Salida == 3)  jack_client_close(hor.jackclient);
if (hor.Salida == 2)  snd_pcm_close (hor.playback_handle);
if (hor.Salida == 1)  close(hor.snd_handle);

    // free memory etc.

  free(hor.lsin);    
  free(hor.history);
  free(hor.buf);
  free(hor.wbuf);
  pthread_mutex_destroy (&mutex);
  delete horUI;

};


// JACK Audio thread

int jackprocess(jack_nframes_t nframes,void *arg)

{

pthread_mutex_lock(&mutex);


  int l1, l2, i,j;
  float sound = 0;
  int output_yes=0;

   jack_default_audio_sample_t *outl = (jack_default_audio_sample_t*)
   jack_port_get_buffer(hor.outport_left, nframes);
   jack_default_audio_sample_t *outr = (jack_default_audio_sample_t*)
   jack_port_get_buffer(hor.outport_right, nframes);


   memset(outl, 0, hor.PERIOD2 * sizeof(jack_default_audio_sample_t));
   memset(outr, 0, hor.PERIOD2 * sizeof(jack_default_audio_sample_t));
   memset (hor.buf, 0, hor.PERIOD8);

   hor.LFO_Frequency =  hor.modulation * hor.LFOpitch * hor.D_PI_to_SAMPLE_RATE;
   if (hor.LFO_Frequency > D_PI ) hor.LFO_Frequency=fmod(hor.LFO_Frequency,D_PI);



  for (l2 = 0; l2 < POLY; l2++)
    {

      if (hor.note_active[l2])
        {
          output_yes=1;
      
          hor.Get_Partial(l2);

          if (hor.LFOpitch > 0 ) hor.LFO_Volume = hor.Pitch_LFO(hor.env_time[l2]);
          
          hor.Envelope_Volume[l2]=hor.Jenvelope (&hor.note_active[l2], hor.gate[l2], hor.env_time[l2], l2);

                    

          for (i=1; i<=10; i++)
            {
             hor.volume_Operator(i,l2);
             
                  if (hor.Operator[i].con1 > 0)
                       {
                         hor.f[i].dphi =  hor.partial * hor.pitch_Operator(i,l2);
                         if (hor.f[i].dphi > D_PI) hor.f[i].dphi = fmod(hor.f[i].dphi,D_PI);
                       }
             }



          for (l1 = 0; l1 <hor.PERIOD2; l1 += 2)
            {

              sound=0;
              
              for (i=1; i<=10; i++)
                   {
                      if (hor.Operator[i].con1>0)
                        {
                          hor.f[i].phi[l2] += hor.f[i].dphi;
                          if (hor.f[i].phi[l2] > D_PI) hor.f[i].phi[l2] = fmod(hor.f[i].phi[l2],D_PI);
                          sound += hor.Operator[i].con1 * hor.Fsin(hor.f[i].phi[l2]);
                        }
                    }
              
              hor.buf[l1] += sound * hor.Organ_Master_Volume * .5;
              hor.buf[l1+1] = hor.buf[l1];
              hor.env_time[l2] += hor.increment;
             }  

        }


    }

if(output_yes)
{
if (hor.E_Chorus_On == 1 ) hor.Effect_Chorus();
if (hor.E_Rotary_On == 1 )  hor.Effect_Rotary();
}
if (hor.E_Delay_On == 1) hor.Effect_Delay();
if (hor.E_Reverb_On == 1)  hor.Effect_Reverb();
if (hor.Rhythm_On == 1)  hor.Get_Rhythm();


for (i=0; i<hor.PERIOD; i++)
{
 j = 2 * i;
 outl[j]=hor.buf[j] * hor.Master_Volume;
 outr[j]=hor.buf[j+1] * hor.Master_Volume;
 outl[j+1]=hor.buf[j] * hor.Master_Volume;
 outr[j+1]=hor.buf[j+1] * hor.Master_Volume;
}

pthread_mutex_unlock(&mutex);
return(0);

};


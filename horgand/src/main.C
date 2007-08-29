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
#include <math.h>
#include "Holrgan.h"
#include "HORGAN.h"
#include "jackoutput.h"

HOR hor;
pthread_t thr1, thr2;



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
  while (Pexitprogram ==0) 
   {
   pthread_mutex_lock(&m_mutex);
   hor.midievents(1);
   pthread_mutex_unlock(&m_mutex);
   }
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
	   "\n%s %s - Copyright (c) 2003-2007 Josep Andreu (Holborn)\n",PACKAGE,VERSION);
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
  int option_index = 0, opt;
  exitwithhelp = 0;
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
  

  hor.init_hor();
  
  if (hor.Salida < 3) hor.Adjust_Audio();

  // Launch GUI
  
  HORGAN *horUI = new HORGAN(argc,argv,&hor);
 
  
  // Launch MIDI thread

  pthread_mutex_init (&mutex, NULL);
  pthread_mutex_init (&m_mutex, NULL);

  pthread_create (&thr1, NULL, thread1, NULL);

  // Launch AUDIO thread for ALSA and OSS, not for JACK
  

  if (hor.Salida < 3)  pthread_create (&thr2, NULL, thread2, NULL); 

  if (hor.Salida==3)
  {
     JACKstart(&hor);
     hor.Adjust_Audio();
  }   
  
  
  // Main  

  while (Pexitprogram == 0)
 { 

 
      // Refresh GUI
     Fl::wait(0.01);
      
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

       if (horUI->CPrograma->active())
       {
        if (preset != 0)
        {
 	  horUI->PutCombi (preset);
	  preset = 0;
	}
          
       } else preset = 0; 
         
 }


    // Exit  Close Audio devices

  hor.CloseAudio(hor.Salida);

    // free memory etc.

  free(hor.lsin);    
  free(hor.history);
  free(hor.buf);
  free(hor.wbuf);
  pthread_mutex_destroy (&mutex);
  delete horUI;

};













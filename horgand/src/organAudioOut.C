/*
  horgand - a organ software

 organAudioOUT.C  -  Audio OUT functions
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
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <math.h>


// Convert fload to short to send to the devices

void
HOR::Final_Output ()
{
  int i,j;
  short sl,sr;
  memset (wbuf, 0, PERIOD4);
  
  
  for (i = 0; i < PERIOD; i +=2)
    { 
    
      j = i*2;            
      // 32767.0      

      sl = (short) (buf[i]  * Master_Volume * 32767.0);
      sr = (short) (buf[i+1] * Master_Volume * 32767.0);
      wbuf[j] = sl;
      wbuf[j+1]=sr;
     
      
    }
};





// OSS AUDIO OUT Check and prepare

void
HOR::ossaudioprepare ()
{

  int snd_bitsize = 16;
  SAMPLE_RATE = DSAMPLE_RATE;
  snd_fragment = 0x00080009;
  snd_stereo = 1;
  snd_format = AFMT_S16_LE;
  snd_samplerate = SAMPLE_RATE;
  PERIOD = MPERIOD;
  Put_Period ();
  snd_handle = open ("/dev/dsp", O_WRONLY, 0);
  if (snd_handle == -1)
    {
      fprintf (stderr, "ERROR - I can't open  /dev/dsp \n");
      return;
    };
  ioctl (snd_handle, SNDCTL_DSP_RESET, NULL);

  ioctl (snd_handle, SNDCTL_DSP_SETFMT, &snd_format);
  ioctl (snd_handle, SNDCTL_DSP_STEREO, &snd_stereo);
  ioctl (snd_handle, SNDCTL_DSP_SPEED, &snd_samplerate);
  ioctl (snd_handle, SNDCTL_DSP_SAMPLESIZE, &snd_bitsize);
  ioctl (snd_handle, SNDCTL_DSP_SETFRAGMENT, &snd_fragment);


};

// ALSA AUDIO OUT Check and prepare

void
HOR::alsaaudioprepare ()
{
  char pcm_name[50];
  sprintf (pcm_name, "plughw:0,0");


  if (snd_pcm_open (&playback_handle, pcm_name, SND_PCM_STREAM_PLAYBACK, 0) <
      0)
    {
      fprintf (stderr, "cannot open audio device %s\n", pcm_name);
      exit (1);
    }
  PERIOD = MPERIOD;
  SAMPLE_RATE=DSAMPLE_RATE;
  Put_Period ();
  snd_pcm_hw_params_alloca (&hw_params);
  snd_pcm_hw_params_any (playback_handle, hw_params);
  snd_pcm_hw_params_set_access (playback_handle, hw_params,
				SND_PCM_ACCESS_RW_INTERLEAVED);
  snd_pcm_hw_params_set_format (playback_handle, hw_params,
				SND_PCM_FORMAT_S16_LE);
  snd_pcm_hw_params_set_rate (playback_handle, hw_params, SAMPLE_RATE, 0);
  snd_pcm_hw_params_set_channels (playback_handle, hw_params, 2);

  snd_pcm_hw_params_set_periods (playback_handle, hw_params, 2, 0);
  snd_pcm_hw_params_set_period_size (playback_handle, hw_params, PERIOD, 0);
  snd_pcm_hw_params (playback_handle, hw_params);
  snd_pcm_sw_params_alloca (&sw_params);
  snd_pcm_sw_params_current (playback_handle, sw_params);
  snd_pcm_sw_params_set_avail_min (playback_handle, sw_params, PERIOD);
  snd_pcm_sw_params (playback_handle, sw_params);


};

// JACK Audio Check and Prepare


void
HOR::jackaudioprepare ()
{

  jackclient = jack_client_new ("Horgand");
  if (jackclient == 0)
    {
      fprintf (stderr, "Cannot make a jack client\n");
      exit (1);
    };
  SAMPLE_RATE=DSAMPLE_RATE;
  fprintf (stderr, "Internal SampleRate   = %d\nJack Output SampleRate= %d\n",
	   SAMPLE_RATE, jack_get_sample_rate (jackclient));
  if ((unsigned int) jack_get_sample_rate (jackclient) !=
      (unsigned int) SAMPLE_RATE)
    fprintf (stderr,
	     "Adjusting SAMPLE_RATE to jackd.\n");

  SAMPLE_RATE = jack_get_sample_rate(jackclient);
  jack_set_process_callback (jackclient, jackprocess, 0);
  PERIOD = jack_get_buffer_size (jackclient);
  Put_Period ();
  outport_left = jack_port_register (jackclient, "out_1",
				     JACK_DEFAULT_AUDIO_TYPE,
				     JackPortIsOutput | JackPortIsTerminal,
				     0);
  outport_right =
    jack_port_register (jackclient, "out_2", JACK_DEFAULT_AUDIO_TYPE,
			JackPortIsOutput | JackPortIsTerminal, 0);



  if (jack_activate (jackclient))
    {
      fprintf (stderr, "Cannot activate jack client\n");
      exit (1);
    };

  jack_connect (jackclient, jack_port_name (outport_left),
		"alsa_pcm:playback_1");
  jack_connect (jackclient, jack_port_name (outport_right),
		"alsa_pcm:playback_2");

};







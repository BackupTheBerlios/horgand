/*
  horgand - a organ software

 organ.MIDIIn.C  -  organ functions
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
HOR::midievents (int keIN)
{

  int l1;
  snd_seq_event_t *midievent;

  midievent = NULL;
  snd_seq_event_input (MidiInPuerto[keIN].midi_in, &midievent);
  if (midievent == NULL)
    return;


  switch (midievent->type)
    {
    case SND_SEQ_EVENT_PITCHBEND:
      pitch = (float) midievent->data.control.value / 8192.0;
      break;

    case SND_SEQ_EVENT_PGMCHANGE:


      if ((midievent->data.control.value > 0)
	  && (midievent->data.control.value < 33))
	programa = midievent->data.control.value;


      break;


    case SND_SEQ_EVENT_CONTROLLER:

      if (midievent->data.control.param == 1)
	modulation = (float) midievent->data.control.value / 12.7;

      if (midievent->data.control.param == 7)
	master = (float) midievent->data.control.value / 127.0;

      if (midievent->data.control.param == 64)
	{
	  if (midievent->data.control.value < 64)
	    pedal = 0;
	  if (midievent->data.control.value > 63)
	    pedal = 1;
	}



      break;




    case SND_SEQ_EVENT_NOTEON:

      if (midievent->data.note.velocity != 0)
	{
	  for (l1 = 0; l1 < POLY; l1++)
	    {
	      if (!note_active[l1])
		{
		  rnote[l1] = midievent->data.note.note;
		  note[l1] = rnote[l1];
		  vumvum = vum;
		  vum = midievent->data.note.velocity;
		  velocity[l1] = midievent->data.note.velocity / 127.0;

		  if ((split == 1) && (rnote[l1] < 60))
		    {
                     
		      note[l1] += 24;
		      velocity[l1] /= 2;
		    }

		  env_time[l1] = 0;
		  gate[l1] = 1;
		  note_active[l1] = 1;
                  MiraChord();
                  break;
		}
	    }
	  break;
	}
      else
	{
	  vumvum = vum;
	  vum = 0;
	  for (l1 = 0; l1 < POLY; l1++)
	    {

	      if (gate[l1] && note_active[l1]
		  && (rnote[l1] == midievent->data.note.note))
		{
		  env_time[l1] = 0;
		  gate[l1] = 0;
                  MiraChord();
		}

	    }
	}
      break;

    case SND_SEQ_EVENT_NOTEOFF:

      vumvum = vum;
      vum = 0;
      for (l1 = 0; l1 < POLY; l1++)
	{

	  if (gate[l1] && note_active[l1]
	      && (rnote[l1] == midievent->data.note.note))
	    {
	      env_time[l1] = 0;
	      gate[l1] = 0;
              MiraChord();
	    }

	}
      break;
    }

};


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

// Read MIDI Events




void
HOR::midievents (int keIN)
{

  int l1;
  snd_seq_event_t *midievent;
  midievent = NULL;
  snd_seq_event_input (MidiInPuerto[keIN].midi_in, &midievent);
  if (midievent == NULL) return;
  if(midievent->type == 42) return;

  switch (midievent->type)
    {
    case SND_SEQ_EVENT_PITCHBEND:
      pitch = (float) midievent->data.control.value / 8192.0;
      break;

    case SND_SEQ_EVENT_PGMCHANGE:


      if ((midievent->data.control.value > 0)
	  && (midievent->data.control.value < 33))
	preset = midievent->data.control.value;


      break;


    case SND_SEQ_EVENT_CONTROLLER:

      if (midievent->data.control.param == 1)
	{
	modulation = (float) midievent->data.control.value / 12.7;
        Calc_LFO_Frequency();
        Calc_Chorus_LFO_Frequency();
        }
 
      if (midievent->data.control.param == 91)
              Reverb_Volume = (float) midievent->data.control.value / 256.0;

      if (midievent->data.control.param == 93)
              Chorus_Volume = (float) midievent->data.control.value / 128.0;
            
      if (midievent->data.control.param == 7)
	Master_Volume = (float) midievent->data.control.value / 128.0;

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
		  LastMidiInLevel = MidiInLevel;
		  MidiInLevel = midievent->data.note.velocity;
		  velocity[l1] = midievent->data.note.velocity / 254.0;

		  if ((split) && (rnote[l1] < 60))
		    {
                     
		      note[l1] += 24;
		      velocity[l1] *= .3;
		    }

		  env_time[l1] = 0;
		  gate[l1] = 1;
		  note_active[l1] = 1;
                  if (split) Get_Chord();
                  break;
		}
	    }
	  break;
	}
      else
	{
	  LastMidiInLevel = MidiInLevel;
	  MidiInLevel = 0;
	  for (l1 = 0; l1 < POLY; l1++)
	    {

	      if (gate[l1] && note_active[l1]
		  && (rnote[l1] == midievent->data.note.note))
		{
                  gate[l1] = 0;
                  env_time[l1] = 0;
                  if (split) Get_Chord();
		}

	    }
	}
      break;












    case SND_SEQ_EVENT_NOTEOFF:

      LastMidiInLevel = MidiInLevel;
      MidiInLevel = 0;
      for (l1 = 0; l1 < POLY; l1++)
	{

	  if (gate[l1] && note_active[l1]
	      && (rnote[l1] == midievent->data.note.note))
	    {
              gate[l1] = 0;
              env_time[l1] = 0;
              Get_Chord();
	    }

	}
      break;
    }

};


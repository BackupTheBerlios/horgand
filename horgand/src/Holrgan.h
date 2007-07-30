/*
  horgand - a organ software
  
  Holrgan.h  -  Variable Definitions and functions
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
 (version2)  along with this program; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
                            
*/

                            
#ifndef DXEMU_H
#define DXEMU_H
#include <pthread.h>
#include <alsa/asoundlib.h>
#include <jack/jack.h>
#include <sndfile.h>
#define MPERIOD  128
#define BUFSIZE 1024
#define POLY 16
#define DSAMPLE_RATE 44100
#define D_PI 6.283184

extern pthread_mutex_t mutex;
extern int Pexitprogram, waitforGUI, UndoCount, preset,MidiInLevel,LastMidiInLevel,BarLead,changeNameChord;
extern int Signal_for_Cb_Sliders,commandline;
extern char NameChord[16];
extern int prefix_trick,Selected_Rhythm;
int  Alg1sj (jack_nframes_t nframes,void *arg);
int  jackprocess (jack_nframes_t nframes,void *arg);


class HOR
{



public:

   HOR ();
  ~HOR ();

  void midievents (int i);
  void panic();
  void Put_Period();
  void Alg1s (int frames, void*);
  float Jenvelope(int *note_active, int gate, float t, int nota);
  void Get_Partial(int note);
  float Chorus_LFO(float *t);
  float Rotary_LFO(float t);  
  float Pitch_LFO(float t);
  void Get_Keyb_Level_Scaling(int note);
  void savefile(char *filename);
  void loadfile(char *filename);
  void savebank(char *filename);
  void loadbank(char *filename);
  void New();
  float pitch_Operator(int i, int note);      
  void volume_Operator(int i, int note);
  void Effect_Delay();
  void Effect_Reverb();
  void delayclean();
  void chorusclean();
  void reverbclean();
  float Fsin(float x);
  float fastabs(float f);
  void Final_Output();
  void Effect_Rotary();
  void Effect_Chorus();
  void ossaudioprepare();
  void alsaaudioprepare();
  void jackaudioprepare();
  int Select_Rhythm(char *nomrit);
  void Get_Rhythm();
  void Select_Bass(char *nomrit);
  void Get_Bass();
  void Get_Bass_Line();
  void Get_Chord();  
  void Get_Tempo();
  void loadrhyt(char *filename);
  void saverhyt(char *filename);
  void MUndo();
  void MRedo();
  void MActu();
  void PutPrim();
  void MGetPrim();
  
  SNDFILE *infile;
  SF_INFO sfinfo;
  SNDFILE *infileb;
  SF_INFO sfinfob;
  int cpreset;
  int marimba;
  int PERIOD;
  unsigned int SAMPLE_RATE;
  int PERIOD2;
  int PERIOD4;
  int PERIOD8;
  float *lsin;
  float *buf;
  short *wbuf;
  float *rbuf;
  float *bbuf;
  float *history;
  float *ehistoryl;
  float *ehistoryr;
  float sound;
  float partial;
  float velocity[POLY];
  float pitch;
  float modulation;
  float freq_note;
  float env_time[POLY];
  float Rotary_LFO_Speed;
  float Pitch_LFO_Speed;
  float Pitch_LFO_Delay;
  float Rotary_LFO_Amplitude;
  float LFOpitch;
  int  note[POLY];
  int rnote[POLY];
  int  gate[POLY];
  float Envelope_Volume[POLY];
  int  note_active[POLY];
  float  mastertune;
  float lasfreq[64];
  int E_Rotary_On;
  float  Master_Volume;
  float Organ_Master_Volume;
  int pedal;
  int perhis;
  int rperhis;
  int hrperhis;
  int eperhis;
  char *c_name;  
  char Name[36];  
  int E_Delay_On;
  int transpose;
  float Delay_Volume;
  float Delay_Delay;
  float Stereo_Side; 
  int To_Stereo_Side;
  float attack;
  float decay;
  float sustain;
  float release;
  float LFO_Volume;
  float Keyb_Level_Scaling; 
  float detune;
  float LFO_Frequency;
  float Rotary_LFO_Frequency;
  float Rotary_X;
  float Chorus_X_R;
  float Chorus_X_L;
  float Chorus_LFO_Speed;
  float Chorus_LFO_Amplitude;
  float Chorus_LFO_Frequency;
  float Chorus_Volume;  
  int E_Chorus_On;            
  float Chorus_Delay;
  int split;
  float ldelay,ldelay1;
  float rdelay,rdelay1;
  float Reverb_Preset;  
  int Salida;
  float increment;
  float D_PI_to_SAMPLE_RATE; 
  float E_Reverb_On;
  float Reverb_Time;
  float Reverb_Diffussion;
  float Reverb_Volume;
  int combl[16];
  int combr[16];
  int apsg[16];
  int capsg;         
  int apss;
  int Bass_On;
  int Rhythm_On;
  float Bass_Volume;
  float Rhythm_Volume;
  float tempo;                  
  int Samples_Readed;
  int Line_Bass_Note[66];
  int Line_Bass_Velocity[66];
  int frame_total_size;
  int fractional_position;
  int basspending;
  // pos means musical subdivision 1/16 position
  int pos;
  // lpos meas last musical subdivision 1/16 checked for bass line
  int lpos;    
  int bass_note;
  float length_bass_note;
  float frames_bass;
  int chord;  
  int fundamental;
  float bass_velocity;
  int bars;
  int quarter_note;
  int chord_type;
  int Num_Rhythm;  
  int bass_transpose;
  int bmt;
//ae means the selected rhythm
  int ae;
  int pattern_bars;
  int file_ok;
  char BankFilename[128];


  
struct Rhythm
{
 char Nom[30];
 char Nfile[256];
 int bars;
 int quarter_note;
 int Line_Bass_Note[68];
 int Line_Bass_Velocity[68];

} Rt[22];



struct NomChord
{
 char Nom[3];
} NC[13];
 

struct AfinaBass

{
float tune;
float bmt;
} AB[13];


struct TipoCh

{
int third;
int five_th;
int seven_th;

} TCh[12];


struct Ch3

{
 int type;  
 int fund;
 int dist1;
 int dist2;
 char Nom[10];
} Chord3[15];

struct Ch4

{
  int type;
  int fund;
  int dist1;
  int dist2;
  int dist3;
  char Nom[10];
} Chord4[50];
     
struct Ch5

{
  int type;
  int fund;
  int dist1;
  int dist2;
  int dist3;
  int dist4;
  char Nom[10];
} Chord5[12];
     


 
  
struct OperatorPar

 {
 int harmonic;
 float harmonic_fine;
 float volumen;
 float con1;
 int marimba; 
 }    
   Operator[11];

struct Todolo

  { OperatorPar Operator[11];

   float modulation;
   float Delay_Volume;
   float Pitch_LFO_Speed;
   float Pitch_LFO_Delay;
   float Rotary_LFO_Speed;
   float LFOpitch;
   float attack;
   float E_Reverb_On;
   float detune;
   int transpose;
   int E_Rotary_On;
   float Organ_Master_Volume;
   int E_Delay_On;
   float Delay_Delay;
   int split;
   int E_Chorus_On;
   float Chorus_Delay;
   float Chorus_LFO_Amplitude;
   float Chorus_LFO_Speed;
   float Reverb_Preset;
   float Chorus_Volume;
   char *nombre;
   char Name[36];





} Banco[35], Undo[100], Prim[2];
    
  char temporal[8]; 
    
 // ALSA Audio 
  
  snd_pcm_t *playback_handle;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_sw_params_t *sw_params;
                


// OSS Audio

  int snd_handle;
  int snd_fragment;
  int snd_stereo;
  int snd_format;
  int snd_samplerate;
  short int *smps;    
  
// JACK Audio

jack_client_t *jackclient;
jack_port_t *outport_left,*outport_right;
                                


  struct freqVarios

  {   
    float phi[POLY];
    float phi_mod[POLY];
    float dphi;
    float dphi_mod;
    float sphi[POLY];
    float sphi_mod[POLY];
  } f[21];
  


  struct Menoscalculos
  
  { 
    float f1,f2,f3;
  }  h[193];

  
  struct PuertoMidiIn
  {
    int YOIN, SettingsIN;
    char *SMidiIn;
    char pMIDIIN[256];
    char SetMidiIn[40];
    int Ports;
    snd_seq_t *midi_in;
    unsigned char IN[16];
  }
  MidiInPuerto[3];

struct PMidiOut
  {
   int Client, Port;
   char Name[40], Info[40];
   const char *CName, *CInfo;
            
   } CPOMidiS[50];
                               

  struct PMidiIn
  {
    int Client, Port;
    char Name[40], Info[40];
    const char *CName, *CInfo;

  } CPIMidiS[50];


};

#endif

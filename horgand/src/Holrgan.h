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
#include <signal.h>
#include <alsa/asoundlib.h>
#include <sndfile.h>
#include "config.h"
#define MPERIOD  128
#define BUFSIZE 1024
#define POLY 32
#define DSAMPLE_RATE 44100
#define D_PI 6.283184

extern pthread_mutex_t mutex, m_mutex;
extern int Pexitprogram, UndoCount, preset,MidiInLevel,LastMidiInLevel,BarLead,changeNameChord;
extern int Signal_for_Cb_Sliders,commandline;
extern char NameChord[16];
extern int Selected_Rhythm;


class HOR
{



public:

   HOR ();
  ~HOR ();

  void  init_hor();
  void Adjust_Audio();
  float Fsin(float x);
  void Alg1s (int frames, void*);
  float Jenvelope(int *note_active, int gate, float t, int nota);
  float Penvelope(int *note_active, int gate, float t, int nota);
  float Get_Partial(int note);
  float Chorus_LFO(float *t);
  float Rotary_LFO(float t);  
  float Pitch_LFO(float t);
  void Calc_LFO_Frequency();
  void Calc_Chorus_LFO_Frequency();
  void Write_Buffer_Effects();
  float Get_Keyb_Level_Scaling(int note);
  void midievents (int i);
  float pitch_Operator(int i, int note);      
  float pitch_Operator2(int i, int note);      
  void volume_Operator(int i, int note);
  void Effect_Delay();
  void Effect_Reverb();
  void Clean_Buffer_Effects();
  void Final_Output(int S_Output);
  void Effect_Rotary();
  void Effect_Chorus();
  int Select_Rhythm(char *nomrit);
  void Get_Rhythm();
  void Select_Bass(char *nomrit);
  void Get_Bass();
  void Get_Bass_Line();
  void Get_Chord();  
  void Get_Tempo();
  void New();
  void PonDATA_Undo(int Undonumber);
  void MUndo();
  void MRedo();
  void MActu();
  void PutPrim();
  void MGetPrim();
  void panic();
  void loadbank(char *filename);
  void loadrhyt(char *filename);
  void Put_Period();
  void ossaudioprepare();
  void alsaaudioprepare();
  void savefile(char *filename);
  void loadfile(char *filename);
  void savebank(char *filename);
  void saverhyt(char *filename);
  void Conecta();
  void disconectaaconnect();
  void conectaaconnect();
  void CloseAudio(int i);
  void Get_Combi_t(int i);
  void Put_Combi_t(int i);
  void syncadsr();

  snd_seq_t *midi_in;
  
  float ldelay,rdelay;
  float *lsin;
  float *buf;
  short *wbuf;
  float *rbuf;
  float *bbuf;
  float *history;
  float *cldelay;
  float *crdelay;
  float attack;
  float decay;
  float sustain;
  float release;
  float p_attack;
  float p_decay;
  float p_sustain;
  float p_release;
  float u_attack;
  float u_p_attack;
  float u_decay;
  float u_p_decay;
  float u_release;
  float u_p_release;
  
  
  int PERIOD;
  unsigned int SAMPLE_RATE;
  int PERIOD2;
  int PERIOD4;
  int PERIOD8;
  float velocity[POLY];
  float pitch;
  float modulation;
  float env_time[POLY];
  float Rotary_LFO_Speed;
  float Pitch_LFO_Speed;
  float Pitch_LFO_Delay;
  float Rotary_LFO_Amplitude;
  float LFOpitch;
  float Keyb_Level_Scaling;
  int  note[POLY];
  int rnote[POLY];
  int  gate[POLY];
  float Envelope_Volume[POLY];
  float Perc_Volume[POLY];
  int  note_active[POLY];
  float  mastertune;
  float lasfreq[24];
  float Normalize[24];
  int E_Rotary_On;
  float  Master_Volume;
  float Organ_Master_Volume;
  int pedal;
  int rperhis;
  char *c_name;  
  char Name[64];  
  int E_Delay_On;
  int transpose;
  int organ_transpose;
  float Delay_Volume;
  float Delay_Delay;
  float Stereo_Side; 
  int To_Stereo_Side;
  float LFO_Volume;
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
  int cl_counter;
  float Chorus_Delay;
  int split;
  int Reverb_Preset;  
  int Salida;
  float increment;
  float D_PI_to_SAMPLE_RATE; 
  int E_Reverb_On;
  int Reverb_Time;
  float Reverb_Diffussion;
  float Reverb_Volume;
  int combl[16];
  int combr[16];
  int a_combl[16];
  int a_combr[16];
  int apsg[16];
  float ready_apsg[16];
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
  int cpreset;
  //ae means the selected rhythm
  int ae;
  int pattern_bars;
  int file_ok;
  int TypeRecChord;
  int Bass_Type;
  char BankFilename[128];
  char RhythmFilename[128];
  SNDFILE *infile;
  SF_INFO sfinfo;
  SNDFILE *infileb;
  SF_INFO sfinfob;
  char MID[128];
  int IsCoIn;
  int Cyoin;
  int Pyoin;
  int Ccin;
  int Pcin;

  
struct Rhythm
{
 char Nfile[256];
 int Line_Bass_Note[68];
 int Line_Bass_Velocity[68];
 char Nom[30];
 int bars;
 int quarter_note;

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
 char Nom[10];
 int type;  
 int fund;
 int dist1;
 int dist2;
} Chord3[15];

struct Ch4

{
  char Nom[10];
  int type;
  int fund;
  int dist1;
  int dist2;
  int dist3;
} Chord4[50];
     
struct Ch5

{
  char Nom[10];
  int type;
  int fund;
  int dist1;
  int dist2;
  int dist3;
  int dist4;
} Chord5[12];
     


 
  
struct OperatorPar

 {
 float harmonic_fine;
 float volumen;
 float con1;
 int harmonic;
 int marimba; 
  }    
   Operator[11];

struct Todolo

  { OperatorPar Operator[11];

   char Name[36];

   float Normalize[24];
   float modulation;
   float Delay_Volume;
   float Pitch_LFO_Speed;
   float Pitch_LFO_Delay;
   float Rotary_LFO_Speed;
   float LFOpitch;
   float attack;
   float decay;
   float sustain;
   float p_attack;
   float p_decay;
   float detune;
   float Organ_Master_Volume;
   float Delay_Delay;
   float Chorus_Delay;
   float Chorus_LFO_Amplitude;
   float Chorus_LFO_Speed;
   float Chorus_Volume;
   float Rotary_LFO_Amplitude;
   int E_Reverb_On;
   int organ_transpose;
   int E_Rotary_On;
   int E_Delay_On;
   int split;
   int E_Chorus_On;
   int Reverb_Preset;
   char *nombre;

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
  


  struct freqVarios

  {   
    float phi[POLY];
    float dphi;
    float phi2[POLY];
    float dphi2; 

  } f[11];
  


  struct Menoscalculos
  
  { 
    float f1,f2,f3;
  }  h[192];

};

#endif

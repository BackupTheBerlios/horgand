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
#define MPERIOD  256
#define BUFSIZE 1024
#define POLY 32
#define SAMPLE_RATE 44100
#define D_PI 6.283184

extern pthread_mutex_t mutex;
extern int Pexitprogram, espera, UndoCount, programa,vum,vumvum,tum,cambialo;
extern int vavi,pr,pr1,commandline;
extern char NombreAcorde[16];
extern int solucion,Rit;
int  Alg1sj (jack_nframes_t nframes,void *arg);
int  jackprocess (jack_nframes_t nframes,void *arg);


class HOR
{



public:

   HOR ();
  ~HOR ();

  void midievents (int i);
  void panico ();
  void ponpe();
  void Alg1s (int frames, void*);
  void Jenvelope(int *note_active, int gate, float t, int nota);
  void MiraNota(int note);
  float ELFO(float *kx);
  float LFO(float t);  
  float PLFO(float t);
  void miraalfo(int note);
  void savefile(char *filename);
  void loadfile(char *filename);
  void savebank(char *filename);
  void loadbank(char *filename);
  void New();
  float pitchOp(int i, int note);      
  void volumeOpC(int i, int note);
  void procesa();
  void reverb();
  void procesaclean();
  void chorusclean();
  void rclean();
  float Fsin(float x);
  float fastabs(float f);
  void Salidafinal();
  void rotary();
  void bchorus();
  void ossaudioprepare();
  void alsaaudioprepare();
  void jackaudioprepare();
  void SalidaJack();
  int SelectRitmo(char *nomrit);
  void CogeRitmo();
  void SelectBass(char *nomrit);
  void CogeBass();
  void MiraLinea();
  void MiraChord();  
  void MiraTempo();
  void loadrhyt(char *filename);
  void saverhyt(char *filename);
  void MUndo();
  void MRedo();
  void MActu();
  void PutPrim();
  void MGetPrim();
  
  SNDFILE *infile;
  SF_INFO sfinfo;
  int readcount;
  SNDFILE *infileb;
  SF_INFO sfinfob;
  int readcountb;
             
  int cprograma;
  int PERIOD;
  int PERIOD2;
  int PERIOD4;
  int PERIOD8;
  float *nsin;  
  float *lsin;
  float *buf;
  short *wbuf;
  float *rbuf;
  float *bbuf;
  float *history;
  float *rhistory;
  float *ehistoryl;
  float *ehistoryr;
  float sound;
  float partial;
  float velocity[POLY];
  float pitch;
  float modulation;
  float freq_note;
  float env_time[POLY];
  float LFOspeed;
  float PLFOspeed;
  float PLFOdelay;
  float LFOamplitude;
  float LFOpitch;
  int  note[POLY];
  int rnote[POLY];
  int  gate[POLY];
  int  note_active[POLY];
  float  mastertune;
  float lasfreq[64];
  int rota;
  float  master;
  int pedal;
  long perhis;
  long rperhis;
  long eperhis;
  char *nombre;  
  char Name[36];  
  int echoon;
  int transpose;
  float echovol;
  float echodelay;
  float lado; 
  int hacia;
  float attack;
  float decay;
  float sustain;
  float release;
  float con1;       
  float envi[POLY];
  float aplfo;
  float alfo; 
  float detune;
  float freqlfo;
  float freqplfo;
  float xx;
  float xr;  
  float xer;
  float xel;
  float ELFOspeed;
  float ELFOamplitude;
  float efreqlfo;
  float chorvol;  
  int choron;            
  float popo;
  int split;
  float ldelay,ldelay1;
  float rdelay,rdelay1;
  float ganmod;  
  int Salida;
  float incre;
  float lalapi; 
  float revon;
  float rtime;
  float diffussion;
  float revvol;
  int combl[16];
  int combr[16];
  int apsg[16];
  int capsg;         
  int apss;
  int basson;
  int riton;
  float bassvol;
  float ritvol;
  float tempo;                  
  int cuenta;
  int linb[66];
  int linbv[66];
  int frametot;
  int fracpos;
  int basspending;
  int pos;
  int lpos;    
  int bnote;
  float bvnote;
  int framesbass;
  float afina;
  int chord;  
  int fundi;
  float velobass;
  int bars;
  int blackn;
  int tercera;
  int quinta;
  int septima; 
  int ctipo;
  int NumRit;  
  int btrans;
  int bmt;
  int ae;
  int sbars;
  int fe;
  char BankFilename[128];


  
struct Ritmo
{
 char Nom[30];
 char Nfile[256];
 int bars;
 int blackn;
 int linb[68];
 int linbv[68];

} Rt[22];



struct NomChord
{
 char Nom[3];
} NC[13];
 

struct AfinaBass

{
float afin;
float bmt;
} AB[13];


struct TipoCh

{
int ter;
int qui;
int sep;

} TCh[12];


struct Ch3

{
 int tipo;  
 int fund;
 int di1;
 int di2;
 char Nom[10];
} Chord3[15];

struct Ch4

{
  int tipo;
  int fund;
  int di1;
  int di2;
  int di3;
  char Nom[10];
} Chord4[50];
     
struct Ch5

{
  int tipo;
  int fund;
  int di1;
  int di2;
  int di3;
  int di4;
  char Nom[10];
} Chord5[12];
     


 
  
struct OperatorPar

 {
 int harmonic;
 float harmonic_fine;
 float volumen;
 float con1;
 int mar; 
 }    
   Operator[21];

struct Todolo

  { OperatorPar Operator[21];

   float modulation;
   float echovol;
   float PLFOspeed;
   float PLFOdelay;
   float LFOspeed;
   float LFOpitch;
   float attack;
   float revon;
   float detune;
   int transpose;
   int rota;
   float  master;
   int echoon;
   float echodelay;
   int split;
   int choron;
   float popo;
   float ELFOamplitude;
   float ELFOspeed;
   float ganmod;
   float chorvol;
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
  }  h[170];

  
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
   char Nombre[40], Info[40];
   const char *CName, *CInfo;
            
   } CPOMidiS[50];
                               

  struct PMidiIn
  {
    int Client, Port;
    char Nombre[40], Info[40];
    const char *CName, *CInfo;

  } CPIMidiS[50];


};

#endif

// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef HORGAN_h
#define HORGAN_h
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Dial.H>
#include "Holrgan.h"

class Drawbar : public Fl_Slider {
public:
  Drawbar(int x,int y, int w, int h, const char *label=0);
  int handle(int event);
};

class Rueda : public Fl_Dial {
public:
  Rueda(int x,int y, int w, int h, const char *label=0);
  int handle(int event);
};
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Value_Input.H>

class HORGAN {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *HORwindow;
private:
  void cb_HORwindow_i(Fl_Double_Window*, void*);
  static void cb_HORwindow(Fl_Double_Window*, void*);
public:
  Fl_Button *PANICO;
private:
  void cb_PANICO_i(Fl_Button*, void*);
  static void cb_PANICO(Fl_Button*, void*);
public:
  Fl_Menu_Bar *MenuPrincipal;
  static Fl_Menu_Item menu_MenuPrincipal[];
  static Fl_Menu_Item *MFile;
private:
  void cb_MFile_i(Fl_Menu_*, void*);
  static void cb_MFile(Fl_Menu_*, void*);
  void cb_New_i(Fl_Menu_*, void*);
  static void cb_New(Fl_Menu_*, void*);
  void cb_Load_i(Fl_Menu_*, void*);
  static void cb_Load(Fl_Menu_*, void*);
  void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  void cb_Load1_i(Fl_Menu_*, void*);
  static void cb_Load1(Fl_Menu_*, void*);
  void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
  void cb_Load2_i(Fl_Menu_*, void*);
  static void cb_Load2(Fl_Menu_*, void*);
  void cb_Save2_i(Fl_Menu_*, void*);
  static void cb_Save2(Fl_Menu_*, void*);
  void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
  void cb_E_i(Fl_Menu_*, void*);
  static void cb_E(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MEdit;
private:
  void cb_Undo_i(Fl_Menu_*, void*);
  static void cb_Undo(Fl_Menu_*, void*);
  void cb_Redo_i(Fl_Menu_*, void*);
  static void cb_Redo(Fl_Menu_*, void*);
  void cb_Synthesizer_i(Fl_Menu_*, void*);
  static void cb_Synthesizer(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MBank;
private:
  void cb_MBank_i(Fl_Menu_*, void*);
  static void cb_MBank(Fl_Menu_*, void*);
  void cb_Settings_i(Fl_Menu_*, void*);
  static void cb_Settings(Fl_Menu_*, void*);
public:
  Fl_Light_Button *CF;
private:
  void cb_CF_i(Fl_Light_Button*, void*);
  static void cb_CF(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *CL;
private:
  void cb_CL_i(Fl_Light_Button*, void*);
  static void cb_CL(Fl_Light_Button*, void*);
public:
  Fl_Slider *VUI1;
private:
  void cb_VUI1_i(Fl_Slider*, void*);
  static void cb_VUI1(Fl_Slider*, void*);
public:
  Fl_Box *DMIN1;
private:
  void cb_DMIN1_i(Fl_Box*, void*);
  static void cb_DMIN1(Fl_Box*, void*);
public:
  Fl_Box *DispNumber;
  Fl_Counter *Transpose;
private:
  void cb_Transpose_i(Fl_Counter*, void*);
  static void cb_Transpose(Fl_Counter*, void*);
public:
  Drawbar *Master;
private:
  void cb_Master_i(Drawbar*, void*);
  static void cb_Master(Drawbar*, void*);
public:
  Fl_Input *Nombre;
private:
  void cb_Nombre_i(Fl_Input*, void*);
  static void cb_Nombre(Fl_Input*, void*);
public:
  Fl_Counter *MasterT;
private:
  void cb_MasterT_i(Fl_Counter*, void*);
  static void cb_MasterT(Fl_Counter*, void*);
public:
  Drawbar *V1;
private:
  void cb_V1_i(Drawbar*, void*);
  static void cb_V1(Drawbar*, void*);
public:
  Drawbar *V2;
private:
  void cb_V2_i(Drawbar*, void*);
  static void cb_V2(Drawbar*, void*);
public:
  Drawbar *V3;
private:
  void cb_V3_i(Drawbar*, void*);
  static void cb_V3(Drawbar*, void*);
public:
  Drawbar *V4;
private:
  void cb_V4_i(Drawbar*, void*);
  static void cb_V4(Drawbar*, void*);
public:
  Drawbar *V5;
private:
  void cb_V5_i(Drawbar*, void*);
  static void cb_V5(Drawbar*, void*);
public:
  Drawbar *V6;
private:
  void cb_V6_i(Drawbar*, void*);
  static void cb_V6(Drawbar*, void*);
public:
  Drawbar *V7;
private:
  void cb_V7_i(Drawbar*, void*);
  static void cb_V7(Drawbar*, void*);
public:
  Drawbar *V8;
private:
  void cb_V8_i(Drawbar*, void*);
  static void cb_V8(Drawbar*, void*);
public:
  Drawbar *V9;
private:
  void cb_V9_i(Drawbar*, void*);
  static void cb_V9(Drawbar*, void*);
public:
  Drawbar *V10;
private:
  void cb_V10_i(Drawbar*, void*);
  static void cb_V10(Drawbar*, void*);
public:
  Rueda *Detune;
private:
  void cb_Detune_i(Rueda*, void*);
  static void cb_Detune(Rueda*, void*);
public:
  Rueda *LFOSpeed;
private:
  void cb_LFOSpeed_i(Rueda*, void*);
  static void cb_LFOSpeed(Rueda*, void*);
public:
  Rueda *LFOPitch;
private:
  void cb_LFOPitch_i(Rueda*, void*);
  static void cb_LFOPitch(Rueda*, void*);
public:
  Rueda *PLFOSpeed;
private:
  void cb_PLFOSpeed_i(Rueda*, void*);
  static void cb_PLFOSpeed(Rueda*, void*);
public:
  Rueda *PLFODelay;
private:
  void cb_PLFODelay_i(Rueda*, void*);
  static void cb_PLFODelay(Rueda*, void*);
public:
  Fl_Counter *EchoVol;
private:
  void cb_EchoVol_i(Fl_Counter*, void*);
  static void cb_EchoVol(Fl_Counter*, void*);
public:
  Fl_Counter *EchoDelay;
private:
  void cb_EchoDelay_i(Fl_Counter*, void*);
  static void cb_EchoDelay(Fl_Counter*, void*);
public:
  Fl_Slider *H1;
private:
  void cb_H1_i(Fl_Slider*, void*);
  static void cb_H1(Fl_Slider*, void*);
public:
  Fl_Slider *H2;
private:
  void cb_H2_i(Fl_Slider*, void*);
  static void cb_H2(Fl_Slider*, void*);
public:
  Fl_Slider *H3;
private:
  void cb_H3_i(Fl_Slider*, void*);
  static void cb_H3(Fl_Slider*, void*);
public:
  Fl_Slider *H4;
private:
  void cb_H4_i(Fl_Slider*, void*);
  static void cb_H4(Fl_Slider*, void*);
public:
  Fl_Slider *H5;
private:
  void cb_H5_i(Fl_Slider*, void*);
  static void cb_H5(Fl_Slider*, void*);
public:
  Fl_Slider *H6;
private:
  void cb_H6_i(Fl_Slider*, void*);
  static void cb_H6(Fl_Slider*, void*);
public:
  Fl_Slider *H7;
private:
  void cb_H7_i(Fl_Slider*, void*);
  static void cb_H7(Fl_Slider*, void*);
public:
  Fl_Slider *H8;
private:
  void cb_H8_i(Fl_Slider*, void*);
  static void cb_H8(Fl_Slider*, void*);
public:
  Fl_Slider *H9;
private:
  void cb_H9_i(Fl_Slider*, void*);
  static void cb_H9(Fl_Slider*, void*);
public:
  Fl_Slider *H10;
private:
  void cb_H10_i(Fl_Slider*, void*);
  static void cb_H10(Fl_Slider*, void*);
public:
  Fl_Button *Rota;
private:
  void cb_Rota_i(Fl_Button*, void*);
  static void cb_Rota(Fl_Button*, void*);
public:
  Rueda *ELFOSpeed;
private:
  void cb_ELFOSpeed_i(Rueda*, void*);
  static void cb_ELFOSpeed(Rueda*, void*);
public:
  Drawbar *ELFOAmplitude;
private:
  void cb_ELFOAmplitude_i(Drawbar*, void*);
  static void cb_ELFOAmplitude(Drawbar*, void*);
public:
  Drawbar *POPO;
private:
  void cb_POPO_i(Drawbar*, void*);
  static void cb_POPO(Drawbar*, void*);
public:
  Fl_Counter *ChorVol;
private:
  void cb_ChorVol_i(Fl_Counter*, void*);
  static void cb_ChorVol(Fl_Counter*, void*);
public:
  Fl_Button *Split;
private:
  void cb_Split_i(Fl_Button*, void*);
  static void cb_Split(Fl_Button*, void*);
public:
  Fl_Box *DMIN2;
private:
  void cb_DMIN2_i(Fl_Box*, void*);
  static void cb_DMIN2(Fl_Box*, void*);
public:
  Fl_Button *EchoOn;
private:
  void cb_EchoOn_i(Fl_Button*, void*);
  static void cb_EchoOn(Fl_Button*, void*);
public:
  Fl_Button *ChorusOn;
private:
  void cb_ChorusOn_i(Fl_Button*, void*);
  static void cb_ChorusOn(Fl_Button*, void*);
public:
  Fl_Button *R1;
private:
  void cb_R1_i(Fl_Button*, void*);
  static void cb_R1(Fl_Button*, void*);
public:
  Fl_Button *R2;
private:
  void cb_R2_i(Fl_Button*, void*);
  static void cb_R2(Fl_Button*, void*);
public:
  Fl_Button *R3;
private:
  void cb_R3_i(Fl_Button*, void*);
  static void cb_R3(Fl_Button*, void*);
public:
  Fl_Button *R4;
private:
  void cb_R4_i(Fl_Button*, void*);
  static void cb_R4(Fl_Button*, void*);
public:
  Fl_Button *R5;
private:
  void cb_R5_i(Fl_Button*, void*);
  static void cb_R5(Fl_Button*, void*);
public:
  Fl_Button *R6;
private:
  void cb_R6_i(Fl_Button*, void*);
  static void cb_R6(Fl_Button*, void*);
public:
  Fl_Button *R7;
private:
  void cb_R7_i(Fl_Button*, void*);
  static void cb_R7(Fl_Button*, void*);
public:
  Fl_Button *R8;
private:
  void cb_R8_i(Fl_Button*, void*);
  static void cb_R8(Fl_Button*, void*);
public:
  Fl_Button *Rev;
private:
  void cb_Rev_i(Fl_Button*, void*);
  static void cb_Rev(Fl_Button*, void*);
public:
  Fl_Slider *RitVol;
private:
  void cb_RitVol_i(Fl_Slider*, void*);
  static void cb_RitVol(Fl_Slider*, void*);
public:
  Fl_Dial *Tempo;
private:
  void cb_Tempo_i(Fl_Dial*, void*);
  static void cb_Tempo(Fl_Dial*, void*);
public:
  Fl_Slider *VUI2;
private:
  void cb_VUI2_i(Fl_Slider*, void*);
  static void cb_VUI2(Fl_Slider*, void*);
public:
  Fl_Button *RitOn;
private:
  void cb_RitOn_i(Fl_Button*, void*);
  static void cb_RitOn(Fl_Button*, void*);
public:
  Fl_Button *StStRiton;
private:
  void cb_StStRiton_i(Fl_Button*, void*);
  static void cb_StStRiton(Fl_Button*, void*);
public:
  Fl_Group *RitButtons;
  Fl_Button *Rit1;
private:
  void cb_Rit1_i(Fl_Button*, void*);
  static void cb_Rit1(Fl_Button*, void*);
public:
  Fl_Button *Rit2;
private:
  void cb_Rit2_i(Fl_Button*, void*);
  static void cb_Rit2(Fl_Button*, void*);
public:
  Fl_Button *Rit3;
private:
  void cb_Rit3_i(Fl_Button*, void*);
  static void cb_Rit3(Fl_Button*, void*);
public:
  Fl_Button *Rit4;
private:
  void cb_Rit4_i(Fl_Button*, void*);
  static void cb_Rit4(Fl_Button*, void*);
public:
  Fl_Button *Rit5;
private:
  void cb_Rit5_i(Fl_Button*, void*);
  static void cb_Rit5(Fl_Button*, void*);
public:
  Fl_Button *Rit6;
private:
  void cb_Rit6_i(Fl_Button*, void*);
  static void cb_Rit6(Fl_Button*, void*);
public:
  Fl_Button *Rit7;
private:
  void cb_Rit7_i(Fl_Button*, void*);
  static void cb_Rit7(Fl_Button*, void*);
public:
  Fl_Button *Rit8;
private:
  void cb_Rit8_i(Fl_Button*, void*);
  static void cb_Rit8(Fl_Button*, void*);
public:
  Fl_Button *Rit9;
private:
  void cb_Rit9_i(Fl_Button*, void*);
  static void cb_Rit9(Fl_Button*, void*);
public:
  Fl_Button *Rit10;
private:
  void cb_Rit10_i(Fl_Button*, void*);
  static void cb_Rit10(Fl_Button*, void*);
public:
  Fl_Button *Rit11;
private:
  void cb_Rit11_i(Fl_Button*, void*);
  static void cb_Rit11(Fl_Button*, void*);
public:
  Fl_Button *Rit12;
private:
  void cb_Rit12_i(Fl_Button*, void*);
  static void cb_Rit12(Fl_Button*, void*);
public:
  Fl_Button *Rit13;
private:
  void cb_Rit13_i(Fl_Button*, void*);
  static void cb_Rit13(Fl_Button*, void*);
public:
  Fl_Button *Rit14;
private:
  void cb_Rit14_i(Fl_Button*, void*);
  static void cb_Rit14(Fl_Button*, void*);
public:
  Fl_Button *Rit15;
private:
  void cb_Rit15_i(Fl_Button*, void*);
  static void cb_Rit15(Fl_Button*, void*);
public:
  Fl_Button *Rit16;
private:
  void cb_Rit16_i(Fl_Button*, void*);
  static void cb_Rit16(Fl_Button*, void*);
public:
  Fl_Button *Rit17;
private:
  void cb_Rit17_i(Fl_Button*, void*);
  static void cb_Rit17(Fl_Button*, void*);
public:
  Fl_Button *Rit18;
private:
  void cb_Rit18_i(Fl_Button*, void*);
  static void cb_Rit18(Fl_Button*, void*);
public:
  Fl_Button *Rit19;
private:
  void cb_Rit19_i(Fl_Button*, void*);
  static void cb_Rit19(Fl_Button*, void*);
public:
  Fl_Button *Rit20;
private:
  void cb_Rit20_i(Fl_Button*, void*);
  static void cb_Rit20(Fl_Button*, void*);
public:
  Fl_Slider *BassVol;
private:
  void cb_BassVol_i(Fl_Slider*, void*);
  static void cb_BassVol(Fl_Slider*, void*);
public:
  Fl_Button *Basson;
private:
  void cb_Basson_i(Fl_Button*, void*);
  static void cb_Basson(Fl_Button*, void*);
public:
  Fl_Button *Bass1;
private:
  void cb_Bass1_i(Fl_Button*, void*);
  static void cb_Bass1(Fl_Button*, void*);
public:
  Fl_Button *Bass2;
private:
  void cb_Bass2_i(Fl_Button*, void*);
  static void cb_Bass2(Fl_Button*, void*);
public:
  Fl_Button *Bass3;
private:
  void cb_Bass3_i(Fl_Button*, void*);
  static void cb_Bass3(Fl_Button*, void*);
public:
  Fl_Box *ACI;
  Fl_Value_Output *NV1;
  Fl_Value_Output *NV2;
  Fl_Value_Output *NV3;
  Fl_Value_Output *NV4;
  Fl_Value_Output *NV5;
  Fl_Value_Output *NV6;
  Fl_Value_Output *NV7;
  Fl_Value_Output *NV8;
  Fl_Value_Output *NV9;
  Fl_Value_Output *NV10;
  Fl_Counter *CPrograma;
private:
  void cb_CPrograma_i(Fl_Counter*, void*);
  static void cb_CPrograma(Fl_Counter*, void*);
public:
  Drawbar *OMaster;
private:
  void cb_OMaster_i(Drawbar*, void*);
  static void cb_OMaster(Drawbar*, void*);
public:
  Fl_Light_Button *Mar1;
private:
  void cb_Mar1_i(Fl_Light_Button*, void*);
  static void cb_Mar1(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar2;
private:
  void cb_Mar2_i(Fl_Light_Button*, void*);
  static void cb_Mar2(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar3;
private:
  void cb_Mar3_i(Fl_Light_Button*, void*);
  static void cb_Mar3(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar4;
private:
  void cb_Mar4_i(Fl_Light_Button*, void*);
  static void cb_Mar4(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar5;
private:
  void cb_Mar5_i(Fl_Light_Button*, void*);
  static void cb_Mar5(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar6;
private:
  void cb_Mar6_i(Fl_Light_Button*, void*);
  static void cb_Mar6(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar7;
private:
  void cb_Mar7_i(Fl_Light_Button*, void*);
  static void cb_Mar7(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar8;
private:
  void cb_Mar8_i(Fl_Light_Button*, void*);
  static void cb_Mar8(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar9;
private:
  void cb_Mar9_i(Fl_Light_Button*, void*);
  static void cb_Mar9(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *Mar10;
private:
  void cb_Mar10_i(Fl_Light_Button*, void*);
  static void cb_Mar10(Fl_Light_Button*, void*);
public:
  Fl_Double_Window *aboutwindow;
private:
  void cb_aboutwindow_i(Fl_Double_Window*, void*);
  static void cb_aboutwindow(Fl_Double_Window*, void*);
  void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
public:
  Fl_Double_Window *Settingswindow;
private:
  void cb_Settingswindow_i(Fl_Double_Window*, void*);
  static void cb_Settingswindow(Fl_Double_Window*, void*);
public:
  Fl_Button *SClose;
private:
  void cb_SClose_i(Fl_Button*, void*);
  static void cb_SClose(Fl_Button*, void*);
  void cb_Save3_i(Fl_Button*, void*);
  static void cb_Save3(Fl_Button*, void*);
public:
  Fl_Browser *BMidiIn;
private:
  void cb_BMidiIn_i(Fl_Browser*, void*);
  static void cb_BMidiIn(Fl_Browser*, void*);
public:
  Fl_Check_Button *OSS;
  Fl_Check_Button *Alsa;
  Fl_Check_Button *Jack;
  Fl_File_Input *BFiname;
private:
  void cb_Browse_i(Fl_Button*, void*);
  static void cb_Browse(Fl_Button*, void*);
public:
  Fl_File_Input *RFiname;
private:
  void cb_Browse1_i(Fl_Button*, void*);
  static void cb_Browse1(Fl_Button*, void*);
public:
  Fl_Double_Window *HORBank;
private:
  void cb_HORBank_i(Fl_Double_Window*, void*);
  static void cb_HORBank(Fl_Double_Window*, void*);
public:
  Fl_Button *BClose;
private:
  void cb_BClose_i(Fl_Button*, void*);
  static void cb_BClose(Fl_Button*, void*);
  static Fl_Menu_Item menu_[];
public:
  static Fl_Menu_Item *BFile;
  static Fl_Menu_Item *BLoad;
private:
  void cb_BLoad_i(Fl_Menu_*, void*);
  static void cb_BLoad(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *BSave;
private:
  void cb_BSave_i(Fl_Menu_*, void*);
  static void cb_BSave(Fl_Menu_*, void*);
  void cb_Close_i(Fl_Menu_*, void*);
  static void cb_Close(Fl_Menu_*, void*);
public:
  Fl_Button *Banco1;
private:
  void cb_Banco1_i(Fl_Button*, void*);
  static void cb_Banco1(Fl_Button*, void*);
public:
  Fl_Button *Banco2;
private:
  void cb_Banco2_i(Fl_Button*, void*);
  static void cb_Banco2(Fl_Button*, void*);
public:
  Fl_Button *Banco3;
private:
  void cb_Banco3_i(Fl_Button*, void*);
  static void cb_Banco3(Fl_Button*, void*);
public:
  Fl_Button *Banco4;
private:
  void cb_Banco4_i(Fl_Button*, void*);
  static void cb_Banco4(Fl_Button*, void*);
public:
  Fl_Button *Banco5;
private:
  void cb_Banco5_i(Fl_Button*, void*);
  static void cb_Banco5(Fl_Button*, void*);
public:
  Fl_Button *Banco6;
private:
  void cb_Banco6_i(Fl_Button*, void*);
  static void cb_Banco6(Fl_Button*, void*);
public:
  Fl_Button *Banco7;
private:
  void cb_Banco7_i(Fl_Button*, void*);
  static void cb_Banco7(Fl_Button*, void*);
public:
  Fl_Button *Banco8;
private:
  void cb_Banco8_i(Fl_Button*, void*);
  static void cb_Banco8(Fl_Button*, void*);
public:
  Fl_Button *Banco9;
private:
  void cb_Banco9_i(Fl_Button*, void*);
  static void cb_Banco9(Fl_Button*, void*);
public:
  Fl_Button *Banco10;
private:
  void cb_Banco10_i(Fl_Button*, void*);
  static void cb_Banco10(Fl_Button*, void*);
public:
  Fl_Button *Banco11;
private:
  void cb_Banco11_i(Fl_Button*, void*);
  static void cb_Banco11(Fl_Button*, void*);
public:
  Fl_Button *Banco12;
private:
  void cb_Banco12_i(Fl_Button*, void*);
  static void cb_Banco12(Fl_Button*, void*);
public:
  Fl_Button *Banco13;
private:
  void cb_Banco13_i(Fl_Button*, void*);
  static void cb_Banco13(Fl_Button*, void*);
public:
  Fl_Button *Banco14;
private:
  void cb_Banco14_i(Fl_Button*, void*);
  static void cb_Banco14(Fl_Button*, void*);
public:
  Fl_Button *Banco15;
private:
  void cb_Banco15_i(Fl_Button*, void*);
  static void cb_Banco15(Fl_Button*, void*);
public:
  Fl_Button *Banco16;
private:
  void cb_Banco16_i(Fl_Button*, void*);
  static void cb_Banco16(Fl_Button*, void*);
public:
  Fl_Button *Banco17;
private:
  void cb_Banco17_i(Fl_Button*, void*);
  static void cb_Banco17(Fl_Button*, void*);
public:
  Fl_Button *Banco18;
private:
  void cb_Banco18_i(Fl_Button*, void*);
  static void cb_Banco18(Fl_Button*, void*);
public:
  Fl_Button *Banco19;
private:
  void cb_Banco19_i(Fl_Button*, void*);
  static void cb_Banco19(Fl_Button*, void*);
public:
  Fl_Button *Banco20;
private:
  void cb_Banco20_i(Fl_Button*, void*);
  static void cb_Banco20(Fl_Button*, void*);
public:
  Fl_Button *Banco21;
private:
  void cb_Banco21_i(Fl_Button*, void*);
  static void cb_Banco21(Fl_Button*, void*);
public:
  Fl_Button *Banco22;
private:
  void cb_Banco22_i(Fl_Button*, void*);
  static void cb_Banco22(Fl_Button*, void*);
public:
  Fl_Button *Banco23;
private:
  void cb_Banco23_i(Fl_Button*, void*);
  static void cb_Banco23(Fl_Button*, void*);
public:
  Fl_Button *Banco24;
private:
  void cb_Banco24_i(Fl_Button*, void*);
  static void cb_Banco24(Fl_Button*, void*);
public:
  Fl_Button *Banco25;
private:
  void cb_Banco25_i(Fl_Button*, void*);
  static void cb_Banco25(Fl_Button*, void*);
public:
  Fl_Button *Banco26;
private:
  void cb_Banco26_i(Fl_Button*, void*);
  static void cb_Banco26(Fl_Button*, void*);
public:
  Fl_Button *Banco27;
private:
  void cb_Banco27_i(Fl_Button*, void*);
  static void cb_Banco27(Fl_Button*, void*);
public:
  Fl_Button *Banco28;
private:
  void cb_Banco28_i(Fl_Button*, void*);
  static void cb_Banco28(Fl_Button*, void*);
public:
  Fl_Button *Banco29;
private:
  void cb_Banco29_i(Fl_Button*, void*);
  static void cb_Banco29(Fl_Button*, void*);
public:
  Fl_Button *Banco30;
private:
  void cb_Banco30_i(Fl_Button*, void*);
  static void cb_Banco30(Fl_Button*, void*);
public:
  Fl_Button *Banco31;
private:
  void cb_Banco31_i(Fl_Button*, void*);
  static void cb_Banco31(Fl_Button*, void*);
public:
  Fl_Button *Banco32;
private:
  void cb_Banco32_i(Fl_Button*, void*);
  static void cb_Banco32(Fl_Button*, void*);
public:
  Fl_Double_Window *RitEdit;
private:
  void cb_RitEdit_i(Fl_Double_Window*, void*);
  static void cb_RitEdit(Fl_Double_Window*, void*);
public:
  Fl_Input *RtName;
private:
  void cb_RtName_i(Fl_Input*, void*);
  static void cb_RtName(Fl_Input*, void*);
public:
  Fl_Input *RtFile;
private:
  void cb_RtFile_i(Fl_Input*, void*);
  static void cb_RtFile(Fl_Input*, void*);
public:
  Fl_Value_Input *RtBars;
private:
  void cb_RtBars_i(Fl_Value_Input*, void*);
  static void cb_RtBars(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *RtDen;
private:
  void cb_RtDen_i(Fl_Value_Input*, void*);
  static void cb_RtDen(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G1;
  Fl_Value_Input *lb1;
private:
  void cb_lb1_i(Fl_Value_Input*, void*);
  static void cb_lb1(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb2;
private:
  void cb_lb2_i(Fl_Value_Input*, void*);
  static void cb_lb2(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb3;
private:
  void cb_lb3_i(Fl_Value_Input*, void*);
  static void cb_lb3(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb4;
private:
  void cb_lb4_i(Fl_Value_Input*, void*);
  static void cb_lb4(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv1;
private:
  void cb_lbv1_i(Fl_Value_Input*, void*);
  static void cb_lbv1(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv2;
private:
  void cb_lbv2_i(Fl_Value_Input*, void*);
  static void cb_lbv2(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv3;
private:
  void cb_lbv3_i(Fl_Value_Input*, void*);
  static void cb_lbv3(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv4;
private:
  void cb_lbv4_i(Fl_Value_Input*, void*);
  static void cb_lbv4(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G2;
  Fl_Value_Input *lb5;
private:
  void cb_lb5_i(Fl_Value_Input*, void*);
  static void cb_lb5(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb6;
private:
  void cb_lb6_i(Fl_Value_Input*, void*);
  static void cb_lb6(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb7;
private:
  void cb_lb7_i(Fl_Value_Input*, void*);
  static void cb_lb7(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb8;
private:
  void cb_lb8_i(Fl_Value_Input*, void*);
  static void cb_lb8(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv5;
private:
  void cb_lbv5_i(Fl_Value_Input*, void*);
  static void cb_lbv5(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv6;
private:
  void cb_lbv6_i(Fl_Value_Input*, void*);
  static void cb_lbv6(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv7;
private:
  void cb_lbv7_i(Fl_Value_Input*, void*);
  static void cb_lbv7(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv8;
private:
  void cb_lbv8_i(Fl_Value_Input*, void*);
  static void cb_lbv8(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G3;
  Fl_Value_Input *lb9;
private:
  void cb_lb9_i(Fl_Value_Input*, void*);
  static void cb_lb9(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb10;
private:
  void cb_lb10_i(Fl_Value_Input*, void*);
  static void cb_lb10(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb11;
private:
  void cb_lb11_i(Fl_Value_Input*, void*);
  static void cb_lb11(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb12;
private:
  void cb_lb12_i(Fl_Value_Input*, void*);
  static void cb_lb12(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv9;
private:
  void cb_lbv9_i(Fl_Value_Input*, void*);
  static void cb_lbv9(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv10;
private:
  void cb_lbv10_i(Fl_Value_Input*, void*);
  static void cb_lbv10(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv11;
private:
  void cb_lbv11_i(Fl_Value_Input*, void*);
  static void cb_lbv11(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv12;
private:
  void cb_lbv12_i(Fl_Value_Input*, void*);
  static void cb_lbv12(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G4;
  Fl_Value_Input *lb13;
private:
  void cb_lb13_i(Fl_Value_Input*, void*);
  static void cb_lb13(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb14;
private:
  void cb_lb14_i(Fl_Value_Input*, void*);
  static void cb_lb14(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb15;
private:
  void cb_lb15_i(Fl_Value_Input*, void*);
  static void cb_lb15(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb16;
private:
  void cb_lb16_i(Fl_Value_Input*, void*);
  static void cb_lb16(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv13;
private:
  void cb_lbv13_i(Fl_Value_Input*, void*);
  static void cb_lbv13(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv14;
private:
  void cb_lbv14_i(Fl_Value_Input*, void*);
  static void cb_lbv14(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv15;
private:
  void cb_lbv15_i(Fl_Value_Input*, void*);
  static void cb_lbv15(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv16;
private:
  void cb_lbv16_i(Fl_Value_Input*, void*);
  static void cb_lbv16(Fl_Value_Input*, void*);
public:
  Fl_Counter *SBar;
private:
  void cb_SBar_i(Fl_Counter*, void*);
  static void cb_SBar(Fl_Counter*, void*);
public:
  Fl_Button *CloRit;
private:
  void cb_CloRit_i(Fl_Button*, void*);
  static void cb_CloRit(Fl_Button*, void*);
public:
  Fl_Double_Window *ADSRwin;
private:
  void cb_ADSRwin_i(Fl_Double_Window*, void*);
  static void cb_ADSRwin(Fl_Double_Window*, void*);
public:
  Rueda *D_attack;
private:
  void cb_D_attack_i(Rueda*, void*);
  static void cb_D_attack(Rueda*, void*);
public:
  Rueda *D_decay;
private:
  void cb_D_decay_i(Rueda*, void*);
  static void cb_D_decay(Rueda*, void*);
public:
  Rueda *D_sustain;
private:
  void cb_D_sustain_i(Rueda*, void*);
  static void cb_D_sustain(Rueda*, void*);
public:
  Rueda *D_p_attack;
private:
  void cb_D_p_attack_i(Rueda*, void*);
  static void cb_D_p_attack(Rueda*, void*);
public:
  Rueda *D_p_decay;
private:
  void cb_D_p_decay_i(Rueda*, void*);
  static void cb_D_p_decay(Rueda*, void*);
public:
  Fl_Box *Saca;
  Fl_Counter *D_Freq;
private:
  void cb_D_Freq_i(Fl_Counter*, void*);
  static void cb_D_Freq(Fl_Counter*, void*);
public:
  Fl_Counter *D_Att;
private:
  void cb_D_Att_i(Fl_Counter*, void*);
  static void cb_D_Att(Fl_Counter*, void*);
public:
  Fl_Counter *D_Freq_F;
private:
  void cb_D_Freq_F_i(Fl_Counter*, void*);
  static void cb_D_Freq_F(Fl_Counter*, void*);
public:
  Fl_Counter *D_FFval;
private:
  void cb_D_FFval_i(Fl_Counter*, void*);
  static void cb_D_FFval(Fl_Counter*, void*);
public:
  Fl_Counter *D_Rot_Amp;
private:
  void cb_D_Rot_Amp_i(Fl_Counter*, void*);
  static void cb_D_Rot_Amp(Fl_Counter*, void*);
public:
  Fl_Counter *D_O_Transpose;
private:
  void cb_D_O_Transpose_i(Fl_Counter*, void*);
  static void cb_D_O_Transpose(Fl_Counter*, void*);
public:
  void metelo();
  void GetCombi(int i);
  void PutCombi(int i);
  void MiraClientes();
  void MiraConfig();
  void metebanco();
  HORGAN(int argc, char **argv,HOR *hor_);
private:
  HOR *hor; 
public:
  void Undo();
  void Actu();
  void Redo();
  void GetPrim();
  static void tick(void *v);
  void ponreverb();
  void GetRit(int Selected_Rhythm);
  void meteritmos();
  void calbtrans();
  void calbtune();
  void EditRit(int i);
  void QuitaPon();
  void meteval();
  void ApagaTodo();
  void meteprog();
  void SetBassType(int type);
  void Guarda_Pref(int parte);
  void ponvalor(float a);
  void metesynth();
};
#endif

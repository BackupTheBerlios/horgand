// generated by Fast Light User Interface Designer (fluid) version 1.0104

#ifndef HORGAN_h
#define HORGAN_h
#include <FL/Fl.H>
#include <alsa/asoundlib.h>
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
  inline void cb_HORwindow_i(Fl_Double_Window*, void*);
  static void cb_HORwindow(Fl_Double_Window*, void*);
public:
  Fl_Button *PANICO;
private:
  inline void cb_PANICO_i(Fl_Button*, void*);
  static void cb_PANICO(Fl_Button*, void*);
public:
  Fl_Menu_Bar *MenuPrincipal;
  static Fl_Menu_Item menu_MenuPrincipal[];
  static Fl_Menu_Item *MFile;
private:
  inline void cb_MFile_i(Fl_Menu_*, void*);
  static void cb_MFile(Fl_Menu_*, void*);
  inline void cb_New_i(Fl_Menu_*, void*);
  static void cb_New(Fl_Menu_*, void*);
  inline void cb_Load_i(Fl_Menu_*, void*);
  static void cb_Load(Fl_Menu_*, void*);
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_Load1_i(Fl_Menu_*, void*);
  static void cb_Load1(Fl_Menu_*, void*);
  inline void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
  inline void cb_Load2_i(Fl_Menu_*, void*);
  static void cb_Load2(Fl_Menu_*, void*);
  inline void cb_Save2_i(Fl_Menu_*, void*);
  static void cb_Save2(Fl_Menu_*, void*);
  inline void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
  inline void cb_E_i(Fl_Menu_*, void*);
  static void cb_E(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MEdit;
private:
  inline void cb_Undo_i(Fl_Menu_*, void*);
  static void cb_Undo(Fl_Menu_*, void*);
  inline void cb_Redo_i(Fl_Menu_*, void*);
  static void cb_Redo(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MBank;
private:
  inline void cb_MBank_i(Fl_Menu_*, void*);
  static void cb_MBank(Fl_Menu_*, void*);
  inline void cb_Settings_i(Fl_Menu_*, void*);
  static void cb_Settings(Fl_Menu_*, void*);
public:
  Fl_Light_Button *CF;
private:
  inline void cb_CF_i(Fl_Light_Button*, void*);
  static void cb_CF(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *CL;
private:
  inline void cb_CL_i(Fl_Light_Button*, void*);
  static void cb_CL(Fl_Light_Button*, void*);
public:
  Fl_Slider *VUI1;
private:
  inline void cb_VUI1_i(Fl_Slider*, void*);
  static void cb_VUI1(Fl_Slider*, void*);
public:
  Fl_Box *DMIN1;
private:
  inline void cb_DMIN1_i(Fl_Box*, void*);
  static void cb_DMIN1(Fl_Box*, void*);
public:
  Fl_Box *DispNumber;
  Fl_Counter *Transpose;
private:
  inline void cb_Transpose_i(Fl_Counter*, void*);
  static void cb_Transpose(Fl_Counter*, void*);
public:
  Drawbar *Master;
private:
  inline void cb_Master_i(Drawbar*, void*);
  static void cb_Master(Drawbar*, void*);
public:
  Fl_Input *Nombre;
private:
  inline void cb_Nombre_i(Fl_Input*, void*);
  static void cb_Nombre(Fl_Input*, void*);
public:
  Fl_Counter *MasterT;
private:
  inline void cb_MasterT_i(Fl_Counter*, void*);
  static void cb_MasterT(Fl_Counter*, void*);
public:
  Drawbar *V1;
private:
  inline void cb_V1_i(Drawbar*, void*);
  static void cb_V1(Drawbar*, void*);
public:
  Drawbar *V2;
private:
  inline void cb_V2_i(Drawbar*, void*);
  static void cb_V2(Drawbar*, void*);
public:
  Drawbar *V3;
private:
  inline void cb_V3_i(Drawbar*, void*);
  static void cb_V3(Drawbar*, void*);
public:
  Drawbar *Marimba;
private:
  inline void cb_Marimba_i(Drawbar*, void*);
  static void cb_Marimba(Drawbar*, void*);
public:
  Drawbar *V4;
private:
  inline void cb_V4_i(Drawbar*, void*);
  static void cb_V4(Drawbar*, void*);
public:
  Drawbar *V5;
private:
  inline void cb_V5_i(Drawbar*, void*);
  static void cb_V5(Drawbar*, void*);
public:
  Drawbar *V6;
private:
  inline void cb_V6_i(Drawbar*, void*);
  static void cb_V6(Drawbar*, void*);
public:
  Rueda *Detune;
private:
  inline void cb_Detune_i(Rueda*, void*);
  static void cb_Detune(Rueda*, void*);
public:
  Rueda *LFOSpeed;
private:
  inline void cb_LFOSpeed_i(Rueda*, void*);
  static void cb_LFOSpeed(Rueda*, void*);
public:
  Rueda *LFOPitch;
private:
  inline void cb_LFOPitch_i(Rueda*, void*);
  static void cb_LFOPitch(Rueda*, void*);
public:
  Rueda *PLFOSpeed;
private:
  inline void cb_PLFOSpeed_i(Rueda*, void*);
  static void cb_PLFOSpeed(Rueda*, void*);
public:
  Rueda *PLFODelay;
private:
  inline void cb_PLFODelay_i(Rueda*, void*);
  static void cb_PLFODelay(Rueda*, void*);
public:
  Fl_Counter *EchoVol;
private:
  inline void cb_EchoVol_i(Fl_Counter*, void*);
  static void cb_EchoVol(Fl_Counter*, void*);
public:
  Fl_Counter *EchoDelay;
private:
  inline void cb_EchoDelay_i(Fl_Counter*, void*);
  static void cb_EchoDelay(Fl_Counter*, void*);
public:
  Fl_Slider *H1;
private:
  inline void cb_H1_i(Fl_Slider*, void*);
  static void cb_H1(Fl_Slider*, void*);
public:
  Fl_Slider *H2;
private:
  inline void cb_H2_i(Fl_Slider*, void*);
  static void cb_H2(Fl_Slider*, void*);
public:
  Fl_Slider *H3;
private:
  inline void cb_H3_i(Fl_Slider*, void*);
  static void cb_H3(Fl_Slider*, void*);
public:
  Fl_Slider *H4;
private:
  inline void cb_H4_i(Fl_Slider*, void*);
  static void cb_H4(Fl_Slider*, void*);
public:
  Fl_Slider *H5;
private:
  inline void cb_H5_i(Fl_Slider*, void*);
  static void cb_H5(Fl_Slider*, void*);
public:
  Fl_Slider *H6;
private:
  inline void cb_H6_i(Fl_Slider*, void*);
  static void cb_H6(Fl_Slider*, void*);
public:
  Fl_Button *Rota;
private:
  inline void cb_Rota_i(Fl_Button*, void*);
  static void cb_Rota(Fl_Button*, void*);
public:
  Rueda *ELFOSpeed;
private:
  inline void cb_ELFOSpeed_i(Rueda*, void*);
  static void cb_ELFOSpeed(Rueda*, void*);
public:
  Drawbar *ELFOAmplitude;
private:
  inline void cb_ELFOAmplitude_i(Drawbar*, void*);
  static void cb_ELFOAmplitude(Drawbar*, void*);
public:
  Drawbar *POPO;
private:
  inline void cb_POPO_i(Drawbar*, void*);
  static void cb_POPO(Drawbar*, void*);
public:
  Fl_Counter *ChorVol;
private:
  inline void cb_ChorVol_i(Fl_Counter*, void*);
  static void cb_ChorVol(Fl_Counter*, void*);
public:
  Fl_Button *Split;
private:
  inline void cb_Split_i(Fl_Button*, void*);
  static void cb_Split(Fl_Button*, void*);
public:
  Fl_Box *DMIN2;
private:
  inline void cb_DMIN2_i(Fl_Box*, void*);
  static void cb_DMIN2(Fl_Box*, void*);
public:
  Fl_Button *EchoOn;
private:
  inline void cb_EchoOn_i(Fl_Button*, void*);
  static void cb_EchoOn(Fl_Button*, void*);
public:
  Fl_Button *ChorusOn;
private:
  inline void cb_ChorusOn_i(Fl_Button*, void*);
  static void cb_ChorusOn(Fl_Button*, void*);
public:
  Fl_Button *R1;
private:
  inline void cb_R1_i(Fl_Button*, void*);
  static void cb_R1(Fl_Button*, void*);
public:
  Fl_Button *R2;
private:
  inline void cb_R2_i(Fl_Button*, void*);
  static void cb_R2(Fl_Button*, void*);
public:
  Fl_Button *R3;
private:
  inline void cb_R3_i(Fl_Button*, void*);
  static void cb_R3(Fl_Button*, void*);
public:
  Fl_Button *R4;
private:
  inline void cb_R4_i(Fl_Button*, void*);
  static void cb_R4(Fl_Button*, void*);
public:
  Fl_Button *R5;
private:
  inline void cb_R5_i(Fl_Button*, void*);
  static void cb_R5(Fl_Button*, void*);
public:
  Fl_Button *R6;
private:
  inline void cb_R6_i(Fl_Button*, void*);
  static void cb_R6(Fl_Button*, void*);
public:
  Fl_Button *R7;
private:
  inline void cb_R7_i(Fl_Button*, void*);
  static void cb_R7(Fl_Button*, void*);
public:
  Fl_Button *R8;
private:
  inline void cb_R8_i(Fl_Button*, void*);
  static void cb_R8(Fl_Button*, void*);
public:
  Fl_Button *Rev;
private:
  inline void cb_Rev_i(Fl_Button*, void*);
  static void cb_Rev(Fl_Button*, void*);
public:
  Fl_Slider *RitVol;
private:
  inline void cb_RitVol_i(Fl_Slider*, void*);
  static void cb_RitVol(Fl_Slider*, void*);
public:
  Fl_Dial *Tempo;
private:
  inline void cb_Tempo_i(Fl_Dial*, void*);
  static void cb_Tempo(Fl_Dial*, void*);
public:
  Fl_Slider *VUI2;
private:
  inline void cb_VUI2_i(Fl_Slider*, void*);
  static void cb_VUI2(Fl_Slider*, void*);
public:
  Fl_Button *RitOn;
private:
  inline void cb_RitOn_i(Fl_Button*, void*);
  static void cb_RitOn(Fl_Button*, void*);
public:
  Fl_Button *StStRiton;
private:
  inline void cb_StStRiton_i(Fl_Button*, void*);
  static void cb_StStRiton(Fl_Button*, void*);
public:
  Fl_Button *Rit4;
private:
  inline void cb_Rit4_i(Fl_Button*, void*);
  static void cb_Rit4(Fl_Button*, void*);
public:
  Fl_Button *Rit1;
private:
  inline void cb_Rit1_i(Fl_Button*, void*);
  static void cb_Rit1(Fl_Button*, void*);
public:
  Fl_Button *Rit2;
private:
  inline void cb_Rit2_i(Fl_Button*, void*);
  static void cb_Rit2(Fl_Button*, void*);
public:
  Fl_Button *Rit3;
private:
  inline void cb_Rit3_i(Fl_Button*, void*);
  static void cb_Rit3(Fl_Button*, void*);
public:
  Fl_Button *Rit5;
private:
  inline void cb_Rit5_i(Fl_Button*, void*);
  static void cb_Rit5(Fl_Button*, void*);
public:
  Fl_Button *Rit6;
private:
  inline void cb_Rit6_i(Fl_Button*, void*);
  static void cb_Rit6(Fl_Button*, void*);
public:
  Fl_Button *Rit7;
private:
  inline void cb_Rit7_i(Fl_Button*, void*);
  static void cb_Rit7(Fl_Button*, void*);
public:
  Fl_Button *Rit8;
private:
  inline void cb_Rit8_i(Fl_Button*, void*);
  static void cb_Rit8(Fl_Button*, void*);
public:
  Fl_Button *Rit9;
private:
  inline void cb_Rit9_i(Fl_Button*, void*);
  static void cb_Rit9(Fl_Button*, void*);
public:
  Fl_Button *Rit10;
private:
  inline void cb_Rit10_i(Fl_Button*, void*);
  static void cb_Rit10(Fl_Button*, void*);
public:
  Fl_Button *Rit11;
private:
  inline void cb_Rit11_i(Fl_Button*, void*);
  static void cb_Rit11(Fl_Button*, void*);
public:
  Fl_Button *Rit12;
private:
  inline void cb_Rit12_i(Fl_Button*, void*);
  static void cb_Rit12(Fl_Button*, void*);
public:
  Fl_Button *Rit13;
private:
  inline void cb_Rit13_i(Fl_Button*, void*);
  static void cb_Rit13(Fl_Button*, void*);
public:
  Fl_Button *Rit14;
private:
  inline void cb_Rit14_i(Fl_Button*, void*);
  static void cb_Rit14(Fl_Button*, void*);
public:
  Fl_Button *Rit15;
private:
  inline void cb_Rit15_i(Fl_Button*, void*);
  static void cb_Rit15(Fl_Button*, void*);
public:
  Fl_Button *Rit16;
private:
  inline void cb_Rit16_i(Fl_Button*, void*);
  static void cb_Rit16(Fl_Button*, void*);
public:
  Fl_Button *Rit17;
private:
  inline void cb_Rit17_i(Fl_Button*, void*);
  static void cb_Rit17(Fl_Button*, void*);
public:
  Fl_Button *Rit18;
private:
  inline void cb_Rit18_i(Fl_Button*, void*);
  static void cb_Rit18(Fl_Button*, void*);
public:
  Fl_Button *Rit19;
private:
  inline void cb_Rit19_i(Fl_Button*, void*);
  static void cb_Rit19(Fl_Button*, void*);
public:
  Fl_Button *Rit20;
private:
  inline void cb_Rit20_i(Fl_Button*, void*);
  static void cb_Rit20(Fl_Button*, void*);
public:
  Fl_Slider *BassVol;
private:
  inline void cb_BassVol_i(Fl_Slider*, void*);
  static void cb_BassVol(Fl_Slider*, void*);
public:
  Fl_Button *Basson;
private:
  inline void cb_Basson_i(Fl_Button*, void*);
  static void cb_Basson(Fl_Button*, void*);
public:
  Fl_Button *Bass1;
private:
  inline void cb_Bass1_i(Fl_Button*, void*);
  static void cb_Bass1(Fl_Button*, void*);
public:
  Fl_Button *Bass2;
private:
  inline void cb_Bass2_i(Fl_Button*, void*);
  static void cb_Bass2(Fl_Button*, void*);
public:
  Fl_Button *Bass3;
private:
  inline void cb_Bass3_i(Fl_Button*, void*);
  static void cb_Bass3(Fl_Button*, void*);
public:
  Fl_Box *ACI;
  Fl_Value_Output *NV1;
  Fl_Value_Output *NV2;
  Fl_Value_Output *NV3;
  Fl_Value_Output *NV4;
  Fl_Value_Output *NV5;
  Fl_Value_Output *NV6;
  Fl_Counter *CPrograma;
private:
  inline void cb_CPrograma_i(Fl_Counter*, void*);
  static void cb_CPrograma(Fl_Counter*, void*);
public:
  Fl_Double_Window *aboutwindow;
private:
  inline void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
public:
  Fl_Double_Window *Settingswindow;
  Fl_Button *SClose;
private:
  inline void cb_SClose_i(Fl_Button*, void*);
  static void cb_SClose(Fl_Button*, void*);
  inline void cb_Save3_i(Fl_Button*, void*);
  static void cb_Save3(Fl_Button*, void*);
public:
  Fl_Browser *BMidiIn;
private:
  inline void cb_BMidiIn_i(Fl_Browser*, void*);
  static void cb_BMidiIn(Fl_Browser*, void*);
public:
  Fl_Check_Button *OSS;
  Fl_Check_Button *Alsa;
  Fl_Check_Button *Jack;
  Fl_File_Input *BFiname;
private:
  inline void cb_Browse_i(Fl_Button*, void*);
  static void cb_Browse(Fl_Button*, void*);
public:
  Fl_Double_Window *HORBank;
  Fl_Button *BClose;
private:
  inline void cb_BClose_i(Fl_Button*, void*);
  static void cb_BClose(Fl_Button*, void*);
  static Fl_Menu_Item menu_[];
public:
  static Fl_Menu_Item *BFile;
  static Fl_Menu_Item *BLoad;
private:
  inline void cb_BLoad_i(Fl_Menu_*, void*);
  static void cb_BLoad(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *BSave;
private:
  inline void cb_BSave_i(Fl_Menu_*, void*);
  static void cb_BSave(Fl_Menu_*, void*);
  inline void cb_Close_i(Fl_Menu_*, void*);
  static void cb_Close(Fl_Menu_*, void*);
public:
  Fl_Button *Banco1;
private:
  inline void cb_Banco1_i(Fl_Button*, void*);
  static void cb_Banco1(Fl_Button*, void*);
public:
  Fl_Button *Banco2;
private:
  inline void cb_Banco2_i(Fl_Button*, void*);
  static void cb_Banco2(Fl_Button*, void*);
public:
  Fl_Button *Banco3;
private:
  inline void cb_Banco3_i(Fl_Button*, void*);
  static void cb_Banco3(Fl_Button*, void*);
public:
  Fl_Button *Banco4;
private:
  inline void cb_Banco4_i(Fl_Button*, void*);
  static void cb_Banco4(Fl_Button*, void*);
public:
  Fl_Button *Banco5;
private:
  inline void cb_Banco5_i(Fl_Button*, void*);
  static void cb_Banco5(Fl_Button*, void*);
public:
  Fl_Button *Banco6;
private:
  inline void cb_Banco6_i(Fl_Button*, void*);
  static void cb_Banco6(Fl_Button*, void*);
public:
  Fl_Button *Banco7;
private:
  inline void cb_Banco7_i(Fl_Button*, void*);
  static void cb_Banco7(Fl_Button*, void*);
public:
  Fl_Button *Banco8;
private:
  inline void cb_Banco8_i(Fl_Button*, void*);
  static void cb_Banco8(Fl_Button*, void*);
public:
  Fl_Button *Banco9;
private:
  inline void cb_Banco9_i(Fl_Button*, void*);
  static void cb_Banco9(Fl_Button*, void*);
public:
  Fl_Button *Banco10;
private:
  inline void cb_Banco10_i(Fl_Button*, void*);
  static void cb_Banco10(Fl_Button*, void*);
public:
  Fl_Button *Banco11;
private:
  inline void cb_Banco11_i(Fl_Button*, void*);
  static void cb_Banco11(Fl_Button*, void*);
public:
  Fl_Button *Banco12;
private:
  inline void cb_Banco12_i(Fl_Button*, void*);
  static void cb_Banco12(Fl_Button*, void*);
public:
  Fl_Button *Banco13;
private:
  inline void cb_Banco13_i(Fl_Button*, void*);
  static void cb_Banco13(Fl_Button*, void*);
public:
  Fl_Button *Banco14;
private:
  inline void cb_Banco14_i(Fl_Button*, void*);
  static void cb_Banco14(Fl_Button*, void*);
public:
  Fl_Button *Banco15;
private:
  inline void cb_Banco15_i(Fl_Button*, void*);
  static void cb_Banco15(Fl_Button*, void*);
public:
  Fl_Button *Banco16;
private:
  inline void cb_Banco16_i(Fl_Button*, void*);
  static void cb_Banco16(Fl_Button*, void*);
public:
  Fl_Button *Banco17;
private:
  inline void cb_Banco17_i(Fl_Button*, void*);
  static void cb_Banco17(Fl_Button*, void*);
public:
  Fl_Button *Banco18;
private:
  inline void cb_Banco18_i(Fl_Button*, void*);
  static void cb_Banco18(Fl_Button*, void*);
public:
  Fl_Button *Banco19;
private:
  inline void cb_Banco19_i(Fl_Button*, void*);
  static void cb_Banco19(Fl_Button*, void*);
public:
  Fl_Button *Banco20;
private:
  inline void cb_Banco20_i(Fl_Button*, void*);
  static void cb_Banco20(Fl_Button*, void*);
public:
  Fl_Button *Banco21;
private:
  inline void cb_Banco21_i(Fl_Button*, void*);
  static void cb_Banco21(Fl_Button*, void*);
public:
  Fl_Button *Banco22;
private:
  inline void cb_Banco22_i(Fl_Button*, void*);
  static void cb_Banco22(Fl_Button*, void*);
public:
  Fl_Button *Banco23;
private:
  inline void cb_Banco23_i(Fl_Button*, void*);
  static void cb_Banco23(Fl_Button*, void*);
public:
  Fl_Button *Banco24;
private:
  inline void cb_Banco24_i(Fl_Button*, void*);
  static void cb_Banco24(Fl_Button*, void*);
public:
  Fl_Button *Banco25;
private:
  inline void cb_Banco25_i(Fl_Button*, void*);
  static void cb_Banco25(Fl_Button*, void*);
public:
  Fl_Button *Banco26;
private:
  inline void cb_Banco26_i(Fl_Button*, void*);
  static void cb_Banco26(Fl_Button*, void*);
public:
  Fl_Button *Banco27;
private:
  inline void cb_Banco27_i(Fl_Button*, void*);
  static void cb_Banco27(Fl_Button*, void*);
public:
  Fl_Button *Banco28;
private:
  inline void cb_Banco28_i(Fl_Button*, void*);
  static void cb_Banco28(Fl_Button*, void*);
public:
  Fl_Button *Banco29;
private:
  inline void cb_Banco29_i(Fl_Button*, void*);
  static void cb_Banco29(Fl_Button*, void*);
public:
  Fl_Button *Banco30;
private:
  inline void cb_Banco30_i(Fl_Button*, void*);
  static void cb_Banco30(Fl_Button*, void*);
public:
  Fl_Button *Banco31;
private:
  inline void cb_Banco31_i(Fl_Button*, void*);
  static void cb_Banco31(Fl_Button*, void*);
public:
  Fl_Button *Banco32;
private:
  inline void cb_Banco32_i(Fl_Button*, void*);
  static void cb_Banco32(Fl_Button*, void*);
public:
  Fl_Double_Window *RitEdit;
private:
  inline void cb_RitEdit_i(Fl_Double_Window*, void*);
  static void cb_RitEdit(Fl_Double_Window*, void*);
public:
  Fl_Input *RtName;
private:
  inline void cb_RtName_i(Fl_Input*, void*);
  static void cb_RtName(Fl_Input*, void*);
public:
  Fl_Input *RtFile;
private:
  inline void cb_RtFile_i(Fl_Input*, void*);
  static void cb_RtFile(Fl_Input*, void*);
public:
  Fl_Value_Input *RtBars;
private:
  inline void cb_RtBars_i(Fl_Value_Input*, void*);
  static void cb_RtBars(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *RtDen;
private:
  inline void cb_RtDen_i(Fl_Value_Input*, void*);
  static void cb_RtDen(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G1;
  Fl_Value_Input *lb1;
private:
  inline void cb_lb1_i(Fl_Value_Input*, void*);
  static void cb_lb1(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb2;
private:
  inline void cb_lb2_i(Fl_Value_Input*, void*);
  static void cb_lb2(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb3;
private:
  inline void cb_lb3_i(Fl_Value_Input*, void*);
  static void cb_lb3(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb4;
private:
  inline void cb_lb4_i(Fl_Value_Input*, void*);
  static void cb_lb4(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv1;
private:
  inline void cb_lbv1_i(Fl_Value_Input*, void*);
  static void cb_lbv1(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv2;
private:
  inline void cb_lbv2_i(Fl_Value_Input*, void*);
  static void cb_lbv2(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv3;
private:
  inline void cb_lbv3_i(Fl_Value_Input*, void*);
  static void cb_lbv3(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv4;
private:
  inline void cb_lbv4_i(Fl_Value_Input*, void*);
  static void cb_lbv4(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G2;
  Fl_Value_Input *lb5;
private:
  inline void cb_lb5_i(Fl_Value_Input*, void*);
  static void cb_lb5(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb6;
private:
  inline void cb_lb6_i(Fl_Value_Input*, void*);
  static void cb_lb6(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb7;
private:
  inline void cb_lb7_i(Fl_Value_Input*, void*);
  static void cb_lb7(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb8;
private:
  inline void cb_lb8_i(Fl_Value_Input*, void*);
  static void cb_lb8(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv5;
private:
  inline void cb_lbv5_i(Fl_Value_Input*, void*);
  static void cb_lbv5(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv6;
private:
  inline void cb_lbv6_i(Fl_Value_Input*, void*);
  static void cb_lbv6(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv7;
private:
  inline void cb_lbv7_i(Fl_Value_Input*, void*);
  static void cb_lbv7(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv8;
private:
  inline void cb_lbv8_i(Fl_Value_Input*, void*);
  static void cb_lbv8(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G3;
  Fl_Value_Input *lb9;
private:
  inline void cb_lb9_i(Fl_Value_Input*, void*);
  static void cb_lb9(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb10;
private:
  inline void cb_lb10_i(Fl_Value_Input*, void*);
  static void cb_lb10(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb11;
private:
  inline void cb_lb11_i(Fl_Value_Input*, void*);
  static void cb_lb11(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb12;
private:
  inline void cb_lb12_i(Fl_Value_Input*, void*);
  static void cb_lb12(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv9;
private:
  inline void cb_lbv9_i(Fl_Value_Input*, void*);
  static void cb_lbv9(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv10;
private:
  inline void cb_lbv10_i(Fl_Value_Input*, void*);
  static void cb_lbv10(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv11;
private:
  inline void cb_lbv11_i(Fl_Value_Input*, void*);
  static void cb_lbv11(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv12;
private:
  inline void cb_lbv12_i(Fl_Value_Input*, void*);
  static void cb_lbv12(Fl_Value_Input*, void*);
public:
  Fl_Group *B1G4;
  Fl_Value_Input *lb13;
private:
  inline void cb_lb13_i(Fl_Value_Input*, void*);
  static void cb_lb13(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb14;
private:
  inline void cb_lb14_i(Fl_Value_Input*, void*);
  static void cb_lb14(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb15;
private:
  inline void cb_lb15_i(Fl_Value_Input*, void*);
  static void cb_lb15(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lb16;
private:
  inline void cb_lb16_i(Fl_Value_Input*, void*);
  static void cb_lb16(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv13;
private:
  inline void cb_lbv13_i(Fl_Value_Input*, void*);
  static void cb_lbv13(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv14;
private:
  inline void cb_lbv14_i(Fl_Value_Input*, void*);
  static void cb_lbv14(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv15;
private:
  inline void cb_lbv15_i(Fl_Value_Input*, void*);
  static void cb_lbv15(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *lbv16;
private:
  inline void cb_lbv16_i(Fl_Value_Input*, void*);
  static void cb_lbv16(Fl_Value_Input*, void*);
public:
  Fl_Counter *SBar;
private:
  inline void cb_SBar_i(Fl_Counter*, void*);
  static void cb_SBar(Fl_Counter*, void*);
public:
  Fl_Button *CloRit;
private:
  inline void cb_CloRit_i(Fl_Button*, void*);
  static void cb_CloRit(Fl_Button*, void*);
public:
  void metelo();
  void GetCombi(int i);
  void PutCombi(int i);
  void MiraClientes();
  void MiraConfig();
  void GrabaSettings();
  void metebanco();
  HORGAN(HOR *hor_);
  void Conecta();
  void Undo();
  void Actu();
  void Redo();
  void PutPrim();
  void GetPrim();
  static void tick(void *v);
private:
  HOR *hor;
public:
  void ponreverb();
  void GetRit(int Rit);
  void meteritmos();
  void calbtrans();
  void calbtune();
  void EditRit(int i);
  void QuitaPon();
  void meteval();
  void ApagaTodo();
  void meteprog();
};
#endif

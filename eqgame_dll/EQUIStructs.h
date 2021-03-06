#pragma once
/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

namespace EQUIStructs
{


enum UIType
{
   UI_Unknown=-1,
   UI_Class=0,
   UI_RGB=1,
   UI_Point=2,
   UI_Size=3,
   UI_TextureInfo=4,
   UI_Frame=5,
   UI_Ui2DAnimation=6,
   UI_ButtonDrawTemplate=7,
   UI_GaugeDrawTemplate=8,
   UI_SpellGemDrawTemplate=9,
   UI_FrameTemplate=10,
   UI_ScrollbarDrawTemplate=11,
   UI_WindowDrawTemplate=12,
   UI_SliderDrawTemplate=13,
   UI_ScreenPiece=14,
   UI_StaticScreenPiece=15,
   UI_StaticAnimation=16,
   UI_StaticTintedBlendAnimation=17,
   UI_StaticText=18,
   UI_StaticFrame=19,
   UI_StaticHeader=20,
   UI_LayoutStrategy=21,
   UI_LayoutVertical=22,
   UI_LayoutHorizontal=23,
   UI_Control=24,
   UI_TemplateAssoc=25,
   UI_TemplateScreen=26,
   UI_ListboxColumn=27,
   UI_Listbox=28,
   UI_Button=29,
   UI_Gauge=30,
   UI_SpellGem=31,
   UI_HtmlComponent=32,
   UI_InvSlot=33,
   UI_EditBox=34,
   UI_Slider=35,
   UI_Label=36,
   UI_STMLBox=37,
   UI_TreeView=38,
   UI_Combobox=39,
   UI_Page=40,
   UI_TabBox=41,
   UI_LayoutBox=42,
   UI_HorizontalLayoutBox=43,
   UI_VerticalLayoutBox=44,
   UI_FinderBox=45,
   UI_TileLayoutBox=46,
   UI_NamedTemplatePiece=47,
   UI_TemplateContainer=48,
   UI_Screen=49,
   UI_SuiteDefaults=50,
   UI_Screens=51,
   UI_TopLevelWindowList=52,
   UI_HotButton=53,
};

// ***************************************************************************
// Structures
// ***************************************************************************

// 10-24-2003 Lax - Massive overhaul.
// See http://macroquest.sourceforge.net/phpBB2/viewtopic.php?t=3569 for
// standards on structures to make things easier on everyone!
// -- ONLY applies to EQ structs, not MQ structs like alerts, etc.





typedef struct _EQCURRENTSELECTION {
/*0x00*/   DWORD   Unknown;
/*0x04*/   DWORD   SelectedWnd;     //address to selection in tree
/*0x08*/   DWORD   Unknownlodncrap;
/*0x0c*/   DWORD   NumberOfSlots;   //merchantslots == 79
/*0x10*/   DWORD   TextureAnim;
/*0x14*/
} EQCURRENTSELECTION, *PEQCURRENTSELECTION;

#define VFTABLE \
/*0x000*/ LPVOID  IsValid; \
/*0x004*/ LPVOID  vector_deleting_destructor; \
/*0x008*/ LPVOID  DrawNC; \
/*0x00c*/ LPVOID  PostDraw; \
/*0x010*/ LPVOID  PostDraw2; \
/*0x014*/ LPVOID  DrawCursor; \
/*0x018*/ LPVOID  nullsub0x18; \
/*0x01c*/ LPVOID  PostDraw3; \
/*0x020*/ LPVOID  DrawBackground; \
/*0x024*/ LPVOID  DrawTooltip; \
/*0x028*/ LPVOID  DrawTooltipAtPoint; \
/*0x02c*/ LPVOID  GetMinimizedRect; \
/*0x030*/ LPVOID  DrawTitleBar; \
/*0x034*/ LPVOID  GetCursorToDisplay; \
/*0x038*/ LPVOID  HandleLButtonDown; \
/*0x03c*/ LPVOID  HandleLButtonUp; \
/*0x040*/ LPVOID  HandleLButtonHeld; \
/*0x044*/ LPVOID  HandleLButtonUpAfterHeld; \
/*0x048*/ LPVOID  HandleRButtonDown; \
/*0x04c*/ LPVOID  HandleRButtonUp; \
/*0x050*/ LPVOID  HandleRButtonHeld; \
/*0x054*/ LPVOID  HandleRButtonUpAfterHeld; \
/*0x058*/ LPVOID  HandleWheelButtonDown; \
/*0x05c*/ LPVOID  HandleWheelButtonUp; \
/*0x060*/ LPVOID  HandleMouseMove; \
/*0x064*/ LPVOID  HandleWheelMove; \
/*0x068*/ LPVOID  GetDragDropCursor; \
/*0x06c*/ LPVOID  PostDraw4; \
/*0x070*/ LPVOID  OnDragDrop; \
/*0x074*/ LPVOID  GetClickStickCursor; \
/*0x078*/ LPVOID  QueryDropOK; \
/*0x07c*/ LPVOID  OnClickStick; \
/*0x080*/ LPVOID  GetClickStickCursor2; \
/*0x084*/ LPVOID  QueryClickStickDropOK; \
/*0x088*/ LPVOID  WndNotification; \
/*0x08c*/ LPVOID  Unknown8c; \
/*0x090*/ LPVOID  ShowWindow; /* Activate */ \
/*0x094*/ LPVOID  Deactivate; \
/*0x098*/ LPVOID  PostDraw5; \
/*0x09c*/ LPVOID  OnResize; \
/*0x0a0*/ LPVOID  OnResize2; \
/*0x0a4*/ LPVOID  Unknown0xa4; \
/*0x0a8*/ LPVOID  Unknown0xa8; \
/*0x0ac*/ LPVOID  OnMinimizeBox; \
/*0x0b0*/ LPVOID  Unknown0xb0; \
/*0x0b4*/ LPVOID  OnTileBox; \
/*0x0b8*/ LPVOID  PostDraw6; \
/*0x0bc*/ LPVOID  OnMove2; \
/*0x0c0*/ LPVOID  OnMove3; \
/*0x0c4*/ LPVOID  OnProcessFrame; \
/*0x0c8*/ LPVOID  OnVScroll; \
/*0x0cc*/ LPVOID  OnHScroll; \
/*0x0d0*/ LPVOID  PostDraw7; \
/*0x0d4*/ LPVOID  OnMove4; \
/*0x0d8*/ LPVOID  Show; \
/*0x0dc*/ LPVOID  Unknown0xdc; \
/*0x0e0*/ LPVOID  Unknown0xe0; \
/*0x0e4*/ LPVOID  OnMove5; \
/*0x0e8*/ LPVOID  GetTooltip; \
/*0x0ec*/ LPVOID  HitTest; \
/*0x0f0*/ LPVOID  GetHitTestRect; \
/*0x0f4*/ LPVOID  GetInnerRect; \
/*0x0f8*/ LPVOID  GetClientRect; \
/*0x0fc*/ LPVOID  GetMinSize; \
/*0x100*/ LPVOID  GetMaxSize; \
/*0x104*/ LPVOID  GetUntileSize; \
/*0x108*/ LPVOID  IsPointTransparent; \
/*0x10c*/ LPVOID  Unknown10c; \
/*0x110*/ LPVOID  Unknown110; \
/*0x114*/ LPVOID  Unknown114; \
/*0x118*/ LPVOID  SetDrawTemplate; \
/*0x11c*/ LPVOID  Move_Rect; \
/*0x120*/ LPVOID  Move_Point; \
/*0x124*/ LPVOID  SetWindowTextA; \
/*0x128*/ LPVOID  Unknown0x128; \
/*0x12c*/ LPVOID  Unknown0x12c; \
/*0x130*/ LPVOID  Unknown0x130; \
/*0x134*/ LPVOID  SetVScrollPos; \
/*0x138*/ LPVOID  SetHScrollPos; \
/*0x13c*/ LPVOID  Unknown0x13c; \
/*0x140*/ LPVOID  Unknown0x140; \
/*0x144*/ LPVOID  SetAttributesFromSidl; \
/*0x148*/ LPVOID  nullsub_1; \
/*0x14c*/ LPVOID  Unknown0x14c; \
/*0x150*/ LPVOID  Unknown0x150; \
/*0x154*/ LPVOID  Unknown0x154; \
/*0x158*/ LPVOID  Unknown0x158; \
/*0x15c*/ LPVOID  PostDraw8; \
/*0x160*/ LPVOID  Unknown0x160; \
/*0x164*/

typedef struct _CSIDLWNDVFTABLE {
VFTABLE;
/*0x168*/ LPVOID  LoadIniInfo;
/*0x16c*/ LPVOID  StoreIniInfo;
/*0x170*/ LPVOID  Unknown0x170;
/*0x174*/ LPVOID  Unknown0x174;
/*0x178*/ LPVOID  Unknown0x178;
/*0x17c*/
} CSIDLWNDVFTABLE, *PCSIDLWNDVFTABLE; 

typedef struct _CXWNDVFTABLE {
VFTABLE;
} CXWNDVFTABLE, *PCXWNDVFTABLE; 


#define CXW_NO_VTABLE \
/*0x004*/   void    *pUnknown0x4; \
/*0x008*/   struct  _CSIDLWND *pNextSiblingWnd; \
/*0x00c*/   void    *pUnknown0xc; \
/*0x010*/   struct  _CSIDLWND *pFirstChildWnd; \
/*0x014*/   BYTE    Unknown0x14[0x5]; \
/*0x019*/   BYTE    Alpha; \
/*0x01a*/   BYTE    Enabled; \
/*0x01b*/   BYTE    Unknown0x1b[0x5]; \
/*0x020*/   BYTE    MouseOver; /*found in CXWnd__SetMouseOver_x*/ \
/*0x021*/   BYTE    Unknown0x21[0xc]; \
/*0x02d*/   BYTE    Locked; /*found in CSidlScreenWnd__LoadIniInfo_x*/ \
/*0x02e*/   BYTE    Unknown0x2e[0x32]; \
/*0x060*/   RECT    Location; \
/*0x070*/   BYTE    Unknown0x70[0x10]; \
/*0x080*/   DWORD   FadeDuration; \
/*0x084*/   DWORD   WindowStyle;    /* bit 1 - vertical scroll, bit 2 - horizontal scroll, bit 4 - title bar?, bit 8 - border */ \
/*0x088*/   BYTE    Unknown0x88[0x10]; \
/*0x098*/   BYTE    CloseOnESC;     /* found in CSidlScreenWnd__StoreIniInfo_x, close when ESC is pressed */ \
/*0x099*/   BYTE    Unknown0x99[0x27]; \
/*0x0c0*/   RECT    OldLocation; \
/*0x0d0*/   BYTE    Unknown0xd0[0x4]; \
/*0x0d4*/   DWORD   TickCount2; \
/*0x0d8*/   DWORD   XMLIndex; \
/*0x0dc*/   BYTE    Unknown0xdc[0xc]; \
/*0x0e8*/   struct  _CXSTR  *Tooltip; /*found in CSidlManager__CreateLabel_x*/ \
/*0x0ec*/   BYTE    Unknown0xec[0x4]; \
/*0x0f0*/   DWORD   TimeMouseOver; \
/*0x0f4*/   BYTE    Unknown0xf4[0x2c]; \
/*0x120*/   DWORD   ZLayer; /*found in CXWndManager__DrawWindows_x*/ \
/*0x124*/   struct  _CXSTR  *XMLToolTip; /*found in CSidlManager__CreateLabel_x*/ \
/*0x128*/   ARGBCOLOR BGColor; \
/*0x12c*/   DWORD   UnknownCW; /*found in OnProcessFrame*/\
/*0x130*/   BYTE    Unknown0x130[0x8]; \
/*0x138*/   BYTE    Clickable;      /* found in CChatWindow__CChatWindow_x and the button handlers */ \
/*0x139*/   BYTE    Unknown0x139[0x3b]; \
/*0x174*/   struct  _CSIDLWND *pParentWindow; /*CXWnd__IsDescendantOf_x has this one, If this is NULL, coordinates are absolute... */ \
/*0x178*/   BYTE    Unknown0x178[0x4]; \
/*0x17c*/   DWORD   VScrollPos; \
/*0x180*/   BYTE    Unknown0x180[0x8]; \
/*0x188*/   LPVOID  DrawTemplate; \
/*0x18c*/   BYTE    Faded; \
/*0x18d*/   BYTE    Unknown0x18d[0x3]; \
/*0x190*/   DWORD   VScrollMax; \
/*0x194*/   BYTE    ValidCXWnd; /*IsValid has this one*/\
/*0x195*/   BYTE    Unknown0x195; \
/*0x196*/   BYTE    dShow; \
/*0x197*/   BYTE    Unknown0x197; \
/*0x198*/   DWORD   HScrollPos; \
/*0x19c*/   BYTE    Unknown0x19c; \
/*0x19d*/   BYTE    Fades; \
/*0x19e*/   BYTE    Unknown0x19e[0x2]; \
/*0x1a0*/   DWORD   HScrollMax; \
/*0x1a4*/   BYTE    Unknown0x1a4[0x4]; \
/*0x1a8*/   struct  _CXSTR  *WindowText; /*CXWnd__GetWindowTextA_x has this one*/ \
/*0x1ac*/   BYTE    Unknown0x1ac[0x2]; \
/*0x1ae*/   BYTE    FadeToAlpha; /*found in CSidlScreenWnd__StoreIniInfo_x*/\
/*0x1af*/   BYTE    Unknown0x1af; \
/*0x1b0*/   DWORD   BGType;         /* found in CSidlScreenWnd__StoreIniInfo_x "BGType" in ini */ \
/*0x1b4*/   BYTE    Unknown0x1b4[0x10]; \
/*0x1c4*/   BYTE    Unlockable;     /* found in CSidlScreenWnd__LoadIniInfo_x related to Locked */ \
/*0x1c5*/   BYTE    Unknown0x1c5[0x9]; \
/*0x1ce*/   BYTE    Minimized; \
/*0x1cf*/   BYTE    Unknown0x1cf[0x9]; \
/*0x1d8*/

#define CXW \
/*0x000*/   struct  _CXWNDVFTABLE   *pvfTable; \
CXW_NO_VTABLE \
/*0x1d8*/

typedef struct _CXWND {
CXW;
} CXWND, *PCXWND;
#define GateBind          0

#define CSW \
/*0x000*/   struct  _CSIDLWNDVFTABLE   *pvfTable; \
CXW_NO_VTABLE; \
/*0x1d8*/   union { \
                struct _CXSTR  *SidlText; /*found in CChatWindow__WndNotification_x*/\
                DWORD  Items; \
            }; \
/*0x1dc*/   union { \
                struct _CXSTR  *SidlScreen; \
                DWORD   SlotID; \
            }; \
/*0x1e0*/   LPVOID  SidlPiece;      /* CScreenPieceTemplate (important) */ \
/*0x1e4*/   union { /*find in CSidlScreenWnd__dCSidlScreenWnd_x*/ \
                struct { \
                    BYTE    Checked; \
                    BYTE    Highlighted; \
                    BYTE    Unused0x1c8[0x2]; \
                }; \
                DWORD MaxChars; \
            }; \
/*0x1e8*/   DWORD   TextureAnim; \
/*0x1ec*/   struct  _CXSTR *   InputText; /*found in CChatWindow__CChatWindow_x*/\
/*0x1f0*/   DWORD   Selector; /*found in CSidlScreenWnd__CSidlScreenWnd1_x*/\
/*0x1f4*/   DWORD   PushToSelector; /*found in CSidlScreenWnd__LoadIniInfo_x*/\
/*0x1f8*/   DWORD   EnableINIStorage; /*found in CSidlScreenWnd__LoadSidlScreen_x*/\
/*0x1fc*/   union { \
                struct _CXSTR *INIStorageName; /*found in CSidlScreenWnd__LoadSidlScreen_x*/\
                struct _EQINVSLOT *pEQInvSlot; \
            }; \
/*0x200*/   BYTE    Unknown0x200[0x10];  \
/*0x210*/   LPVOID  ContextMenu;    /* CTextureAnimation */ \
/*0x214*/   DWORD   Unknown0x214;   /* CTextureAnimation */ \
/*0x218*/   DWORD   Unknown0x218;   /* CTextureAnimation */ \
/*0x21c*/   DWORD   Unknown0x21c; \
/*0x220*/

typedef struct _CSIDLWND {
CSW;
} CSIDLWND, *PCSIDLWND;

// size 0x298  09-03-2008
typedef struct _CSIDLMGR {
/*0x000*/    BYTE    Unknown0x000[0x144];
/*0x144*/    PVOID   pXMLDataMgr;
/*0x148*/    BYTE    Unknown0x11c[0x150];
/*0x298*/
} CSIDLMGR, *PCSIDLMGR;

//11-6-2003 lax
//Actual size 0x140 11-11-09 - ieatacid
typedef struct _CXWNDMGR {
/*0x000*/ LPVOID CXWNDMGR__vtable;
/*0x004*/ DWORD Count;
/*0x008*/ struct _CSIDLWND **pWindows;
/*0x00c*/ BYTE Unknown0x00C[0x91];
/*0x09d*/ bool KeyboardFlags[4];    // 7d-80
/*0x0a1*/ CHAR Unknown0x0a1[0x6b];
/*0x10c*/ DWORD ScreenExtentX;
/*0x110*/ DWORD ScreenExtentY;
/*0x114*/ DWORD Unknown;
/*0x118*/ DWORD font_list_ptr;
/*0x11c*/ BYTE Unknown0x11c[0x24];
/*0x140*/ 
} CXWNDMGR, *PCXWNDMGR;


typedef struct _CONTENTSARRAY {
    struct _CONTENTS* Array[1];
} CONTENTSARRAY, *PCONTENTSARRAY;

// 20120316 - ieatacid
struct merchdata {
/*0x00*/ void   *vftable;
/*0x04*/ BYTE   Unknown0x4[0xc];
/*0x10*/ DWORD  MerchSlots;
/*0x14*/ DWORD  Unknown0x14;
/*0x18*/ struct _CONTENTSARRAY *pMerchArray;
/*0x1c*/ DWORD  MerchMaxSlots;
/*0x20*/
};

struct merch_other {
    merchdata *pMerchData;
    void *other;
    void *other2;
};

// size 0x2b0 20130514 - eqmule
typedef struct _EQMERCHWINDOW {
/*0x000*/   struct  _CSIDLWND Wnd;
/*0x220*/   BYTE    Unknown0x220[0x0c];
/*0x22c*/   merch_other   *pMerchOther;
/*0x230*/   BYTE    Unknown0x230[0x8];
/*0x238*/   FLOAT   Markup;//777026 has this in 04-15-2013
/*0x23c*/   BYTE    Unknown0x23c[0xc];
/*0x248*/   DWORD   SelectedSlotID;
// more data but this is all we need
} EQMERCHWINDOW, *PEQMERCHWINDOW;



// 10-27-2003 Lax
// Actual size 0x208 11-5-2003
typedef struct _EQCHATMGR
{
/*0x000*/ struct _EQCHATWINDOW* ChatWnd[0x20];
/*0x080*/ DWORD NumWindows;
/*0x084*/ DWORD ActiveWindow; // CChat::GetActiveChatWindow
/*0x088*/ DWORD LockedWindow; // CChatManager::GetActiveChatWindow
/*0x08c*/ DWORD Unknown0x08c;
/*0x090*/ struct _EQCHATWINDOW* ChannelMap[0x20];   // channel map
/*0x110*/ BYTE  Unknown0x110[0x28];
/*0x138*/ DWORD Unknown0x138;
/*0x13c*/ DWORD Unknown0x13c;
/*0x140*/ DWORD Unknown0x140;
/*0x144*/ LPVOID ChatMenu;
/*0x148*/ DWORD Unknown0x148;
/*0x14c*/ DWORD Unknown0x14c;
/*0x150*/ DWORD Unknown0x150;
/*0x154*/ DWORD Unknown0x154;
/*0x158*/ LPVOID MeleeMenu;
/*0x15c*/ DWORD Unknown0x15c;
/*0x160*/ LPVOID SpellMenu;
/*0x164*/ DWORD Unknown0x164;
/*0x168*/ DWORD Unknown0x168;
/*0x16c*/ LPVOID ChannelMenu;
/*0x170*/ LPVOID ChatMenu2;
/*0x174*/ LPVOID FilterMenu;
/*0x178*/ DWORD Unknown0x178;
/*0x17c*/ DWORD Unknown0x17c;
/*0x180*/ DWORD Unknown0x180;
/*0x184*/ LPVOID HitsModeMenu;
/*0x188*/ LPVOID MeleeMenu2;
/*0x18c*/ LPVOID HitsModeMenu2;
/*0x190*/ DWORD Unknown0x190;
/*0x194*/ LPVOID HitsModeMenu3;
/*0x198*/ DWORD Unknown0x198;
/*0x19c*/ LPVOID HitsModeMenu4;
/*0x1a0*/ DWORD Unknown0x1a0;
/*0x1a4*/ LPVOID HitsModeMenu5;
/*0x1a8*/ DWORD Unknown0x1a8;
/*0x1ac*/ LPVOID HitsModeMenu6;
/*0x1b0*/ DWORD Unknown0x1b0;
/*0x1b4*/ DWORD Unknown0x1b4; // CChatManager__UpdateTellMenus
/*0x1b8*/ DWORD Unknown0x1b8;
/*0x1bc*/ DWORD Unknown0x1bc; // CChatManager__UpdateTellMenus
/*0x1c0*/ DWORD Unknown0x1c0;
/*0x1c4*/ DWORD Unknown0x1c4; // CChatManager__UpdateTellMenus // raid
/*0x1c8*/ DWORD Unknown0x1c8;
/*0x1cc*/ DWORD Unknown0x1cc; // CChatManager__UpdateTellMenus
/*0x1d0*/ DWORD Unknown0x1d0; // CChatManager__UpdateTellMenus
/*0x1d4*/ DWORD Unknown0x1d4; // CChatManager__UpdateTellMenus
/*0x1d8*/ DWORD Unknown0x1d8;
/*0x1dc*/ DWORD Unknown0x1dc;
/*0x1e0*/ DWORD Unknown0x1e0;
/*0x1e4*/ BYTE  Unknown0x1e4[0x1c];
/*0x200*/ DWORD Unknown0x200;
/*0x204*/ DWORD Unknown0x204;
/*0x208*/
} EQCHATMGR, *PEQCHATMGR;

// Actual size 0x26c 02-14-2007
// 10-27-2003 Lax
typedef struct _EQCHATWINDOW
{
/*0x000*/ struct _CSIDLWND Wnd;
/*0x214*/ struct _EQCHATMGR *ChatManager; 
/*0x218*/ struct _CSIDLWND* InputWnd;
/*0x21c*/ struct _CSIDLWND* OutputWnd;
/*0x220*/ DWORD Unknown0x154;
/*0x224*/ DWORD Unknown0x158;       // need to update locations..
/*0x228*/ BYTE Unknown0x148;
/*0x229*/ BYTE Unknown0x149[0x3f];
/*0x268*/ DWORD Unknown0x188;
/*0x26c*/ DWORD Unknown0x18c;
/*0x270*/ struct _CXSTR *CommandHistory[0x28]; // ->0x198
/*0x310*/ DWORD Unknown0x230;       // CChatWindow::HistoryBack/forward .. maybe total or current history lines
/*0x314*/ DWORD Unknown0x234;       // CChatWindow::HistoryBack/forward .. maybe total or current history lines
/*0x318*/ DWORD FontSize;
/*0x268*/ DWORD Unknown0x23C;
/*0x26c*/
} EQCHATWINDOW, *PEQCHATWINDOW;

// in CChatWindow__CChatWindow
#define EQ_CHAT_HISTORY_OFFSET 0x288
// in CChatWindow__SetChatFont
#define EQ_CHAT_FONT_OFFSET    0x114

// Actual size 0x1dc old
// Lax 10-24-2003
typedef struct _EQBUFFWINDOW
{
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x48];
/*0x184*/ DWORD pBuff[0x0f];        // CButton*
/*0x1C0*/ DWORD Unknown0x1C0;
/*0x1C4*/ DWORD Unknown0x1C4;
/*0x1C8*/ DWORD Unknown0x1C8;
/*0x1CC*/ DWORD Unknown0x1CC;
/*0x1D0*/ DWORD FirstEffectSlot;    //0-15
/*0x1D4*/ DWORD LastEffectSlot;     //0-15
/*0x1D8*/ DWORD MaxBuffs;           // either 0x0F or 0x06  (normal or shortbuffs)
/*0x1DC*/
} EQBUFFWINDOW, *PEQBUFFWINDOW;

// actual size 0x294 20120316 - ieatacid
typedef struct _EQINVSLOTWND {
/*0x000*/   struct _CXWND Wnd;      //----/ actually CButtonWnd
/*0x1d4*/   BYTE Unknown0x1d4[0x88];  //___/
/*0x25c*/   DWORD Unknown0x25c;
/*0x260*/   LONG WindowType;        // ieatacid has this as InventoryType
                                    // 0 for inventory
                                    // 01 for bank
                                    // 02 for shared bank
                                    // 03 for trader window
                                    // 04 for World/Tradeskill/Combine
                                    // 11 for loot window
/*0x264*/   WORD InvSlotForBag;
/*0x266*/   WORD BagSlot;
/*0x268*/   BYTE Unknown0x268[0x20];
/*0x288*/   struct _EQINVSLOT *pInvSlot;
/*0x28c*/   BOOL ProcessClick;
/*0x290*/
} EQINVSLOTWND, *PEQINVSLOTWND;

// actual size 0x14 10-12-2010
typedef struct _EQINVSLOT {
/*0x00*/    LPVOID pvfTable;        // not based on cxwnd
/*0x04*/    struct _EQINVSLOTWND *pInvSlotWnd;
/*0x08*/    DWORD Unknown0x08;
/*0x0C*/    DWORD InvSlot;
/*0x10*/    BYTE Valid;
/*0x11*/    BYTE Unknown0x11[3];
/*0x14*/    
} EQINVSLOT, *PEQINVSLOT;

// actual size 0x2014 10-12-2010
typedef struct _EQINVSLOTMGR {
/*0x0000*/    DWORD Unknown0x0000;
/*0x0004*/    struct _EQINVSLOT *SlotArray[0x800];
/*0x2004*/    DWORD TotalSlots;
/*0x2008*/    DWORD Unknown0x2008;
/*0x200c*/    struct _EQINVSLOT *pSelectedItem;
/*0x2010*/    DWORD Unknown0x2010;
/*0x2014*/
} EQINVSLOTMGR, *PEQINVSLOTMGR;


// onetimehero 09-17-03
// ContainerWindow
// Actual Size 0x17C old
typedef struct _EQCONTAINERWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ struct _CONTENTS*   pContents;         // Pointer to the contents of the container;
                                                 // Matches the pointer in CHARINFO.Inventory/Bank/World
/*0x14c*/ struct _CSIDLWND*   pSlots[0x0a];
/*0x000*/ struct _CSIDLWND*   pCombine;
/*0x168*/ struct _CSIDLWND*   pDone;
/*0x16c*/ struct _CSIDLWND*   pIcon;
/*0x170*/ struct _CSIDLWND*   pUnknown;
/*0x174*/ struct _CSIDLWND*   pLabel;
/*0x178*/ BYTE Unknown0x178[4];
/*0x17c*/
} EQCONTAINERWINDOW, *PEQCONTAINERWINDOW;

// Actual Size 0x98  03/15/06
typedef struct _EQ_CONTAINERWND_MANAGER {
/*0x000*/   DWORD pvfTable;                           // NOT based on CXWnd.  Contains only destructor
/*0x004*/   PEQCONTAINERWINDOW pPCContainers[0x22];   // All open containers, including World, in order of opening...
/*0x08c*/   PCONTENTS   pWorldContents;               // Pointer to the contents of the world   If NULL, world container isn't open;
/*0x090*/   DWORD dwWorldContainerID;                 // ID of container in zone, starts at one (zero?) and goes up.
/*0x094*/   DWORD dwTimeSpentWithWorldContainerOpen;  // Cumulative counter?
/*0x078*/
} EQ_CONTAINERWND_MANAGER, *PEQ_CONTAINERWND_MANAGER;

typedef struct _POINT3 {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
} POINT3, *PPOINT3;

// plazmic 08-17-03
// Map Window
typedef struct _MAPLABEL { // sizeof() = 0x38
/*0x00*/    DWORD Unknown0x0;
/*0x04*/    struct _MAPLABEL *pNext;
/*0x08*/    struct _MAPLABEL *pPrev;
/*0x0c*/    POINT3 Location;
/*0x18*/    ARGBCOLOR Color;
/*0x1c*/    DWORD Size;     //1-3;
/*0x20*/    PCHAR Label;
/*0x24*/    DWORD Layer;    //0-3;
/*0x28*/    DWORD Width;
/*0x2c*/    DWORD Height;
/*0x30*/    DWORD unk_0x2c;
/*0x34*/    DWORD unk_0x30;
} MAPLABEL, *PMAPLABEL;

typedef struct _MAPLINE { // sizeof() = 0x28 (think this might be 0x34 now)
    struct _MAPLINE *pNext;
    struct _MAPLINE *pPrev;
    POINT3 Start;
    POINT3 End;
    ARGBCOLOR Color;
    DWORD Layer;          //0-3;
} MAPLINE, *PMAPLINE;

// size 0x3a8 20130514 - eqmule
typedef struct _EQLOOTWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x220*/ void   *vftable; // for CLootWnd::DialogResponse handler
/*0x224*/ BYTE   Unknown0x224[0x9c];
/*0x2c0*/ DWORD  NumOfSlots;
/*0x2c4*/ DWORD  Unknown0x2c4;
/*0x2c8*/ struct _INVENTORYARRAY *pInventoryArray;
/*0x2cc*/ DWORD  NumOfSlots2;
/*0x2d0*/ DWORD  NumOfSlots3;
/*0x2d4*/ BYTE   Unknown0x2d4[0x24];
/*0x2f8*/ BYTE   Unknown0x2f8;
/*0x2f9*/ BYTE   Unknown0x2f9;
/*0x2fa*/ BYTE   Unknown0x2fa;
/*0x2fb*/ BYTE   Unknown0x2fb;
/*0x2fc*/ struct _CSIDLWND *CLoot_LootInvWnd;
/*0x300*/ struct _CSILDWND *CLoot_LootSlotWnd[0x22];
/*0x388*/ struct _CSIDLWND *CLoot_CorpseName;
/*0x38c*/ struct _CSIDLWND *CLoot_DoneButton;
/*0x390*/ struct _CSIDLWND *CLoot_BroadcastButton;
/*0x394*/ struct _CSIDLWND *CLoot_LootAllButton;
/*0x398*/ BYTE   Unknown0x398[0x10];
/*0x3a8*/
} EQLOOTWINDOW, *PEQLOOTWINDOW;

//Size: 0x920 20130514 - ieatacid
typedef struct _EQPETINFOWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x220*/ BYTE  Unknown0x21c[0x14];
/*0x234*/ struct _CBUTTONWND *pButton[0xe];
/*0x26c*/ BYTE  Unknown0x26c[0x1dc];
/*0x448*/ struct _CSIDLWND *pWnd[NUM_BUFF_SLOTS]; // buff icons?
/*0x5cc*/ int   Buff[NUM_BUFF_SLOTS];        // Spell ID# of each buff -- 85 total
/*0x750*/ BYTE  Unknown0x750[0x20];
/*0x770*/ DWORD BuffFadeETA[NUM_BUFF_SLOTS]; // duration until buff fades, in thousands of a second
/*0x8f4*/ BYTE  Unknown0x8f4[0x2c];
/*0x920*/
} EQPETINFOWINDOW, *PEQPETINFOWINDOW; 

typedef struct _EQTRADESKILLRECIPE {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Trivial;
/*0x08*/ DWORD Unknown0x08;
/*0x0c*/ DWORD Unknown0x0c;
/*0x10*/ DWORD Unknown0x10;
/*0x14*/ CHAR  Name[0x40];
/*0x54*/ DWORD Unknown0x54;
/*0x58*/ DWORD Ingredient[0xa];     // ID# of ingredient(s)
/*0x80*/ DWORD IngredientIcon[0xa]; //Icon# of ingredient(s) (Note: 499 is blank)
} EQTRADESKILLRECIPE, *PEQTRADESKILLRECIPE;

//Size 0x3d8 (02/10/2004)
typedef struct _EQTRADESKILLWINDOW {
/*0x000*/   struct _CSIDLWND Wnd;
/*0x148*/ DWORD Unknown0x148[0x1b];  
/*0x1b4*/ PEQTRADESKILLRECIPE SearchResults[0x64]; 
/*0x344*/ DWORD    Unknown0x344;
/*0x348*/ DWORD Unknown0x348;
/*0x34c*/ DWORD Unknown0x34c;
/*0x350*/ PCONTENTS Container;
/*0x354*/ DWORD Unknown0x354;
/*0x358*/ PEQTRADESKILLRECIPE SelectedRecipe;
/*0x35c*/ DWORD Unknown0x35c;
/*0x360*/ DWORD SkillLevel;
/*0x364*/ DWORD Unknown0x364;
/*0x368*/ DWORD Unknown0x368;
/*0x36c*/ BYTE  Unknown0x36c[0x58];
/*0x3c4*/ DWORD Unknown0x3c4;
/*0x3c8*/ DWORD Unknown0x3c8;
/*0x3cc*/ BYTE  Unknonw0x3cc[0x8];
/*0x3d4*/ DWORD Unknown0x3d4;
/*0x3d8*/ DWORD Unknown0x3d8;
} EQTRADESKILLWINDOW, *PTRADESKILLWINDOW;

//Actual Size 0x308 - 20130514 - eqmule
typedef struct _EQTRADEWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x220*/ BYTE   Unknown0x220[0xd8];
/*0x2f8*/ BYTE   HisTradeReady;
/*0x2f9*/ BYTE   MyTradeReady;
/*0x300*/ BYTE   TradeWndOpen;
/*0x301*/ BYTE   Unknown0x301[0x7];
/*0x308*/
} EQTRADEWINDOW, *PTRADEWINDOW;

//Actual Size: 0x388 20121016 - ieatacid
typedef struct _EQRAIDWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x214*/ BYTE  Unknown0x214[0xb8];
/*0x2cc*/ DWORD ClassColors[0x10];
/*0x30c*/ BYTE  Unknown0x30c[0x7c];
/*0x388*/
} EQRAIDWINDOW, *PEQRAIDWINDOW;

typedef struct _GUILDMEMBERINFO {
/*0x000*/ DWORD Unknown0x000; //pointer?
/*0x004*/ BYTE OnlineStatus;  // 00=offline, 01=online
/*0x005*/ BYTE UnknownData0x005;
/*0x006*/ BYTE UnknownData0x006;
/*0x007*/ BYTE Unknown0x007;
/*0x008*/ BYTE Unknown0x008[0x8];
/*0x010*/ CHAR Name[0x40];
/*0x050*/ DWORD Level;
/*0x054*/ DWORD Class; 
/*0x058*/ DWORD Rank;         //0=member, 1=officer, 2=leader
/*0x05c*/ FLOAT UnknownData0x05c;
/*0x060*/ CHAR PublicNote[0x80];
/*0x0e0*/ BYTE Unknown0x0e0[0x180];
/*0x260*/ WORD UnknownData0x260;
/*0x262*/ WORD UnknownData0x262;
/*0x264*/ WORD UnknownData0x264;
/*0x266*/ WORD UnknownData0x266;
} GUILDMEMBERINFO, *PGUILDMEMBERINFO;

//Size: 0x3d0 (02/18/2004)
typedef struct _EQGUILDWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x4c];
/*0x194*/ BYTE Unknown0x194;
/*0x195*/ BYTE ShowOffline;                  // 01 = show offline box is checked
/*0x196*/ BYTE Unknown0x196[0x2];
/*0x198*/ struct _GUILDMEMBERINFO **pMember; // This is a pointer to the beginning of a list of pointers, 
                                             // each representing one player in the guild.  The number of 
                                             // pointers depends upon TotalMemberCount.
/*0x19c*/ DWORD TotalMemberCount;
/*0x1a0*/ DWORD Unknown0x1a0;                // 150?
/*0x1a4*/ DWORD Unknown0x1a4;                // 1?
/*0x1a8*/ DWORD TotalMemberCountAgain;
/*0x1ac*/ BYTE Unknown0x1ac[0x1c];
/*0x1c8*/ CHAR PersonalNotesFilePath[0x40];  // path to personal notes file
/*0x208*/ BYTE Unknown0x208[0x1c0];          // empty
/*0x3c8*/ DWORD Unknown0x3c8;                // 1?
/*0x3cc*/ DWORD Unknown0x3cc;                // some sort of bizaare pointer...
/*0x3d0*/
} EQGUILDWINDOW, *PEQGUILDWINDOW;

typedef struct _EQNOTESWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE  Unknown0x148[0x04];
/*0x14c*/ struct _CSIDLWND *pEditWnd;
} EQNOTESWINDOW, *PEQNOTESWINDOW;

// Lax 10-29-2003 
// Actual size 0x5dc 20121212 - ieatacid
typedef struct _EQITEMWINDOW 
{ 
/*0x000*/ struct _CSIDLWND Wnd;
/*0x21c*/ struct _CSIDLWND *DisplayWnd;
/*0x220*/ BYTE Unknown0x220[0x70];
/*0x290*/ PCXSTR ItemInfo;
/*0x294*/ PCXSTR WindowTitle;
/*0x298*/ PCXSTR Unknown0x298; // possibly PCXSTR of information as on charms 
/*0x29c*/ DWORD Unknown0x29c;
/*0x2a0*/ DWORD Unknown0x2a0;
/*0x2a4*/ PCXSTR UnknownCXStr; // if this is NULL don't populate item data in MQ2ItemDisplay
/*0x2a8*/ PCXSTR Unknown0x2a8;
/*0x2ac*/ PCONTENTS pItem;
/*0x29c*/ PVOID TextureAnim;
/*0x2a0*/ PVOID TextureAnim2;
/*0x2a4*/ BYTE  Unknown0x2a4[0x4c];
/*0x2f0*/ DWORD IDW_ItemInfo_Num_Lines;
/*0x2f4*/ struct _CSIDLWND *IDW_ItemInfo[0xc];
// pointers to stat labels, etc, in this area
} EQITEMWINDOW, *PEQITEMWINDOW;

// Actual size 0x1c8 07-09-2008
typedef struct _EQSPELLINFOWINDOW 
{ 
/*0x000*/ struct _CSIDLWND Wnd;
/*0x208*/ PVOID Unknown0x190;
/*0x20c*/ PVOID Unknown0x194;
/*0x210*/ struct _CSIDLWND *DisplayWnd;
/*0x214*/ PVOID Unknown0x19c; 
/*0x218*/ PVOID Unknown0x1a0; 
/*0x21c*/ PCXSTR ItemInfo;
/*0x220*/ PVOID Unknown0x1a8;
/*0x224*/ DWORD Unknown0x1ac;
/*0x228*/ DWORD Unknown0x1b0;
/*0x22c*/ DWORD Unknown0x1b4;
/*0x230*/ DWORD Unknown0x1b8;
/*0x234*/ PVOID TextureAnim;
/*0x238*/ DWORD SpellID;
/*0x23c*/ DWORD TimeStamp;
/*0x240*/ 
} EQSPELLINFOWINDOW, *PEQSPELLINFOWINDOW;

// Size: 0x1a4 (4/14/2005)
typedef struct _EQMAILWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x158  Finish... */
} EQMAILWINDOW, *PEQMAILWINDOW;


// Actual Size 0x624 20130514 - ieatacid/eqmule
typedef struct _EQMAPWINDOW {
/*0x000*/ struct    _CSIDLWND   Wnd;
/*0x220*/ BYTE      Unknown0x220[0x40];
/*0x260*/ CHAR      shortzonename[0x20];
/*0x280*/ BYTE      Unknown0x280[0x9c];
/*0x31c*/ struct    _CXWND  *wnd;           // MVW_MapRenderArea
/*0x320*/ BYTE      Unknown0x320[0x38];
/*0x358*/ struct    _CSIDLWNDVFTABLE    *pMapViewMapVfTable; // start of MapViewMap
/*0x35c*/ BYTE      Unknown0x35c[0x24c];
/*0x5a8*/ PMAPLINE  pLines;     //0x250
/*0x5ac*/ PMAPLABEL pLabels;    //0x254
/*0x5b0*/ BYTE      Unknown0x5b0[0x74];
/*0x624*/
} EQMAPWINDOW, *PEQMAPWINDOW;

// ieatacid 20120316
// Spell Window
typedef struct _EQCASTSPELLWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x214*/ BYTE Unknown0x214[0x14];
/*0x228*/  struct _EQCASTSPELLGEM   *SpellSlots[NUM_SPELL_GEMS];
/*0x258*/  BYTE    Unknown0x258[0x30]; 
/*0x288*/
} EQCASTSPELLWINDOW, *PEQCASTSPELLWINDOW;

// Individual Gems 
typedef struct _EQCASTSPELLGEM { 
/*0x000*/ struct    _CXWND Wnd;
/*0x1cc*/ BYTE      Unknown0x1cc[0x44]; 
/*0x210*/ DWORD     TimeStamp;
/*0x214*/ DWORD     RecastTime;
/*0x218*/ BYTE      Unknown0x218[0xa8]; 
/*0x2c0*/ DWORD     spellicon;       //if this is equal to FFFFFFFF there is no spell memmed in this slot... 
/*0x2c4*/ DWORD     spellstate;      // 1 = cast in progress or refreshtime not met 2 means we ducked or aborted cast, 0 means its ok to cast 
/*0x2c8*/ BYTE      Unknown0x2c8[0x18];
/*0x2e0*/ 
} EQCASTSPELLGEM, *PEQCASTSPELLGEM;
#define Fly                     0

// Actual size 0x1c4 10-9-2003
typedef struct _EQHOTBUTTONWINDOW {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x148*/ BYTE Unknown0x138[0xc];
/*0x000*/ DWORD   HotButtonWndView;     //0 to 9 for the different views
/*0x14c*/ struct _CSIDLWND   *HotButtons[0x0a];//these will change when you switch page...
/*0x174*/
} EQHOTBUTTONWINDOW, *PEQHOTBUTTONWINDOW;

typedef struct _LOOTCORPSE {
/*0x000*/   BYTE    Unknown0x000;   // 03 seems very common (for NPC anyway)
/*0x001*/   CHAR    Name[0x4b];
/*0x04c*/   FLOAT   Timer;          //Uncertain the equation used here, but fairly certain it's the timer
/*0x050*/   FLOAT   X;
/*0x054*/   BYTE    Unknown0x054[0x4];
/*0x058*/   FLOAT   Y;
/*0x05c*/   FLOAT   Z;
/*0x060*/   BYTE    Unknown0x060[0x24];
/*0x084*/   DWORD   Flags;
/*0x088*/   BYTE    Unknown0x088[0x4];
/*0x08c*/   DWORD   Unknown0x08c;   //256 seems very common
/*0x090*/
// I think there might be pointers at 0x0e0..but no clue what to
} LOOTCORPSE, *PLOOTCORPSE;

// size 0x180 3-10-2004
typedef struct _EQCOMPASSWINDOW {
/*0x000*/    struct _CSIDLWND Wnd;
/*0x148*/    struct _CSIDLWND *pStrip1;
/*0x14C*/    struct _CSIDLWND *pStrip2;
// in progress.
/*0x16C*/   BOOL DrawLine;
/*0x170*/   DWORD Unknown0x170;
/*0x174*/    DWORD LineRed;
/*0x178*/    DWORD LineGreen;
/*0x17C*/    DWORD LineBlue;
/*0x180*/
} EQCOMPASSWINDOW, *PEQCOMPASSWINDOW;

// used by options window
typedef struct _EQKBASSIGN
{
/*0x00*/    struct _CXSTR *pDescription;
/*0x04*/    DWORD nAssignmentNumber;
/*0x08*/
} EQKBASSIGN, *PEQKBASSIGN;

// size 0x904 3-10-2004
typedef struct _EQOPTIONSWINDOW {
/*0x000*/    struct _CSIDLWND Wnd;
/*0x148*/

/*0x264*/ struct _EQKBASSIGN Binds[0xA1];
/*0x508*/

/*0x904*/
} EQOPTIONSWINDOW, *PEQOPTIONSWINDOW;

// size 0x28 4-24-2004 Lax
typedef struct _EQGRAPHICSENGINE {
/*0x00*/ // Graphics file handler
/*0x04*/
} EQGRAPHICSENGINE, *PEQGRAPHICSENGINE;
#define SafeXLoc 0

typedef struct _CBUTTONWND {
/*0x000*/ struct    _CXWND Wnd;
/*0x1c4*/ BYTE      Unknown[0x4];
/*0x1c8*/ BYTE      State;        //1=down 0=up
/*0x1c9*/ BYTE      Unknown0x1c9; //something to do with State
/*0x1ca*/ BYTE      Unknown0x1ca[0x12];
/*0x1dc*/ ARGBCOLOR Color;
/*0x1e0*/
} CBUTTONWND, *PCBUTTONWND;
 
typedef struct _CTEXTENTRYWND {
/*0x000*/ struct    _CXWND Wnd;
/*0x1c4*/ DWORD     CursorPos1;
/*0x13c*/ DWORD     CursorPos2; //same as above but only this needs to be set to update cursor position
/*0x140*/
} CTEXTENTRYWND, *PCTEXTENTRYWND;

// size 0x2c8 20121128 - ieatacid
typedef struct _CPLAYERWND {
/*0x000*/ struct _CSIDLWND Wnd;
/*0x214*/ BYTE   Unknown[0xb0];
/*0x2c4*/ DWORD  CombatState;   // 1=debuffed, 2=combat cooldown, 3=stand, 4=sit
/* more data */ 
} CPLAYERWND, *PCPLAYERWND;

// size 0x87c 20120316 - ieatacid
typedef struct _CTARGETWND {
/*0x000*/ struct  _CSIDLWND Wnd;
/*0x208*/ BYTE    Unknown0x198[0x198];
/*0x3a0*/ struct _CBUTTONWND *pBuff[NUM_BUFF_SLOTS]; // buff icons

/*0x524*/ int     BuffSpellID[NUM_BUFF_SLOTS]; // 0xffffffff if no buff
/*0x6a8*/ DWORD   BuffTimer[NUM_BUFF_SLOTS];
/*0x82c*/ BYTE    Unknown0x6f8[0x24];
/*0x850*/ DWORD   Type;              // 1 = self, 4 = group member, 5 = PC, 7 = NPC
/*0x850*/ BYTE    Unknown0x720[0x2c];
/*0x87c*/
} CTARGETWND, *PCTARGETWND;

typedef struct _CLABELWND {
/*0x000*/ struct    _CXWND Wnd;
/*0x1c4*/ BYTE      Unknown[0x8];
/*0x1cc*/ DWORD     SidlPiece;
/*0x1d0*/
} CLABELWND, *PCLABELWND;

// size 0x92c8 20130417 - ieatacid
typedef struct _BAZAARSEARCHWND {
/*0x0000*/ struct _CSIDLWND     Wnd;
/*0x022c*/ BYTE                 Unknown0x22c[0x8ff8];
/*0x9224*/ void                 **ppTraderData;
/*0x9228*/ DWORD                hashVal;
/* more data */
} BAZAARSEARCHWND, *PBAZAARSEARCHWND;

};

using namespace EQUIStructs;

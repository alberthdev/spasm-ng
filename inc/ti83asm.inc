;
;       TI83 SYSTEM ROUTINE EQUATES
;
_CLRLCDFULL             equ     4755h
_clrScrnFull            equ     475Dh
_CLRTXTSHD              equ     4765h
_dispDone               equ     47F1h
_dispHL                 equ     4709h
_DISPOP1A               equ     51D4h
_eraseEOL               equ     476Dh
_formDCplx              equ     4D2Eh
_formReal               equ     4D32h
_GDISPTOKEN             equ     4B20h
_homeUp                 equ     4775h
_lcd_busy               equ     4066h
_moveup                 equ     474Dh
_newline                equ     473Dh
_outputExpr             equ     5106h
_putc                   equ     4705h
_putmap                 equ     4701h
_putps                  equ     4715h
_puts                   equ     470Dh
_runIndicOff            equ     4795h
_runIndicOn             equ     4791h
_scrollDown             equ     4751h
_scrollUp               equ     4745h
_setPenT                equ     51B9h
_setPenX                equ     51A7h
_setPenY                equ     51B0h
_SFONT_LEN              equ     4A6Ch
_VPUTBLANK              equ     4C53h
_vputmap                equ     477Dh
_vputs                  equ     4781h
_vputsn                 equ     4785h
_Axes                   equ     519Eh
_CLine                  equ     4A84h
_CPointS                equ     4B00h
_GRBUFCLR               equ     515Bh
_GRBUFCPY_V             equ     5164h
_HORIZCMD               equ     4BEFh
_ILINE                  equ     4AE4h
_IPOINT                 equ     4AE8h
_moveDown               equ     4741h
_PDspGrph               equ     4BEBh
_PUTXY                  equ     4BE4h
_REGRAPH                equ     4BCCh
_VERTCMD                equ     4BF3h
_GetK                   equ     4A18h
_getkey                 equ     4CFEh
_ADRLELE                equ     489Dh
_GETLTOOP1              equ     48A9h
_PUTTOL                 equ     48BDh
_ADRMELE                equ     486Dh
_GETMTOOP1              equ     487Dh
_PUTTOMAT               equ     4889h
_ACOS                   equ     4122h
_ACOSH                  equ     413Ah
_ANGLE                  equ     4152h
_ASIN                   equ     412Ah
_ASINH                  equ     4136h
_ATAN                   equ     4126h
_ATANH                  equ     4132h
_Ceiling                equ     4BE0h
_COS                    equ     40FAh
_COSH                   equ     410Ah
_CUBE                   equ     409Eh
_DTOR                   equ     4096h
_ETOX                   equ     40EAh
_FACTORIAL              equ     50C6h
_FPADD                  equ     4092h
_FPDIV                  equ     40C6h
_FPMULT                 equ     40AAh
_FPRECIP                equ     40C2h
_FPSQUARE               equ     40A6h
_FPSUB                  equ     408Eh
_FRAC                   equ     40BEh
_INT                    equ     40D6h
_INTGR                  equ     4076h
_INVOP1SC               equ     40B2h
_INVSUB                 equ     407Eh
_LNX                    equ     40DEh
_LOGX                   equ     40E2h
_MAX                    equ     406Eh
_MIN                    equ     406Ah
_MINUS1                 equ     408Ah
_PLUS1                  equ     4086h
_PTOR                   equ     413Eh
_RANDOM                 equ     50B6h
_RNDGUARD               equ     40CEh
_ROUND                  equ     40DAh
_RTOD                   equ     409Ah
_RTOP                   equ     4142h
_SIN                    equ     40F6h
_SINH                   equ     410Eh
_SQROOT                 equ     40CAh
_STORAND                equ     50BAh
_TAN                    equ     40FEh
_TANH                   equ     4106h
_TENX                   equ     40EEh
_TIMES2                 equ     4082h
_TIMESPT5               equ     40A2h
_TRUNC                  equ     407Ah
_XROOTY                 equ     4A8Ch
_YTOX                   equ     4A90h
_CHKFINDSYM             equ     442Ah
_DELVAR                 equ     44AAh
_RCLSYSTOK              equ     4EF0h
_RCLVARSYM              equ     4EECh
_RCLX                   equ     4EE8h
_RCLY                   equ     4EE0h
_RSTRSHADOW             equ     47A1h
_SAVESHADOW             equ     479Dh
_STOOTHER               equ     4ED8h
_STOSYSTOK              equ     4EB8h
_STOX                   equ     4ED4h
_STOY                   equ     4EC8h
_CKINT                  equ     4322h
_CKODD                  equ     4326h
_CKOP1FP0               equ     4312h
_CKOP1POS               equ     435Ah
_CKOP1REAL              equ     414Eh
_CKOP2FP0               equ     4316h
_CKOP2POS               equ     4356h
_CKOP2REAL              equ     4412h
_CKPOSINT               equ     431Eh
_CLROP1S                equ     4362h
_CLROP2S                equ     435Eh
_CONVOP1                equ     4EFCh
_cphlde                 equ     4004h
_CPOP1OP2               equ     4166h
_divHLbyA               equ     400Ch
_HTIMESL                equ     4382h
_INVOP1S                equ     40B6h
_INVOP2S                equ     40BAh
_ldHLind                equ     4000h
_MOVFROP1               equ     4212h
_OP1EXOP2               equ     4306h
_OP1EXOP3               equ     42FEh
_OP1EXOP4               equ     4302h
_OP1EXOP5               equ     42EEh
_OP1EXOP6               equ     42F2h
_OP1SET0                equ     4286h
_OP1SET1                equ     4232h
_OP1SET2                equ     4242h
_OP1SET3                equ     423Ah
_OP1SET4                equ     4236h
_OP1TOOP2               equ     418Eh
_OP1TOOP3               equ     417Eh
_OP1TOOP4               equ     416Eh
_OP1TOOP5               equ     41BEh
_OP1TOOP6               equ     41BAh
_OP2EXOP4               equ     42F6h
_OP2EXOP5               equ     42FAh
_OP2EXOP6               equ     42E6h
_OP2SET0                equ     4282h
_OP2SET1                equ     4252h
_OP2SET2                equ     4246h
_OP2SET3                equ     422Eh
_OP2SET4                equ     422Ah
_OP2SET5                equ     4222h
_OP2SET60               equ     4EA8h
_OP2SET8                equ     421Eh
_OP2SETA                equ     4226h
_OP2TOOP1               equ     41C2h
_OP2TOOP3               equ     41F6h
_OP2TOOP4               equ     4172h
_OP2TOOP5               equ     41B2h
_OP2TOOP6               equ     41B6h
_OP3SET0                equ     427Eh
_OP3SET1                equ     421Ah
_OP3SET2                equ     423Eh
_OP3TOOP1               equ     41A2h
_OP3TOOP2               equ     417Ah
_OP3TOOP4               equ     416Ah
_OP3TOOP5               equ     41AEh
_OP4SET0                equ     427Ah
_OP4SET1                equ     4216h
_OP4TOOP1               equ     419Ah
_OP4TOOP2               equ     4176h
_OP4TOOP3               equ     41FAh
_OP4TOOP5               equ     41AAh
_OP4TOOP6               equ     4202h
_OP5EXOP6               equ     42EAh
_OP5SET0                equ     4276h
_OP5TOOP1               equ     419Eh
_OP5TOOP2               equ     4182h
_OP5TOOP3               equ     41FEh
_OP5TOOP4               equ     418Ah
_OP5TOOP6               equ     4186h
_OP6TOOP1               equ     4196h
_OP6TOOP2               equ     4192h
_OP6TOOP5               equ     41A6h
_PUSHREALO1             equ     4536h
_SETXXOP1               equ     4A74h
_SETXXOP2               equ     4A78h
_SETXXXXOP2             equ     4A7Ch
_ZEROOOP1               equ     428Eh

;
;       OP1 TO OP6 RAM EQUATES
;
OP2         EQU                 8044h
op2exp      equ                 8045h
op2m        equ                 8046H
OP1M        EQU                 803Bh
OP1         EQU                 8039h
OP3         EQU                 804Fh
OP3EXP      EQU                 8050h
OP3EXT      EQU                 8058h
OP3M        EQU                 8051h
OP4         EQU                 805Ah
OP4EXP      EQU                 805Bh
OP4EXT      EQU                 8063h
OP4M        EQU                 805Ch
OP5         EQU                 8065h
OP5EXP      EQU                 8066h
OP5EXT      EQU                 806Eh
OP5M        EQU                 8067h
OP6         EQU                 8070h
OP6EXP      EQU                 8071h
OP6EXT      EQU                 8079h
OP6M        EQU                 8072h
;
;       POINTERS
;
IMATHPTR1   EQU                 8094h
IMATHPTR2   EQU                 8096h
IMATHPTR3   EQU                 8098h
IMATHPTR4   EQU                 809Ah
IMATHPTR5   EQU                 809Ch
;
;       POIONTER TO START OF PROGRAM/LIST SYMBOL ENTRIES
;
PROGPTR     EQU                 9319h
;
;       ADDRESS OF LCD DRIVER INSTRUCTION PORT
;
LCDINSTPORT  EQU                10h
;
;       SCREEN SHADOWS
;
TEXTSHADOW  EQU                 80C9h
CMDSHADOW   EQU                 9157h
;
;       GRAPH BACKUP BUFFER
;
PLOTSSCREEN EQU                 8E29h
;
;       SAFE RAM LOCATIONS
;
SAVESSCREEN EQU                 8265h
STATVARS    EQU                 858Fh
;
;       START OF SYMBOL TABLE
;
SYMTABLE    EQU                 0FE6Eh
;
;       RAM EQUATES DEALING WITH DISPLAY ROUTINES
;
CURROW      EQU                 800Ch
CURCOL      EQU                 800Dh
PENCOL      EQU                 8252h
PENROW      EQU                 8253h
CURGY       EQU                 886Dh
CURGX       EQU                 886Eh
;
;       INDIRECT CALL BYTE
;
ASM_IND_CALL    EQU             80C8h
;
;       LINK PORT WRITE EQUATES
;
D0LD1L      EQU              0C3h
D0LD1H      EQU              0C1h
D0HD1L      EQU              0C2h
D0HD1H      EQU              0C0h
BPORT       EQU              0
;
;       SYSTEM FLAG EQUATES
;       ALL OF THESE FLAGS CAN BE ACCESSED THROUGH THE 'IY' REGISTER
;
trigflags       EQU       0           ; IY OFFSET VALUE
trigdeg         EQU       2
;
plotflags       EQU       2           ; IY OFFSET VALUE
plotloc         EQU       1
plotdisp        EQU       2
;
grfmodeflags    EQU       2           ; IY OFFSET VALUE
grffuncm        EQU       4
grfpolarm       EQU       5
grfparamm       EQU       6
grfrecurm       EQU       7
;
graphflags      EQU       3           ; IY OFFSET VALUE
graphdraw       EQU       0
graphcursor     EQU       2
;
grfdbflags      EQU       4           ; IY OFFSET VALUE
grfdot          EQU       0
grfsimul        EQU       1
grfgrid         EQU       2
grfpolar        EQU       3
grfnocoord      EQU       4
grfnoaxis       EQU       5
grflabel        EQU       6
;
textflags       EQU       5           ; IY OFFSET VALUE
textEraseBelow  EQU       1
textScrolled    EQU       2
textInverse     EQU       3
;
onflags         EQU       9           ; IY OFFSET VALUE
onRunning       EQU       3
onInterrupt     EQU       4
;
statflags       EQU       9           ; IY OFFSET VALUE
statsvalid      EQU       6
;
fmtflags        EQU       10          ; IY OFFSET VALUE
fmtExponent     EQU       0
fmtEng          EQU       1
;
nummode         EQU       10          ; IY OFFSET VALUE
FMTREAL         EQU       5
FMTRECT         EQU       6
FMTPOLAR        EQU       7
;
curflags        EQU       12          ; IY OFFSET VALUE
curAble         EQU       2
curOn           EQU       3
curLock         EQU       4
;
appflags        EQU       13          ; IY OFFSET VALUE
appTextSave     EQU       1
appAutoScroll   EQU       2
;
PLOTFLAG2       EQU       17          ; IY OFFSET VALUE
EXPR_PARAM      EQU       3
EXPR_WRITING    EQU       4
;
indicflags      EQU       18          ; IY OFFSET VALUE
indicRun        EQU       0
indicOnly       EQU       2
;
shiftflags      EQU       18          ; IY OFFSET VALUE
shift2nd        EQU       3
shiftAlpha      EQU       4
shiftALock      EQU       6
;
tblflags        EQU       19          ; IY OFFSET VALUE
AutoFill        EQU       4
AutoCalc        EQU       5
;
sgrflags        EQU       20          ; IY OFFSET VALUE
grfSplit        EQU       0
VertSplit       EQU       1
WRITE_ON_GRAPH  EQU       4
textwrite       EQU       7
;
asm_flag1       EQU       33          ; IY OFFSET VALUE
asm_flag1_0     EQU       0
asm_flag1_1     EQU       1
asm_flag1_2     EQU       2
asm_flag1_3     EQU       3
asm_flag1_4     EQU       4
asm_flag1_5     EQU       5
asm_flag1_6     EQU       6
asm_flag1_7     EQU       7
;
asm_flag2       EQU       34          ; IY OFFSET VALUE
asm_flag2_0     EQU       0
asm_flag2_1     EQU       1
asm_flag2_2     EQU       2
asm_flag2_3     EQU       3
asm_flag2_4     EQU       4
asm_flag2_5     EQU       5
asm_flag2_6     EQU       6
asm_flag2_7     EQU       7
;
asm_flag3       EQU       35          ; IY OFFSET VALUE
asm_flag3_0     EQU       0
asm_flag3_1     EQU       1
asm_flag3_2     EQU       2
asm_flag3_3     EQU       3
asm_flag3_4     EQU       4
asm_flag3_5     EQU       5
asm_flag3_6     EQU       6
asm_flag3_7     EQU       7
;
;       SYSTEM VAR EQUATES, FOR STORING AND RECALLING THEM
;
XSCLt       EQU  2        ; XSCALE
YSCLt       EQU  3        ; YSCALE
XMINt       EQU  0AH      ; XMIN
XMAXt       EQU  0BH      ; XMAX
YMINt       EQU  0CH      ; YMIN
YMAXt       EQU  0DH      ; XMAX
TMINt       EQU  0EH      ; TMIN
TMAXt       EQU  0FH      ; TMAX
THETMINt    EQU  10H      ; THETA MIN
THETMAXt    EQU  11H      ; THETA MAX
TBLMINt     EQU  1AH      ; TABLE MIN
PLOTSTARTt  EQU  1BH      ; PLOT START
NMAXt       EQU  1DH      ; NMAX
nmint       EQU  1FH      ; NMIN
TBLSTEPt    EQU  21H      ; TABLE STEP
TSTEPt      EQU  22H      ; T STEP
THETSTEPt   EQU  23H      ; THETA STEP
DELTAXt     EQU  26H      ; DELTA X
DELTAYt     EQU  27H      ; DELTA Y
XFACTt      EQU  28H      ; X ZOOM FACTOR
YFACTt      EQU  29H      ; Y ZOOM FACTOR
FINnT       EQU  2Bh      ; TVM n
FINiT       EQU  2Ch      ; TVM i
FINpvT      EQU  2Dh      ; TVM pv
FINpmtT     EQU  2Eh      ; TVM pmt
FINfvT      EQU  2Fh      ; TVM fv
FINpyT      EQU  30h      ; TVM p/y
FINcyT      EQU  31h      ; TVM c/y
PLOTSTEPT   EQU  34h      ; PLOT STEP
XREST       EQU  36h      ; X RES

















;
;       CHARACTER FONT EQUATES
;
LSEQ_N          equ     001h
LSEQ_U          equ     002h
LSEQ_V          equ     003h
LSEQ_W          equ     004h
Lconvert        equ     005h
LsqUp           equ     006h
LsqDown         equ     007h
Lintegral       equ     008h
Lcross          equ     009h
LBOXICON        equ     00Ah
LCROSSICON      equ     00Bh
LDOTICON        equ     00Ch
LsubT           equ     00Dh            ;small capital T for parametric mode.
LcubeR          equ     00Eh            ;slightly different 3 for cubed root.
LhexF           equ     00Fh
Lroot           equ     010h
Linverse        equ     011h
Lsquare         equ     012h
Langle          equ     013h
Ldegree         equ     014h
Lradian         equ     015h
Ltranspose      equ     016h
LLE             equ     017h
LNE             equ     018h
LGE             equ     019h
Lneg            equ     01Ah
Lexponent       equ     01Bh
Lstore          equ     01Ch
Lten            equ     01Dh
LupArrow        equ     01Eh
LdownArrow      equ     01Fh
Lspace          equ     020h
Lexclam         equ     021h
Lquote          equ     022h
Lpound          equ     023h
LFOURTH         equ     024h
Lpercent        equ     025h
Lampersand      equ     026h
Lapostrophe     equ     027h
LlParen         equ     028h
LrParen         equ     029h
Lasterisk       equ     02Ah
LplusSign       equ     02Bh
Lcomma          equ     02Ch
Ldash           equ     02Dh
Lperiod         equ     02Eh
Lslash          equ     02Fh
L0              equ     030h
L1              equ     031h
L2              equ     032h
L3              equ     033h
L4              equ     034h
L5              equ     035h
L6              equ     036h
L7              equ     037h
L8              equ     038h
L9              equ     039h
Lcolon          equ     03Ah
Lsemicolon      equ     03Bh
LLT             equ     03Ch
LEQ             equ     03Dh
LGT             equ     03Eh
Lquestion       equ     03Fh
LatSign         equ     040h
LcapA           equ     041h
LcapB           equ     042h
LcapC           equ     043h
LcapD           equ     044h
LcapE           equ     045h
LcapF           equ     046h
LcapG           equ     047h
LcapH           equ     048h
LcapI           equ     049h
LcapJ           equ     04Ah
LcapK           equ     04Bh
LcapL           equ     04Ch
LcapM           equ     04Dh
LcapN           equ     04Eh
LcapO           equ     04Fh
LcapP           equ     050h
LcapQ           equ     051h
LcapR           equ     052h
LcapS           equ     053h
LcapT           equ     054h
LcapU           equ     055h
LcapV           equ     056h
LcapW           equ     057h
LcapX           equ     058h
LcapY           equ     059h
LcapZ           equ     05Ah
Ltheta          equ     05Bh
Lbackslash      equ     05Ch
LrBrack         equ     05Dh
Lcaret          equ     05Eh
Lunderscore     equ     05Fh
Lbackquote      equ     060h
La              equ     061h
Lb              equ     062h
Lc              equ     063h
Ld              equ     064h
Le              equ     065h
Lf              equ     066h
Lg              equ     067h
Lh              equ     068h
Li              equ     069h
Lj              equ     06Ah
Lk              equ     06Bh
Ll              equ     06Ch
Lm              equ     06Dh
Ln              equ     06Eh
Lo              equ     06Fh
Lp              equ     070h
Lq              equ     071h
Lr              equ     072h
Ls              equ     073h
Lt              equ     074h
Lu              equ     075h
Lv              equ     076h
Lw              equ     077h
Lx              equ     078h
Ly              equ     079h
Lz              equ     07Ah
LlBrace         equ     07Bh
Lbar            equ     07Ch
LrBrace         equ     07Dh
Ltilde          equ     07Eh
LinvEQ          equ     07Fh
Lsub0           equ     080h
Lsub1           equ     081h
Lsub2           equ     082h
Lsub3           equ     083h
Lsub4           equ     084h
Lsub5           equ     085h
Lsub6           equ     086h
Lsub7           equ     087h
Lsub8           equ     088h
Lsub9           equ     089h
LcapAAcute      equ     08Ah
LcapAGrave      equ     08Bh
LcapACaret      equ     08Ch
LcapADier       equ     08Dh
LaAcute         equ     08Eh
LaGrave         equ     08Fh
LaCaret         equ     090h
LaDier          equ     091h
LcapEAcute      equ     092h
LcapEGrave      equ     093h
LcapECaret      equ     094h
LcapEDier       equ     095h
LeAcute         equ     096h
LeGrave         equ     097h
LeCaret         equ     098h
LeDier          equ     099h
LcapIAcute      equ     09Ah
LcapIGrave      equ     09Bh
LcapICaret      equ     09Ch
LcapIDier       equ     09Dh
LiAcute         equ     09Eh
LiGrave         equ     09Fh
LiCaret         equ     0A0h
LiDier          equ     0A1h
LcapOAcute      equ     0A2h
LcapOGrave      equ     0A3h
LcapOCaret      equ     0A4h
LcapODier       equ     0A5h
LoAcute         equ     0A6h
LoGrave         equ     0A7h
LoCaret         equ     0A8h
LoDier          equ     0A9h
LcapUAcute      equ     0AAh
LcapUGrave      equ     0ABh
LcapUCaret      equ     0ACh
LcapUDier       equ     0ADh
LuAcute         equ     0AEh
LuGrave         equ     0AFh
LuCaret         equ     0B0h
LuDier          equ     0B1h
LcapCCed        equ     0B2h
LcCed           equ     0B3h
LcapNTilde      equ     0B4h
LnTilde         equ     0B5h
Laccent         equ     0B6h
Lgrave          equ     0B7h
Ldieresis       equ     0B8h
LquesDown       equ     0B9h
LexclamDown     equ     0BAh
Lalpha          equ     0BBh
Lbeta           equ     0BCh
Lgamma          equ     0BDh
LcapDelta       equ     0BEh
Ldelta          equ     0BFh
Lepsilon        equ     0C0h
LlBrack         equ     0C1h
Llambda         equ     0C2h
Lmu             equ     0C3h
Lpi             equ     0C4h
Lrho            equ     0C5h
LcapSigma       equ     0C6h
Lsigma          equ     0C7h
Ltau            equ     0C8h
Lphi            equ     0C9h
LcapOmega       equ     0CAh
LxMean          equ     0CBh
LyMean          equ     0CCh
LsupX           equ     0CDh
Lellipsis       equ     0CEh
Lleft           equ     0CFh
Lblock          equ     0D0h
Lper            equ     0D1h
Lhyphen         equ     0D2h
Larea           equ     0D3h
Ltemp           equ     0D4h
Lcube           equ     0D5h
Lenter          equ     0D6h
LimagI          equ     0D7h
Lphat           equ     0D8h
Lchi            equ     0D9h
LstatF          equ     0DAh
Llne            equ     0DBh
LlistL          equ     0DCh
LfinanN         equ     0DDh

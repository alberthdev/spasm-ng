.NOLIST
;                                             length (+80h for leading blank)
;       # TOKENS IN USE = 249
;						     (+40h for trailing blank)
EOSSTART        EQU       0
;
;
;   DISPLAY CONVERSIONS  COME IMMEDIATELY BEFORE 'TSTORE'
;
DCONV   EQU     01H
;
TTODMS          equ       DCONV       ; 01H
TTODEC          equ       DCONV+1     ; 02H
TTOAbc          EQU       DCONV+2     ; 03H    > A b/c
;
TSTORE          equ       DCONV+3     ; 04H Lstore                01
;
TBOXPLOT        EQU       05h
;
BRACKS          EQU       06H
;
tLBrack         equ       BRACKS      ; 06h '['
tRBrack         equ       BRACKS+1    ; 07h ']'
tLBrace         equ       BRACKS+2    ; 08h '{'
tRBrace         equ       BRACKS+3    ; 09h '}'
;
TPOST1          EQU       BRACKS+4
;
tFromRad        equ       TPOST1       ; 0Ah Lradian
tFromDeg        equ       TPOST1+1     ; 0Bh Ldegree
tRecip          equ       TPOST1+2     ; 0Ch Linverse
tSqr            equ       TPOST1+3     ; 0Dh Lsquare
tTrnspos        equ       TPOST1+4     ; 0Eh Ltranspose
TCUBE           EQU       TPOST1+5     ; 0Fh '^3'
;
tLParen         equ       10H         ; 10h '('
tRParen         equ       11H         ; 11h ')'
;
;
;   IMMEDIATE UNARY TOKENS GO FROM HERE TO 'EOSEL-1'
;
IMUN            EQU       12H
;
tRound          equ       IMUN        ; 12h 'round'
TPXTST          equ       IMUN+1      ; 13h 'PXL-TEST'
tAug            equ       IMUN+2      ; 14h 'aug'
tRowSwap        EQU       IMUN+3      ; 15h 'rSwap'
tRowPlus        equ       IMUN+4      ; 16h 'rAdd'
tmRow           EQU       IMUN+5      ; 17h 'multR'
tmRowPlus       EQU       IMUN+6      ; 18h 'mRAdd'
tMax            equ       IMUN+7      ; 19H 'max'
tMin            equ       IMUN+8      ; 1AH 'min'
TRTOPr          EQU       IMUN+9      ; 1BH 'R>Pr
TRTOPo          EQU       IMUN+10     ; 1CH 'R>Po
TPTORx          EQU       IMUN+11     ; 1DH 'P>Rx
TPTORy          EQU       IMUN+12     ; 1EH 'P>Ry
tMEDIAN         equ       IMUN+13     ; 1Fh 'MEDIAN
tRandM          equ       IMUN+14     ; 20h 'randM'
TMEAN           EQU       IMUN+15     ; 21h
TROOT           EQU       IMUN+16     ; 22h 'ROOT'
tSeries         equ       IMUN+17     ; 23h 'seq'
tFnInt          equ       IMUN+18     ; 24h 'fnInt'
tNDeriv         equ       IMUN+19     ; 25h 'fnIr'
TEVALF          EQU       IMUN+20     ; 26h
TFMIN           EQU       IMUN+21     ; 27h
TFMAX           EQU       IMUN+22     ; 28h
;
;
;
;  TOKEN 29H CANNOT BE AN EOS FUNCTION SINCE EL(=29H ALREADY
;
tEOSEL          EQU       IMUN+23
;
TSPACE          EQU       tEOSEL       ; 29h   ' '
tString         equ       tEOSEL+1     ; 2Ah  '"'
tComma          equ       tEOSEL+2     ; 2Bh  ','
;
;
;
Tii             equ       2Ch         ; i
;
; ===== Postfix functions
;
TPOST           EQU       2Dh
;
tFact           equ       TPOST       ; 2Dh '!'



TCUBICR         EQU       2Eh
TQUARTR         EQU       2Fh

;
;       NUMBER TOKENS
;
NUMS            EQU       30h
;
T0              EQU       NUMS        ; 30h
T1              EQU       NUMS+1      ; 31h
T2              EQU       NUMS+2      ; 32h
T3              EQU       NUMS+3      ; 33h
T4              EQU       NUMS+4      ; 34h
T5              EQU       NUMS+5      ; 35h
T6              EQU       NUMS+6      ; 36h
T7              EQU       NUMS+7      ; 37h
T8              EQU       NUMS+8      ; 38h
T9              EQU       NUMS+9      ; 39h
TDECPT          EQU       NUMS+10     ; 3Ah
Tee             EQU       NUMS+11     ; 3Bh
;
;   BINARY OP
;
tOr             equ       3Ch         ; 3Ch  '_or_'
TXOR            equ       3Dh         ; 3Dh
;
tColon          equ       3Eh         ; 3Eh ':'
tEnter          equ       3Fh         ; 3Fh  Lenter
;
;   BINARY OP
;
tAnd            equ       40h         ; 40h  '_and_'               05
;
;       LETTER TOKENS
;
LET             EQU       41h
;
TA              EQU       LET         ; 41h
TB              EQU       LET+1       ; 42h
TC              EQU       LET+2       ; 43h
TD              EQU       LET+3       ; 44h
TE              EQU       LET+4       ; 45h
TF              EQU       LET+5       ; 46h
TG              EQU       LET+6       ; 47h
TH              EQU       LET+7       ; 48h
TI              EQU       LET+8       ; 49h
TJ              EQU       LET+9       ; 4Ah
TK              EQU       LET+10      ; 4Bh
TL              EQU       LET+11      ; 4Ch
TM              EQU       LET+12      ; 4Dh
TN              EQU       LET+13      ; 4Eh
TO              EQU       LET+14      ; 4Fh
TP              EQU       LET+15      ; 50h
TQ              EQU       LET+16      ; 51h
TR              EQU       LET+17      ; 52h
TS              EQU       LET+18      ; 53h
TT              EQU       LET+19      ; 54h
TU              EQU       LET+20      ; 55h
TV              EQU       LET+21      ; 56h
TW              EQU       LET+22      ; 57h
TX              EQU       LET+23      ; 58h
TY              EQU       LET+24      ; 59h
TZ              EQU       LET+25      ; 5Ah
TTHETA          EQU       LET+26      ; 5Bh
;
;
;   THESE VAR TOKENS ARE 1ST OF A DOUBLE TOKEN
;
;   SEE 'VARS.DOC' FOR MORE INFO ON VARS
;
VTOKS   EQU     LET+27    ;
;
;       USER MATRIX TOKEN, 2ND TOKEN NEEDED FOR NAME
;
TVARMAT         EQU       VTOKS       ; 5Ch
;
;       USER LIST TOKEN, 2ND TOKEN NEEDED FOR NAME
;
TVARLST         EQU       VTOKS+1     ; 5Dh
;
;       USER EQUATION TOKEN, 2ND TOKEN NEEDED FOR NAME
;
TVAREQU         EQU       VTOKS+2     ; 5Eh
;
;       THIS IS A SINGLE TOKEN, I WILL HAVE TO READ THE NAME IN
;       EVERY SINGLE TIME I EXECUTE
;
TPROG           EQU       VTOKS+3     ; 5Fh
;
;       USER PICT TOKEN, 2ND TOKEN NEEDED FOR NAME
;
TVARPICT        EQU       VTOKS+4     ; 60h
;
;       USER GDB TOKEN, 2ND TOKEN NEEDED FOR NAME
;
TVARGDB         EQU       VTOKS+5     ; 61h
;
;       SYSTEM VARS THAT ARE USED FOR OUTPUT ONLY
;       CANNOT BE STORED TO BY THE USER
;
tVarOut         equ       VTOKS+6     ; 62h
;
;       SYSTEM VARS THAT ARE NOT IN THE SYMBOL TABLE
;       BUT THE USER CAN STORE TO THEM.
;
tVarSys         equ       VTOKS+7     ; 63h
;
;
; ===== Mode setting commands
;
MODESA          EQU       VTOKS+8     ; 64h
;
tRad            equ       MODESA      ; 64h 'Radian'
tDeg            equ       MODESA+1    ; 65h 'Degree'
tNormF          equ       MODESA+2    ; 66h 'Normal'
tSci            equ       MODESA+3    ; 67h 'Sci'
tEng            equ       MODESA+4    ; 68h 'Eng'
tFloat          equ       MODESA+5    ; 69h 'Float'
;
CMPS            EQU       6Ah
;
tEQ             equ       CMPS        ; 6Ah '=='
tLT             equ       CMPS+1      ; 6Bh '<'
tGT             equ       CMPS+2      ; 6Ch '>'
tLE             equ       CMPS+3      ; 6Dh LLE
tGE             equ       CMPS+4      ; 6Eh LGE
tNE             equ       CMPS+5      ; 6Fh LNE
;
;   BINARY OP
;
tAdd            equ       70h         ; 70h '+'
tSub            equ       71h         ; 71h '-'
;
TANS            EQU       72H         ; 72h
;
; ===== Mode setting commands
;
MODES           EQU       73h
;
tFix            equ       MODES       ; 73h 'Fix_'
TSPLITON        equ       MODES+1     ; 74h
TFULLSCREEN     EQU       MODES+2     ; 75h
tStndrd         EQU       MODES+3     ; 76h 'Func'
tParam          equ       MODES+4     ; 77h 'Param'
tPolar          EQU       MODES+5     ; 78h 'Pol'
TSEQG           equ       MODES+6     ; 79h
TAFILLON        equ       MODES+7     ; 7Ah 'AUTO FILL ON
TAFILLOFF       equ       MODES+8     ; 7Bh
TACALCON        EQU       MODES+9     ; 7Ch
TACALCOFF       equ       MODES+10    ; 7Dh 'AUTOFILL OFF
;
;
;       GRAPH FORMAT TOKENS ARE 2 BYTE TOKENS
;
TGFORMAT        EQU       MODES+11    ; 7Eh
;
TBOXICON        equ       7Fh
TCROSSICON      EQU       80h
TDOTICON        EQU       81h
;
;       BINARY OP
;
tMul            equ       82h         ; 82h  '*'
tDiv            equ       83h         ; 83h  '/'
;
;       SOME GRAPH COMMANDS
;
GRCMDS          EQU       84h
;
tTrace          equ       GRCMDS      ; 84h 'Trace'
tClDrw          equ       GRCMDS+1    ; 85h 'ClDrw'
tZoomStd        equ       GRCMDS+2    ; 86h 'ZStd'
tZoomtrg        equ       GRCMDS+3    ; 87h 'Ztrg'
tZOOMBOX        EQU       GRCMDS+4    ; 88h 'ZBOX'
tZoomIn         equ       GRCMDS+5    ; 89h 'ZIn'
tZoomOut        equ       GRCMDS+6    ; 8Ah 'ZOut'
tZoomSqr        equ       GRCMDS+7    ; 8Bh 'ZSqr'
tZoomInt        equ       GRCMDS+8    ; 8Ch 'ZInt'
tZoomPrev       equ       GRCMDS+9    ; 8Dh 'ZPrev'
tZoomDec        equ       GRCMDS+10   ; 8Eh 'ZDecm'
TZOOMSTAT       EQU       GRCMDS+11   ; 8Fh 'ZSTAT
tUsrZm          equ       GRCMDS+12   ; 90h 'ZRcl'
tPrtScrn        equ       GRCMDS+13   ; 91h 'PrtScrn'
tZOOMSTO        EQU       GRCMDS+14   ; 92H  ZOOM STORE
TTEXT           EQU       GRCMDS+15   ; 93h
;
;       BINARY OP
;
tnPr            equ       GRCMDS+16   ; 94h '_nPr_'
tnCr            equ       GRCMDS+17   ; 95h '_nCr_'
;
;       MORE GRAPH COMMANDS
;
tYOn            equ       GRCMDS+18   ; 96h 'FnOn_'
tYOff           equ       GRCMDS+19   ; 97h 'FnOff_'
tStPic          equ       GRCMDS+20   ; 98h 'StPic_'
tRcPic          equ       GRCMDS+21   ; 99h 'RcPic_'
tStoDB          equ       GRCMDS+22   ; 9Ah 'StGDB_'
tRclDB          equ       GRCMDS+23   ; 9Bh 'RcGDB_'
tLine           equ       GRCMDS+24   ; 9Ch 'Line'
tVert           equ       GRCMDS+25   ; 9Dh 'Vert_'
tPtOn           equ       GRCMDS+26   ; 9Eh 'PtOn'
tPtOff          equ       GRCMDS+27   ; 9Fh 'PtOff'
;
;  TOKEN A0 CANNOT BE AN EOS FUNCTION SINCE LOW MULT=A0 ALREADY
;
tPtChg          equ       GRCMDS+28   ; A0h 'PtChg'
TPXON           EQU       GRCMDS+29   ; A1h
TPXOFF          EQU       GRCMDS+30   ; A2h
TPXCHG          EQU       GRCMDS+31   ; A3h
tShade          equ       GRCMDS+32   ; A4h 'Shade'
tCircl          equ       GRCMDS+33   ; A5h 'Circl'
tHORZ           equ       GRCMDS+34   ; A6h 'HORIZONTAL'
tTanLn          equ       GRCMDS+35   ; A7h 'TanLn'
tDrInv          equ       GRCMDS+36   ; A8h 'DrInv_'
tDrawF          equ       GRCMDS+37   ; A9h 'DrawF_'
;
TVARSTRNG       EQU       0AAh
;
; ===== Functions with no arguments
;
NOARG   EQU     0ABh
;
tRand           equ       NOARG       ; ABh 'rand'
tPi             equ       NOARG+1     ; ACh  Lpi
tGetKey         equ       NOARG+2     ; ADh 'getKy'
;
;
TAPOST          EQU       TGETKEY+1   ; APOSTROPHY
TQUEST          EQU       TAPOST+1    ; QUESTION MARK
;
;
; ===== Unary functions
;
;       UNARY : THESE UNARY FUNCTIONS TAKE A COMBINATION OF
;               ARGUMENTS, REAL,LIST,MATRIX
;
UNARY   EQU     TQUEST+1              ; B0h
;
tChs            equ       UNARY       ; B0h
tInt            equ       UNARY+1     ; B1h
TABS            equ       UNARY+2     ; B2h
tDet            equ       UNARY+3     ; B3h
tIdent          equ       UNARY+4     ; B4h
tDim            equ       UNARY+5     ; B5h
tSum            equ       UNARY+6     ; B6h
tProd           equ       UNARY+7     ; B7h
tNot            equ       UNARY+8     ; B8h
tIPart          equ       UNARY+9     ; B9h
tFPart          equ       UNARY+10    ; BAh
;
;
;       NEW 2 BYTE TOKENS
;
T2BYTETOK       EQU       0BBh         ;
;
;
;       UNARYLR : UNARY FUNCTIONS THAT ONLY WORK WITH
;                 REAL NUMBERS AND LISTS
;
UNARYLR EQU     UNARY+12
;
tSqrt           equ       UNARYLR     ; BCh
TCUBRT          equ       UNARYLR+1   ; BDh
tLn             equ       UNARYLR+2   ; BEh
tExp            equ       UNARYLR+3   ; BFh
tLog            equ       UNARYLR+4   ; C0h
tALog           equ       UNARYLR+5   ; C1h
tSin            equ       UNARYLR+6   ; C2h
tASin           equ       UNARYLR+7   ; C3h
tCos            equ       UNARYLR+8   ; C4h
tACos           equ       UNARYLR+9   ; C5h
tTan            equ       UNARYLR+10  ; C6h
tATan           equ       UNARYLR+11  ; C7h
tSinh           equ       UNARYLR+12  ; C8h
tASinh          equ       UNARYLR+13  ; C9h
tCosh           equ       UNARYLR+14  ; CAh
tACosh          equ       UNARYLR+15  ; CBh
tTanh           equ       UNARYLR+16  ; CCh
tATanh          equ       UNARYLR+17  ; CDh
;
;       SOME PROGRAMMING COMMANDS
;
PROGTOK EQU     UNARYLR+18
;
tIf             equ       PROGTOK     ; CEh
tThen           equ       PROGTOK+1   ; CFh
tElse           equ       PROGTOK+2   ; D0h
tWhile          equ       PROGTOK+3   ; D1h
tRepeat         equ       PROGTOK+4   ; D2h
tFor            equ       PROGTOK+5   ; D3h
tEnd            equ       PROGTOK+6   ; D4h
tReturn         equ       PROGTOK+7   ; D5h
tLbl            equ       PROGTOK+8   ; D6h   'Lbl_'
tGoto           equ       PROGTOK+9   ; D7h   'Goto_'
tPause          equ       PROGTOK+10  ; D8h   'Pause_'
tStop           equ       PROGTOK+11  ; D9h   'Stop'
tISG            equ       PROGTOK+12  ; DAh   'IS>'
tDSL            equ       PROGTOK+13  ; DBh   'DS<'
tInput          equ       PROGTOK+14  ; DCh   'Input_'
tPrompt         equ       PROGTOK+15  ; DDh   'Prompt_'
tDisp           equ       PROGTOK+16  ; DEh   'Disp_'
tDispG          equ       PROGTOK+17  ; DFh   'DispG'
;
;  TOKEN E0 CANNOT BE AN EOS FUNCTION SINCE HI MU
;
tOutput         equ       PROGTOK+18  ; E0H    'Outpt'
tClLCD          equ       PROGTOK+19  ; E1H    'ClLCD'
tConst          equ       PROGTOK+20  ; E2H    'Fill'
tSortA          equ       PROGTOK+21  ; E3H    'sortA_'
tSortD          equ       PROGTOK+22  ; E4H    'sortD_'
TDISPTAB        EQU       PROGTOK+23  ; E5h    'DISP TABLE
tMenu           equ       PROGTOK+24  ; E6H    'Menu'
tSENDMBL        EQU       PROGTOK+25  ; E7H    'SEND'
tGETMBL         EQU       PROGTOK+26  ; E8H    'GET'
;
;       STAT PLOT COMMANDS
;
STATPCMD        EQU       PROGTOK+27
;
TPLOTON         EQU       STATPCMD    ; E9h     ' PLOTSON'
TPLOTOFF        EQU       STATPCMD+1   ; EAh     ' PLOTSOFF
;
TLISTNAME       EQU       0EBH        ; LIST DESIGNATOR
;
;
;
TPLOT1          EQU       0ECH
TPLOT2          EQU       0EDH
TPLOT3          EQU       0EEH
;
tPower          equ       0F0h        ;        '^'
tXRoot          equ       0F1h        ;        LsupX,Lroot

STATCMD         EQU       0F2h
;
tOneVar         equ       STATCMD     ; F2h    'OneVar_'
TTWOVAR         EQU       STATCMD+1   ; F3h
tLR             equ       STATCMD+2   ; F4h    'LinR(A+BX
tLRExp          equ       STATCMD+3   ; F5h    'ExpR_'
tLRLn           equ       STATCMD+4   ; F6h    'LnR_'
tLRPwr          equ       STATCMD+5   ; F7h    'PwrR_'
TMEDMED         EQU       STATCMD+6   ; F8h
TQUAD           EQU       STATCMD+7   ; F9h
tCLRLST         equ       STATCMD+8   ; FAh    'CLEAR LIST
TCLRTBL         EQU       STATCMD+9   ; FBH    CLEAR TABLE
tHist           equ       STATCMD+10  ; FCh    'Hist_'
txyLine         equ       STATCMD+11  ; FDH    'xyline_'
tScatter        equ       STATCMD+12  ; FEh    'Scatter_'
tLR1            equ       STATCMD+13  ; FFh    'LINR(AX+B
;
; 2ND HALF OF GRAPH FORMAT TOKENS
;
; ===== Format settings commands
;
GFMT            EQU       0
;
tSeq            equ       GFMT        ; 'SeqG'
tSimulG         equ       GFMT+1      ; 'SimulG'
tPolarG         equ       GFMT+2      ; 'PolarGC'
tRectG          equ       GFMT+3      ; 'RectGC'
tCoordOn        equ       GFMT+4      ; 'CoordOn'
tCoordOff       equ       GFMT+5      ; 'CoordOff'
tDrawLine       equ       GFMT+6      ; 'DrawLine'
tDrawDot        equ       GFMT+7      ; 'DrawDot'
tAxisOn         equ       GFMT+8      ; 'AxesOn'
tAxisOff        equ       GFMT+9      ; 'AxesOff'
tGridOn         equ       GFMT+10     ; 'GridOn'
tGridOff        equ       GFMT+11     ; 'GridOff'
tLblOn          equ       GFMT+12     ; 'LabelOn'
tLblOff         equ       GFMT+13     ; 'LabelOff'
tWebOn          equ       GFMT+14     ; 'WebOn'
tWebOff         equ       GFMT+15     ; 'WebOFF'
TUV             EQU       GFMT+16     ; U vs V
TVW             EQU       GFMT+17     ; V vs W
TUW             EQU       GFMT+18     ; U vs W
;
;       2ND HALF OF USER MATRIX TOKENS
;
TMATA           EQU       00h         ; MAT A
TMATB           EQU       01h         ; MAT B
TMATC           EQU       02h         ; MAT C
TMATD           EQU       03h         ; MAT D
TMATE           EQU       04h         ; MAT E
TMATF           EQU       05h         ; MAT F
TMATG           EQU       06h         ; MAT G
TMATH           EQU       07h         ; MAT H
TMATI           EQU       08h         ; MAT I
TMATJ           EQU       09h         ; MAT J
;
;       2ND HALF OF USER LIST TOKENS
;
TL1             EQU       00h         ; LIST 1
TL2             EQU       01h         ; LIST 2
TL3             EQU       02h         ; LIST 3
TL4             EQU       03h         ; LIST 4
TL5             EQU       04h         ; LIST 5
TL6             EQU       05h         ; LIST 6
;
;       2ND HALF OF USER EQUATION TOKENS
;
;
;       "Y" EQUATIONS HAVE BIT 4 SET
;
TY1             EQU       10h         ; Y1
TY2             EQU       11h         ; Y2
TY3             EQU       12h         ; Y3
TY4             EQU       13h         ; Y4
TY5             EQU       14h         ; Y5
TY6             EQU       15h         ; Y6
TY7             EQU       16h         ; Y7
TY8             EQU       17h         ; Y8
TY9             EQU       18h         ; Y9
TY0             EQU       19H         ; Y0
;
;       PARAM EQUATIONS HAVE BIT 5 SET
;
TX1T            EQU       20h         ; X1t
TY1T            EQU       21h         ; Y1t
TX2T            EQU       22h         ; X2t
TY2T            EQU       23h         ; Y2t
TX3T            EQU       24h         ; X3t
TY3T            EQU       25h         ; Y3t
TX4T            EQU       26h         ; X4t
TY4T            EQU       27h         ; Y4t
TX5T            EQU       28h         ; X5t
TY5T            EQU       29h         ; Y5t
TX6T            EQU       2Ah         ; X6t
TY6T            EQU       2Bh         ; Y6t
;
;       POLAR EQUATIONS HAVE BIT 6 SET
;
TR1             EQU       40h         ; R1
TR2             EQU       41h         ; R2
TR3             EQU       42h         ; R3
TR4             EQU       43h         ; R4
TR5             EQU       44h         ; R5
TR6             EQU       45h         ; R6
;
;       RECURSION EQUATIONS HAVE BIT 7 SET
;
TUN             EQU       80h         ; Un
TVN             EQU       81h         ; Vn
TWN             EQU       82h         ; Wn
;
;       2ND HALF OF USER PICTURE TOKENS
;
TPIC1           EQU       00h         ; PIC1
TPIC2           EQU       01h         ; PIC2
TPIC3           EQU       02h         ; PIC3
TPIC4           EQU       03h         ; PIC4
TPIC5           EQU       04h         ; PIC5
TPIC6           EQU       05h         ; PIC6
TPIC7           EQU       06h         ; PIC7
TPIC8           EQU       07h         ; PIC8
TPIC9           EQU       08h         ; PIC9
TPIC0           EQU       09h         ; PIC0
;
;       2ND HALF OF USER GRAPH DATABASE TOKENS
;
TGDB1           EQU       00h         ; GDB1
TGDB2           EQU       01h         ; GDB2
TGDB3           EQU       02h         ; GDB3
TGDB4           EQU       03h         ; GDB4
TGDB5           EQU       04h         ; GDB5
TGDB6           EQU       05h         ; GDB6
TGDB7           EQU       06h         ; GDB7
TGDB8           EQU       07h         ; GDB8
TGDB9           EQU       08h         ; GDB9
TGDB0           EQU       09h         ; GDB0
;
;       2ND HALF OF STRING VARS
;
TSTR1           EQU       00h
TSTR2           EQU       01h
TSTR3           EQU       02h
TSTR4           EQU       03h
TSTR5           EQU       04h
TSTR6           EQU       05h
TSTR7           EQU       06h
TSTR8           EQU       07h
TSTR9           EQU       08h
TSTR0           EQU       09h
;
;       2ND HALF OF SYSTEM OUTPUT ONLY VARIABLES
;
;
;   OPEN        EQU       00H
;
TREGEQ          EQU       01h         ; REGRESSION EQUATION
;
TSTATN          EQU       02h         ; STATISTICS N
;
TXMEAN          EQU       03h         ; X MEAN
TSUMX           EQU       04h         ; SUM(X)
TSUMXSQR        EQU       05h         ; SUM(X^2)
TSTDX           EQU       06h         ; STANDARD DEV X
TSTDPX          EQU       07h         ; STANDARD DEV POP X
TMINX           EQU       08h         ; MIN X VALUE
TMAXX           EQU       09h         ; MAX X VALUE
;
TMINY           EQU       0Ah         ; MIN Y VALUE
TMAXY           EQU       0Bh         ; MAX Y VALUE
TYMEAN          EQU       0Ch         ; Y MEAN
TSUMY           EQU       0Dh         ; SUM(Y)
TSUMYSQR        EQU       0Eh         ; SUM(Y^2)
TSTDY           EQU       0Fh         ; STANDARD DEV Y
TSTDPY          EQU       10h         ; STANDARD DEV POP Y
;
TSUMXY          EQU       11h         ; SUM(XY)
TCORR           EQU       12h         ; CORRELATION
TMEDX           EQU       13h         ; MED(X)
TQ1             EQU       14h         ; 1ST QUADRANT OF X
TQ3             EQU       15h         ; 3RD QUADRANT OF X
TQUADa          EQU       16h         ; 1ST TERM OF QUAD POLY REG/ Y-INT
TQUADb          EQU       17h         ; 2ND TERM OF QUAD POLY REG/ SLOPE
TQUADc          EQU       18h         ; 3RD TERM OF QUAD POLY REG
TCUBEd          EQU       19h         ; 4TH TERM OF CUBIC POLY REG
TQUARTe         EQU       1Ah         ; 5TH TERM OF QUART POLY REG
TMEDX1          EQU       1Bh         ; x1 FOR MED-MED
TMEDX2          EQU       1Ch         ; x2 FOR MED-MED
TMEDX3          EQU       1Dh         ; x3 FOR MED-MED
TMEDY1          EQU       1Eh         ; y1 FOR MED-MED
TMEDY2          EQU       1Fh         ; y2 FOR MED-MED
TMEDY3          EQU       20h         ; y3 FOR MED-MED
;
TRECURN           EQU       21h       ; RECURSION N
TSTATP          EQU       22h
TSTATZ          EQU       23h
TSTATT          EQU       24h
TSTATCHI        EQU       25h
TSTATF          EQU       26h
TSTATDF         EQU       27h
TSTATPHAT       EQU       28h
TSTATPHAT1      EQU       29h
TSTATPHAT2      EQU       2Ah
TSTATMEANX1     EQU       2Bh
TSTATSTDX1      EQU       2Ch
TSTATN1         EQU       2Dh
TSTATMEANX2     EQU       2Eh
TSTATSTDX2      EQU       2Fh
TSTATN2         EQU       30h
TSTATSTDXP      EQU       31h
TSTATLOWER      EQU       32h
TSTATUPPER      EQU       33h
TSTAT_S         EQU       34h
TLRSQR          EQU       35h         ; r^2
TBRSQR          EQU       36h         ; R^2
;
;       these next tokens are only used to acess the data
;       they are display only and the user cannot access them at all
;
TF_DF    EQU     37h       ; ANOFAV FACTOR DF
TF_SS    EQU     38h       ; ANOFAV FACTOR SS
TF_MS    EQU     39h       ; ANOFAV FACTOR MS
TE_DF    EQU     3Ah       ; ANOFAV ERROR DF
TE_SS    EQU     3Bh       ; ANOFAV ERROR SS
TE_MS    EQU     3Ch       ; ANOFAV ERROR MS
;
;
;       2ND HALF OF SYSTEM INPUT/OUTPUT VARIABLES
;

; SYSTEM VARIABLE EQUATES
;
;       VARS WITH NO RESTRICTION
;
TUXSCL       EQU  0
TUYSCL       EQU  1
TXSCL        EQU  2
TYSCL        EQU  3
TRECURU0     EQU  4        ; U 1ST INITIAL COND
TRECURV0     EQU  5        ; V 1ST INITIAL COND
TUN1         EQU  6        ; U(N-1)    ; NOT USED
TVN1         EQU  7        ; V(N-1)    ; NOT USED
TURECURU0    EQU  8        ;
TURECURV0    EQU  9        ;
;
;       VARS ROUNDED TO 10 DIGITS
;
TXMIN        EQU  0AH
TXMAX        EQU  0BH
TYMIN        EQU  0CH
TYMAX        EQU  0DH
TTMIN        EQU  0EH
TTMAX        EQU  0FH
TTHETAMIN    EQU  10H
TTHETAMAX    EQU  11H
TUXMIN       EQU  12H
TUXMAX       EQU  13H
TUYMIN       EQU  14H
TUYMAX       EQU  15H
TUTHETMIN    EQU  16H
TUTHETMAX    EQU  17H
TUTMIN       EQU  18H
TUTMAX       EQU  19H
TTBLMIN      EQU  1AH
TPLOTSTART   EQU  1BH
TUPLOTSTART  EQU  1CH
TNMAX        EQU  1DH
TUNMAX       EQU  1EH
TNMIN        EQU  1FH
TUNMIN       EQU  20H
;
;       VARS CANNOT BE 0
;
TTBLSTEP     EQU  21H
TTSTEP       EQU  22H
TTHETASTEP    EQU  23H
TUTSTEP      EQU  24H
TUTHETSTEP     EQU  25H
;
;       SPECIAL LIMITS ON THESE
;
TDELTAX      EQU  26H
TDELTAY      EQU  27H
;
;       SPECIAL LIMITS ON THESE
;
TXFACT       EQU  28H
TYFACT       EQU  29H
;
TTBLINPUT       EQU       2Ah
;
;       ANY RESTRICTIONS ??????
;
TFINn           EQU       2Bh
TFINi           EQU       2Ch
TFINpv          EQU       2Dh
TFINpmt         EQU       2Eh
TFINfv          EQU       2Fh
TFINpy          EQU       30h
TFINcy          EQU       31h
;
TRECURW0        EQU       32h         ; W0(1)
TURECURW0       EQU       33h
;
TPLOTSTEP       EQU       34h
TUPLOTSTEP      EQU       35h
;
TXRES           EQU       36h
TUXRES          EQU       37h
;
;       ALL THE TOKENS BELOW DO NOT HAVE STRINGS ASSOCIATED
;       THEY ARE HERE JUST FOR STORING AND RECALLING
;
TRECURU02       EQU       38h         ; U0(2)
TURECURU02      EQU       39h
TRECURV02       EQU       3Ch         ; V0(2)
TURECURV02      EQU       3Dh
TRECURW02       EQU       3Eh         ; W0(2)
TURECURW02      EQU       3Fh
;
; NO RESTRICTIONS
;
;TWN1           EQU       40h         ; W(N-1)
;UN2           EQU       41h         ; U(N-2)
;VN2           EQU       42h         ; V(N-2)
;WN2           EQU       43h         ; W(N-2)
;
;
;       DON'T KNOW IF NEED THESE YET ?
;
;TUI12
;TUI22
;TUUI12
;TUUI22
;
;

TFINnpv         EQU       00h         ; immediate unary
TFINirr         EQU       01h         ; immediate unary
TFINbal         EQU       02h         ; immediate unary
TFINprn         EQU       03h         ; immediate unary
TFINint         EQU       04h         ; immediate unary
TFINtonom       EQU       05h         ; immediate unary
TFINtoeff       EQU       06h         ; immediate unary
TFINdbd         EQU       07h         ; immediate unary
TLCM            EQU       08h         ; immediate unary
TGCD            EQU       09h         ; immediate unary
TRANDINT        EQU       0Ah         ; immediate unary
TRANDBIN        EQU       0Bh         ; immediate unary
TSUBSTRNG       EQU       0Ch         ; immediate unary
TSTDDEV         EQU       0Dh         ; immediate unary
TVARIANCE       EQU       0Eh         ; immediate unary
TINSTRNG        EQU       0Fh         ; immediate unary
TDNORMAL        EQU       10h         ; immediate unary
TINVNORM        EQU       11h         ; immediate unary
TDT             EQU       12h         ; immediate unary
TCHI            EQU       13h         ; immediate unary
TDF             EQU       14h         ; immediate unary
TBINPDF         EQU       15h         ; immediate unary
TBINCDF         EQU       16h         ; immediate unary
TPOIPDF         EQU       17h         ; immediate unary
TPOICDF         EQU       18h         ; immediate unary
TGEOPDF         EQU       19h         ; immediate unary
TGEOCDF         EQU       1Ah         ; immediate unary
TNORMALPDF      EQU       1Bh         ; immediate unary
TTPDF           EQU       1Ch         ; immediate unary
TCHIPDF         EQU       1Dh         ; immediate unary
TFPDF           EQU       1Eh         ; immediate unary
;TRANDBIN        EQU       1Fh         ; immediate unary
TRANDNORM       EQU       1Fh         ; immediate unary
TFINFpmt        EQU       20h         ; 0 or multy arg function
TFINFi          EQU       21h         ; 0 or multy arg function
TFINFpv         EQU       22h         ; 0 or multy arg function
TFINFn          EQU       23h         ; 0 or multy arg function
TFINFfv         EQU       24h         ; 0 or multy arg function
TCONJ           EQU       25h         ; unary
TREAL           EQU       26h         ; unary
TIMAG           EQU       27h         ; unary
TANGLE          EQU       28h         ; unary
TCUMSUM         EQU       29h         ; unary
TEXPR           EQU       2Ah         ; unary
TLENGTH         EQU       2Bh         ; unary
TDELTALST       EQU       2Ch         ; unary
TREF            EQU       2Dh         ; unary
TRREF           EQU       2Eh         ; unary
TTORECT         EQU       2Fh         ; display conversion
TTOPOLAR        EQU       30h         ; display conversion
TCONSTE         EQU       31h         ; function no arg
TSINREG         EQU       32h         ; command opt push
TLOGISTIC       EQU       33h         ; command opt push
TLINREGTTEST    EQU       34h         ; command opt push
TSHADENORM      EQU       35h         ; command pushed
TSHADET         EQU       36h         ; command pushed
TSHADECHI       EQU       37h         ; command pushed
TSHADEF         EQU       38h         ; command pushed
TMATTOLST       EQU       39h         ; command pushed
TLSTTOMAT       EQU       3Ah         ; command pushed
TZTEST          EQU       3Bh         ; command pushed
TTTEST          EQU       3Ch         ; command pushed
T2SAMPZTEST     EQU       3Dh         ; command pushed
T1PROPZTEST     EQU       3Eh         ; command pushed
T2PROPZTEST     EQU       3Fh         ; command pushed
TCHITEST        EQU       40h         ; command pushed
TZINTVAL        EQU       41h         ; command pushed
T2SAMPZINT      EQU       42h         ; command pushed
T1PROPZINT      EQU       43h         ; command pushed
T2PROPZINT      EQU       44h         ; command pushed
TGRAPHSTYLE     EQU       45h         ; command pushed
T2SAMPTTEST     EQU       46h         ; command opt pushed
T2SAMPFTEST     EQU       47h         ; command opt pushed
TTINTVAL        EQU       48h         ; command opt pushed
T2SAMPTINT      EQU       49h         ; command opt pushed
TSETUPLST       EQU       4Ah         ; command opt pushed
TFINpmtend      EQU       4Bh         ; mode command
TFINpmtbeg      EQU       4Ch         ; mode command
TREALM          EQU       4Dh         ; mode command
TPOLARM         EQU       4Eh         ; mode command
TRECTM          EQU       4Fh         ; mode command
TEXPRON         EQU       50h         ; mode command
TEXPROFF        EQU       51h         ; mode command
TCLRALLLST      EQU       52h         ; command not pushed
TGETCALC        EQU       53h         ; command not pushed
TDELVAR         EQU       54h         ; command not pushed
TEQUTOSTRNG     EQU       55h         ; command not pushed
TSTRNGTOEQU     EQU       56h         ; command not pushed
tdellast        EQU       57h         ; command not pushed
TSELECT         EQU       58h         ; command not pushed
TANOVA          EQU       59h         ; command not pushed
TMODBOX         EQU       5Ah         ; icon
TNORMPROB       EQU       5Bh         ; icon
;
;       tokens 5Ch to 63h CANNOT BE THE 2ND BYTE OF
;       TWO BYTE TOKENS. THESE ARE ALREADY THE 1ST BYTE VALUE
;       OF TWO BYTE TOKENS. READING TOKENS BACKWARDS WILL NOT
;       WORK IF THIS RESTRICTION IS NOT IN PLACE.
;
;
;       NO USE  EQU       5Ch
;       NO USE  EQU       5Dh
;       NO USE  EQU       5Eh
;       NO USE  EQU       5Fh
;       NO USE  EQU       60h
;       NO USE  EQU       61h
;       NO USE  EQU       62h
;       NO USE  EQU       63h
;
TMGT            EQU       64h         ; VERTICAL SPLIT
TZFIT           EQU       65h         ; ZOOM FIT
TDIAG_ON        EQU       66h         ; DIANOSTIC DISPLAY ON
TDIAG_OFF       EQU       67h         ; DIANOSTIC DISPLAY OFF
;
;




#include "stdafx.h"

#include "opcodes.h"

#define NumElm(array) (sizeof (array) / sizeof ((array)[0]))

static instr cp_instrs[] = {
		{ "A,IXH", { 0xBC, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0xBC, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0xBD, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0xBD, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0xBE, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0xBE, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0xB8 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0xB9 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0xBA }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0xBB }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0xBC }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0xBD }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0xBE }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0xBF }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xFE }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0xBC, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0xBC, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0xBD, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0xBD, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0xBE, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@)", { 0xBE, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "B", { 0xB8 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0xB9 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0xBA }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0xBB }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0xBC }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0xBD }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0xBE }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A", { 0xBF }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "&", { 0xFE }, 1, 2, 2, false, 0x00, 2, 0 } };

static instr di_instrs[] = {
		{ "", { 0xF3 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr ei_instrs[] = {
		{ "", { 0xFB }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr ex_instrs[] = {
		{ "(SP),IX", { 0xE3, 0xDD }, 2, 6, 6, false, 0x00, 2, 2 },
		{ "(SP),IY", { 0xE3, 0xFD }, 2, 6, 6, false, 0x00, 2, 2 },
		{ "AF,AF'", { 0x08 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(SP),HL", { 0xE3 }, 1, 5, 5, false, 0x00, 1, 2 },
		{ "DE,HL", { 0xEB }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr im_instrs[] = {
		{ "0", { 0x46, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "1", { 0x56, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "2", { 0x5E, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr in_instrs[] = {
		{ "A,(C)", { 0x78, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "A,(BC)", { 0x78, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "A,(&)", { 0xDB }, 1, 3, 3, false, 0x00, 2, 0 },
		{ "B,(C)", { 0x40, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "B,(BC)", { 0x40, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "C,(C)", { 0x48, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "C,(BC)", { 0x48, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "D,(C)", { 0x50, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "D,(BC)", { 0x50, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "E,(C)", { 0x58, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "E,(BC)", { 0x58, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "H,(C)", { 0x60, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "H,(BC)", { 0x60, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "L,(C)", { 0x68, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "L,(BC)", { 0x68, 0xED }, 2, 3, 3, false, 0x00, 2, 0 }, };

static instr jp_instrs[] = {
		{ "(IX)", { 0xE9, 0xDD }, 2, 4, 4, false, 0x00, 2, 0 },
		{ "(IY)", { 0xE9, 0xFD }, 2, 4, 4, false, 0x00, 2, 0 },
		{ "NZ,*", { 0xC2 }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "Z,*", { 0xCA }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "NC,*", { 0xD2 }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "C,*", { 0xDA }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "PO,*", { 0xE2 }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "(HL)", { 0xE9 }, 1, 3, 3, false, 0x00, 1, 0 },
		{ "PE,*", { 0xEA }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "P,*", { 0xF2 }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "M,*", { 0xFA }, 1, 3, 4, false, 0x00, 3, 1 },
		{ "*", { 0xC3 }, 1, 4, 4, false, 0x00, 3, 1 } };

static instr jr_instrs[] = {
		{ "NZ,%", { 0x20 }, 1, 2, 3, false, 0x00, 2, 0 },
		{ "Z,%", { 0x28 }, 1, 2, 3, false, 0x00, 2, 0 },
		{ "NC,%", { 0x30 }, 1, 2, 3, false, 0x00, 2, 0 },
		{ "C,%", { 0x38 }, 1, 2, 3, false, 0x00, 2, 0 },
		{ "%", { 0x18 }, 1, 3, 3, false, 0x00, 2, 0 } };

static instr ld_instrs[] = {
		{ "SP,HL", { 0xF9 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "BC,(HL)", { 0x07, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "(HL),BC", { 0x0F, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "DE,(HL)", { 0x17, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "(HL),DE", { 0x1F, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "HL,(HL)", { 0x27, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "(HL),HL", { 0x2F, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "IY,(HL)", { 0x31, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "IX,(HL)", { 0x37, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "(HL),IY", { 0x3E, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "(HL),IX", { 0x3F, 0xED }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "BC,(IX@)", { 0x07, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IX@),BC", { 0x0F, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "DE,(IX@)", { 0x17, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IX@),DE", { 0x1F, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "HL,(IX@)", { 0x27, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IX@),HL", { 0x2F, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "IY,(IX@)", { 0x31, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "IX,(IX@)", { 0x37, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IX@),IY", { 0x3E, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IX@),IX", { 0x3F, 0xDD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "BC,(IY@)", { 0x07, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IY@),BC", { 0x0F, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "DE,(IY@)", { 0x17, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IY@),DE", { 0x1F, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "HL,(IY@)", { 0x27, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IY@),HL", { 0x2F, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "IX,(IY@)", { 0x31, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "IY,(IY@)", { 0x37, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IY@),IX", { 0x3E, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "(IY@),IY", { 0x3F, 0xFD }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "A,I", { 0x57, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,R", { 0x5F, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,MB", { 0x6E, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "I,HL", { 0xC7, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,I", { 0xD7, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,B", { 0x60, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,B", { 0x60, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,C", { 0x61, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,C", { 0x61, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,D", { 0x62, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,D", { 0x62, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,E", { 0x63, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,E", { 0x63, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,IXH", { 0x64, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,IYH", { 0x64, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH,IXL", { 0x65, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,IYL", { 0x65, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H,(IX@)", { 0x66, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "H,(IY@)", { 0x66, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "IXH,A", { 0x67, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH,A", { 0x67, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,B", { 0x68, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,B", { 0x68, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,C", { 0x69, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,C", { 0x69, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,D", { 0x6A, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,D", { 0x6A, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,E", { 0x6B, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,E", { 0x6B, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,IXH", { 0x6C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,IYH", { 0x6C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL,IXL", { 0x6D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,IYL", { 0x6D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L,(IX@)", { 0x6E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "L,(IY@)", { 0x6E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "IXL,A", { 0x6F, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL,A", { 0x6F, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(*),IX", { 0x22, 0xDD }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "(*),IY", { 0x22, 0xFD }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "IXH,&", { 0x26, 0xDD }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IYH,&", { 0x26, 0xFD }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IX,(*)", { 0x2A, 0xDD }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "IY,(*)", { 0x2A, 0xFD }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "IXL,&", { 0x2E, 0xDD }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IYL,&", { 0x2E, 0xFD }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "B,IXH", { 0x44, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "B,IYH", { 0x44, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "B,IXL", { 0x45, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "B,IYL", { 0x45, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "B,(IX@)", { 0x46, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "B,(IY@)", { 0x46, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "C,IXH", { 0x4C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C,IYH", { 0x4C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C,IXL", { 0x4D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C,IYL", { 0x4D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C,(IX@)", { 0x4E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "C,(IY@)", { 0x4E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "D,IXH", { 0x54, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D,IYH", { 0x54, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D,IXL", { 0x55, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D,IYL", { 0x55, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D,(IX@)", { 0x56, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "D,(IY@)", { 0x56, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "E,IXH", { 0x5C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E,IYH", { 0x5C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E,IXL", { 0x5D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E,IYL", { 0x5D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E,(IX@)", { 0x5E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "E,(IY@)", { 0x5E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),B", { 0x70, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),B", { 0x70, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),C", { 0x71, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),C", { 0x71, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),D", { 0x72, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),D", { 0x72, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),E", { 0x73, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),E", { 0x73, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),H", { 0x74, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),H", { 0x74, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),L", { 0x75, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),L", { 0x75, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),A", { 0x77, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@),A", { 0x77, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,IXH", { 0x7C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0x7C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0x7D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0x7D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0x7E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0x7E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IX@),&", { 0x36, 0xDD }, 2, 5, 5, false, 0x00, 4, 0 },
		{ "(IY@),&", { 0x36, 0xFD }, 2, 5, 5, false, 0x00, 4, 0 },
		{ "SP,IX", { 0xF9, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "SP,IY", { 0xF9, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		//{ "B,B", { 0x40 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,C", { 0x41 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,D", { 0x42 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,E", { 0x43 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,H", { 0x44 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,L", { 0x45 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B,(HL)", { 0x46 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "B,A", { 0x47 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,B", { 0x48 }, 1, 1, 1, false, 0x00, 1, 0 },
		//{ "C,C", { 0x49 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,D", { 0x4A }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,E", { 0x4B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,H", { 0x4C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,L", { 0x4D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C,(HL)", { 0x4E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "C,A", { 0x4F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,B", { 0x50 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,C", { 0x51 }, 1, 1, 1, false, 0x00, 1, 0 },
		//{ "D,D", { 0x52 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,E", { 0x53 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,H", { 0x54 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,L", { 0x55 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D,(HL)", { 0x56 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "D,A", { 0x57 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,B", { 0x58 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,C", { 0x59 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,D", { 0x5A }, 1, 1, 1, false, 0x00, 1, 0 },
		//{ "E,E", { 0x5B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,H", { 0x5C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,L", { 0x5D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E,(HL)", { 0x5E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "E,A", { 0x5F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,B", { 0x60 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,C", { 0x61 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,D", { 0x62 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,E", { 0x63 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,H", { 0x64 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,L", { 0x65 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H,(HL)", { 0x66 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "H,A", { 0x67 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,B", { 0x68 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,C", { 0x69 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,D", { 0x6A }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,E", { 0x6B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,H", { 0x6C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,L", { 0x6D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L,(HL)", { 0x6E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "L,A", { 0x6F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL),B", { 0x70 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),C", { 0x71 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),D", { 0x72 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),E", { 0x73 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),H", { 0x74 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),L", { 0x75 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "(HL),A", { 0x77 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,B", { 0x78 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0x79 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0x7A }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0x7B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0x7C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0x7D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0x7E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0x7F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(BC),A", { 0x02 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "B,&", { 0x06 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "A,(BC)", { 0x0A }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "C,&", { 0x0E }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "(DE),A", { 0x12 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "D,&", { 0x16 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "A,(DE)", { 0x1A }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "E,&", { 0x1E }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "(*),HL", { 0x22 }, 1, 5, 5, false, 0x00, 3, 2  },
		{ "H,&", { 0x26 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "HL,(*)", { 0x2A }, 1, 5, 5, false, 0x00, 3, 2 },
		{ "L,&", { 0x2E }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "(*),A", { 0x32 }, 1, 4, 4, false, 0x00, 3, 1 },
		{ "(HL),&", { 0x36 }, 1, 3, 3, false, 0x00, 2, 0 },
		{ "A,(*)", { 0x3A }, 1, 4, 4, false, 0x00, 3, 1 },
		{ "A,&", { 0x3E }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "(*),BC", { 0x43, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "I,A", { 0x47, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "BC,(*)", { 0x4B, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "R,A", { 0x4F, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(*),DE", { 0x53, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "DE,(*)", { 0x5B, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "(*),HL", { 0x63, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "HL,(*)", { 0x6B, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "MB,A", { 0x6E, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(*),SP", { 0x73, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "SP,(*)", { 0x7B, 0xED }, 2, 6, 6, false, 0x00, 4, 2 },
		{ "HL,*", { 0x21 }, 1, 3, 3, false, 0x00, 3, 1 },
		{ "BC,*", { 0x01 }, 1, 3, 3, false, 0x00, 3, 1 },
		{ "DE,*", { 0x11 }, 1, 3, 3, false, 0x00, 3, 1 },
		{ "IX,*", { 0x21, 0xDD }, 2, 4, 4, false, 0x00, 4, 1 },
		{ "IY,*", { 0x21, 0xFD }, 2, 4, 4, false, 0x00, 4, 1 },
		{ "SP,*", { 0x31 }, 1, 3, 3, false, 0x00, 3, 1 },

};

static instr or_instrs[] = {
		{ "A,IXH", { 0xB4, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0xB4, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0xB5, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0xB5, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0xB6, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0xB6, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0xB0 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0xB1 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0xB2 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0xB3 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0xB4 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0xB5 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0xB6 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0xB7 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xF6 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0xB4, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0xB4, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0xB5, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0xB5, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0xB6, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@)", { 0xB6, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "B", { 0xB0 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0xB1 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0xB2 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0xB3 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0xB4 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0xB5 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0xB6 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A", { 0xB7 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "&", { 0xF6 }, 1, 2, 2, false, 0x00, 2, 0} };

static instr rl_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x16, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x16, 4, 0 },
		{ "B", { 0x10, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x11, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x12, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x13, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x14, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x15, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x16, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x17, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr rr_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x1E, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x1E, 4, 0 },
		{ "B", { 0x18, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x19, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x1A, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x1B, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x1C, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x1D, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x1E, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x1F, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr adc_instrs[] = {
		{ "A,IXH", { 0x8C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0x8C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0x8D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0x8D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0x8E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0x8E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0x88 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0x89 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0x8A }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0x8B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0x8C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0x8D }, 1, 7, 7, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0x8E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0x8F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xCE }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "HL,BC", { 0x4A, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,DE", { 0x5A, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,HL", { 0x6A, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,SP", { 0x7A, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr add_instrs[] = {
		{ "IX,BC", { 0x09, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY,BC", { 0x09, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IX,DE", { 0x19, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY,DE", { 0x19, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IX,IX", { 0x29, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY,IY", { 0x29, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IX,SP", { 0x39, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY,SP", { 0x39, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXH", { 0x84, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0x84, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0x85, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0x85, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0x86, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0x86, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0x80 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0x81 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0x82 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0x83 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0x84 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0x85 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0x86 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0x87 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL,BC", { 0x09 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL,DE", { 0x19 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL,HL", { 0x29 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL,SP", { 0x39 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xC6 }, 1, 2, 2, false, 0x00, 2, 0 } };

static instr and_instrs[] = {
		{ "A,IXH", { 0xA4, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0xA4, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0xA5, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0xA5, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0xA6, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0xA6, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0xA0 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0xA1 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0xA2 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0xA3 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0xA4 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0xA5 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0xA6 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0xA7 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xE6 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0xA4, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0xA4, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0xA5, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0xA5, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0xA6, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@)", { 0xA6, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "B", { 0xA0 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0xA1 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0xA2 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0xA3 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0xA4 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0xA5 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0xA6 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A", { 0xA7 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "&", { 0xE6 }, 1, 2, 2, false, 0x00, 2, 0 } };

static instr bit_instrs[] = {
		{ "^,(IX@)", { 0xCB, 0xDD }, 2, 5, 5, true, 0x46, 4, 0 },
		{ "^,(IY@)", { 0xCB, 0xFD }, 2, 5, 5, true, 0x46, 4, 0 },
		{ "^,B", { 0xCB }, 1, 2, 2, true, 0x40, 2, 0 },
		{ "^,C", { 0xCB }, 1, 2, 2, true, 0x41, 2, 0 },
		{ "^,D", { 0xCB }, 1, 2, 2, true, 0x42, 2, 0 },
		{ "^,E", { 0xCB }, 1, 2, 2, true, 0x43, 2, 0 },
		{ "^,H", { 0xCB }, 1, 2, 2, true, 0x44, 2, 0 },
		{ "^,L", { 0xCB }, 1, 2, 2, true, 0x45, 2, 0 },
		{ "^,(HL)", { 0xCB }, 1, 3, 3, true, 0x46, 2, 0 },
		{ "^,A", { 0xCB }, 1, 2, 2, true, 0x47, 2, 0 } };

static instr ccf_instrs[] = {
		{ "", { 0x3F }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr cpd_instrs[] = {
		{ "", { 0xA9, 0xED }, 2, 3, 3, false, 0x00, 2, 0 } };

static instr cpi_instrs[] = {
		{ "", { 0xA1, 0xED }, 2, 3, 3, false, 0x00, 2, 0 } };

static instr cpl_instrs[] = {
		{ "", { 0x2F }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr daa_instrs[] = {
		{ "", { 0x27 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr dec_instrs[] = {
		{ "IXH", { 0x25, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0x25, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IX", { 0x2B, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY", { 0x2B, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0x2D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0x2D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0x35, 0xDD }, 2, 6, 6, false, 0x00, 3, 0 },
		{ "(IY@)", { 0x35, 0xFD }, 2, 6, 6, false, 0x00, 3, 0 },
		{ "B", { 0x05 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "BC", { 0x0B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0x0D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0x15 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "DE", { 0x1B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0x1D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0x25 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL", { 0x2B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0x2D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0x35 }, 1, 4, 4, false, 0x00, 1, 0 },
		{ "SP", { 0x3B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A", { 0x3D }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr exx_instrs[] = {
		{ "", { 0xD9 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr inc_instrs[] = {
		{ "IX", { 0x23, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IY", { 0x23, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0x24, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0x24, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0x2C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0x2C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0x34, 0xDD }, 2, 6, 6, false, 0x00, 3, 0 },
		{ "(IY@)", { 0x34, 0xFD }, 2, 6, 6, false, 0x00, 3, 0 },
		{ "BC", { 0x03 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B", { 0x04 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0x0C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "DE", { 0x13 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0x14 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0x1C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "HL", { 0x23 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0x24 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0x2C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "SP", { 0x33 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0x34 }, 1, 4, 4, false, 0x00, 1, 0 },
		{ "A", { 0x3C }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr in0_instrs[] = {
		{ "B,(&)", { 0x00, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "C,(&)", { 0x08, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "D,(&)", { 0x10, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "E,(&)", { 0x18, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "H,(&)", { 0x20, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "L,(&)", { 0x28, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(&)", { 0x38, 0xED }, 2, 4, 4, false, 0x00, 3, 0 } };

static instr ind_instrs[] = {
		{ "", { 0xAA, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr ini_instrs[] = {
		{ "", { 0xA2, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr ldd_instrs[] = {
		{ "", { 0xA8, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr ldi_instrs[] = {
		{ "", { 0xA0, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr lea_instrs[] = {
		{ "BC,IX@", { 0x02, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "BC,IY@", { 0x03, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "DE,IX@", { 0x12, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "DE,IY@", { 0x13, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "HL,IX@", { 0x22, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "HL,IY@", { 0x23, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IX,IX@", { 0x32, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IY,IY@", { 0x33, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IX,IY@", { 0x54, 0xED }, 2, 3, 3, false, 0x00, 3, 0 },
		{ "IY,IX@", { 0x55, 0xED }, 2, 3, 3, false, 0x00, 3, 0 } };

static instr mlt_instrs[] = {
		{ "BC", { 0x4C, 0xED }, 2, 6, 6, false, 0x00, 2, 0 },
		{ "DE", { 0x5C, 0xED }, 2, 6, 6, false, 0x00, 2, 0 },
		{ "HL", { 0x6C, 0xED }, 2, 6, 6, false, 0x00, 2, 0 },
		{ "SP", { 0x7C, 0xED }, 2, 6, 6, false, 0x00, 2, 0 } };

static instr neg_instrs[] = {
		{ "", { 0x44, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr nop_instrs[] = {
		{ "", { 0x00 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr out_instrs[] = {
		{ "(C),A", { 0x79, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),A", { 0x79, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(&),A", { 0xD3 }, 1, 3, 3, false, 0x00, 2, 0 },
		{ "(C),B", { 0x41, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),B", { 0x41, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(C),C", { 0x49, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),C", { 0x49, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(C),D", { 0x51, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),D", { 0x51, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(C),E", { 0x59, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),E", { 0x59, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(C),H", { 0x61, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),H", { 0x61, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(C),L", { 0x69, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "(BC),L", { 0x69, 0xED }, 2, 3, 3, false, 0x00, 2, 0 } };

static instr pea_instrs[] = {
		{ "IX@", { 0x65, 0xED }, 2, 5, 5, false, 0x00, 3, 1 },
		{ "IY@", { 0x66, 0xED }, 2, 5, 5, false, 0x00, 3, 1 } };

static instr pop_instrs[] = {
		{ "IX", { 0xE1, 0xDD }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "IY", { 0xE1, 0xFD }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "BC", { 0xC1 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "DE", { 0xD1 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "HL", { 0xE1 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "AF", { 0xF1 }, 1, 3, 3, false, 0x00, 1, 1 } };

static instr res_instrs[] = {
		{ "^,(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x86, 4, 0 },
		{ "^,(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x86, 4, 0 },
		{ "^,B", { 0xCB }, 1, 2, 2, true, 0x80, 2, 0 },
		{ "^,C", { 0xCB }, 1, 2, 2, true, 0x81, 2, 0 },
		{ "^,D", { 0xCB }, 1, 2, 2, true, 0x82, 2, 0 },
		{ "^,E", { 0xCB }, 1, 2, 2, true, 0x83, 2, 0 },
		{ "^,H", { 0xCB }, 1, 2, 2, true, 0x84, 2, 0 },
		{ "^,L", { 0xCB }, 1, 2, 2, true, 0x85, 2, 0 },
		{ "^,(HL)", { 0xCB }, 1, 5, 5, true, 0x86, 2, 0 },
		{ "^,A", { 0xCB }, 1, 2, 2, true, 0x87, 2, 0 } };

static instr ret_instrs[] = {
		{ "", { 0xC9 }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "NZ", { 0xC0 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "Z", { 0xC8 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "NC", { 0xD0 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "C", { 0xD8 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "PO", { 0xE0 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "PE", { 0xE8 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "P", { 0xF0 }, 1, 2, 6, false, 0x00, 1, 1 },
		{ "M", { 0xF8 }, 1, 2, 6, false, 0x00, 1, 1 } };

static instr rla_instrs[] = {
		{ "", { 0x17 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr rlc_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x06, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x06, 4, 0 },
		{ "B", { 0x00, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x01, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x02, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x03, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x04, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x05, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x06, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x07, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr rld_instrs[] = {
		{ "", { 0x6F, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr rra_instrs[] = {
		{ "", { 0x1F }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr rrc_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x0E, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x0E, 4, 0 },
		{ "B", { 0x08, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x09, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x0A, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x0B, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x0C, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x0D, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x0E, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x0F, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr rrd_instrs[] = {
		{ "", { 0x67, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr rst_instrs[] = {
		{ "00H", { 0xC7 }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "08H", { 0xCF }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "10H", { 0xD7 }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "18H", { 0xDF }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "20H", { 0xE7 }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "28H", { 0xEF }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "30H", { 0xF7 }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "38H", { 0xFF }, 1, 5, 5, false, 0x00, 1, 1 },
		{ "#", { 0xFF }, 0, 5, 5, false, 0x00, 1, 1 } };

static instr sbc_instrs[] = {
		{ "A,IXH", { 0x9C, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0x9C, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0x9D, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0x9D, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0x9E, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0x9E, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0x98 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0x99 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0x9A }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0x9B }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0x9C }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0x9D }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0x9E }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0x9F }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xDE }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "HL,BC", { 0x42, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,DE", { 0x52, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,HL", { 0x62, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "HL,SP", { 0x72, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr scf_instrs[] = {
		{ "", { 0x37 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr set_instrs[] = {
		{ "^,(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0xC6, 4, 0 },
		{ "^,(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0xC6, 4, 0 },
		{ "^,B", { 0xCB }, 1, 2, 2, true, 0xC0, 2, 0 },
		{ "^,C", { 0xCB }, 1, 2, 2, true, 0xC1, 2, 0 },
		{ "^,D", { 0xCB }, 1, 2, 2, true, 0xC2, 2, 0 },
		{ "^,E", { 0xCB }, 1, 2, 2, true, 0xC3, 2, 0 },
		{ "^,H", { 0xCB }, 1, 2, 2, true, 0xC4, 2, 0 },
		{ "^,L", { 0xCB }, 1, 2, 2, true, 0xC5, 2, 0 },
		{ "^,(HL)", { 0xCB }, 1, 5, 5, true, 0xC6, 2, 0 },
		{ "^,A", { 0xCB }, 1, 2, 2, true, 0xC7, 2, 0 } };

static instr sla_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x26, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x26, 4, 0 },
		{ "B", { 0x20, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x21, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x22, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x23, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x24, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x25, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x26, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x27, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr slp_instrs[] = {
		{ "", { 0x76, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr sra_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x2E, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x2E, 4, 0 },
		{ "B", { 0x28, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x29, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x2A, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x2B, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x2C, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x2D, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x2E, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x2F, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr srl_instrs[] = {
		{ "(IX@)", { 0xCB, 0xDD }, 2, 7, 7, true, 0x3E, 4, 0 },
		{ "(IY@)", { 0xCB, 0xFD }, 2, 7, 7, true, 0x3E, 4, 0 },
		{ "B", { 0x38, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "C", { 0x39, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "D", { 0x3A, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "E", { 0x3B, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "H", { 0x3C, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "L", { 0x3D, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(HL)", { 0x3E, 0xCB }, 2, 5, 5, false, 0x00, 2, 0 },
		{ "A", { 0x3F, 0xCB }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr sub_instrs[] = {
		{ "A,IXH", { 0x94, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0x94, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0x95, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0x95, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0x96, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0x96, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,B", { 0x90 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0x91 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0x92 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0x93 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0x94 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0x95 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0x96 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,A", { 0x97 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,&", { 0xD6 }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0x94, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0x94, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0x95, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0x95, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0x96, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@)", { 0x96, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "B", { 0x90 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0x91 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0x92 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0x93 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0x94 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0x95 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0x96 }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A", { 0x97 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "&", { 0xD6 }, 1, 2, 2, false, 0x00, 2, 0 } };

static instr tst_instrs[] = {
		{ "A,B", { 0x04, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,C", { 0x0C, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,D", { 0x14, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,E", { 0x1C, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,H", { 0x24, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,L", { 0x2C, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(HL)", { 0x34, 0xED }, 2, 3, 3, false, 0x00, 2, 0 },
		{ "A,A", { 0x3C, 0xED }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,&", { 0x64, 0xED }, 2, 3, 3, false, 0x00, 3, 0 } };

static instr xor_instrs[] = {
		{ "A,IXH", { 0xAC, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYH", { 0xAC, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IXL", { 0xAD, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,IYL", { 0xAD, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "A,(IX@)", { 0xAE, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,(IY@)", { 0xAE, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A,A", { 0xAF }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,B", { 0xA8 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,C", { 0xA9 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,D", { 0xAA }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,E", { 0xAB }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,H", { 0xAC }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,L", { 0xAD }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "A,(HL)", { 0xAE }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "A,&", { 0xEE }, 1, 2, 2, false, 0x00, 2, 0 },
		{ "IXH", { 0xAC, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYH", { 0xAC, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IXL", { 0xAD, 0xDD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "IYL", { 0xAD, 0xFD }, 2, 2, 2, false, 0x00, 2, 0 },
		{ "(IX@)", { 0xAE, 0xDD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(IY@)", { 0xAE, 0xFD }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "A", { 0xAF }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "B", { 0xA8 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "C", { 0xA9 }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "D", { 0xAA }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "E", { 0xAB }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "H", { 0xAC }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "L", { 0xAD }, 1, 1, 1, false, 0x00, 1, 0 },
		{ "(HL)", { 0xAE }, 1, 2, 2, false, 0x00, 1, 0 },
		{ "&", { 0xEE }, 1, 2, 2, false, 0x00, 2, 0 } };

static instr call_instrs[] = {
		{ "NZ,*", { 0xC4 }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "Z,*", { 0xCC }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "NC,*", { 0xD4 }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "C,*", { 0xDC }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "PO,*", { 0xE4 }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "PE,*", { 0xEC }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "P,*", { 0xF4 }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "M,*", { 0xFC }, 1, 3, 6, false, 0x00, 3, 1 },
		{ "*", { 0xCD }, 1, 5, 5, false, 0x00, 3, 2 } };

static instr cpdr_instrs[] = {
		{ "", { 0xB9, 0xED }, 2, 3, 4, false, 0x00, 2, 0 } };

static instr cpir_instrs[] = {
		{ "", { 0xB1, 0xED }, 2, 3, 4, false, 0x00, 2, 0 } };

static instr djnz_instrs[] = {
		{ "%", { 0x10 }, 1, 2, 4, false, 0x00, 2, 0 } };

static instr halt_instrs[] = {
		{ "", { 0x76 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr ind2_instrs[] = {
		{ "", { 0x8C, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr indm_instrs[] = {
		{ "", { 0x8A, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr indr_instrs[] = {
		{ "", { 0xBA, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr ini2_instrs[] = {
		{ "", { 0x84, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr inim_instrs[] = {
		{ "", { 0x82, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr inir_instrs[] = {
		{ "", { 0xB2, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr lddr_instrs[] = {
		{ "", { 0xB8, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr ldir_instrs[] = {
		{ "", { 0xB0, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otdm_instrs[] = {
		{ "", { 0x8B, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr otdr_instrs[] = {
		{ "", { 0xBB, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otim_instrs[] = {
		{ "", { 0x83, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr otir_instrs[] = {
		{ "", { 0xB3, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr out0_instrs[] = {
		{ "(&),B", { 0x01, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),C", { 0x09, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),D", { 0x11, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),E", { 0x19, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),H", { 0x21, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),L", { 0x29, 0xED }, 2, 4, 4, false, 0x00, 3, 0 },
		{ "(&),A", { 0x39, 0xED }, 2, 4, 4, false, 0x00, 3, 0 } };

static instr outd_instrs[] = {
		{ "", { 0xAB, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr outi_instrs[] = {
		{ "", { 0xA3, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr push_instrs[] = {
		{ "IX", { 0xE5, 0xDD }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "IY", { 0xE5, 0xFD }, 2, 4, 4, false, 0x00, 2, 1 },
		{ "BC", { 0xC5 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "DE", { 0xD5 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "HL", { 0xE5 }, 1, 3, 3, false, 0x00, 1, 1 },
		{ "AF", { 0xF5 }, 1, 3, 3, false, 0x00, 1, 1 } };

static instr reti_instrs[] = {
		{ "", { 0x4D, 0xED }, 2, 6, 6, false, 0x00, 2, 1 } };

static instr retn_instrs[] = {
		{ "", { 0x45, 0xED }, 2, 6, 6, false, 0x00, 2, 1 } };

static instr rlca_instrs[] = {
		{ "", { 0x07 }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr rrca_instrs[] = {
		{ "", { 0x0F }, 1, 1, 1, false, 0x00, 1, 0 } };

static instr ind2r_instrs[] = {
		{ "", { 0x9C, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr indmr_instrs[] = {
		{ "", { 0x9A, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr indrx_instrs[] = {
		{ "", { 0xCA, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr ini2r_instrs[] = {
		{ "", { 0x94, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr inimr_instrs[] = {
		{ "", { 0x92, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr inirx_instrs[] = {
		{ "", { 0xC2, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otd2r_instrs[] = {
		{ "", { 0xBC, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otdmr_instrs[] = {
		{ "", { 0x9B, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otdrx_instrs[] = {
		{ "", { 0xCB, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr oti2r_instrs[] = {
		{ "", { 0xB4, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otimr_instrs[] = {
		{ "", { 0x93, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr otirx_instrs[] = {
		{ "", { 0xC3, 0xED }, 2, 3, 5, false, 0x00, 2, 0 } };

static instr outd2_instrs[] = {
		{ "", { 0xAC, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr outi2_instrs[] = {
		{ "", { 0xA4, 0xED }, 2, 5, 5, false, 0x00, 2, 0 } };

static instr rsmix_instrs[] = {
		{ "", { 0x7E, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr stmix_instrs[] = {
		{ "", { 0x7D, 0xED }, 2, 2, 2, false, 0x00, 2, 0 } };

static instr tstio_instrs[] = {
		{ "&", { 0x74, 0xED }, 2, 4, 4, false, 0x00, 3, 0 } };

opcode opcode_list_ez80[] = {
		{ "LD", ld_instrs, NumElm(ld_instrs), 0, &opcode_list[1], false },
		{ "CALL", call_instrs, NumElm(call_instrs), 0, &opcode_list[2], false },
		{ "RET", ret_instrs, NumElm(ret_instrs), 0, &opcode_list[3], false },
		{ "JR", jr_instrs, NumElm(jr_instrs), 0, &opcode_list[4], false },
		{ "JP", jp_instrs, NumElm(jp_instrs), 0, &opcode_list[5], false },
		{ "ADD", add_instrs, NumElm(add_instrs), 0, &opcode_list[6], false },
		{ "INC", inc_instrs, NumElm(inc_instrs), 0, &opcode_list[7], false },
		{ "POP", pop_instrs, NumElm(pop_instrs), 0, &opcode_list[8], false },
		{ "PUSH", push_instrs, NumElm(push_instrs), 0, &opcode_list[9], false },
		{ "DEC", dec_instrs, NumElm(dec_instrs), 0, &opcode_list[10], false },
		{ "CP", cp_instrs, NumElm(cp_instrs), 0, &opcode_list[11], false },
		{ "OR", or_instrs, NumElm(or_instrs), 0, &opcode_list[12], false },
		{ "EX", ex_instrs, NumElm(ex_instrs), 0, &opcode_list[13], false },
		{ "XOR", xor_instrs, NumElm(xor_instrs), 0, &opcode_list[14], false },
		{ "EXX", exx_instrs, NumElm(exx_instrs), 0, &opcode_list[15], false },
		{ "SUB", sub_instrs, NumElm(sub_instrs), 0, &opcode_list[16], false },
		{ "AND", and_instrs, NumElm(and_instrs), 0, &opcode_list[17], false },
		{ "SET", set_instrs, NumElm(set_instrs), 0, &opcode_list[18], false },
		{ "BIT", bit_instrs, NumElm(bit_instrs), 0, &opcode_list[19], false },
		{ "DJNZ", djnz_instrs, NumElm(djnz_instrs), 0, &opcode_list[20], false },
		{ "RRA", rra_instrs, NumElm(rra_instrs), 0, &opcode_list[21], false },
		{ "RR", rr_instrs, NumElm(rr_instrs), 0, &opcode_list[22], false },
		{ "SRA", sra_instrs, NumElm(sra_instrs), 0, &opcode_list[23], false },
		{ "RES", res_instrs, NumElm(res_instrs), 0, &opcode_list[24], false },
		{ "LDIR", ldir_instrs, NumElm(ldir_instrs), 0, &opcode_list[25], false },
		{ "RLA", rla_instrs, NumElm(rla_instrs), 0, &opcode_list[26], false },
		{ "OUT", out_instrs, NumElm(out_instrs), 0, &opcode_list[27], false },
		{ "SBC", sbc_instrs, NumElm(sbc_instrs), 0, &opcode_list[28], false },
		{ "CPL", cpl_instrs, NumElm(cpl_instrs), 0, &opcode_list[29], false },
		{ "RL", rl_instrs, NumElm(rl_instrs), 0, &opcode_list[30], false },
		{ "NEG", neg_instrs, NumElm(neg_instrs), 0, &opcode_list[31], false },
		{ "RLC", rlc_instrs, NumElm(rlc_instrs), 0, &opcode_list[32], false },
		{ "SRL", srl_instrs, NumElm(srl_instrs), 0, &opcode_list[33], false },
		{ "RST", rst_instrs, NumElm(rst_instrs), 0, &opcode_list[34], false },
		{ "IN", in_instrs, NumElm(in_instrs), 0, &opcode_list[35], false },
		{ "LDDR", lddr_instrs, NumElm(lddr_instrs), 0, &opcode_list[36], false },
		{ "EI", ei_instrs, NumElm(ei_instrs), 0, &opcode_list[37], false },
		{ "IM", im_instrs, NumElm(im_instrs), 0, &opcode_list[38], false },
		{ "ADC", adc_instrs, NumElm(adc_instrs), 0, &opcode_list[39], false },
		{ "DAA", daa_instrs, NumElm(daa_instrs), 0, &opcode_list[40], false },
		{ "DI", di_instrs, NumElm(di_instrs), 0, &opcode_list[41], false },
		{ "NOP", nop_instrs, NumElm(nop_instrs), 0, &opcode_list[42], false },
		{ "RLCA", rlca_instrs, NumElm(rlca_instrs), 0, &opcode_list[43], false },
		{ "SLA", sla_instrs, NumElm(sla_instrs), 0, &opcode_list[44], false },
		{ "LDI", ldi_instrs, NumElm(ldi_instrs), 0, &opcode_list[45], false },
		{ "CCF", ccf_instrs, NumElm(ccf_instrs), 0, &opcode_list[46], false },
		{ "SCF", scf_instrs, NumElm(scf_instrs), 0, &opcode_list[47], false },
		{ "RRC", rrc_instrs, NumElm(rrc_instrs), 0, &opcode_list[48], false },
		{ "HALT", halt_instrs, NumElm(halt_instrs), 0, &opcode_list[49], false },
		{ "RLD", rld_instrs, NumElm(rld_instrs), 0, &opcode_list[50], false },
		{ "TST", tst_instrs, NumElm(tst_instrs), 0, &opcode_list[51], false },
		{ "CPD", cpd_instrs, NumElm(cpd_instrs), 0, &opcode_list[52], false },
		{ "CPDR", cpdr_instrs, NumElm(cpdr_instrs), 0, &opcode_list[53], false },
		{ "CPI", cpi_instrs, NumElm(cpi_instrs), 0, &opcode_list[54], false },
		{ "CPIR", cpir_instrs, NumElm(cpir_instrs), 0, &opcode_list[55], false },
		{ "IND", ind_instrs, NumElm(ind_instrs), 0, &opcode_list[56], false },
		{ "INDR", indr_instrs, NumElm(indr_instrs), 0, &opcode_list[57], false },
		{ "INI", ini_instrs, NumElm(ini_instrs), 0, &opcode_list[58], false },
		{ "INIR", inir_instrs, NumElm(inir_instrs), 0, &opcode_list[59], false },
		{ "LDD", ldd_instrs, NumElm(ldd_instrs), 0, &opcode_list[60], false },
		{ "OTDR", otdr_instrs, NumElm(otdr_instrs), 0, &opcode_list[61], false },
		{ "OTIR", otir_instrs, NumElm(otir_instrs), 0, &opcode_list[62], false },
		{ "OUTD", outd_instrs, NumElm(outd_instrs), 0, &opcode_list[63], false },
		{ "OUTI", outi_instrs, NumElm(outi_instrs), 0, &opcode_list[64], false },
		{ "RETI", reti_instrs, NumElm(reti_instrs), 0, &opcode_list[65], false },
		{ "RETN", retn_instrs, NumElm(retn_instrs), 0, &opcode_list[66], false },
		{ "RRCA", rrca_instrs, NumElm(rrca_instrs), 0, &opcode_list[67], false },
		{ "RRD", rrd_instrs, NumElm(rrd_instrs), 0, &opcode_list[68], false },
		{ "LEA", lea_instrs, NumElm(lea_instrs), 0, &opcode_list[69], false },
		{ "PEA", pea_instrs, NumElm(pea_instrs), 0, &opcode_list[70], false },
		{ "MLT", mlt_instrs, NumElm(mlt_instrs), 0, &opcode_list[71], false },
		{ "IND2", ind2_instrs, NumElm(ind2_instrs), 0, &opcode_list[72], false },
		{ "INDM", indm_instrs, NumElm(indm_instrs), 0, &opcode_list[73], false },
		{ "INI2", ini2_instrs, NumElm(ini2_instrs), 0, &opcode_list[74], false },
		{ "INIM", inim_instrs, NumElm(inim_instrs), 0, &opcode_list[75], false },
		{ "OTDM", otdm_instrs, NumElm(otdm_instrs), 0, &opcode_list[76], false },
		{ "OTIM", otim_instrs, NumElm(otim_instrs), 0, &opcode_list[77], false },
		{ "OUT0", out0_instrs, NumElm(out0_instrs), 0, &opcode_list[78], false },
		{ "IN0", in0_instrs, NumElm(in0_instrs), 0, &opcode_list[79], false },
		{ "SLP", slp_instrs, NumElm(slp_instrs), 0, &opcode_list[80], false },
		{ "IND2R", ind2r_instrs, NumElm(ind2r_instrs), 0, &opcode_list[81], false },
		{ "INDMR", indmr_instrs, NumElm(indmr_instrs), 0, &opcode_list[82], false },
		{ "INDRX", indrx_instrs, NumElm(indrx_instrs), 0, &opcode_list[83], false },
		{ "INI2R", ini2r_instrs, NumElm(ini2r_instrs), 0, &opcode_list[84], false },
		{ "INIMR", inimr_instrs, NumElm(inimr_instrs), 0, &opcode_list[85], false },
		{ "INIRX", inirx_instrs, NumElm(inirx_instrs), 0, &opcode_list[86], false },
		{ "OTD2R", otd2r_instrs, NumElm(otd2r_instrs), 0, &opcode_list[87], false },
		{ "OTDMR", otdmr_instrs, NumElm(otdmr_instrs), 0, &opcode_list[88], false },
		{ "OTDRX", otdrx_instrs, NumElm(otdrx_instrs), 0, &opcode_list[89], false },
		{ "OTI2R", oti2r_instrs, NumElm(oti2r_instrs), 0, &opcode_list[90], false },
		{ "OTIMR", otimr_instrs, NumElm(otimr_instrs), 0, &opcode_list[91], false },
		{ "OTIRX", otirx_instrs, NumElm(otirx_instrs), 0, &opcode_list[92], false },
		{ "OUTD2", outd2_instrs, NumElm(outd2_instrs), 0, &opcode_list[93], false },
		{ "OUTI2", outi2_instrs, NumElm(outi2_instrs), 0, &opcode_list[94], false },
		{ "RSMIX", rsmix_instrs, NumElm(rsmix_instrs), 0, &opcode_list[95], false },
		{ "STMIX", stmix_instrs, NumElm(stmix_instrs), 0, &opcode_list[96], false },
		{ "TSTIO", tstio_instrs, NumElm(tstio_instrs), 0, NULL, false },
};
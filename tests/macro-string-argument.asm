; Test macro string argument handling
; CHECK: 74657374 00
#define string(value) .db value,0
string("test")

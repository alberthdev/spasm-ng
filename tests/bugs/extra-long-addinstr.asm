; Test for correct error handling on long (but invalid)
; .addinstr arguments
; CHECK-ERR: 126
.addinstr 0 0 0000000000000000000000000000

; Test error handling for non-existent label
; CHECK-NFERR: 106
; CHECK: C3 0E 00 C3 00 00 00 00 00 00 00 00 00 00
start:
    jp end
    jp doesntexist
    .fill 8
end:

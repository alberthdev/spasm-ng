; Test error handling for too far relative jump
; CHECK-ERR: 120
start:
    jr end
    .fill 128
end:

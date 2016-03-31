; Test jr relative offsets for 24-bit eZ80 code as fixed by PR #22.
;
; RUN-ARGS: -E
.assume ADL=1

; CHECK: 5B 18 FD
    jr.lil $


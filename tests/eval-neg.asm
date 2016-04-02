; Test using an eval'd negative number.
#define test eval(-1)
; CHECK: FF
.db test

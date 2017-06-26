; Test large 32-bit unsigned values don't trigger overflow error.
#macro dd(value)
	.db value & $ff
	.dl value >> 8
#endmacro
#define .dd dd(
.dd 1 << 31
.dd -1 << 31
.dd $ffffffff
; CHECK: 00000080 00000080 FFFFFFFF

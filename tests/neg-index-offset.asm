; Test negative offsets on index registers
; CHECK: DD77FF FD7E80 DD7740 FD7E00
	ld	( ix - 1 ), a
	ld	a, ( iy - 128 )
	ld	( ix + 64 ) , a
	ld	a, ( iy )

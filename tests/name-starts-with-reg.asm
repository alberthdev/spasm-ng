; Test names that start with ix or iy
; CHECK: 323412 3A7856
ixtest = $1234
iytest = $5678
	ld	(ixtest), a
	ld	a, (iytest)

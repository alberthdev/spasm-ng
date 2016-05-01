; Test ez80 undoc insts.
; RUN-ARGS: -E
; CHECK: ED3012 ED3034  ED70 ED70  ED70 ED70

	in0	f, (12h)
	in0	(34h)

	in	f, (bc)
	in	(bc)

	in	f, (c)
	in	(c)

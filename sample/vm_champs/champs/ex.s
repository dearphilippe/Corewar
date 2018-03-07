.name "zork"
.comment "just a basic living prog"

l2: sti	r1,%:live,%0
	and	r1,%0,r1
live:	live	%:l2
	zjmp #	%9
	add		r1,r2,r3

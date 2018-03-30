.name    "kratos"
.comment "Foul Beasts!"
.extend

l1:	live	%1
	ld	%:l1 - :l2, r2
l3:	ldi	%:l2, r2, r4
live:	zjmp	%:l1 - 100
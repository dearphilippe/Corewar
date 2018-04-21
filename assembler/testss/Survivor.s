.name"⌛".comment"Invincible"
	live %1
	fork %:f1
	zjmp %:j1
f1:	ld -5,r2
	zjmp %:run
j1: run: xorr 0,r0,r0
l1:	str 2,1
	live %1
	zjmp %:l1

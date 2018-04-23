# comment
# comment
.name"Testing"
.comment"Invincible"
	live %1
	fork %:f1
	zjmp %:f1
f1:	ld -5,r2
	zjmp %:run
	live %1
	zjmp %:f1

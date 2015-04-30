.text
.global _start
_start:
	BL main
	
_loop:
	B _loop

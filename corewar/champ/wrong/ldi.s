.name "ldi"
.comment "gnar"

# 	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},

 ldi		r2, %10, r3
 zjmp	%-10
 st		r3, 500
 ldi		r2, %0, r3
 zjmp	%-10
 ldi		r2, %512, r3
 zjmp	%-10
 st		r3, 500
 ldi		r3, r2, r3
 st		r3, 500
 ldi		%0, %0, r3
 zjmp	%-10
 ldi		%-2000, %-4000, r3
 zjmp	%-10
 st		r3, 500
 ldi		%2000, r1, r3
 st		r3, 500
 ldi		-2000, %-4000, r3
 zjmp	%-10
 st		r3, 500
 ldi		%1000, r1, r3
 st		r3, 500
 ldi		0, %0, r3
 zjmp	%-10
 st		r3, 500

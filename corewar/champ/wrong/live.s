	.name "mon cul"
	.comment "mon zbi"

	live %1
	ld %0, r2
	zjmp %-1 # jump
	ld 0, r2
	zjmp %-5 # no jump
	ld 1, r2
	zjmp %-5 # no jump
	ld %57672192, r2
	zjmp %-5 # no jump
	st r2, 0
	zjmp %-5 # no jump
	st r2, 8
	ld %500, r2
	zjmp %-5 # no jump
	st r2, 500
	ld %0, r2
	live %1
	zjmp %-5 # jump

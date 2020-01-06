.name "sti"
.comment "coucou"

 ld		150, r3
 sti	r1, %0, %0 # ok ( ! verifier le carry ! )
 sti	r1, 100, %100 # ok
 sti	r1, 100, %1 # ok
 sti	r1, 10, %0 # ok
 sti	r1, 0, %0 # ok
 sti	r1, 0, %1 # ok
 sti	r1, 0, %10 # ok
 sti	r1, 0, %100 # ok
 sti	r1, 100, %0 # ok
 sti	r1, 10, %0 # ok
 sti	r1, 0, %0 # ok
 sti	r1, r3, %15 # ok
 sti	r1, %20, %15 # ok
 sti	r1, %20, r1 # OK
 sti	r1, -10, %-50 # faux
 sti	r1, -20, r1 # ok
 sti	r1, r1, r3 # ok

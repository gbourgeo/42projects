#deassembler par msa 1.8, made by joe
.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

	 fork  %0 	         		# 3,0,281
	 ld    %-272,r3           		# 7,3,278
	 live  %0                 		# 5,10,271
	 fork  %1       	   		# 3,15,266
	 ld    %-272,r3           		# 7,18,263
	 fork  %2          			# 3,25,256
	 ld    %0,r2              		# 7,28,253
	 ld    %0,r4              		# 7,35,246
	 zjmp  %3          			# 3,42,239

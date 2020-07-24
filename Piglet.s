.name "Piglet (~* (o o) *~)"
.comment "

        Hru
    Hru     Hru
        Hru
                ,-,------,
              _ \(\(_,--'
   hru   <'--'\>/(/(__
         /. .  '  '   \
        ('')  ,        @
         '-._,        /
            )-)_/--( >
           ''''  ''''
    "

next: live %-1
live %-2
live %-3
live %-4
lfork %-5000 

loop:	add	r3, r4, r3
	zjmp	%:next
	xor	r5, r5, r5
	zjmp	%:loop

st	r1, 1383
	st	r1, 50
	st	r1, 100
	st	r1, 2000
	st	r1, 2569
	st	r1, 2273


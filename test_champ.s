.name       "Batman"
.comment    "This city needs me"

loop:
        sti r4,%:live,%1
live:
        live %0
        ld %0, r4
        zjmp %:loop

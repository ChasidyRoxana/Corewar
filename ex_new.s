.name "zork.lll"
.comment "just a basic living prog"

live %1
sti r1, %20, %9
and r1, %-12, r1
ld 5, r1
live %-21
zjmp %-5

This program unrolls a section of sample code by a user-specified number of times; it additionally, provides the ability to minimize the number of registers used through register reuse and minimize the number of clock cycles needed through scheduling. The unrolled code can be printed to console or file.

The program is invoked using the following command and arguments:

ECE422_Project2 [kVal] [rFlag] [sFlag] [outFile]

[kVal]
Required. Describes the number of times the loop is unrolled. Must be an integer divider of 120.

[rFlag]
Required. Flag used to determine whether registers can be reused or not. For a zero value, the code is unrolled such that the destination of the LD instruction and the destination of the ADD instruction are different. For a non-zero value, the code is unrolled such that the destination of the LD instruction and the destination of the ADD instruction are the same.

[sFlag]
Required. Flag used to determine whether the code should be scheduled or not. For a zero value, the code is unrolled but is not scheduled. For a non-zero value, the code is unrolled and is scheduled.

[outFile]
Optional. When not included, the code is unrolled and is printed to the console. When included, the code is unrolled and is printed to the file with the given filename.

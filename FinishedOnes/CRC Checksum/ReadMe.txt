
	CRC is a algorithm that is used to generate a checksum for a message (block of bits), using a generator key that will be provided.
	This checksum is then added to the message and transmitted. CRC is used to detect any error that might have occured to the 
	message during transit, by means of the check sum

	The generator algorithm follows as :
	1. get generator (G) and message (M)
	2. calculate their degrees a and b respectively
	3. left shift M by a
	4. perform modulo-2 division to this result and obtain remainder which is the check sum
	5. add the checksum to the message and transmit

	The checker algorithm follows as :
	1. get transmitted message (M)
	2. perform modulo-2 division and find remainder
	3. if rem = 0 no error else error

	eg:
	G = 1011
	M = 10101010
	then output will be
	10101010010

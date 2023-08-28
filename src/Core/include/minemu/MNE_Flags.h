#ifndef MNE_FLAGS_H
#define MNE_FLAGS_H

#define MNE_HEX_DUMP_FILE_FLAG        0x02
#define MNE_DONT_DISPOSE_BUFFER_FLAG  0x04
#define MNE_TEST_FLAG(v,f) (v >> f-1) & 0x01

#endif
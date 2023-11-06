#ifndef HAMPOD_PACKET
#define HAMPOD_PACKET

typedef enum {
    KEYPAD,
    AUDIO,
    SERIAL,
    CONFIG
} Packet_type;

typedef struct Inst_packet {
    Packet_type type;
    unsigned short data_len;
    unsigned char *data;
} Inst_packet;

Inst_packet* create_inst_packet(Packet_type new_type, unsigned short new_len, unsigned char *new_data);
void destroy_inst_packet(Inst_packet** packet);

#endif

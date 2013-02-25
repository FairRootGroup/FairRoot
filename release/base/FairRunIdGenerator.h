#ifndef FAIRRUNIDGENERATOR_H
#define FAIRRUNIDGENERATOR_H


typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned char      uuid_t[16];

class FairRunIdGenerator
{
    struct uuid {
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_hi_and_version;
      uint16_t clock_seq;
      uint8_t node[6];
    };
    int get_random_fd(void);
    void get_random_bytes(void*, int);
    int get_node_id(unsigned char*);
    int get_clock(uint32_t*, uint32_t*, uint16_t*);
    void uuid_generate_time(uuid_t);
    void uuid_generate_random(uuid_t);
    void uuid_generate(uuid_t);
    void uuid_pack(const struct uuid*, uuid_t);
    void uuid_unpack(const uuid_t, struct uuid*);
  public:
    FairRunIdGenerator() {}
    ~FairRunIdGenerator() {}
    unsigned int generateId(void);
};

#endif

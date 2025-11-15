#ifndef _PKT_DUMP_H_
#define _PKT_DUMP_H_

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <rte_mbuf.h>

#define DUMP_PCAP

void open_pcap_file(const char *filename);
void dump_packet(struct rte_mbuf *pkt);

#endif

#include "gfx/gfx.h"
#include "general/general.h"
#include "maths/maths.h"

#include <nng/nng.h>
#include <nng/transport/tcp/tcp.h>
#include <nng/protocol/pair0/pair.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

#include <stdlib.h>
#include <stdio.h>

#define NET_NOERROR 0
#define NET_ERROR 1

struct net_msg
{
	int func_return;
	char *msg;
	size_t msg_size;
};


int net_host_pair(int max_wait_ms);
int net_connect_pair(int port, int max_wait_ms);

int net_send_msg(char *msg);
struct net_msg net_recv_msg();

void net_test_listen();
void net_test_send(int port);
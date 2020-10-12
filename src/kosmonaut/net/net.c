#include "gfx/gfx.h"
#include "gfx/ui/ui.h"
#include "general/general.h"
#include "maths/maths.h"

#include <nng/nng.h>
#include <nng/transport/tcp/tcp.h>
#include <nng/protocol/pair0/pair.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>

#include <stdlib.h>
#include <stdio.h>

void net_test_listen()
{

	nng_socket sock;
	nng_listener lp;

	int return_val;

	if(nng_pull0_open(&sock)==0)
	{
		printf("Socket created\n");
	}
	else
	{
		printf("Socket couldn't be created\n");
	}

	switch(nng_listen(sock, "tcp://127.0.0.1:0", &lp, 0))
	{
		case 0:
			printf("Is listening...\n");
			break;

		case NNG_ENOMEM:
			printf("Not enough memory\n");

		case NNG_EADDRINUSE:
			printf("URL is already in use\n");
			break;

		case NNG_EADDRINVAL:
			printf("INVALID URL\n");
			break;

		case NNG_ECLOSED:
			printf("Socket is not open\n");
			break;

		case NNG_EINVAL:
			printf("Invalid flags or URL\n");
			break;

		default:
			printf("Can't listen\n\n");
			break;

	}

	int rv;
	nng_listener_getopt_int(lp, NNG_OPT_TCP_BOUND_PORT, &rv);
	printf("Port: %i\n", rv);

	while(1)
	{
		char *buf=NULL;
		size_t sz;
		if(nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)!=0)
		{
			printf("error while receiving a message\n");
			break;
		}

		if(buf!=NULL)
		{
			printf("RECEIVED: %s\n", buf);
			nng_free(buf, sz);
			break;
		}
		nng_free(buf, sz);
	}

}

void net_test_send()
{
	char *msg="HALLO ICH BIN EINE NACHRICHT\n";
	int sz_msg=strlen(msg)+1;

	nng_socket sock;
	nng_dialer dp;

	if(nng_push0_open(&sock)==0)
	{
		printf("Socket created\n");
	}
	else
	{
		printf("Socket couldn't be created\n");
	}

	switch(nng_dial(sock, "tcp://127.0.0.1:35753", &dp, 0))
	{
		case 0:
			printf("Has dialed in...\n");
			break;

		case NNG_EADDRINVAL:
			printf("Invalid URL\n");
			break;

		case NNG_ECLOSED:
			printf("Socket is not open\n");
			break;

		case NNG_ECONNREFUSED:
			printf("Peer declined connection\n");
			break;

		case NNG_ECONNRESET:
			printf("Peer reset the connection\n");
			break;

		case NNG_EINVAL:
			printf("Invalid flags\n");
			break;

		case NNG_ENOMEM:
			printf("Insufficient memory\n");
			break;

		case NNG_EPEERAUTH:
			printf("Authentication or authorization failed\n");
			break;

		case NNG_EPROTO:
			printf("Protocol error occured\n");
			break;

		case NNG_EUNREACHABLE:
			printf("Remote adress is not reachable\n");
			break;

		default:
			printf("Couldn't dial in\n");
			break;
	}

	if(nng_send(sock, msg, sz_msg, 0)!=0)
	{
		printf("error while sending a message\n");
	}
}
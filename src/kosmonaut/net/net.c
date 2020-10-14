#include "net/net.h"
#include "gfx/gfx.h"
#include "gfx/ui/ui.h"
#include "general/general.h"
#include "maths/maths.h"

#include <nng/nng.h>
#include <nng/transport/tcp/tcp.h>
#include <nng/protocol/pair0/pair.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/protocol/bus0/bus.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HOST 2
#define CLIENT 1

int host_client_state=0;

int send_count=0;
int recv_count=0;

/*host variables*/
nng_socket sock_host;
nng_listener lp;

/*client variables*/
nng_socket sock_client;
nng_dialer dp;

int net_host_pair(int max_wait_ms)
{
	host_client_state=HOST;

	int func_return=NET_NOERROR;

	if(nng_pair0_open(&sock_host)!=0)
	{
		engine_log("Socket couldn't be created.\n Can't host\n");
		func_return=NET_ERROR;
		return func_return;
	}

	switch(nng_listen(sock_host, "tcp://127.0.0.1:0", &lp, 0))
	{
		case 0:
			engine_log("Is listening...\n");
			break;

		case NNG_ENOMEM:
			engine_log("Not enough memory\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EADDRINUSE:
			engine_log("URL is already in use\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EADDRINVAL:
			engine_log("INVALID URL\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_ECLOSED:
			engine_log("Socket is not open\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EINVAL:
			engine_log("Invalid flags or URL\n");
			func_return=NET_ERROR;
			return func_return;

		default:
			engine_log("Can't listen\n\n");
			func_return=NET_ERROR;
			return func_return;

	}

	/*getting the port that was given to the listener*/
	int rv;
	nng_listener_getopt_int(lp, NNG_OPT_TCP_BOUND_PORT, &rv);
	engine_log("Port: %i\n", rv);
	printf("Port: %i\n", rv);

	nng_socket_set_ms(sock_host, NNG_OPT_RECVTIMEO, max_wait_ms);
	nng_socket_set_ms(sock_host, NNG_OPT_SENDTIMEO, max_wait_ms);

	/*waiting for handshake*/
	engine_log("Waiting for client...\n");
	printf("Waiting for client...\n");

	int count=60;
	char *msg_handshake=NULL;
	size_t sz_msg=0;

	while(count>0)
	{
		nng_recv(sock_host, &msg_handshake, &sz_msg, NNG_FLAG_ALLOC);
		SDL_Delay(1000);
		if(msg_handshake!=NULL)
		{
			printf("%s\nSize: %i\n", msg_handshake, (int)sz_msg);
			if(strstr(msg_handshake,"ready")!=NULL)
			{
				break;
			}
		}
		nng_free(msg_handshake, sz_msg);
		count--;
	}

	return func_return;
}

int net_connect_pair(int port, int max_wait_ms)
{
	host_client_state=CLIENT;

	int func_return=NET_NOERROR;

	if(nng_pair0_open(&sock_client)==0)
	{
		engine_log("Socket created\n");
	}
	else
	{
		engine_log("Socket couldn't be created\n");
		func_return=NET_ERROR;
		return func_return;
	}

	char url[32]="tcp://127.0.0.1:";
	char str_buf[10];
	sprintf(str_buf, "%d", port);
	strcat(url, str_buf);

	switch(nng_dial(sock_client, url, &dp, 0))
	{
		case 0:
			engine_log("Has dialed in...\n");
			break;

		case NNG_EADDRINVAL:
			engine_log("Invalid URL\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_ECLOSED:
			engine_log("Socket is not open\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_ECONNREFUSED:
			engine_log("Peer declined connection\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_ECONNRESET:
			engine_log("Peer reset the connection\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EINVAL:
			engine_log("Invalid flags\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_ENOMEM:
			engine_log("Insufficient memory\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EPEERAUTH:
			engine_log("Authentication or authorization failed\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EPROTO:
			engine_log("Protocol error occured\n");
			func_return=NET_ERROR;
			return func_return;

		case NNG_EUNREACHABLE:
			engine_log("Remote adress is not reachable\n");
			func_return=NET_ERROR;
			return func_return;

		default:
			engine_log("Couldn't dial in\n");
			func_return=NET_ERROR;
			return func_return;
	}

	nng_socket_set_ms(sock_client, NNG_OPT_RECVTIMEO, max_wait_ms);
	nng_socket_set_ms(sock_client, NNG_OPT_SENDTIMEO, max_wait_ms);

	/*sending handshake*/
	char msg_handshake[16]="ready";
	nng_send(sock_client, msg_handshake, sizeof(msg_handshake), NNG_FLAG_NONBLOCK);

	return func_return;
}

struct net_msg net_recv_msg()
{
	struct net_msg net_msg;
	net_msg.msg=NULL;

	if(host_client_state==HOST)
	{
		if(nng_recv(sock_host, &net_msg.msg, &net_msg.msg_size, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK)!=0)
		{
			net_msg.func_return=NET_ERROR;
		}
	}
	if(host_client_state==CLIENT)
	{
		if(nng_recv(sock_client, &net_msg.msg, &net_msg.msg_size, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK)!=0)
		{
			net_msg.func_return=NET_ERROR;
		}
	}

	return net_msg;
}

int net_send_msg(char *msg)
{
	int func_return=NET_NOERROR;
	size_t sz_msg=strlen(msg);


	if(host_client_state==HOST)
	{
		int rv=0;
		rv=nng_send(sock_host, msg, sz_msg, NNG_FLAG_NONBLOCK);
		if(rv==NNG_ETIMEDOUT)
		{
			engine_log("HOST SOCKET: TIME OUT\n");
		}
		if(rv!=0)
		{
			func_return=NET_ERROR;
		}	
	}

	if(host_client_state==CLIENT)
	{
		if(nng_send(sock_client, msg, sz_msg, NNG_FLAG_NONBLOCK)!=0)
		{
			func_return=NET_ERROR;
		}	
	}


	return func_return;
}

void net_sync()
{
		char msg_handshake[16]="ready";

		char *msg_handshake_recv=NULL;
		size_t sz_msg=0;

	if(host_client_state==HOST)
	{
		nng_send(sock_host, msg_handshake, sizeof(msg_handshake), NNG_FLAG_NONBLOCK);
		while(1)
		{
			nng_recv(sock_host, &msg_handshake_recv, &sz_msg, NNG_FLAG_ALLOC);
			if(msg_handshake!=NULL)
			{
				if(strstr(msg_handshake,"ready")!=NULL)
				{
					nng_free(msg_handshake_recv, sz_msg);
					break;
				}
			}
			nng_free(msg_handshake_recv, sz_msg);
		}		
	}

	if(host_client_state==CLIENT)
	{
		nng_send(sock_client, msg_handshake, sizeof(msg_handshake), NNG_FLAG_NONBLOCK);
		while(1)
		{
			nng_recv(sock_client, &msg_handshake_recv, &sz_msg, NNG_FLAG_ALLOC);
			if(msg_handshake!=NULL)
			{
				if(strstr(msg_handshake,"ready")!=NULL)
				{
					nng_free(msg_handshake_recv, sz_msg);
					break;
				}
			}
			nng_free(msg_handshake_recv, sz_msg);
		}	
	}
}
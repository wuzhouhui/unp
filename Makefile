CC	= gcc 
OPT	= -I./ -g -pthread

# when new executables created, added to EXECS, needed by 'make clean'
EXECS	= daytimetcpcli daytimetcpcliv6 daytimetcpserv 1.3 1.4 1.5	\
	  daytimetcpsrv1 4.2 4.4 4.5 tcpserv01 tcpcli01	tcpcli04	\
	  tcpserv04 5.6 tcpservselect01 tcpservpoll01 checkopts		\
	  7.1 udpserv01 udpcli01 udpcli09 udpservselect01 sctpserv01	\
	  sctpclient01 hostent daytimetcpcli1 daytimetcpserv1		\
	  daytimetcpserv2 daytimeudpcli1 daytimeudpsrv2 daytimetcpsrv2	\
	  daytimetcpsrv3 unixbind unixstrserv01 unixstrcli01 		\
	  unixdgserv01 unixdgcli01 mycat openfile web tcpcli03		\
	  daytimetcpcli01 a.out prifinfo prmac getrt.c checkudpsum

DEPS	= config.h unp.h unpthread.h
WRAPERS	= wraplib.o wrappthread.o wrapsock.o wrapstdio.o wrapunix.o

.PHONY: clean all git

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

all: 
	make 1-5
	make 1-6
	make 1-9
	make 1.3
	make 1.4
	make 1.5
	make 4-11
	make 4.2
	make 4.4
	make 4.5
	make 5-2
	make 5-4
	make 5-9
	make 5-12
	make 5.1
	make 5.6
	make 6-9
	make 6-13
	make 6-22
	make 6-26
#	make 7-4
	make 7.1
	make 8-3
	make 8-7
	make 8-23
	make 8-24
	make 10-2
	make 10-3
	make 11-3
	make 11-4
	make 11-13
	make 11-14
	make 11-16
	make 11-19
	make 13-5
	make 13-12
	make 15-2
	make 15-3
	make 15-4
	make 15-5
	make 15-6
	make 15-9
	make 15-12
	make 16-15
	make 16-21
	make 17-6
#	make 17-13
#	make 18-14

1-5: daytimetcpcli.o  error.o
	${CC} ${OPT} error.o daytimetcpcli.o  -o daytimetcpcli

1-6: daytimetcpcliv6.o  error.o
	${CC} ${OPT} error.o daytimetcpcliv6.o  -o daytimetcpcliv6

1-9: daytimetcpserv.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o daytimetcpserv.o  ${WRAPERS} -o		\
		daytimetcpserv

1.3: 1.3.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o 1.3.o  ${WRAPERS} -o 1.3

1.4: 1.4.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o 1.4.o  ${WRAPERS} -o 1.4

1.5: 1.5.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o 1.5.o  ${WRAPERS} -o 1.5

4-11: daytimetcpsrv1.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o daytimetcpsrv1.o  ${WRAPERS} -o 		\
		daytimetcpsrv1

4.2: 4.2.o  error.o sock_ntop.o
	${CC} ${OPT} error.o 4.2.o  sock_ntop.o -o 4.2

4.4: 4.4.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o 4.4.o  ${WRAPERS} -o 4.4

4.5: 4.5.o  error.o ${WRAPERS}
	${CC} ${OPT} error.o 4.5.o  ${WRAPERS} -o 4.5

5-2:  ${WRAPERS} error.o tcpserv01.o str_echo.o writen.o
	${CC} ${OPT} error.o ${WRAPERS}   tcpserv01.o 	str_echo.o 	\
		writen.o -o tcpserv01

5-4:  ${WRAPERS} error.o tcpcli01.o writen.o readline.o	\
	str_cli.o
	${CC} ${OPT} error.o ${WRAPERS}  tcpcli01.o writen.o str_cli.o	\
		readline.o -o tcpcli01

5-9:  ${WRAPERS} error.o tcpcli04.o str_cli.o writen.o	\
	readline.o
	${CC} ${OPT} error.o ${WRAPERS}  tcpcli04.o str_cli.o		\
	writen.o readline.o -o tcpcli04	

5-12:  ${WRAPERS} error.o tcpserv04.o str_echo.o writen.o	\
	sigchldwaitpid.o signal.o
	${CC} ${OPT} error.o ${WRAPERS}   tcpserv04.o 	str_echo.o 	\
		writen.o sigchldwaitpid.o signal.o -o tcpserv04

5.1:  ${WRAPERS} error.o tcpserv01.o str_echo.o writen.o	\
	tcpcli01.o readline.o
	make 5-2
	make 5-4

5.6:  ${WRAPERS} error.o 5.6.o daytimetcpserv.o signal.o
	${CC} ${OPT} error.o 5.6.o ${WRAPERS}  signal.o -o 5.6
	make 1-9

6-9:  ${WRAPERS} error.o tcpcli01.o writen.o readline.o	\
	strcliselect01.o
	${CC} ${OPT} error.o ${WRAPERS}  tcpcli01.o writen.o 		\
		strcliselect01.o readline.o -o tcpcli01

6-13:  ${WRAPERS} error.o tcpcli01.o writen.o readline.o	\
	strcliselect02.o
	${CC} ${OPT} error.o ${WRAPERS}  tcpcli01.o writen.o 		\
		strcliselect02.o readline.o -o tcpcli01

6-22:  ${WRAPERS} error.o str_echo.o writen.o		\
	sigchldwaitpid.o signal.o tcpservselect01.o
	${CC} ${OPT} error.o ${WRAPERS}  str_echo.o tcpservselect01.o	\
		writen.o sigchldwaitpid.o signal.o -o tcpservselect01

6-26:  ${WRAPERS} error.o str_echo.o writen.o		\
	sigchldwaitpid.o signal.o tcpservpoll01.o
	${CC} ${OPT} error.o ${WRAPERS}  str_echo.o tcpservpoll01.o	\
		writen.o sigchldwaitpid.o signal.o -o tcpservpoll01

# 7-4 cannot be compiled because it is uncomplemeted.
#7-4:  ${WRAPERS} error.o checkopts.o
#	${CC} ${OPT} error.o ${WRAPERS}  checkopts.o

7.1:  error.o 7.1.o
	${CC} ${OPT} error.o  7.1.o -o 7.1

8-3:  error.o udpserv01.o dg_echo.o
	${CC} ${OPT} error.o  udpserv01.o dg_echo.o -o udpserv01

8-7:  error.o udpcli01.o dg_cli.o
	${CC} ${OPT} error.o  udpcli01.o dg_cli.o -o udpcli01

8-23:  error.o udpcli09.o sock_ntop.o
	${CC} ${OPT} error.o  udpcli09.o sock_ntop.o -o udpcli09

8-24:  error.o udpservselect01.o str_echo.o ${WRAPERS}	\
	writen.o
	${CC} ${OPT} error.o  udpservselect01.o str_echo.o ${WRAPERS}	\
		writen.o -o udpservselect01

10-2:  error.o sctpserv01.o sctp_getnostrm.o 		\
	sctp_addr_to_associd.o 
	${CC} ${OPT} error.o  sctpserv01.o sctp_getnostrm.o 		\
		sctp_addr_to_associd.o -lsctp -o sctpserv01

10-3:  error.o sctpclient01.o sctpstr_cli.o			\
	sctpstr_cli_echoall.o
	${CC} ${OPT} error.o  sctpclient01.o sctpstr_cli.o 		\
		sctpstr_cli_echoall.o -lsctp -o sctpclient01

11-3:  error.o hostent.o
	${CC} ${OPT} error.o  hostent.o -o hostent

11-4:  error.o daytimetcpcli01.o sock_ntop.o
	${CC} ${OPT} error.o  daytimetcpcli01.o sock_ntop.o 		\
		-o daytimetcpcli01

11-13:  error.o daytimetcpserv1.o tcp_listen.o sock_ntop.o
	${CC} ${OPT} error.o  daytimetcpserv1.o tcp_listen.o 		\
		sock_ntop.o -o daytimetcpserv1

11-14:  error.o daytimetcpserv2.o tcp_listen.o sock_ntop.o
	${CC} ${OPT} error.o  daytimetcpserv2.o tcp_listen.o 		\
		sock_ntop.o -o daytimetcpserv2

11-16:  error.o daytimeudpcli1.o udp_client.o 		\
	sock_ntop_host.o
	${CC} ${OPT} error.o  daytimeudpcli1.o udp_client.o 		\
		sock_ntop_host.o -o daytimeudpcli1

11-19:  error.o daytimeudpsrv2.o udp_server.o sock_ntop.o
	${CC} ${OPT} error.o  daytimeudpsrv2.o udp_server.o 		\
		sock_ntop.o -o daytimeudpsrv2

13-5:  error.o daytimetcpsrv2.o signal.o daemon_init.o	\
	tcp_listen.o
	${CC} ${OPT} error.o  daytimetcpsrv2.o signal.o daemon_init.o	\
		tcp_listen.o sock_ntop.o

13-12:  error.o daemon_inetd.o daytimetcpsrv3.o 		\
	sock_ntop.o
	${CC} ${OPT} error.o  daemon_inetd.o daytimetcpsrv3.o		\
		sock_ntop.o -o daytimetcpsrv3

15-2:  error.o unixbind.o
	${CC} ${OPT} error.o  unixbind.o -o unixbind

15-3:  error.o unixstrserv01.o signal.o str_echo.o
	${CC} ${OPT} error.o unixstrserv01.o signal.o str_echo.o  	\
		${WRAPERS} -o unixstrserv01

15-4:  error.o unixstrcli01.o str_cli.o ${WRAPERS}		\
	readline.o writen.o
	${CC} ${OPT} error.o unixstrcli01.o str_cli.o ${WRAPERS} 	\
		readline.o writen.o -o unixstrcli01

15-5:  error.o unixdgserv01.o dg_echo.o 
	${CC} ${OPT} error.o  unixdgserv01.o dg_echo.o -o unixdgserv01

15-6:  error.o unixdgcli01.o dg_cli.o
	${CC} ${OPT} error.o  unixdgcli01.o dg_cli.o -o unixdgcli01

15-9:  error.o mycat.o my_open.o read_fd.o
	${CC} ${OPT} error.o  mycat.o my_open.o read_fd.o -o mycat

15-12:  error.o openfile.o  write_fd.o
	${CC} ${OPT} error.o  openfile.o write_fd.o -o openfile

16-15:  error.o web.o write_get_cmd.o writen.o 	\
	home_page.o tcp_connect.o host_serv.o start_connect.o
	${CC} ${OPT} error.o web.o  writen.o write_get_cmd.o 		\
		home_page.o tcp_connect.o  host_serv.o start_connect.o	\
		-o web

16-21:  error.o tcpcli03.o web.h
	${CC} ${OPT} error.o  tcpcli03.o -o tcpcli03

17-6: prifinfo.o unpifi.h error.o get_ifi_info.o sock_ntop_host.o	\
	free_ifi_info.o
	${CC} ${OPT} prifinfo.o error.o get_ifi_info.o sock_ntop_host.o	\
		free_ifi_info.o -o prifinfo

17-13: prmac.o error.o get_ifi_info.o sock_ntop.o
	${CC} ${OPT} prmac.o error.o get_ifi_info.o sock_ntop.o		\
		-o prmac

#18-6: error.o getrt.o unproute.h 
#	${CC} ${OPT} error.o getrt.o 

#18-14: error.o checkudpsum.o 
#	${CC} ${OPT} error.o checkudpsum.o 

clean:
	rm -f *.o ${EXECS}

git:
	sed -i '/### Makefile ###/,$$$ d' .gitignore
	echo '### Makefile ###' >> .gitignore
	(for file in `ls`; do \
		if [ -f $$file ] && [ -x $$file ]; \
		then echo $$file >> .gitignore;	\
		fi \
	done)


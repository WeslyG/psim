from socket import socket, AF_UNIX, SOCK_DGRAM
import logging

socketAddr = '/var/ossec/queue/ossec/queue'


def socket_writer(system_type, msg):
    logging.debug('Sending {} to {} socket.'.format(msg, socketAddr))
    string = '1:{0}:{1}'.format(system_type, msg)
    sock = socket(AF_UNIX, SOCK_DGRAM)
    sock.connect(socketAddr)
    sock.send(string.encode())
    sock.close()

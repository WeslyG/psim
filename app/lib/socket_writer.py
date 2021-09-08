from socket import AF_UNIX, SOCK_DGRAM, socket

socketAddr = '/var/ossec/queue/ossec/queue'

def socket_writer(msg: str):
    string = '1:psim:{0}'.format(msg)
    sock = socket(AF_UNIX, SOCK_DGRAM)
    sock.connect(socketAddr)
    sock.send(string.encode())
    sock.close()

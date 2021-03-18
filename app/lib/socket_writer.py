from socket import socket, AF_UNIX, SOCK_DGRAM
from aiohttp import web

socketAddr = '/var/ossec/queue/ossec/queue'
routes = web.RouteTableDef()


@routes.get('/')
async def hello(request):
    return web.json_response({"message": "ok"})


@routes.post('/write')
async def write(request):
    data = await request.json()
    if (data['system_type'] and data['message']):
        socket_writer(system_type=data['system_type'], msg=data['message'])
        return web.json_response({"message": "ok"})
    else:
        return web.json_response({"message": "data not valid"}, status=400)


def socket_writer(system_type, msg):
    string = '1:{0}:{1}'.format(system_type, msg)
    sock = socket(AF_UNIX, SOCK_DGRAM)
    sock.connect(socketAddr)
    sock.send(string.encode())
    sock.close()


app = web.Application()
app.add_routes(routes)
web.run_app(app, port=9000)

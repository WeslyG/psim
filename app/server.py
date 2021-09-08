import json

from aiohttp import web
from lib import socket_writer

routes = web.RouteTableDef()


@routes.get('/')
async def hello():
    return web.json_response({"message": "ok"})


@routes.get('/write')
async def zzz():
    return web.json_response({"message": "for send data, use POST request"})


@routes.post('/write')
async def write(request):
    data = await request.json()
    socket_writer(json.dumps(data))
    return web.json_response({"message": "ok"})


app = web.Application()
app.add_routes(routes)
web.run_app(app, port=9000)

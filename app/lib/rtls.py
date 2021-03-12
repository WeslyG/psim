#!/bin/python3

import random
import json
from lib.lib import get_current_time, get_uuid

names = ['BLINK', 'CLE', 'CS_RX']

def message(user_id: str, status: str):
    objectId = get_uuid()
    return str(json.dumps({
        "userId": user_id,
        "system": "rtls",
        "status": random.choice(names),
        "date": get_current_time(),
        "severity": status,
        "actorId": objectId,
        "zoneX": random.uniform(1.1, 2.6),
        "zoneY": random.uniform(4.2, 8.8),
        "zoneZ": random.uniform(3.2, 4.8),
    }))


def rtls_ok(id: str):
    return message(id, 'INFO')


def rtls_alarm(id: str):
    return message(id, 'ALARM')

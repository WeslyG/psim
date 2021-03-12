#!/bin/python3

import json
import random
from lib.lib import get_current_time, get_uuid


def message(user_id: str, status: str):
    objectId = get_uuid()
    return str(json.dumps({
        "userId": user_id,
        "date": get_current_time(),
        "system": "camera",
        "severity": status,
        "message": f'{status} message in object = {objectId} for user = {user_id}',
        "cameraId": objectId,
        "zoneX": random.randint(300, 900),
        "zoneY": random.randint(200, 1600),
    }))


def camera_ok(id: str):
    return message(id, 'INFO')


def camera_alarm(id: str):
    return message(id, 'ALARM')

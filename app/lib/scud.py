#!/bin/python3

import json
from lib.lib import get_current_time, get_uuid


def message(user_id: str, status: str):
    objectId = get_uuid()
    return str(json.dumps({
        "userId": user_id,
        "date": get_current_time(),
        "severity": status,
        "system": "scud",
        "message": f'{status} message in object = {objectId} for user = {user_id}',
        "objectId": objectId
    }))


def scud_ok(id: str):
    return message(id, 'INFO')


def scud_alarm(id: str):
    return message(id, 'ALARM')

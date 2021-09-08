#!/bin/python3

import logging
import random
import threading
import time

from lib.camera import camera_alarm, camera_ok
from lib.lib import generage_user
from lib.rtls import rtls_alarm, rtls_ok
from lib.scud import scud_alarm, scud_ok
from lib.socket import socket_writer

USER_COUNT = 12
THREAD_SLEEP = 3
FAILE_EATCH_OF = 20
THREAD_COUNT = 5

logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.StreamHandler()
    ])


def generate_user_list(len: int):
    user_list = []
    for _ in range(len):
        user_list.append(generage_user())
    return user_list


def runner(userList, sleep_time, range_int, runner_def_ok, runner_def_err, index_name):
    for i in range(0, range_int):
        user = random.choice(userList)
        if i == range_int - 1:
            body = runner_def_err(user['id'])
            socket_writer(system_type=index_name, msg=body)
            time.sleep(sleep_time)
        else:
            body = runner_def_ok(user['id'])
            socket_writer(system_type=index_name, msg=body)
            time.sleep(sleep_time)


def main():
    userList = generate_user_list(USER_COUNT)
    logging.info("User list generated")
    while True:
        for i in range(THREAD_COUNT):
            scud_thread = threading.Thread(target=runner, args=(userList, THREAD_SLEEP, FAILE_EATCH_OF, scud_ok, scud_alarm, 'siem-scud'))
            camera_thread = threading.Thread(target=runner, args=(userList, THREAD_SLEEP, FAILE_EATCH_OF, camera_ok, camera_alarm, 'siem-camera'))
            rtls_thread = threading.Thread(target=runner, args=(userList, THREAD_SLEEP, FAILE_EATCH_OF, rtls_ok, rtls_alarm, 'siem-rtls'))
            scud_thread.start()
            camera_thread.start()
            rtls_thread.start()
        time.sleep(100)


if __name__ == '__main__':
    logging.info("App started")
    main()

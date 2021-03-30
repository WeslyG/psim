from locust import HttpUser, task
import random
import json
import uuid
import datetime
import string


def get_current_time():
    return datetime.datetime.now().isoformat()


def get_uuid():
    return str(uuid.uuid4())


def get_random_string(N):
    return ''.join(random.choices(string.ascii_uppercase + string.digits, k=N))


list = ['camera', 'scud', 'rtls', 'server', 'gps']


def short_message_builder_success():
    return json.dumps({
        "userId": get_uuid(),
        "date": get_current_time(),
        "system": random.choice(list),
        "severity": 'SUCCESS',
        "message": f'success message in object = {get_uuid()} for user = {get_uuid()}',
        "cameraId": get_uuid(),
        "zoneX": random.randint(300, 900),
        "zoneY": random.randint(200, 1600),
        "zoneZ": random.randint(5, 800),
    })


def short_message_builder_error():
    return json.dumps({
        "userId": get_uuid(),
        "date": get_current_time(),
        "system": random.choice(list),
        "severity": 'ERROR',
        "message": f'success message in object = {get_uuid()} for user = {get_uuid()}',
        "cameraId": get_uuid(),
        "zoneX": random.randint(300, 900),
        "zoneY": random.randint(200, 1600),
        "zoneZ": random.randint(5, 1600),
    })


def long_message_builder_success():
    return json.dumps({
        "userId": get_uuid(),
        "date": get_current_time(),
        "system": random.choice(list),
        "severity": 'ERROR',
        "message": f'success message in object = {get_uuid()} for user = {get_uuid()}',
        "cameraId": get_uuid(),
        "field1": get_random_string(25),
        "field3": get_random_string(12),
        "field4": get_random_string(30),
        "field5": get_random_string(40),
        "field6": get_random_string(100),
        "field7": get_random_string(10),
        "field8": get_random_string(6),
        "field9": get_random_string(20),
        "field10": get_random_string(15),
        "field11": get_random_string(15),
        "field12": get_random_string(30),
        "field13": get_random_string(40),
        "field14": get_random_string(25),
        "field15": get_random_string(25),
        "field16": get_random_string(16),
        "field17": get_random_string(8),
        "field18": get_random_string(10),
        "field19": get_random_string(25),
        "field20": get_random_string(25),
        "field21": get_random_string(25),
        "field22": get_random_string(20),
        "field23": get_random_string(20),
        "field24": get_random_string(20),
        "field25": get_random_string(2),
        "field26": get_random_string(250),
        "field27": get_random_string(30),
        "field28": get_random_string(14),
    })


def long_message_builder_error():
    return {

    }


class QuickstartUser(HttpUser):
    # wait_time = between(1, 2.5)

    # @task(3)
    # def broken_message(self):
    #     self.client.post('/write', json={
    #         "message": "test",
    #         "qwe": 12
    #     })

    # @task(3)
    # def hello(self):
    #     self.client.get('/')

    @task(5)
    def short_message_success(self):
        self.client.post('/write', json={
            "system_type": random.choice(list),
            "message": short_message_builder_success()
        })


    @task(5)
    def short_message_error(self):
        self.client.post('/write', json={
            "system_type": random.choice(list),
            "message": short_message_builder_error()
        })

    # @task()
    # def long_message_error(self):
    #     self.client.post('/write', json={
    #         "system_type": random.choice(list),
    #         "message": long_message_builder_error()
    #     })

    @task(3)
    def long_message_success(self):
        self.client.post('/write', json={
            "system_type": random.choice(list),
            "message": long_message_builder_success()
        })

    # @task(3)
    # def view_items(self):
    #     self.client.get("/_cluster/health", verify=False, headers={
    #       "authorization": "Basic YWRtaW46YWRtaW4="
    #     })


    # def on_start(self):
        # self.client.post("/", )
        # self.client.verify = False

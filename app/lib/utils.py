import random
import uuid
import datetime

names = ['Петя', 'Вася', 'Игорь', 'Коля']


def get_current_time():
    return datetime.datetime.now().isoformat()


def get_uuid():
    return str(uuid.uuid4())


def generage_user():
    return {
        'name': random.choice(names),
        'id':  get_uuid()
    }

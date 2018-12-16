#!/usr/bin/env python3

# stdlib
import configparser
import os.path

# project
from tool.utils import mkdirp


_CONFIG_PATH = '.aoc'
_CONFIG_FILE = os.path.join(_CONFIG_PATH, 'config.cfg')
_CONFIG_SECTION = 'preferences'


class Config(object):

    @staticmethod
    def load():
        config = configparser.ConfigParser()
        config[_CONFIG_SECTION] = {
            'username': '',
            'language': 'py',
        }
        config.read(_CONFIG_FILE)
        return Config(config[_CONFIG_SECTION]['username'], config[_CONFIG_SECTION]['language'])

    def __init__(self, user, language):
        self.user = user
        self.language = language

    def save(self):
        config = configparser.ConfigParser()
        config[_CONFIG_SECTION] = {
            'username': self.user,
            'language': self.language,
        }
        mkdirp(_CONFIG_PATH)
        with open(_CONFIG_FILE, 'w') as configfile:
            config.write(configfile)


CONFIG = Config.load()


def config(username, language):
    global CONFIG
    if not username:
        username = CONFIG.user
    if not language:
        username = CONFIG.language
    cc = Config(username, language)
    cc.save()
    CONFIG = cc

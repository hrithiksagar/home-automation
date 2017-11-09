import json

from typeguard import typechecked

from web.CorsHandler import CorsHandler
from web.security.secure import secure
from communication.actuator.AsyncActuatorCommands import AsyncActuatorCommands


class ApiActuatorHandler(CorsHandler):
    @typechecked()
    def initialize(self, async_actuator_commands: AsyncActuatorCommands):
        self.__async_actuator_commands = async_actuator_commands

    @secure
    def post(self):
        data = json.loads(self.request.body.decode("utf-8"))
        print(data, data['id'], data['value'])
        self.__async_actuator_commands.change_actuator(data['id'], data['value'])
        self.set_status(200)
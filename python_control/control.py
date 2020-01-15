# -*- coding: utf-8 -*-
import logging

class Control:

    def __init__(self,configfile):

        self.parseconfig(configfile)

        self.temp_min
        self.temp_max

        self.duty_min 
        self.duty_dic = self.get_prop_duty()
        self.curr_duty = self.duty_min
        self.duty_max = 100.0

        self.hysterie

        self.temp_file
        self.cpu_temp = 0
        self.cpu_temp_old = 0

        self.is_logging
        self.log_file

        if self.is_logging and log_file:
            self.set_logging()

    def parseconfig(self, configfile):
        f = open(configfile)
        configDic = eval(f.read())

        self.temp_min = configDic["temp_min"]
        self.temp_max = configDic["temp_max"]

        self.duty_min = configDic["duty_min"]

        self.hysterie = configDic["hysterie"]

        self.temp_file = configDic["temp_file"]

        self.is_logging = configDic["log"]
        self.log_file = configDic["log_file"]

    def manual_input(self):
        self.curr_duty = float(input("Duty: "))

    def set_logging(self):

        logging.basicConfig(filename=self.log_file,
                            filemode='a',
                            format='%(asctime)s - %(message)s',
                            level=logging.INFO)

    def log(self):
        # TODO: get cpu use
        # /proc/stat
        msg = str(self.cpu_temp) + " " + str(self.curr_duty)
        logging.info(msg)

    def get_prop_duty(self):
        """
        m * temp + b = duty
        m = ( speedMax - speedMin ) / ( temp_max - temp_min )
        b = speedMax - (m * temp_max)
        """
        duty_dic = {}
        duty_max = 100
        m = ((duty_max - self.duty_min) / (self.temp_max - self.temp_min))
        duty = lambda temp: m * temp + (duty_max - (m * self.temp_max))
        for temp in range(self.temp_min, self.temp_max):
            duty_dic[temp] = duty(temp)
        return duty_dic


    def get_curr_temp(self):
        cpu_temp_file = open(self.temp_file)
        self.cpu_temp = int(cpu_temp_file.read()) / 1000
        cpu_temp_file.close()

        if self.is_logging:
            self.log()


    def has_hysterie(self):
        self.get_curr_temp()
        return abs(self.cpu_temp - self.cpu_temp_old) > self.hysterie

    def get_new_duty(self):
        if self.cpu_temp >= self.temp_max:
            self.curr_duty = self.duty_max
        elif self.cpu_temp <= self.temp_min:
            self.curr_duty = self.duty_min
        else:
            self.curr_duty = self.duty_dic[self.cpu_temp]


        self.cpu_temp_old = self.cpu_temp

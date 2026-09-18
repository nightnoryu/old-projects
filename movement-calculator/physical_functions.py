import math


G = 9.8066
PI = 3.1415


def deg_to_rad(angle):
	"""Перевод из градусов в радианы"""
	return angle / 180 * PI

def sin(angle):
	"""Синус в градусах"""
	return math.sin(deg_to_rad(angle))

def cos(angle):
	"""Косинус в градусах"""
	return math.cos(deg_to_rad(angle))

def speed_x(speed, angle):
	"""Проекция скорости на ось X"""
	return speed * cos(angle)
	
def speed_y(speed, angle):
	"""Проекция скорости на ось Y"""
	return speed * sin(angle)

def get_distance(speed, angle):
	"""Нахождение расстояния баллистического движения"""
	return (speed ** 2 * sin(2 * angle) / G)

def get_time(speed, angle):
	"""Нахождение времени полета"""
	return (2 * speed * sin(angle) / G)

def get_max_height(speed, angle):
	"""Нахождение максимальной высоты траектории"""
	half_time = get_time(speed, angle) / 2
	return ((speed * sin(angle) * half_time) - (half_time ** 2 * G / 2))

def trajectory_func(speed, angle, x):
	"""Функция графика траектории тела"""
	speedx = speed_x(speed, angle)
	speedy = speed_y(speed, angle)
	return (speedy / speedx * x - G / 2 / speedx ** 2 * x ** 2)

def get_x_max(speed, angle):
	"""Возвращает максимальную координату X тела"""
	time_max = get_time(speed, angle)
	return speed_x(speed, angle) * time_max
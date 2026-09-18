import math


class Settings():

	def __init__(self):
		# Screen settings
		self.screen_width = 800
		self.screen_height = 600
		self.background_color = (0, 0, 0)

		# Player settings
		self.player_color = (230, 230, 230)
		self.player_width = 20
		self.player_height = 150
		self.player_speed_rate = 2

		# Player start position
		self.startx = 0
		self.starty = (self.screen_height // 2) - (self.player_height // 2)

		# Ball settings
		self.ball_speed_rate = 0.5
		self.ball_radius = 10
		self.ball_color = (255, 255, 255)

		# Ball start position
		self.ball_startx = self.screen_width // 2
		self.ball_starty = self.screen_height // 2
		self.ball_start_angle = math.pi / 6

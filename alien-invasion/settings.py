class Settings():
	def __init__(self):
		"""Static game settings"""
		# Game settigs
		self.screen_width = 900
		self.screen_height = 600
		self.bg_color = (230, 230, 230)

		# Ship settings
		self.ship_limit = 3

		# Bullet settings
		self.bullet_width = 3
		self.bullet_height = 15
		self.bullet_color = (60, 60, 60)
		self.bullets_allowed = 3

		# Aliens settings
		self.fleet_drop_speed = 10
		self.score_scale = 1.5

		# Game speed up tempo
		self.speed_up_scale = 1.1
		self.initialize_dynamic_settings()

	def initialize_dynamic_settings(self):
		"""Dynaimic game settings"""
		self.ship_speed_factor = 1.5
		self.bullet_speed_factor = 2
		self.alien_speed_factor = 1
		self.fleet_direction = 1 # 1 - to the right, -1 - to the left
		self.alien_points = 50

	def increase_speed(self):
		self.ship_speed_factor *= self.speed_up_scale
		self.bullet_speed_factor *= self.speed_up_scale
		self.alien_speed_factor *= self.speed_up_scale
		self.alien_points = int(self.alien_points * self.score_scale)
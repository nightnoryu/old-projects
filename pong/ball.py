import math

import pygame
from pygame.sprite import Sprite


class Ball(Sprite):

	def __init__(self, settings, screen, player):
		super().__init__()
		self.settings = settings
		self.screen = screen
		self.player = player

		# Position the ball
		self.centerx = self.settings.ball_startx
		self.centery = self.settings.ball_starty

		self.angle = self.settings.ball_start_angle

	def get_speed_x(self):
		"""Returns balls speed on the X axis"""
		return self.settings.ball_speed_rate * math.cos(self.angle)

	def get_speed_y(self):
		"""Returns balls speed on the Y axis"""
		return self.settings.ball_speed_rate * math.sin(self.angle)

	def get_sides(self):
		"""Returns a tuple of side coordiantes (right, left, top and bottom)"""
		right = self.centerx + (self.settings.ball_radius // 2)
		left = self.centerx - (self.settings.ball_radius // 2)
		top = self.centery + (self.settings.ball_radius // 2)
		bottom = self.centery - (self.settings.ball_radius // 2)
		return (right, left, top, bottom)

	def check_edges(self):
		"""Checks whether the ball hit the edge and changes angle"""
		right, left, top, bottom = self.get_sides()

		# centerx and centery must change to create some space for ball to move
		# Top edge
		if top <= 0:
			if self.angle < math.pi / 2:
				self.angle -= math.pi / 2
				if self.angle < 0:
					self.angle = (math.pi * 2) - abs(self.angle)
			else:
				self.angle = (self.angle + math.pi / 2) % (math.pi * 2)
			self.centery += 5
		# Bottom edge
		elif bottom >= self.settings.screen_height:
			if self.angle < 3 * math.pi / 2:
				self.angle -= math.pi / 2
			else:
				self.angle = (self.angle + math.pi / 2) % (math.pi * 2)
			self.centery -= 5
		# Right edge
		elif right >= self.settings.screen_width:
			if self.angle < 0:
				self.angle -= math.pi / 2
			else:
				self.angle += math.pi / 2
			self.centerx -= 5
		# Left edge
		elif left <= 0:
			if self.angle < math.pi:
				self.angle -= math.pi / 2
			else:
				self.angle += math.pi / 2
			self.centerx += 5

	def update(self):
		"""Updates ball's position"""
		self.centerx += self.get_speed_x()
		self.centery -= self.get_speed_y()
		self.check_edges()

	def blitme(self):
		"""Renders the ball on the screen"""
		pos = (int(self.centerx), int(self.centery))

		pygame.draw.circle(
			self.screen,
			self.settings.ball_color,
			pos,
			self.settings.ball_radius
		)

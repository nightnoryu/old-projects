import pygame
from pygame.sprite import Sprite


class Player(Sprite):

	def __init__(self, settings, screen):
		self.settings = settings
		self.screen = screen

		# Create the sprite
		self.rect = pygame.Rect(
			self.settings.startx,
			self.settings.starty,
			self.settings.player_width,
			self.settings.player_height
		)

		# Movement directions
		self.moving_up = False
		self.moving_down = False

	def update(self):
		"""Updates player's position"""
		if self.moving_up and not self.rect.top <= 0:
			self.rect.centery -= self.settings.player_speed_rate
		elif (self.moving_down and
			  not self.rect.bottom >= self.settings.screen_height):
			self.rect.centery += self.settings.player_speed_rate

	def blitme(self):
		"""Renders the player on the screen"""
		pygame.draw.rect(self.screen, self.settings.player_color, self.rect)

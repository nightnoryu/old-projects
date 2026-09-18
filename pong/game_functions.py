import sys

import pygame


def handle_keydown_events(event, player):
	if event.key == pygame.K_ESCAPE:
		sys.exit(0)
	elif event.key == pygame.K_UP:
		player.moving_up = True
	elif event.key == pygame.K_DOWN:
		player.moving_down = True

def handle_keyup_events(event, player):
	if event.key == pygame.K_UP:
		player.moving_up = False
	elif event.key == pygame.K_DOWN:
		player.moving_down = False

def handle_events(player):
	"""Handles all in-game events"""
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit(0)
		elif event.type == pygame.KEYDOWN:
			handle_keydown_events(event, player)
		elif event.type == pygame.KEYUP:
			handle_keyup_events(event, player)

def update_screen(settings, screen, player, ball):
	"""Renders all objects on the screen"""
	screen.fill(settings.background_color)
	player.blitme()
	ball.blitme()
	pygame.display.flip()

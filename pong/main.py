import sys

import pygame

from settings import Settings
import game_functions as gf
from player import Player
from ball import Ball

def main():
	pygame.init()
	settings = Settings()

	screen = pygame.display.set_mode((800, 600))
	pygame.display.set_caption('Pong')

	# Create player
	player = Player(settings, screen)
	ball = Ball(settings, screen, player)

	# Main loop
	while True:
		gf.handle_events(player)

		player.update()
		ball.update()

		gf.update_screen(settings, screen, player, ball)

if __name__ == '__main__':
	main()

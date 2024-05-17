import pygame

class Window:
    def __init__(self):
        # Initialize Pygame
        pygame.init()

        # Set the width and height of the window
        self.width = 800
        self.height = 600

        # Create the window
        self.window = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("My Pygame Window")
        self.running = True
        self.port = None

    def setGreen(self, data):
        print(data)
        self.window.fill((0, 255, 0))

    def setRed(self, data):
        print(data)
        self.window.fill((255, 0, 0))

    def run(self):
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
                    port.sendMessage("stop\0")
                    
            
            pygame.display.flip()


import time
from Serial import initialisePortInterfaces

window = Window()
port = initialisePortInterfaces(window.setGreen, window.setRed)
window.port = port
window.run()
import serial
import pygame

pygame.init()
pygame.font.init()
size = (300,300)
screen = pygame.display.set_mode(size)

#text variables
theme_font = pygame.font.Font(None,44)
my_num = "0"
title_text = theme_font.render(my_num,True, (255,255,255))

ser = serial.Serial("COM8", 9600)
while True:
     for event in pygame.event.get():
          if event.type == pygame.QUIT:
               pygame.quit()
     screen.fill((0,0,0))
     cc=str(ser.readline())

     my_num = cc[2:][:-5]

     title_text = theme_font.render(my_num,True, (255,255,255))

     screen.blit(title_text,(10,10))

     pygame.display.flip()
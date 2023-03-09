# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 21:19:28 by mguille           #+#    #+#              #
#    Updated: 2023/01/20 23:01:39 by mguille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_bzero.c ft_isprint.c ft_memcmp.c ft_strlcat.c \
	   ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strlcpy.c ft_strnstr.c \
	   ft_tolower.c ft_isascii.c ft_memcpy.c ft_memmove.c \
	   ft_strncmp.c ft_strrchr.c ft_toupper.c ft_isdigit.c ft_memchr.c \
	   ft_memset.c ft_atoi.c ft_substr.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_calloc.c ft_itoa.c ft_isalnum.c \
	   ft_strdup.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) -I. -o $@ -c $? $(CFLAGS)

clean:ç
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


# CC: variable qui contient le nom du compilateur.
# CFLAGS: variables qui contient les options de compilation.
# SRCS: variable qui contient la liste des fichiers source du projet.
# OBJS: variable qui contient la liste des fichiers objets générés à partir des fichiers sources.
# NAME: variable qui contient le nom de la bibliothèque.
# all: cible par défaut qui construit tous les fichiers nécessaires.
# $(NAME): cible pour créer la bibliothèque à partir des fichiers objets.
# $(OBJS): dépendance de la cible $(NAME) - les fichiers objets nécessaires pour construire la bibliothèque.
# ar rcs $(NAME) $(OBJS): commande pour créer la bibliothèque statique.
# %.o: %.c: règle générique pour la compilation de fichiers source en fichiers objets.
# clean: cible pour nettoyer les fichiers objets.
# fclean: cible pour nettoyer les fichiers objets et la bibliothèque.
# re: cible pour reconstruire le projet entier en exécutant fclean et all.
# .PHONY: déclare les cibles "all", "clean", "fclean" et "re" comme des cibles "factices" pour s'assurer qu'elles
# seront toujours exécutées, même si des fichiers portant leur nom existent déjà.
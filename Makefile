##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -f

NAME	=	Raytracer

FOLDER	=	build/

all:	$(NAME)

$(NAME):	fclean
	mkdir $(FOLDER)
	cd $(FOLDER) && cmake .. && make
	cp $(FOLDER)$(NAME) ./

clean:
	@echo "Cleaning..."

fclean:	clean
	$(RM) -r $(FOLDER)
	$(RM) ./$(NAME)

re:	fclean all

.PHONY:	all clean fclean re $(NAME)

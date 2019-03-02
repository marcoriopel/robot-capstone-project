# Makefile Global pour compiler notre librairie


####### variables #######
SRC_dir = sources
BUILD_dir = build
TRG = libanane.a

CC = avr-gcc
AR = avr-ar



####### flags #######
CFLAGS = -mmcu=atmega324pa -Wall
LIBFLAGS = -csr



####### Cible (Target) #######
SRC = $(wildcard $(SRC_dir)/*.cpp)
OBJ = $(subst $(SRC_dir),$(BUILD_dir),$(SRC:.cpp=.o))



####### Commandes du Makefile ####### 

# Compiler le projet
all: $(TRG)

$(TRG): $(OBJ)
	$(AR) $(LIBFLAGS) -o $@ $(OBJ)

$(BUILD_dir)/%.o: $(SRC_dir)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

# Afficher les variables
vars:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@echo "TRG = $(TRG)"

# Nettoyer les dossiers
clean: 
	rm $(BUILD_dir)/*.o $(TRG)
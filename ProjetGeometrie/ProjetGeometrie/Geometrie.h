#include "Instrument.h"
#include "Figure.h"

class Geometrie
{
public:
	Instrument* instruments; //Tableau des instruments
							 //0- Crayon
							 //1- Equerre
							 //2- Regle
							 //3- Compas
	Figure* figures;
};
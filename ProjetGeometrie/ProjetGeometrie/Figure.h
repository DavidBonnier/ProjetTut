class Figure
{
protected:
	double x;
	double y;
	bool selectionne;
	int couleur[3];

public :
	void selectionner();
	void setColor(int newColor[3]); //Change la couleur
};
class Instrument
{
	double x;
	double y;
	double angle;
	bool transparence;

	virtual void translation (double newx , double newy);
	void rotation (double newangle);
};
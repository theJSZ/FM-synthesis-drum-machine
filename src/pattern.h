#ifndef PATTERN_H
#define PATTERN_H

class Pattern {
public:
	Pattern();
	~Pattern();
	int *getPatternParameters();
	void setPatternParameters(int*);
private:
	int patternParameters[14*8];
	/*
	First 80 are dial values. Last 32 are step button values
	*/
};

#endif
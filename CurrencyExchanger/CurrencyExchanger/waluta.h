#pragma once
#include <iostream>

using namespace std;

class waluta
{
private:
	string name;
	double rate;

public:
	waluta() : name{ "XXX" }, rate{ 1 } {};
	waluta(string name_, double rate_) : name{ name_ }, rate{ rate_ } {}


	string getName() const { return this->name; }
	double getRate() const { return this->rate; }

	void setName(string newname) { this->name = newname; }
	void setRate(double x) { this->rate = x; }


	friend istream& operator >> (istream& in, waluta& x) { return in >> x.name >> x.rate; }
	friend ostream& operator << (ostream& out, const waluta& x) { return out << x.name << " " << x.rate; }
};
#pragma once
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <limits>

class rand_q
{
	std::random_device rd;
	double l, u;
public:
	rand_q(double lower_bound, double upper_bound) {
		l = lower_bound;
		u = upper_bound;
	}
	double gen_d() {
		std::uniform_real_distribution<double> dist(l, u);
		return dist(rd);
	}
};

template<typename T>
class people
{
protected:
	std::string name;

public:
	people(std::string& s) {
		name = s;
	}
	void tell_message(std::string& msg) {
		std::cout << name + ": " + msg << std::endl;
	}
	virtual void role(std::vector<T*>* v_st = nullptr) = 0;
};

class student : people<student>
{
private:
	double succsess_q, a, b, c;
	double x1 = std::numeric_limits<double>::quiet_NaN();
	double x2 = std::numeric_limits<double>::quiet_NaN();
	rand_q* prop_gen = new rand_q(0, 1);
	rand_q* coef_gen = new rand_q(-100, 100);
	void set_coefficients() {
		a = coef_gen->gen_d();
		b = coef_gen->gen_d();
		c = coef_gen->gen_d();
	}
public:
	student(std::string& s, double q) : people(s) {
		succsess_q = q;
	}
	~student() {
		delete prop_gen;
		delete coef_gen;
	}
	std::string get_name() {
		return name;
	}
	void role(std::vector<student*>* v_st = nullptr) {
		if (prop_gen->gen_d() < succsess_q)
		{
			std::string s("Fail test");
			tell_message(s);
			return;
		}
		set_coefficients();
		double d = b * b - 4 * a * c;
		if (d >= 0) {
			x1 = (-b + sqrt(d)) / (2 * a);
			x2 = (-b - sqrt(d)) / (2 * a);
			std::string m;
			m = "Roots is " + std::to_string(x1) + " and " + std::to_string(x2);
			tell_message(m);
		}
		else
		{
			std::string m("No root");
			x1 = 0;
			tell_message(m);
		}
	}
	std::pair<double, double> get_corners() {
		return std::pair<double, double>(x1, x2);
	}
};

class teacher : people<student>
{
private:
	std::string passed = " - 5", failed = " - 2";
public:
	teacher(std::string& s) : people(s) {};
	void estimate(student* st) {
		std::pair<double, double> res = st->get_corners();
		if (std::isnan(res.first)) {
			std::string s = st->get_name() + failed;
			tell_message(s);
		}
		else {
			std::string s = st->get_name() + passed;
			tell_message(s);
		}
	}
	void role(std::vector<student*>* v_st = nullptr) {
		for (student* e : *v_st)
			estimate(e);
	}
};
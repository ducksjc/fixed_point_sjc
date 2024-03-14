#include <iostream>
#include <charconv>
#include <sstream>
#include <cmath>
using namespace std;

struct fixp {
	long long left;
	long long right;
	const int sb = 32;
	const long long s = (long long)1 << sb;
	const long g = 100000000;

	fixp operator+(const fixp& t) {
		cout << "fixp.op+" << endl;
		fixp r;
		r.right = this->right + t.right;
		r.left = this->left + t.left;
		r.reset();
		return r;
	}

	fixp operator*(const fixp& t) {
		cout << "fixp.op* fixp" << endl;
		return this->operator*((double)t);
	}

	fixp operator*(const double& d) {
		cout << "fixp.op* double" << endl;
		fixp r;
		r.right = this->right * d;
		r.left = this->left * d;
		r.reset();
		return r;
	}

	operator string () const {
		cout << "fixp.op.ch " << sb << ", " << s << endl;

		//string r = to_string(left >> sb) + "." + to_string(right << sb);
		string r = to_string(left/g) + " + " + to_string( (double)right / g );

		return r;
	}

	operator double() const {
		double d = left + (double)right / g;
		return d;
	}

	fixp operator=(const double t) {
		double dl, dr;
		dr = modf(t, &dl);
		left = dl*g;
		//right = (t * s) - left << sb;
		right = t * g;
		//long long left2 = left << sb;
		//right = right - (left << sb);
		right = right - left;
		
		return *this;
	}

	void reset() {
		long long tmp = right / g;
		left += tmp *g;
		right -= tmp * g;

		tmp = left % g;
		right += tmp;
		
	}

	fixp operator=(const fixp t) {
		left = t.left;
		right = t.right;
		return *this;
	}
};

static char common_buff[16384];

const char* _sstr(double v) {
	if (v == -0.0) v = 0.0;
	auto res = std::to_chars(common_buff, common_buff + 64, v, std::chars_format::fixed);
	*res.ptr = '\0';
	return common_buff;
}

const char* _sstr(long double v) {
	if (v == -0.0) v = 0.0;
	auto res = std::to_chars(common_buff, common_buff + 64, v, std::chars_format::fixed);
	*res.ptr = '\0';
	return common_buff;
}

void main() {
	cout << "hi" << endl;

	//string x = "123.456";
	////x = "abc";
	//double xd = 1;
	//auto ret = from_chars(x.c_str(), x.c_str()+x.length(), xd);
	//cout << xd << endl;
	//cout << make_error_code(ret.ec).message() << endl;

	fixp a, b;
	a = 89550.0;
	b = a;
	fixp c = a + b;
	cout << (string)c << endl;

	c = a * 0.7;
	cout << (string)c << endl;

	double d = 0;
	for (int i = 0; i < 10; i++)
		d += 0.1;
	cout << "d = " << _sstr(d) << endl;

	fixp e;
	e = 0.0;
	for (int i = 0; i < 10; i++)
		e = e + 0.1;
	cout << "e = " << (string)e << endl;
}


int main2()
{
	long double a = 89550.0 * 0.7;
	if (a == 62685.0) cout << "OK\n";
	cout << "Hello " << a << "," << _sstr(a) << endl;
	return 0;
}
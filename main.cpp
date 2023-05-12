#include <iostream>
#include <fstream>
#include <string>

//basically implements long division, but we're returning the remainder
// input: the dividend in the form of a string, and a modulo in the
// form of a ull
// output: the result of a modulo in the form of a ull
unsigned long long modulo(std::string dividend, unsigned long long modulo) {
	if(dividend == "0") {
		return 0;
	}
	unsigned long long quotient = 0;
	int index = 0;
	unsigned long long dummy = dividend[0] & 0xf;
	while(dummy < modulo) {
		index++;
		dummy = dummy * 10 + (dividend[index] & 0xf);
	}

	while(dividend.length()-1 > index) {
		index++;
		dummy = (dummy % modulo) * 10 + (dividend[index] & 0xf);
	}
	dummy = dummy % modulo;
	return dummy;
}

// algorithm uses the property of exponents and dynamic programming to get the
// modulo of a number raise to a power.
// input: the base number as a ull, the power as a ull, and the modulo as a ull
// output: the result of the modulo in the form of a ull
int mod_exp(unsigned long long a, unsigned long long b, unsigned long long c) {
	int dummy = 1;
	for(unsigned long long i = 1; i <= b; i++) {
		dummy = (dummy * a) % c;
	}
	return dummy;
}

int main(int argc, char * argv[]) {
	std::ofstream outstream;
	std::ifstream instream;
    
	// error if arguments !=3
    if (argc != 3) {
		std::cout << "ERROR: Input and output files must be specified." << std::endl;
        return -1;
    }
    instream.open(argv[1]);
	outstream.open(argv[2]);
	if(!instream.is_open() || !outstream.is_open()) {
		std::cout << "ERROR: input or output file couldn't be opened." << std::endl;
		return -1;
	}

	std::string base;
	unsigned long long power;
	unsigned long long mod;
	unsigned long long reduction;
	instream >> base >> power >> mod;
	while(power != 0 || base != "0" || mod != 0) {
		if (mod == 0) {
			outstream << "impossible" << std::endl;
		}
		reduction = modulo(base, mod);
		outstream << mod_exp(reduction, power, mod) << std::endl;
		instream >> base >> power >> mod;
	}
	return 0;
}

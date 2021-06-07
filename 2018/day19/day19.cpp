#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;


typedef struct program
{
	string op;
	int a, b, c;
} program;

class cpu
{
private:
	int r[6];
	int ip;
	int ip_r;
	vector<program> input; 

public:

	cpu();
	
	void load_input(string);

	void reset(int a, int b, int c, int d) { r[0]=a; r[1]=b; r[2]=c; r[3]=d; };
	void print_reg(void);
	void print_program(void);
	int step_program(void);
	int get_reg(int);
	void set_reg(int, int);

	void addr_f(int, int, int);
	void addi_f(int, int, int);

	void mulr_f(int, int, int);
	void muli_f(int, int, int);

	void banr_f(int, int, int);
	void bani_f(int, int, int);

	void borr_f(int, int, int);
	void bori_f(int, int, int);

	void setr_f(int, int, int);
	void seti_f(int, int, int);

	void gtir_f(int, int, int);
	void gtri_f(int, int, int);
	void gtrr_f(int, int, int);
	
	void eqir_f(int, int, int);
	void eqri_f(int, int, int);
	void eqrr_f(int, int, int);
};

cpu::cpu()
{
	for (int x = 0; x < 6; x++)
		cpu::r[x] = 0;
	
	cpu::ip = 0;
}

int cpu::get_reg(int x)
{
	return cpu::r[x];
}

void cpu::set_reg(int x, int y)
{
	cpu::r[x] = y;
}

int cpu::step_program(void)
{
	if (cpu::ip > (cpu::input.size()-1))
		return 1;

	cpu::r[cpu::ip_r] = cpu::ip;

	program current_step;
	current_step = cpu::input.at(cpu::ip);

	string opc = current_step.op;
	int a = current_step.a;
	int b = current_step.b;
	int c = current_step.c;

	// program loops horribly to find factors of r[2], when we hit this loop, do it easier
	if (cpu::ip == 2)
	{
	    while (r[5] <= r[2])
	    {
	    	if ((r[5] != 0) && (r[2] % r[5]) == 0)
	            r[0] += r[5];
	        
	        r[5]++;
	    }
	    
	    cpu::ip = 16;
	    cpu::r[4] = 1;

	    return 0;
	}
	
	if (opc == "addr")
		cpu::addr_f(a, b, c);
	else if (opc == "addi")
		cpu::addi_f(a, b, c);
	else if (opc == "mulr")
		cpu::mulr_f(a, b, c);
	else if (opc == "muli")
		cpu::muli_f(a, b, c);
	else if (opc == "banr")
		cpu::banr_f(a, b, c);
	else if (opc == "bani")
		cpu::bani_f(a, b, c);
	else if (opc == "borr")
		cpu::borr_f(a, b, c);
	else if (opc == "bori")
		cpu::bori_f(a, b, c);
	else if (opc == "setr")
		cpu::setr_f(a, b, c);
	else if (opc == "seti")
		cpu::seti_f(a, b, c);
	else if (opc == "gtir")
		cpu::gtir_f(a, b, c);
	else if (opc == "gtri")
		cpu::gtri_f(a, b, c);
	else if (opc == "gtrr")
		cpu::gtrr_f(a, b, c);
	else if (opc == "eqir")
		cpu::eqir_f(a, b, c);
	else if (opc == "eqri")
		cpu::eqri_f(a, b, c);
	else if (opc == "eqrr")
		cpu::eqrr_f(a, b, c);

	cpu::ip = cpu::r[cpu::ip_r];
	cpu::ip++;

	return 0;
}

void cpu::print_program(void)
{
	for (const auto &i: cpu::input)
		cout<<i.op<<" "<<i.a<<" "<<i.b<<" "<<i.c<<endl;
}

void cpu::print_reg(void)
{
	for (int x = 0; x < 6; x++)
		cout<<cpu::r[x]<<" ";
	cout<<endl;
}


void cpu::addr_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] + cpu::r[b];
}
void cpu::addi_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] + b;
}

void cpu::mulr_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] * cpu::r[b];
}
void cpu::muli_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] * b;
}

void cpu::banr_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] & cpu::r[b];
}
void cpu::bani_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] & b;
}

void cpu::borr_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] | cpu::r[b];
}
void cpu::bori_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a] | b;
}

void cpu::setr_f(int a, int b, int c)
{
	cpu::r[c] = cpu::r[a];
}
void cpu::seti_f(int a, int b, int c)
{
	cpu::r[c] = a;
}

void cpu::gtir_f(int a, int b, int c)
{
	if (a > cpu::r[b])
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}
void cpu::gtri_f(int a, int b, int c)
{
	if (cpu::r[a] > b)
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}
void cpu::gtrr_f(int a, int b, int c)
{
	if (cpu::r[a] > cpu::r[b])
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}

void cpu::eqir_f(int a, int b, int c)
{
	if (a == cpu::r[b])
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}
void cpu::eqri_f(int a, int b, int c)
{
	if (cpu::r[a] == b)
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}
void cpu::eqrr_f(int a, int b, int c)
{
	if (cpu::r[a] == cpu::r[b])
		cpu::r[c] = 1;
	else
		cpu::r[c] = 0;
}


void cpu::load_input(string filename)
{
	vector<program> data;
	ifstream file;
	file.open(filename);
	if (!file)
	{
		cerr<<"Cannot open file:"<<filename<<endl;
	}

	string str;

	bool first = true;
	while (getline(file, str))
	{
		if (first == true)
		{
			first = false;
			regex rem("[#ip ]+([0-9]+)");
			smatch sm;
			regex_match(str, sm, rem);
			cpu::ip_r = stoi(sm[1]);
		
		} else {
			program this_line;
			regex rem("([a-z]+)[ ]([0-9]+)[ ]([0-9]+)[ ]([0-9]+)");
			smatch sm;
			regex_match(str, sm, rem);
		
			this_line.op = sm[1];
			this_line.a = stoi(sm[2]);
			this_line.b = stoi(sm[3]);
			this_line.c = stoi(sm[4]);

			data.push_back(this_line);
		}
	}
	cpu::input = data;
}


int main()
{
	cpu testbench;
	testbench.load_input("input");

	// comment next line for part1
	testbench.set_reg(0, 1);
	
	int count = 0;
	while (count < 5)
	{
		int outcome;
		outcome = testbench.step_program();

		if (outcome == 1)
			break;
	}

	cout<<testbench.get_reg(0)<<endl;

	return 0;
}

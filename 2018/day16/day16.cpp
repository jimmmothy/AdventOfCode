#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

typedef struct op_eval
{
	int b[4];
	int c[4];
	int a[4];
} op_eval;

typedef struct ops
{
	int q[4];
} ops;


class cpu
{
public:
	int r[4];
	int op_mapping[16];
	bool op_found[16];

	enum op_codes { addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };
	cpu();
	void reset(int a, int b, int c, int d) { r[0]=a; r[1]=b; r[2]=c; r[3]=d; };
	void print_reg(void);
	int test(op_eval);
	bool all_op_found(void);
	vector<int> work_out_mappings(op_eval);
	void do_program(int, int, int, int);

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
	for (int x = 0; x < 16; x++)
	{
		cpu::op_mapping[x] = 42;
		cpu::op_found[x] = false;
	}
}

void cpu::do_program(int a, int b, int c, int d)
{
	if (op_mapping[a] == addr)
		cpu::addr_f(b, c, d);
	
	else if (op_mapping[a] == addi)
		cpu::addi_f(b, c, d);

	else if (op_mapping[a] == mulr)
		cpu::mulr_f(b, c, d);
	
	else if (op_mapping[a] == muli)
		cpu::muli_f(b, c, d);
	
	else if (op_mapping[a] == banr)
		cpu::banr_f(b, c, d);
	
	else if (op_mapping[a] == bani)
		cpu::bani_f(b, c, d);
	
	else if (op_mapping[a] == borr)
		cpu::borr_f(b, c, d);
	
	else if (op_mapping[a] == bori)
		cpu::bori_f(b, c, d);
	
	else if (op_mapping[a] == setr)
		cpu::setr_f(b, c, d);
	
	else if (op_mapping[a] == seti)
		cpu::seti_f(b, c, d);
	
	else if (op_mapping[a] == gtir)
		cpu::gtir_f(b, c, d);
	
	else if (op_mapping[a] == gtri)
		cpu::gtri_f(b, c, d);
	
	else if (op_mapping[a] == gtrr)
		cpu::gtrr_f(b, c, d);
	
	else if (op_mapping[a] == eqri)
		cpu::eqri_f(b, c, d);
	
	else if (op_mapping[a] == eqir)
		cpu::eqir_f(b, c, d);
	
	else if (op_mapping[a] == eqrr)
		cpu::eqrr_f(b, c, d);

}

bool cpu::all_op_found(void)
{
	for (int x = 0; x < 16; x++)
		if (cpu::op_found[x] == false)
			return false;
	return true;
}

vector<int> cpu::work_out_mappings(op_eval i)
{
	int final_count = 0;
	vector<int> hits;

	if (cpu::op_found[addr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::addr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(addr);
			final_count++;
		}
	}
	
	if (cpu::op_found[addi] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::addi_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(addi);
			final_count++;
		}
	}
	
	
	if (cpu::op_found[mulr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::mulr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(mulr);
			final_count++;
		}
	}
	
	if (cpu::op_found[muli] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::muli_f(i.c[1], i.c[2], i.c[3]);
			if (r[i.c[3]] == i.a[i.c[3]])
			{
				hits.push_back(muli);
				final_count++;
			}
	}

	if (cpu::op_found[banr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::banr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(banr);
			final_count++;
		}
	}
	
	if (cpu::op_found[bani] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::bani_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(bani);
			final_count++;
		}
	}

	if (cpu::op_found[borr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::borr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(borr);
			final_count++;
		}
	}
	
	if (cpu::op_found[bori] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::bori_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(bori);
			final_count++;
		}
	}
	

	if (cpu::op_found[setr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::setr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(setr);
			final_count++;
		}
	}

	if (cpu::op_found[seti] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::seti_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(seti);
			final_count++;
		}
	}

	if (cpu::op_found[gtir] == false)
	{	
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::gtir_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(gtir);
			final_count++;
		}
	}

	if (cpu::op_found[gtri] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::gtri_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(gtri);
			final_count++;
		}
	}

	if (cpu::op_found[gtrr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::gtrr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(gtrr);
			final_count++;
		}
	}

	if (cpu::op_found[eqir] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::eqir_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(eqir);
			final_count++;
		}
	}

	if (cpu::op_found[eqri] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::eqri_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(eqri);
			final_count++;
		}
	}

	if (cpu::op_found[eqrr] == false)
	{
		cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
		cpu::eqrr_f(i.c[1], i.c[2], i.c[3]);
		if (r[i.c[3]] == i.a[i.c[3]])
		{
			hits.push_back(eqrr);
			final_count++;
		}
	}

	return hits;
}

void cpu::print_reg(void)
{
	cout<<r[0]<<" "<<r[1]<<" "<<r[2]<<" "<<r[3]<<endl;
}

int cpu::test(op_eval i)
{
	int final_count = 0;

	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::addr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::addi_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;

	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::mulr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::muli_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;


	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::banr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::bani_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;


	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::borr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::bori_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;


	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::setr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::seti_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;


	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::gtir_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::gtri_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::gtrr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;


	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::eqir_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::eqri_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;
	cpu::reset(i.b[0], i.b[1], i.b[2], i.b[3]);
	cpu::eqrr_f(i.c[1], i.c[2], i.c[3]);
	if (r[i.c[3]] == i.a[i.c[3]])
		final_count++;

	return final_count;
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


vector<op_eval> get_data(string filename)
{
	vector<op_eval> data;
	ifstream file;
	file.open(filename);
	if (!file)
	{
		cerr<<"Cannot open file:"<<filename<<endl;
		return {};
	}

	string str = "";
	vector<string> strbuff = {};

	while (getline(file, str))
	{
		if (strbuff.size() == 2)
		{
			strbuff.push_back(str);
			op_eval new_entry;

			// Line 1
			regex rem1("[[Before: \\[|After: \\[]+(\\d+)[, ]+(\\d+)[, ]+(\\d+)[, ]+(\\d+)[\\]]");
			smatch sm;
			regex_match(strbuff.at(0), sm, rem1);
			new_entry.b[0] = stoi(sm[1]);
			new_entry.b[1] = stoi(sm[2]);
			new_entry.b[2] = stoi(sm[3]);
			new_entry.b[3] = stoi(sm[4]);

			// Line 2
			regex rem2("(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)");
			regex_match(strbuff.at(1), sm, rem2);
			new_entry.c[0] = stoi(sm[1]);
			new_entry.c[1] = stoi(sm[2]);
			new_entry.c[2] = stoi(sm[3]);
			new_entry.c[3] = stoi(sm[4]);

			// Line 3
			regex rem3("[[Before: \\[|After: \\[]+(\\d+)[, ]+(\\d+)[, ]+(\\d+)[, ]+(\\d+)[\\]]");
			regex_match(strbuff.at(2), sm, rem3);
			new_entry.a[0] = stoi(sm[1]);
			new_entry.a[1] = stoi(sm[2]);
			new_entry.a[2] = stoi(sm[3]);
			new_entry.a[3] = stoi(sm[4]);

			data.push_back(new_entry);
			strbuff.clear();
		
		} else if (str.size() > 0 && (strbuff.size() < 2))
		{
			strbuff.push_back(str);
		}
	}

	return data;
}

vector<ops> get_data_p2(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file)
	{
		cerr<<"Cannot open file:"<<filename<<endl;
		return {};
	}

	string str = "";
	vector<ops> all_data;
	ops buff;

	while (getline(file, str))
	{
			regex rem("(\\d+)\\s(\\d+)\\s(\\d+)\\s(\\d+)");
			smatch sm;
			regex_match(str, sm, rem);
			buff.q[0] = stoi(sm[1]);
			buff.q[1] = stoi(sm[2]);
			buff.q[2] = stoi(sm[3]);
			buff.q[3] = stoi(sm[4]);

			all_data.push_back(buff);
	}

	return all_data;
}

int op_test(void)
{
	vector<op_eval> datapoints = get_data("input");

	int count = 0;
	for (const auto &i: datapoints)
	{
		cpu testbench;
		int similar = testbench.test(i);
		if (similar >= 3)
			count++;
	}

	cout<<count<<endl;


	// part two
	cpu testbench;
	int iterations = 0;
	while (testbench.all_op_found() != true)
	{
		for (int x = 0; x < 16; x++)
		{
			// skip if we found it already
			if (testbench.op_found[testbench.op_mapping[x]] == true)
				continue;

			// make vector of all with op code of 0,1,2 etc
			vector<op_eval> data_per;
			for (const auto &i: datapoints)
				if (i.c[0] == x)
					data_per.push_back(i);

			vector<vector<int>> our_hits;
			for (const auto &i: data_per)
				our_hits.push_back(testbench.work_out_mappings(i));
			
			if (our_hits.size() > 0)
			{
				vector<int> possible_code = our_hits.at(0);
				
				int enum_count = 0;
				int recent;

				for (const auto &i: possible_code)
				{
					enum_count++;
					recent = i;
				}

				// single hit found
				if (enum_count == 1)
				{
					testbench.op_mapping[x] = recent;
					testbench.op_found[recent] = true;
				}
			}
		}
	}

	// All op mappings found
	testbench.reset(0, 0, 0, 0);
	vector<ops> program_instructions = get_data_p2("input_part2");
	for (const auto &i: program_instructions)
		testbench.do_program(i.q[0], i.q[1], i.q[2], i.q[3]);

	cout<<testbench.r[0]<<endl;

	return 0;
}


int main()
{
	op_test();

	return 0;
}

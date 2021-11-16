#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <map>

using namespace std; 

map<string, int> availableAtoms;

void generateAtomsTable() {

	map<string, int> fip;
	fip.insert({ "ID",      0 });
	fip.insert({ "CONST",   1 });
	fip.insert({ "int", 2 });
	fip.insert({ "double",  3 });
	fip.insert({ "circle",  4 });
	fip.insert({ ":", 5 });
	fip.insert({ ",", 6 });
	fip.insert({ ";", 7 });
	fip.insert({ "{", 8 });
	fip.insert({ "}", 9 });
	fip.insert({ "(", 10 });
	fip.insert({ ")", 11 });
	fip.insert({ ">>",  12 });
	fip.insert({ "<<",  13 });
	fip.insert({ "+",   14 });
	fip.insert({ "-",   15 });
	fip.insert({ "*",   16 });
	fip.insert({ "++",  17 });
	fip.insert({ "--",  18 });
	fip.insert({ "<",   19 });
	fip.insert({ ">",   20 });
	fip.insert({ "!=",  21 });
	fip.insert({ "!",   22 });
	fip.insert({ "<=",  23 });
	fip.insert({ "=",   24 });
	fip.insert({ "main",    25 });
	fip.insert({ "return",  26 });
	fip.insert({ "if",      27 });
	fip.insert({ "while",   28 });
	fip.insert({ "cin",     29 });
	fip.insert({ "cout",    30 });
	fip.insert({ "for",     31 });
	availableAtoms = fip;
}

class TS {
	string symbol;
	int code;

public:
	TS(string symbol, int code) : symbol{ symbol }, code{ code }{

	}

	string toString() {
		string s = "";
		s.append("symbol= ").append(symbol).append(" , code= ").append(to_string(code));
		return s;
	}

	void setCode(int code) {
		this->code = code;
	}

	string getSymbol() {
		return symbol;
	}
};

class FIP {

	int codeAtom;
	int codeTS;

public:
	std::string atom;

	FIP(std::string atom, int codeAtom, int codeTS = -1) : atom{ atom }, codeAtom{ codeAtom }, codeTS{ codeTS }{

	}

	bool operator==(FIP& other) const {
		return atom == other.atom && codeAtom == other.codeAtom && codeTS == other.codeTS;
	}

	void setCodeTS(int code) {
		codeTS = code;
	}

	std::string toString() {
		std::string s = "";
		s.append("atom= ").append(atom).append(" ");
		s.append("codeAtom= ").append(std::to_string(codeAtom)).append(" , codeTS= ").append(std::to_string(codeTS));
		return s;
	}
};

class LT {
	//the maximum capacity
	int capacity;
	//the actual size
	int size;
	//the current code - generated incrementally
	int code = 0;

	//the array
	TS** table;

	//doubles the capacity of the table
	void resize() {
		int newCap = capacity * 2;
		TS** tmp = new TS * [newCap];
		for (int i = 0; i < size; i++) {
			tmp[i] = table[i];
		}

		capacity = newCap;
		table = tmp;
	}

	void init(int cap) {
		capacity = cap;
		table = new TS * [cap];
	}

public:
	/*
		constructor
		param: cap - the initial capacity
	*/
	LT(int cap) {
		init(cap);
	}

	LT() {
		init(7);
	}

	/*
		adds the given element in the table
		returns the codeTS of the element that was inserted
	*/
	int add(string element) {
		if (size >= 0.75 * capacity)
			resize();
		//insertion sort lexicografic
		//add element on the last position
		table[size++] = new TS(element, code++);

		int pos = size - 1;
		//as long as the inserted element is smaller lexicographically then the current one
		while (pos > 0 && table[pos]->getSymbol().compare(table[pos - 1]->getSymbol()) < 0) {
			//interchange them
			TS* tmp = table[pos];
			table[pos] = table[pos - 1];
			table[pos - 1] = tmp;
			table[pos]->setCode(pos);
			table[pos - 1]->setCode(pos - 1);
			pos--;
		}

		return pos + 1;
	}

	//returns the actual size of the table
	int getSize() {
		return size;
	}

	//returns the entry on position @index from the table
	TS* get(int index) {
		return table[index];
	}

	//returns  the position the desired element is found on
	//or -1 if it is not in the table
	int find(string element) {
		//binary search
		int right = size - 1, left = 0;
		while (left <= right) {
			int middle = (left + right) / 2;
			if (table[middle]->getSymbol().compare(element)==0)
				return middle;
			if (table[middle]->getSymbol().compare(element) < 0)
				left = middle + 1;
			else
				right = middle - 1;
		}
		return -1;
	}

	/*
		returns a reference to the LT as a string*
		THIS REFERENCE SHOULD NOT BE STORED
		AND MUST BE USED ONLY FOR READ OPERATIONS
	*/
	TS** getLTasVector() {
		return table;
	}


};

vector<FIP*> fip;
LT* ts = new LT();

int main(int argc, char* argv[])
{
	generateAtomsTable();

	string errors;
	string text = argv[1];
	istringstream f(text);
	int lineNo = 0;
	string line;
	while (getline(f, line)) {
		lineNo++;
		istringstream iss(line);

		while (iss) {
			string type, atom;
			iss >> type;
			iss >> atom;
			if (type.empty() || atom.empty())continue;
			cout << type << " " << atom << '\n';
			if (type.find("Keyword") != string::npos) {
				fip.push_back(new FIP(atom, availableAtoms.find(atom)->second));
			}
			else if (type.find("Identifier") != string::npos) {
				if (ts->find(atom) == -1)
					ts->add(atom);
				fip.push_back(new FIP(atom, 0));
			}
			else if (type.find("Double") != string::npos || type.find("Integer") != string::npos) {
				if (ts->find(atom) == -1)
					ts->add(atom);
				fip.push_back(new FIP(atom, 1));
			}
			else if (type.find("Operator") != string::npos) {
				fip.push_back(new FIP(atom, availableAtoms.find(atom)->second));
			}
			else if (type.find("Paranthesis") != string::npos) {
				fip.push_back(new FIP(atom, availableAtoms.find(atom)->second));
			}
			else {
				errors.append("Error on line: ").append(to_string(lineNo)).append(" , " + line).append("\n");
				while (iss)iss >> type;
			}
		}
	}

	if (errors.empty()) {
		cout << "FIP\n";
		for (auto i : fip) {
			i->setCodeTS(ts->find(i->atom));
			cout << i->toString() << '\n';
		}
		cout << "TS\n";
		for (int i = 0; i < ts->getSize(); i++) {
			cout << ts->get(i)->toString() << '\n';
		}
	}
	else {
		cout << "Compilation FAILED! There were syntax errors:\n";
		cout << errors;
	}

	return 0;
}


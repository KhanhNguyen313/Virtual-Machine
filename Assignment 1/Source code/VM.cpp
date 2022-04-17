#include "VM.h"

bool isInterger(string s)
{
	unsigned int i = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
	if (s[i] == '-')
	{
		if(s.length() == 1) return 0;
		i++;
	}
	while (i < s.length() && s[i] >= '0' && s[i] <= '9')
		i++;
	if (i >= s.length() && s.length() > 0)
		return 1;
	return 0;
}

bool isFloat(string s)
{
	unsigned int i = 0;
	if(s[0] == '.') return 0;
	if (s[i] == '-')
		i++;
	while (i < s.length() && s[i] != '.' && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '.' && i < s.length() - 1)
	{
		if(s[0] == '-' && s[1] == '.') return 0;
		i++;
		while (i < s.length() && s[i] >= '0' && s[i] <= '9')
			i++;
		if (i >= s.length())
			return 1;
		return 0;
	}
	return 0;
}

bool isAddress(string s)
{
	unsigned int i = 0;
	if(s[0] == '0' && s.length() > 2) return 0;
	while (i < s.length() && s[i] != 'A' && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == 'A' && (i == s.length() - 1) && s.length() > 1)
		return 1;
	return 0;
}

bool isBoolean(string s)
{
	if (s == "true" || s == "false")
		return 1;
	return 0;
}

bool isZero(string s)
{
	unsigned int i = 0;
	while (i < s.length() && s[i] == '0')
		i++;
	if (s[i] == '.' && i > 0)
		i++;
	while (i < s.length() && s[i] == '0')
		i++;
	if (i >= s.length() && s.length() > 0)
		return 1;
	return 0;
}

bool isRegister(string s)
{
	if ((s.length() == 2 && s[0] == 'R' && s[1] >= '1' && s[1] <= '9') ||
		(s.length() == 3 && s[0] == 'R' && s[1] == '1' && s[2] >= '0' && s[2] <= '5'))
		return true;
	return false;
}

bool isLiteral(string s)
{
	if (s == "true" || s == "false")
		return 1;
	unsigned int i = 0;
	while (s[i] >= '0' && s[i] <= '9' && i < s.length())
		i++;
	if (i >= s.length() && s.length() >= 1)
	{
		//if(s[0] == '0' && s.length() > 1) return 0;
		return 1;
	}
	if (s[i] == 'A' && (i == s.length() - 1) && s.length() >= 2)
	{
		if(s[0] == '0' && s.length() > 2) return 0;
		return 1;
	}
	if (s[i] == '.' && i > 0 && (i < s.length() - 1) && s[i + 1] >= '0' && s[i + 1] <= '9')
	{
		i++;
		while (s[i] >= '0' && s[i] <= '9' && i < s.length())
			i++;
		if (i >= s.length())
			return 1;
	}
	return 0;
}

int getIndex(string s)
{
	s.erase(0, 1);
	return stoi(s) - 1;
}

string getIntrCode(string s)
{
	unsigned int i = 0;
	string temp;
	while (s[i] != ' ' && i < s.length())
	{
		temp.push_back(s[i]);
		i++;
	}
	return temp;
}

string getOperand1(string s)
{
	unsigned int i = 0;
	string temp = "";
	while (s[i] != ' ')
		i++;
	i++;
	while (s[i] != ',' && i < s.length())
	{
		temp.push_back(s[i]);
		i++;
	}
	return temp;
}

string getOperand2(string s)
{
	unsigned int i = 0;
	string temp = "";
	while (s[i] != ',')
		i++;
	i += 2;
	while (i < s.length())
	{
		temp.push_back(s[i]);
		i++;
	}
	return temp;
}

int checkLoading(string s)
{
	unsigned int i = 0;
	string temp;
	while (i < s.length())
	{
		while (s[i] != ' ' && i < s.length())
		{
			temp.push_back(s[i]);
			i++;
		}
		if (i >= s.length())
		{
			if (temp == "Return" || temp == "Halt")
				return 1;
			return 411;
		}
		if (temp == "Add" || temp == "Minus" || temp == "Mul" || temp == "Div" ||
			temp == "CmpEQ" || temp == "CmpNE" || temp == "CmpLT" || temp == "CmpLE" || temp == "CmpGT" || temp == "CmpGE" ||
			temp == "And" || temp == "Or" ||
			temp == "Move" || temp == "Load" || temp == "Store" ||
			temp == "JumpIf")
		{
			if (s[i] == ' ')
			{
				i++;
				if(i >= s.length()) return 411;
				//chua xu li loi loi "Add 12[2]d, wew", "Add 2as, 10A"
				while (s[i] != ',' && i < s.length() && s[i] != ' ')
					i++;
				if (s[i] == ',' && s[i - 1] != ' ')
				{
					if (s[i + 1] == ' ')
					{
						i += 2;
						if(i >= s.length()) return 411;
						while (s[i] != ',' && s[i] != ' ' && i < s.length())
							i++;
						if (i >= s.length() && s[i - 1] != ' ' && s[i - 1] != ',')
						{
							if (isRegister(getOperand1(s)))
							{
								if (isLiteral(getOperand2(s)) || isRegister(getOperand2(s)))
									return 1;
								return 412;
							}
							return 412;
						}
						return 411;
					}
					return 411;
				}
				return 411;
			}
			return 411;
		}
		if (temp == "Not" ||
			temp == "Jump" ||
			temp == "Call" ||
			temp == "Input" ||
			temp == "Output")
		{
			if (s[i] == ' ')
			{
				i++;
				if(i >= s.length()) return 411;
				while (s[i] != ' ' && s[i] != ',' && i < s.length())
					i++;
				if (i >= s.length() && s[i - 1] != ' ')
				{
					if (temp == "Not" || temp == "Input")
					{
						if (isRegister(getOperand1(s)))
							return 1;
						return 412;
					}
					if (temp == "Jump" || temp == "Call" || temp == "Output")
					{
						if (isRegister(getOperand1(s)) || isLiteral(getOperand1(s)))
							return 1;
						return 412;
					}
					return 412;
				}
				return 411;
			}
			return 411;
		}
		return 411;
	}
	return 411;
}

void VM::Arithmetic(string op1, string op2, string instruction)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if (isInterger(t1) && isInterger(t2))
	{
		long r;
		if (instruction == "Add")
			r = stol(t1) + stol(t2);
		if (instruction == "Minus")
			r = stol(t1) - stol(t2);
		if (instruction == "Mul")
			r = stol(t1) * stol(t2);
		if (instruction == "Div")
		{
			if (stol(t2) == 0)
				throw DivideByZero(IP - 1);
			r = stol(t1) / stol(t2);
		}
		R[getIndex(op1)] = to_string(r);
		return;
	}
	if ((isInterger(t1) && isFloat(t2)) || (isFloat(t1) && isInterger(t2)) || (isFloat(t1) && isFloat(t2)))
	{
		double r;
		if (instruction == "Add")
			r = stod(t1) + stod(t2);
		if (instruction == "Minus")
			r = stod(t1) - stod(t2);
		if (instruction == "Mul")
			r = stod(t1) * stod(t2);
		if (instruction == "Div")
		{
			if (isZero(t2))
				throw DivideByZero(IP - 1);
			r = stod(t1) / stod(t2);
		}
		// string temp = to_string(r);
		// unsigned int i = temp.length() - 1;
		// while (temp[i] == '0')
		// {
		// 	temp.pop_back();
		// 	i = temp.length() - 1;
		// }
		// if (temp[i] == '.')
		// 	temp.push_back('0');
		// R[getIndex(op1)] = temp;

		char buffer[50];
		sprintf(buffer, "%.20g", r);
		string temp = string(buffer);
		R[getIndex(op1)] = temp;
		return;
	}
	throw TypeMismatch(IP - 1);
}

void VM::Comparison(string op1, string op2, string instruction)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if (isBoolean(t1) && isBoolean(t2))
	{
		int r1, r2;
		r1 = (t1 == "true") ? 1 : 0;
		r2 = (t2 == "true") ? 1 : 0;
		if (instruction == "CmpEQ")
		{
			if (r1 == r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpNE")
		{
			if (r1 != r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpLT")
		{
			if (r1 < r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpLE")
		{
			if (r1 <= r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpGT")
		{
			if (r1 > r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpGE")
		{
			if (r1 >= r2)
				R[getIndex(op1)] = "true";
			else
				R[getIndex(op1)] = "false";
			return;
		}
	}
	if ((isInterger(t1) && isInterger(t2)) || (isInterger(t1) && isFloat(t2)) ||
		(isFloat(t1) && isInterger(t2)) || (isFloat(t1) && isFloat(t2)))
	{
		string t1_1, t1_2, t2_1, t2_2;
		unsigned int i = 0;

		while (t1[i] != '.' && i < t1.length())
		{
			t1_1.push_back(t1[i]);
			i++;
		}
		if (i >= t1.length())
			t1_2 = "0";
		else if (t1[i] == '.')
		{
			i++;
			while (i < t1.length())
			{
				t1_2.push_back(t1[i]);
				i++;
			}
		}
		while(t1_2[t1_2.length() - 1] == '0' && t1_2.length() > 1) t1_2.pop_back(); 
		i = 0;
		while (t2[i] != '.' && i < t2.length())
		{
			t2_1.push_back(t2[i]);
			i++;
		}
		if (i >= t2.length())
			t2_2 = "0";
		else if (t2[i] == '.')
		{
			i++;
			while (i < t2.length())
			{
				t2_2.push_back(t2[i]);
				i++;
			}
		}
		while(t2_2[t2_2.length() - 1] == '0' && t2_2.length() > 1) t2_2.pop_back();

		if((t1_2.length() < t2_2.length()))
		{
			while(t1_2.length() < t2_2.length()) t1_2.push_back('0');
		}
		if((t2_2.length() < t1_2.length()))
		{
			while(t2_2.length() < t1_2.length()) t2_2.push_back('0');
		}

		if (instruction == "CmpEQ")
		{
			if ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) == stoull(t2_2)))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpNE")
		{
			if ((stoll(t1_1) != stoll(t2_1)) || ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) != stoull(t2_2))))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpLT")
		{
			if ((stoll(t1_1) < stoll(t2_1)) || ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) < stoull(t2_2))))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpLE")
		{
			if ((stoll(t1_1) < stoll(t2_1)) || ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) <= stoull(t2_2))))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpGT")
		{
			if ((stoll(t1_1) > stoll(t2_1)) || ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) > stoull(t2_2))))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
		if (instruction == "CmpGE")
		{
			if ((stoll(t1_1) > stoll(t2_1)) || ((stoll(t1_1) == stoll(t2_1)) && (stoull(t1_2) >= stoull(t2_2))))
			{
				R[getIndex(op1)] = "true";
				return;
			}
			R[getIndex(op1)] = "false";
			return;
		}
	}
	throw TypeMismatch(IP - 1);
}

void VM::Not(string op1)
{
	string t1;
	t1 = R[getIndex(op1)];
	if (isBoolean(t1))
	{
		if (t1 == "true")
			R[getIndex(op1)] = "false";
		if (t1 == "false")
			R[getIndex(op1)] = "true";
		return;
	}
	else
		throw TypeMismatch(IP - 1);
}

void VM::And(string op1, string op2)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if(isBoolean(t1) && isBoolean(t2))
	{
		if(t1 == "false" || t2 == "false") R[getIndex(op1)] = "false";
		if(t1 == "true" && t2 == "true") R[getIndex(op1)] = "true";
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Or(string op1, string op2)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if(isBoolean(t1) && isBoolean(t2))
	{
		if(t1 == "true" || t2 == "true") R[getIndex(op1)] = "true";
		if(t1 == "false" && t2 == "false") R[getIndex(op1)] = "false";
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Move(string op1, string op2)
{
	string t2;
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	R[getIndex(op1)] = t2;
}

void VM::Load(string op1, string op2)
{
	string t2;
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if(isAddress(t2))
	{
		t2.pop_back();
		int i = stoi(t2);
		R[getIndex(op1)] = staticVM.getValue(i); 
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Store(string op1, string op2)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if(isAddress(t1))
	{
		t1.pop_back();
		int i = stoi(t1);
		staticVM.setValue(i, t2);
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Jump(string op1)
{
	string t2;
	t2 = isRegister(op1) ? R[getIndex(op1)] : op1;
	if(isAddress(t2))
	{
		t2.pop_back();
		int temp = stoi(t2);
		if(temp < 0 || temp >= instructionVM.getSize()) throw InvalidDestination(IP - 1);
		IP = temp;
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::JumpIf(string op1, string op2)
{
	string t1, t2;
	t1 = R[getIndex(op1)];
	t2 = isRegister(op2) ? R[getIndex(op2)] : op2;
	if(isBoolean(t1) && isAddress(t2))
	{
		// t2.pop_back();
		// int temp = stoi(t2);
		// if(temp < 0 || temp >= instructionVM.getSize()) throw InvalidDestination(IP - 1);
		if(t1 == "true")
		{
			t2.pop_back();
			int temp = stoi(t2);
			if(temp < 0 || temp >= instructionVM.getSize()) throw InvalidDestination(IP - 1);
			IP = temp;
		}
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Call(string op1)
{
	string t2;
	t2 = isRegister(op1) ? R[getIndex(op1)] : op1;
	if(isAddress(t2))
	{
		if(stackVM.isFull()) throw StackFull(IP - 1);
		stackVM.pushStack(IP);
		t2.pop_back();
		int temp = stoi(t2);
		if(temp < 0 || temp >= instructionVM.getSize()) throw InvalidDestination(IP - 1);
		IP = temp;
		return;
	}
	else throw TypeMismatch(IP - 1);
}

void VM::Return()
{
	IP = stackVM.popStack();
}

// void VM::Halt()
// {
// 	exit(0);
// }

void VM::Input(string op1)
{
	//Literal or not literal
	string temp;
	getline(cin, temp);
	if((isInterger(temp) && temp[0] != '-') || (isFloat(temp) && temp[0] != '-') || isBoolean(temp))
	{
		R[getIndex(op1)] = temp;
	}
	else throw InvalidInput(IP);
}

void VM::Output(string op1)
{
	string t2;
	t2 = isRegister(op1) ? R[getIndex(op1)] : op1;
	if(isInterger(t2))
	{
		cout << stoi(t2);
	}
	else if(isFloat(t2))
	{
		cout << stod(t2);
	}
	else cout << t2;
}

void VM::execution(string s)
{
	string temp;
	temp = getIntrCode(s);
	if(temp == "Add" || temp == "Minus" || temp == "Mul" || temp == "Div") Arithmetic(getOperand1(s), getOperand2(s), getIntrCode(s));
	if(temp == "CmpEQ" || temp == "CmpNE" || temp == "CmpLT" || temp == "CmpLE" || temp == "CmpGT" || temp == "CmpGE")
		Comparison(getOperand1(s), getOperand2(s), getIntrCode(s));
	if(temp == "Not") Not(getOperand1(s));
	if(temp == "And") And(getOperand1(s), getOperand2(s));
	if(temp == "Or") Or(getOperand1(s), getOperand2(s));
	if(temp == "Move") Move(getOperand1(s), getOperand2(s));
	if(temp == "Load") Load(getOperand1(s), getOperand2(s));
	if(temp == "Store") Store(getOperand1(s), getOperand2(s));
	if(temp == "Jump") Jump(getOperand1(s));
	if(temp == "JumpIf") JumpIf(getOperand1(s), getOperand2(s));
	if(temp == "Call") Call(getOperand1(s));
	if(temp == "Return") Return();
	//if(temp == "Halt") Halt();
	if(temp == "Input") Input(getOperand1(s));
	if(temp == "Output") Output(getOperand1(s));
}

void VM::run(string filename)
{
	ifstream file(filename);
	string temp;

	while (!file.eof())
	{
		getline(file, temp);
		char t = temp[temp.length() - 1];
		if (!(t >= ' ' && t <= '~'))
			temp.pop_back();
		int tempVal = checkLoading(temp);
		instructionVM.addInstruction(temp);
		if (tempVal == 411)
			throw InvalidInstruction(instructionVM.getSize() - 1);
		if (tempVal == 412)
			throw InvalidOperand(instructionVM.getSize() - 1);
	}
	while (IP < instructionVM.getSize())
	{
		string instruction = instructionVM.getInstruction(IP);
		IP++;
		if(instruction == "Halt") break;
		execution(instruction);
	}

	file.close();
}
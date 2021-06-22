#include "notebook_header.h"

using namespace std;
abstr_emp::abstr_emp() : fname(""), lname(""), job("")
{
}

abstr_emp::abstr_emp(const string & fn, const string &  ln,
	const string &  j) : fname(fn), lname(ln), job(j)
{
}

void abstr_emp::ShowAll() const 
{
	cout << "First name: " << fname << endl;
	cout << "Last name: " << lname << endl;
	cout << "Job: " << job << endl;
}

void abstr_emp::SetAll()        
{
	cout << "Enter first name: ";
	cin >> fname;
	while (cin.get() != '\n')
		continue;
	cout << "Enter last name: ";
	cin >> lname;
	while (cin.get() != '\n')
		continue;
	cout << "Enter the job: ";
	getline(cin, job);
}

void abstr_emp::writeall(ofstream & f)
{
    f<<setw(80)<<setfill('=')<<endl;
    f<<setw(15)<<"First name: "<<fname<<endl;
    f<<setw(15)<<"Last name: "<<lname<<endl;
    f<<setw(15)<<"Job: "<<job<<endl;
}

// just displays first and last name
ostream & operator<<(ostream & os, const abstr_emp & e)
{
	os << e.lname << ", " << e.fname;
	return os;
}

abstr_emp::~abstr_emp()
{
}

employee::employee() : abstr_emp()
{
}

employee::employee(const string & fn, const string &  ln,
             const string &  j) : abstr_emp(fn, ln, j)
{
}

void employee::ShowAll() const
{
	cout << "Status: Employee" << endl;
	abstr_emp::ShowAll();
}
void employee::writeall(ofstream & f)
{
    abstr_emp::writeall(f);
}

void employee::SetAll()
{
	abstr_emp::SetAll();
}

manager::manager() : abstr_emp()
{
	inchargeof = 0;
}

manager::manager(const string & fn, const string & ln,
	const string & j, int ico) : abstr_emp(fn, ln, j)
{
	inchargeof = ico;
	if (inchargeof < 0)
	{
		cout << "Error, cannot be in charge of negative people." << endl;
		cout << "Setting inchargeof to 0" << endl;
		inchargeof = 0;
	}
}

manager::manager(const abstr_emp & e, int ico) : abstr_emp(e)
{
	inchargeof = ico;
	if (inchargeof < 0)
	{
		cout << "Error, cannot be in charge of negative people." << endl;
		cout << "Setting inchargeof to 0" << endl;
		inchargeof = 0;
	}
}

manager::manager(const manager & m) : abstr_emp(m)
{
	inchargeof = m.inchargeof;
}

void manager::ShowAll() const
{
	cout << "Status: Manager" << endl;
	abstr_emp::ShowAll();
	cout << "In charge of " << inchargeof << " people" << endl;
}

void manager::SetAll()
{
	abstr_emp::SetAll();
	cout << "Enter the number of people the manager is in charge of: ";
	cin >> inchargeof;
	if (inchargeof < 0)
	{
		cout << "Error, cannot be in charge of negative people." << endl;
		cout << "Setting inchargeof to 0" << endl;
		inchargeof = 0;
	}
}
void manager::writeall(ofstream &f)
{
    abstr_emp::writeall(f);
    f<<setw(15)<<"In charge of: "<<this->InChargeOf()<<" people"<<endl;
}

fink::fink() : abstr_emp(), reportsto("")
{
}

fink::fink(const string & fn, const string & ln,
	const string & j, const string & rpo) 
	: abstr_emp(fn, ln, j), reportsto(rpo)
{
}

fink::fink(const abstr_emp & e, const string & rpo) 
	: abstr_emp(e), reportsto(rpo)
{
}

fink::fink(const fink & e) : abstr_emp(e)
{
	reportsto = e.reportsto;
}

void fink::ShowAll() const
{
	cout << "Status: fink" << endl;
	abstr_emp::ShowAll();
	cout << "Reports to " << reportsto << endl;
}

void fink::SetAll()
{
	abstr_emp::SetAll();
	cout << "Enter whomever is reported to: ";
	getline(cin, reportsto);
}

void fink::writeall(ofstream & f)
{
    abstr_emp::writeall(f);
    f<<setw(15)<<"Reports to: "<<reportsto<<endl;
}

highfink::highfink() : abstr_emp(), manager(), fink()
{
}

highfink::highfink(const string & fn, const string & ln,
	const string & j, const string & rpo, int ico) 
	: abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo)
{
}

highfink::highfink(const abstr_emp & e, const string & rpo, int ico)
	: abstr_emp(e), manager(e, ico), fink(e, rpo)
{
}

highfink::highfink(const fink & f, int ico)
	: abstr_emp(f), manager(f, ico), fink()
{
}

highfink::highfink(const manager & m, const string & rpo)
	: abstr_emp(m), manager(m), fink(m, rpo)
{
}

highfink::highfink(const highfink & h) : abstr_emp(h), manager(h), fink(h)
{
}

void highfink::ShowAll() const
{
	cout << "Status: Highfink" << endl;
	abstr_emp::ShowAll();
	cout << "In charge of " << InChargeOf() << " people" << endl;
	cout << "Reports to " << ReportsTo() << endl;
}

void highfink::SetAll()
{
	abstr_emp::SetAll();
	cout << "Enter the number of people managed: ";
	cin >> InChargeOf();
	if (InChargeOf() < 0)
	{
		cout << "Error, cannot be in charge of negative people." << endl;
		cout << "Setting inchargeof to 0" << endl;
		InChargeOf() = 0;
	}
	cin.get(); 	
	cout << "Enter whomever is reported to: ";
	getline(cin, ReportsTo());
}

void highfink::writeall(ofstream & f)
{
    abstr_emp::writeall(f);
    f<<setw(15)<<"In charge of: "<<this->InChargeOf()<<" people"<<endl;
    f<<setw(15)<<"Reports to: "<<ReportsTo()<<endl;
}
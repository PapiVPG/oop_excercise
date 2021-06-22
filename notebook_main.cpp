#include "notebook_header.h"

int max = 5;
void showfile(ifstream & d)
{
    string exp;
    while (!d.eof())
    {
        getline(d,exp);
        cout<<exp<<endl;
    }
    
}

void showmenu()
{
    cout<<"You can create max "<<::max<<" workers"<<endl;
    cout<<"press 1 to create emplyee \tpress 2 to create manager"<<endl;
    cout<<"press 3 to create fink    \tpress 4 to create highfink"<<endl;
    cout<<"press q to quit programm"<<endl;
    --::max;
}

int main(){
    abstr_emp * pc[::max];
    string filename ="cadre.txt" ;
    ifstream file;
    file.open(filename.c_str());

    if (file.is_open())
    {
        cout<<"Your file content: "<<endl;
        showfile(file);
        file.close();
    }
    
    
    ofstream sfile;
    sfile.open(filename.c_str(),ios::in | ios::app);
    if (!sfile.is_open())
    {
        cerr<<"Could not open "<<filename<<" file"<<endl;
        exit(EXIT_FAILURE);
    }
    showmenu();
    char answer;
    int i = 0;
    int z = ::max;
    while(cin>>answer && i <=z)
    {
        if(answer == 'q')
            break;
        switch (answer)
        {
        case '1':
            pc[i] = new employee;
            pc[i] ->SetAll();
            pc[i] ->writeall(sfile);
            break;
        case '2':
            pc[i] = new manager;
            pc[i]-> SetAll();
            pc[i] ->writeall(sfile);
            break;
        case '3':
            pc[i] = new fink;
            pc[i]-> SetAll();
            pc[i] ->writeall(sfile);
            break;
        case '4':
            pc[i] = new highfink;
            pc[i]-> SetAll();
            pc[i] ->writeall(sfile);
            break;
        default:
            cout<<"Wrong value. Try again. "<<endl;
            --i;
            ++::max;
            break;
        }
        ++i;
        if (i == z)
            break;
        showmenu();
        

        
    }
    sfile.close();

    ifstream ofile(filename.c_str());
    if (i>0)
       showfile(ofile);
    for (int k = 0; k<z;++k)
    {
        delete pc[i];
    }
   
    return 0;
}
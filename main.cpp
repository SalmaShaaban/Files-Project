#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<bits/stdc++.h>
using namespace std;
class Employee
{
private:
    string name;
    string position;
    string id;
    string dept_id;
    string idArray[10];
    string byteOffsett[10];
    int counter=0;

public:
    Employee(){

    }
    void add(string name,string id,string dept_id,string postion,fstream& EmployeesFile,fstream& EmployeesPrimaryIndex)
   {
       this->name=name;
       this->id=id;
       this->dept_id=dept_id;
       this->position=postion;
       idArray[counter]=id;
       int recordLength;
       int id_length;
       int byte_offset;

       EmployeesFile.seekp(0,ios::end);
       byte_offset = EmployeesFile.tellg();

       EmployeesFile << "#";
       recordLength = 3 + name.length()+id.length()+dept_id.length()+position.length();
       if (recordLength<10 && recordLength>0)
           EmployeesFile<<"00";
       else if (recordLength>=10 && recordLength<100)
           EmployeesFile<<"0";
       EmployeesFile<<recordLength;
       EmployeesFile<<id<<",";
       EmployeesFile<<name<<",";
       EmployeesFile<<dept_id<<",";
       EmployeesFile<<position;

       EmployeesPrimaryIndex.seekp(0,ios::end);
       EmployeesPrimaryIndex<<id;
       id_length = id.length();
       while(id_length<13)
       {
           EmployeesPrimaryIndex<<"&";
           id_length++;
       }
       if (byte_offset<10 && byte_offset>=0)
           EmployeesPrimaryIndex<<"000";
       else if (byte_offset>=10 && byte_offset<100)
           EmployeesPrimaryIndex<<"00";
       else if (byte_offset>=100 && byte_offset<1000)
           EmployeesPrimaryIndex<<"0";

       EmployeesPrimaryIndex<<to_string(byte_offset);
       byteOffsett[counter]= to_string(byte_offset);
       cout<<byteOffsett[counter];
       counter++;
   }

   void sortFile(fstream& EmployeesPrimaryIndex, int left, int right)
       {
           int i = left;
           int j = right;
           string tmp;
           string pivot = idArray[(left + right) / 2];
           while (i <= j) {
               while (idArray[i] < pivot)
                   i++;
               while (idArray[j] > pivot)
                   j--;
               if (i <= j) {
                   tmp = idArray[i];
                   idArray[i] = idArray[j];
                   idArray[j] = tmp;
                   i++;
                   j--;
               }
           }
           if (left < j)
               sortFile(EmployeesPrimaryIndex, left, j);
           if (i < right)
               sortFile(EmployeesPrimaryIndex, i, right);



       /*EmployeesPrimaryIndex.seekg(0,ios::beg);
       string curID;
       int len,countID=0;
       char y;
       while (true)
       {
           len=0;
           curID="";
           while (len < 13)
           {
               EmployeesPrimaryIndex>>y;
               curID+=y;
               len++;
           }
           countID++;
           if (id>curID)
           {
               EmployeesPrimaryIndex.seekp(4,ios::cur);
           }
           else if (id <curID)
           {
               break;
           }
           else if (id==curID)
           {
               cout<<"Same ID go to search method to get it\n";
               break;
           }


       }
       cout<<countID<<" "<<curID<<endl;*/

   }
    string getidArray(int i){
        return idArray[i];
   }
   string search(string sid,fstream& EmployeesFile,fstream& EmployeesPrimaryIndex)
   {
       for(int i=0;i<counter;i++)
        {
            if (sid==idArray[i])
            {
                cout<<"Found";
                cout<<"byteOffset: "<<byteOffsett[i]<<endl;
                return byteOffsett[i];
            }

        }
/*
       EmployeesPrimaryIndex.seekp(0,ios::beg);
       string indexId="";
       int counter1=0;
       char z;
       string curID;
       int len,countID=0;
       char y;
       string byteOffset;
       bool check=false;
       while (!EmployeesPrimaryIndex.eof())
       {
           byteOffset="";
           len=0;
           curID="";
           while (len < 13)
           {
               EmployeesPrimaryIndex>>y;
               curID+=y;
               len++;
           }
            cout<<curID;
           curID.substr(0,'&');
           cout << curID;
           countID++;
           len=0;
           while (len<4){
               EmployeesPrimaryIndex>>y;
               byteOffset+=y;
               len++;
           }
           if (sid==curID) {
               cout<<"byte: "<<byteOffset<<endl;
               //EmployeesFile.seekp(byteOffset,ios::cur);
                cout<<"There is found in "<<byteOffset<<endl;
                check=true;
           }
           else
           {
               check = false;
           }

       }
       if (check == false)
           cout<<"Not found\n";

*/
   }

   void deleteEmp(string did,fstream& EmployeesFile,fstream& EmployeesPrimaryIndex)
    {
        string byteoffset = search(did,EmployeesFile,EmployeesPrimaryIndex);
        for(int i=0;i<counter;i++){
            if (byteOffsett[i]==byteoffset){

                int x= stoi(byteoffset);
                EmployeesFile.seekp(x,ios::beg);
                EmployeesFile.write("^",ios::cur);
                cout<<"Deleted"<<endl;

            }
        }


    }
   void printEmp(string did,fstream& EmployeesFile,fstream& EmployeesPrimaryIndex)
   {
       string info;

       char z;
       string byteoffset = search(did,EmployeesFile,EmployeesPrimaryIndex);
       for(int i=0;i<counter;i++){
           if (byteOffsett[i]==byteoffset) {

               int x = stoi(byteoffset);
               EmployeesFile.seekp(x, ios::beg);
           }
       }
       EmployeesFile.seekp(1,ios::cur);
        int len =0;
        string length="";
        char zz;
       while(len<3)
            {
                EmployeesFile>>zz;
                length+=zz;
                len++;

            }
            int lennn= stoi(length);
            int i=0;
            while(i<lennn){
                EmployeesFile>>z;
                info+=z;
                i++;
            }
            cout<<info;
}};
struct SIndex{
string Dept_Name;
int pointer;
/*bool operator<(const SIndex &r) const {
		if (strcmp(Name, r.Name) == 0)
			return strcmp(ID, r.ID) < 0;
		return strcmp(Name, r.Name) < 0;
	}*/
};
struct PrimaryI
{
    int offset;
    string DeptID;
    /*bool operator <(const PrimaryI &r) const
    { // for the sort function
		return strcmp(DeptID, r.DeptID) < 0;
	}*/
};
struct node{
string Dept_ID;
int refrence;
node*next;
int ptr;
};
node*head= NULL;
int counter=0;
void insertNode(string value,int refrence,int ptr){
counter++;
node * newNode, *last;
newNode= new node;
newNode->Dept_ID=value;
newNode->refrence=refrence;
newNode->ptr=ptr;
if(head==NULL){
  head = newNode;
  newNode->next=NULL;
}
else{
  last = head;
  while(last->next!=NULL){
    if(last->Dept_ID==value){
     last->ptr=counter;
    }
    last= last->next;


  }
    last->next=newNode;
    newNode->next=NULL;
}
}
string searchList(int ref)
{
    node *tmp;
    int i=0,flag;
    tmp = head;
    if(head == NULL)
    {
        cout<<"\nEmpty List\n";
    }
    else
    {
        while (tmp!=NULL)
        {
            if(tmp->refrence==ref)
            {
              if(tmp->ptr!= -1){
                searchList(tmp->ptr);
              }
              else{
                  return(tmp->Dept_ID);

              }
        }

    }
    return(0);
}
}

int addSIndex (SIndex SIndxArray[], SIndex s1, int n){
    int flag=0;
    SIndex temp;
for(int i=0; i<n ; i++){
        if(SIndxArray[i].Dept_Name==s1.Dept_Name){
          flag=1;
          return(SIndxArray[i].pointer);
        }
      /*if(SIndxArray[i].Dept_Name>s1.Dept_Name){
         temp.Dept_Name= SIndxArray[i].Dept_Name;
         temp.pointer=SIndxArray[i].pointer;
         SIndxArray[i].Dept_Name=s1.Dept_Name;
         SIndxArray[i].pointer=s1.pointer;
         s1.Dept_Name=temp.Dept_Name;
         s1.pointer=temp.pointer;
        }*/
}
if (flag==0){
    SIndxArray[n]=s1;
    return -1;
}

}
void WriteSIndex(SIndex SIndxArray[], int recNumbers, fstream&out) {
	for (int i = 0; i < recNumbers; i++){
	//	out.write((char*) &SIndxArray[i].Dept_Name, sizeof SIndxArray[i].Dept_Name);
      //  out.write((char*) &SIndxArray[i].pointer, sizeof SIndxArray[i].pointer);
      out<<SIndxArray[i].pointer<<"  "<<SIndxArray[i].Dept_Name <<'#';
}
}
/*void ReadSIndex(SIndex SIndxArray[], int recNumbers, fstream& out) {
	for (int i = 0; i < recNumbers; i++)

}*/
class Department
{
public:
string Dept_ID;
string Dept_Name;
string Dept_Manager;
fstream dep,SIndexFileOut,PI;
void addDep(int number)
{

dep.open("Department.txt", ios::out|ios::in);
SIndexFileOut.open("WriteSecondryIndex.txt",ios::out|ios::in);
Department d;
int length=0,p;
SIndex s;
SIndex *SIndxArray = new SIndex[number];
PI.open("PrimaryIndex.txt", ios::out);
PrimaryI *PrimaryIndexArray = new PrimaryI[number];
int m;
int sum =0;
for(int i= 0; i<number; i++)
{
    length = 0;
    cout<<"Enter Department ID:";
    cin>>d.Dept_ID;
    length= length + d.Dept_ID.length();
    PrimaryIndexArray[i].DeptID=d.Dept_ID;

    cout<<"Enter Department Name:";
    cin>>d.Dept_Name;

    length= length + d.Dept_Name.length();

    cout<<"Enter Department Manager:";
    cin>>d.Dept_Manager;
    length= length + d.Dept_Manager.length();

     int *arr= new int[number];
    for(m =0; m<number; m++)
    {
        sum = sum + (length + 3);
        arr[m] = sum;
        PI<<PrimaryIndexArray[i].DeptID<<"|"<<arr[m]<<"#";
        break;
    }
    /*for(int h = 0; h<number; h++)
    {
        if (PrimaryIndexArray[i].DeptID < PrimaryIndexArray[i+1].DeptID)
        {
            swap(PrimaryIndexArray[i],PrimaryIndexArray[i+1]);
            PI<<PrimaryIndexArray[i].DeptID<<"|"<<PrimaryIndexArray[i].offset<<"#";
        }
    }*/
    //sort(PrimaryIndexArray, PrimaryIndexArray + number);
     /*dep.seekg(length, ios::beg);
     int new_offset = dep.tellg()+(length+3);
     PI<<PrimaryIndexArray[i].DeptID<<"|"<<new_offset<<"#"; //first record printed*/

    dep<<length+3;
    dep<<d.Dept_ID<<"|";
    dep<<d.Dept_Name<<"|";
    dep<<d.Dept_Manager<<"#";
    s.Dept_Name=d.Dept_Name;
    s.pointer=i;
    p= addSIndex(SIndxArray,s,i);

    insertNode(d.Dept_ID,i,p);
	}
	//sort(SIndxArray,SIndxArray+number);
	WriteSIndex(SIndxArray, number, SIndexFileOut);
    //ReadSIndex(SIndxArray,number,SIndexFileIn);

//quickSort(PrimaryIndexArray,0,number-1);
dep.close();
PI.close();
}

/*void deleteDep(int offset, fstream dep)
{
    for(int x=0; x<; x++)
    {

    }
}*/
};
/*class Select{
    public:
Department d;
void selectFromDepart(string id){
string line ;
if (d.SIndexFileOut.is_open())
  {
    while ( getline(d.SIndexFileOut,line) )
    {
      cout << line << '\n';
    }
    d.SIndexFileOut.close();
  }



}*/

int main()
{
    Department d;
   d.addDep(5);
/*Select s;
string t ="02";
s.selectFromDepart(t);*/

    fstream EmployeesFile("Employees.txt", ios::out|ios::in);
    fstream EmployeesPrimaryIndex("EmployeesPrimary.txt", ios::out|ios::in);
    int x;
    if (!EmployeesFile.good() ||!EmployeesPrimaryIndex.good()  )
    {
        cout << "Error opening file. Program aborting.\n";
        return -1;
    }
    int count=0;
    Employee e;
    string name, id, dept_id, position;
    while (true) {
        cout << "\n1.Add \n2.Search \n3.Delete \n4.Print \n";
        cin >> x;
        cin.ignore();
        if (x==1) {

            count++;
            cout << "\n Employee Name: ";
            getline(cin, name);
            if (name.length() > 50) {
                cout << "Name is greater than 50 ";
                return -1;
            }

            cout << "\n Employee ID: ";
            getline(cin, id);
            if (id.length() > 13) {
                cout << "ID is greater than 13 ";
                return -1;
            }

            cout << "\n Department ID: ";
            getline(cin, dept_id);
            if (dept_id.length() > 30) {
                cout << "Department id is greater than 30 ";
                return -1;
            }

            cout << "\n Position: ";
            getline(cin, position);
            if (position.length() > 50) {
                cout << "Position is greater than 50 ";
                return -1;
            }
            EmployeesPrimaryIndex.seekg(0, ios::end);
            int right = EmployeesPrimaryIndex.tellg();
            //e.sortFile(EmployeesPrimaryIndex,0,right--);
            e.add(name, id, dept_id, position, EmployeesFile, EmployeesPrimaryIndex);
        }
        else if (x == 2) {
            cout<<"Enter ID: ";
            cin>>id;
            e.search(id,EmployeesFile,EmployeesPrimaryIndex);
        }
        else if (x==3){
            cout<<"Enter ID: ";
            cin>>id;
            e.deleteEmp(id,EmployeesFile,EmployeesPrimaryIndex);

        }
        else if (x==4) {
            cout << "Enter ID: ";
            cin >> id;
            e.printEmp(id,EmployeesFile,EmployeesPrimaryIndex);

        }
            else
               break;
    }

    EmployeesFile.close();
    EmployeesPrimaryIndex.close();


    return 0;
}

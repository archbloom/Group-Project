//Assignment No.: 4

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fstream>
using namespace std;
class FileOpen
{
  fstream fileName;
public:
  FileOpen()
  {
    cout<<"Welcome to SVC!!\n";
  }
  void commit(char []);
  void display(char[]);
}; // class to control the operations
void FileOpen :: display(char ver[]) // display the contents of the file
{
  // cout<<"\nthis is display\n";
  char file[256]=".test";
  cout<<"Showing the version : "<<ver;
  strcat(file,ver);
  strcat(file,".txt");
  cout<<"\nFile Name : "<<file<<endl;
  struct tm* clock;
  struct stat attrib; // stat is for
  stat(file,&attrib);
  clock = localtime(&attrib.st_mtime);
  char timestr[100];
  strftime(timestr,100,"%Y-%m-%d at %H:%M:%S",clock);
  cout<<"Last modified on : "<<timestr<<endl;
  cout<<"Size of the file is : "<<attrib.st_size<<" bytes.\n";
  cout<<"\n--------------------------------------\n";
  system(("(cat "+string(file)+" )").c_str());
}
void FileOpen :: commit(char file[])
{
  fstream count;
  char data[256];
  count.open(".count.txt",ios::in);//for reading only
  count.getline(data,100);
  // cout<<"count file : "<<data<<endl;
  count.close();
  char newfile[]=".test";
  strcat(newfile,data);
  strcat(newfile,".txt");//file is-->.test(data).txt
  strcat(newfile," ");
  strcat(newfile,file);
  // cout<<"new file : "<<newfile<<"   argv[1]"<<file;
  int cmp=system(("(cmp --silent "+string(newfile)+")").c_str());
  // cmp is system command to compare the file
  if(cmp==0) // if file contents are same..
  {
    cout<<"\nNo change found in new file and lastly updated file.\n";
    cout<<"No new version is created.\n";
  }
  else // if contents are different
  {
    int updatedData = atoi(data);
    count.open(".count.txt",ios::out);//for updating the version only
    updatedData++;
    count<<updatedData;
    count.close();
    count.open(".count.txt",ios::in);//for reading only
    count.getline(data,100);
    cout<<"new version of file : "<<data<<endl;
    count.close();
    char newfile[]=".test";
    strcat(newfile,data);
    strcat(newfile,".txt");
    system(("(touch "+string(newfile)+" )").c_str()); // create new file-->.test(data+1).txt
    strcat(file," > ");
    strcat(file,newfile);
    system(("(cat "+string(file)+")").c_str()); // copy the latest version of data to .test(data+1).txt
    cout<<"Newly create file versio name : "<<newfile<<endl; // gives the latest version file name
  }
}
int main(int argc, char** argv)
{
  FileOpen OpenFile;
  if(argc!=2) // chrck if arg is provided
  {
    cout<<"Provide the operation to be performed as argument.\n";
    cout<<"For eg.:\n svc N OR svc filename.txt\n";
    exit(0);
  }
  else
  {
    if(isdigit(*argv[1]))//show the Nth version content of file
    {
      OpenFile.display(argv[1]);
    }
    else // commit the file
    {
      OpenFile.commit(argv[1]);
    }
  }
  cout<<endl;
  return 0;
}

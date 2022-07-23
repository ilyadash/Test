#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct path {//будем использовать заданную структуру
	char* From;
	char* To;
};

class PathClass {
	public:
	path unit_path;
	string From, To;
	PathClass() {
		unit_path.From = nullptr; 
		unit_path.To = nullptr; 
		From = ""; 
		To = ""; 
	}
	PathClass(char* From_in, char* To_in) {
		unit_path.From = From_in; 
		unit_path.To = To_in;
		From = From_in;
		To = To_in;
	}
	PathClass(string From_in, string To_in) {
		unit_path.From = const_cast<char*>(From_in.c_str()); 
		unit_path.To = const_cast<char*>(To_in.c_str());
		From = From_in;
		To = To_in;
	}
	void print() {
		cout<<From<<" "<<To<<"\n";
	}
};

class FullPath {
	public:
	vector<PathClass> paths;
	vector<PathClass> sorted_list;
	vector<string> result;
	void read_input() {
		ifstream input;
		input.open ("input.txt", ios::in);
		if (input.is_open())
		{
			//cout << "Reading from input file.\n";
		}
		else
		{
			//cout << "Error: Check input file!\n";
			return;
		}
		string line, str_From, str_To;
		unsigned int lines_num=0;
		stringstream ss0;
		getline (input,line);
		ss0<<line;
		ss0>>lines_num;
		for(unsigned int i=0;i<lines_num;i++){
			getline (input,line);
			stringstream ss;
			ss<<line;
			ss>>str_From>>str_To;
			PathClass buf_path(str_From,str_To);
			paths.push_back(buf_path);
		}
		input.close();
	}
	void sort() {
		//найдём путь, который должен быть первым:
		unsigned int begin_index=0;
		for(unsigned int i=0;i<paths.size();i++) {
			bool has_match_flag=0;
			for(unsigned int j=0;j<paths.size();j++) {
				if(paths[i].From==paths[j].To) {
					has_match_flag=1;
					break;
				}
			}
			if(has_match_flag==0) begin_index=i;
		}
		//поместим на нулевую позицию начальный маршрут:
		swap(paths[0],paths[begin_index]);
		//отсортируем от начала до конца:
		for(unsigned int i=0;i<paths.size();i++) {
			for(unsigned int j=i+1;j<paths.size();j++) {
				if(paths[i].To==paths[j].From) {
					swap(paths[i+1],paths[j]);
					break;
				}
			}
		}
	}
	void write_output() {
		ofstream output;
		output.open ("output.txt", ios::trunc);
		if (output.is_open())
		{
			output << paths[0].From <<" ";
			for(unsigned int i=0;i<paths.size();i++) {
				output << paths[i].To <<" ";
			}
			output.close();
		}
	}
	void print() {
		for(unsigned int i=0;i<paths.size();i++){
			paths[i].print();
		}
	}
};

int main() {
	FullPath result_path;
	result_path.read_input();//считываем из файла на диске
	result_path.sort();//сортируем вектор отрезков
	result_path.write_output();
	return 0;
}

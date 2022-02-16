#include <numeric>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>

using namespace std;
void replace(string &line, char at, char w){
    for(int i = 0; i < line.length(); i++){
        if(line[i] == at){
            line[i] = w;
        }
    }
}
// This function calculates the average prices per brand
void calculateAveragePerBrand(vector<string> vBrand, vector<float> vPrice, ofstream& out_stream){
    // Declaring a map to store the prices band wise
    map<string,vector<float> > BMap;
    // Storing the prices band wise
    for(int i = 0; i < vBrand.size(); i++){
        BMap[vBrand[i]].push_back(vPrice[i]);
    }
    // Writing the headers to the output file
    out_stream << "\tBrand\tAverage\n";
    // Declaring an iterator for map to iterate over the map
    map<string,vector<float> >::iterator it;
    // Iterating over the map
    for(it = BMap.begin(); it != BMap.end(); ++it){
        string currencyBrand = it->first;
        vector<float> curPrices = it->second;
        float BSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        float average = BSum / curPrices.size();
        out_stream << "\t" << currencyBrand << "\t" << average << "\n";
    }
    out_stream << endl;
}

void calculateSKUCount(vector<int> vYear,vector<int> vSKU, ofstream& out_stream){
    map<int,vector<int> > yearMap;
    for(int i = 0; i < vYear.size(); i++){
        yearMap[vYear[i]].push_back(vSKU[i]);
    }
    out_stream << "\tYear\tSKU's\n";
    map<int,vector<int> >::iterator it;
    for(it = yearMap.begin(); it != yearMap.end(); it++){
        out_stream << it->first << "\t";
        vector<int>::iterator sku_it;
        for(sku_it = it->second.begin(); sku_it != it->second.end(); sku_it++){
            out_stream << *sku_it;
            if(sku_it != it->second.end()){
                out_stream << " ";
            }
            else{
                out_stream << "\t";
            }
        }
        out_stream << "(Count: " << it->second.size() << ")" << endl;
    }
}
// This function calculates the average prices per category
void calculateAveragePerCategory(vector<string> vCategory, vector<float> vPrice, ofstream& out_stream){
    map<string,vector<float> > categoryMap;
    for(int i = 0; i < vCategory.size(); i++){
        categoryMap[vCategory[i]].push_back(vPrice[i]);
    }
    out_stream << "\tCategory\tAverage\n";
    map<string,vector<float> >::iterator it;
    for(it = categoryMap.begin(); it != categoryMap.end(); it++){
        string CurrencyCategory = it->first;
        vector<float> curPrices = it->second;
        float BSum = accumulate(curPrices.begin(), curPrices.end(),0.0);
        float average = BSum / curPrices.size();
        out_stream << "\t" << CurrencyCategory << "\t" << average << "\n";
    }
    out_stream << endl;
}
int main(){
    vector<int> vSKU;
    vector<string> vBrand;
    vector<string> vCategory;
    vector<int> vYear;
    vector<float> vPrice;
    // This variable reads data from the file
    ifstream in_stream;
    // This variable writes data to the file
    ofstream out_stream;
    out_stream.open("output.txt");// opening the output file
        MyWriteFile << "sku,brand,category,year,price";
        MyWriteFile << "\n";
        MyWriteFile << "111,ABC,A,2000,0.5";
        MyWriteFile << "\n";
        MyWriteFile << "112,ABC,B,2010,0.5";
        MyWriteFile << "\n";
        MyWriteFile << "113,ABC,C,2020,0.5";
        MyWriteFile << "\n";
        MyWriteFile << "211,ABC,A,2000,1.5";
        MyWriteFile << "\n";
        MyWriteFile << "212,ABC,B,2010,1.5";
        MyWriteFile << "\n";
        MyWriteFile << "213,ABC,C,2020,1.5";
        MyWriteFile << "\n";
        MyWriteFile << "321,XYZ,A,2020,1.0";
        MyWriteFile << "\n";
        MyWriteFile << "322,XYZ,A,2020,2.0";
        MyWriteFile << "\n";
        MyWriteFile << "323,XYZ,A,2020,3.0";
    in_stream.open("data.csv"); // opening the input file.
    // If file is opened
    if (!in_stream.fail()){
        string line;
        getline(in_stream,line);
        while (getline(in_stream, line)){
            replace(line,',',' ');
            stringstream ss(line);
            int iSKU;
            string brand;
            string category;
            int iYear;
            float fPrice;
            
            ss >> iSKU;
            ss >> brand;
            ss >> category;
            ss >> iYear;
            ss >> fPrice;

            vSKU.push_back(iSKU);
            vBrand.push_back(brand);
            vCategory.push_back(category);
            vYear.push_back(iYear);
            vPrice.push_back(fPrice);
        }
        in_stream.close(); // closing the file
    }
    // Else
    else{
        out_stream << "Unable to open file";
    }
    // Writing headers to the output file
    out_stream << "SKU" << "\t" << "Brand" << "\t" << "Category" << "\t\t" << "Year" << "\t" << "Price" << endl;
    // Writing rows read to the output file
    for (int j = 0; j < vSKU.size(); j++){
            out_stream << vSKU[j] << "\t" << vBrand[j] << "\t   " << vCategory[j] << "\t\t" << vYear[j] << "\t" << vPrice[j] << endl;
    }
    // Writing a newline to the output file
    out_stream << endl;
    calculateAveragePerBrand(vBrand,vPrice,out_stream);
    calculateAveragePerCategory(vCategory,vPrice,out_stream);
    calculateSKUCount(vYear,vSKU, out_stream);
    // Closing the input and output files
    in_stream.close();
    out_stream.close();
}


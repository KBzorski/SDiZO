#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;
   
float t_average(float* arr, int size)
{
    float average = arr[1];
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    average = sum / size;
    return average;
}
float t_min(float* arr, int size)
{
    float min=arr[1];
    for (int i = 0; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }

    return min;
}
float t_max(float* arr, int size)
{
    float max = arr[1];
    for (int i = 0; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

void menu(vector <string> options, int selected)
{
    cout << "\t\tMENU"<<endl;
    int i = 0;
    for (string option : options)
    {
        if (i == selected) 
            cout<<option<<"   <--"<<endl;
        else
            cout<<option<<endl;       
        i++;
    }
}

int main()
{    
    vector <string> options;
    options.push_back("1. Wgraj plik wejsciowy");
    options.push_back("2. Zapisz plik");
    options.push_back("3. Sortowanie algorytmem babelkowym");
    options.push_back("4. Sortowanie algorytmem szybkim");
    options.push_back("5. Sortowanie przez zliczanie");
    options.push_back("6. Budowanie BST i kopca");
    options.push_back("7. Sortowanie kopcowe");
    options.push_back("8. Zamknij program");
    options.push_back("9. OBLICZENIA TESTOWE");

    int selected = 0;
    char pressed='0';
    string file_path = "";
    bool float_type = false;
    float* float_array=new float[1];
    int* int_array=new int[1];
    int number_of_lines=0;
    string tmp_str[6] = {"","","","","",""};

    bool data = false;

    while ((selected==7 && pressed==13)==false)
    {
        system("cls");
        menu(options, selected);
        
        pressed = _getch();
        if (pressed == 'w')
        {
            if (selected > 0) 
                selected--;
            else 
                selected = options.size() - 1;
        }
        else if (pressed == 's')
        {
            if (selected < options.size() - 1)
                selected++;
            else 
                selected = 0;
        }
        else if (pressed == 13)
        {
            system("cls");
            //cout << "Wybrano opcje: " << selected + 1 << endl;
            //cin.get();
            switch (selected) {
            case 0:
            {
                
                cout << "Wybrano opcje: 1. Wgraj plik wejsciowy"<<endl;
                cout << "Wprowadz sciezke do pliku:";
                cin >> file_path;
                //cout << file_path;

                fstream myfile;
                //file_path = "C:\\Users\\kamil\\Downloads\\dane (1).csv";
                myfile.open(file_path, ios::in);
                //myfile.open("C:\\Users\\kamil\\Downloads\\dane (1).csv", ios::in);
                if (myfile.good() == false)
                {
                    cout << "Nieprawidlowa sciezka do pliku";
                }
                else
                {   
                    data = true;
                    string line = "";
                    getline(myfile, line);
                    tmp_str[0] = line;
                    getline(myfile, line);
                    tmp_str[1] = line;
                    getline(myfile, line);
                    tmp_str[2] = line;
                    string tmp_line="";
                    for (int i = 13; i < sizeof(line); i++) 
                    {   
                        if (isdigit(line[i]))
                            tmp_line += line[i];
                        else break;
                    }
                    line = tmp_line;
                    number_of_lines = atoi(line.c_str());
                    getline(myfile, line);
                    tmp_str[3] = line;
                    if (line[8] == 'f' && line[9]=='l' && line[10] == 'o' && line[11] == 'a' && line[12] == 't')
                    {
                        float_type = true;
                        float_array = new float[number_of_lines];
                    }
                    else if (line[8] == 'i' && line[9] == 'n' && line[10] == 't')
                    {
                        float_type = false;
                        int_array = new int[number_of_lines];
                    }
                    getline(myfile, line);
                    tmp_str[4] = line;

                    if (float_type == true)
                        for (int i = 0; i < number_of_lines; i++) 
                        {
                            getline(myfile, line);
                            float_array[i] = stof(line);
                        }
                    else if (float_type == false)
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            getline(myfile, line);
                            int_array[i] = stof(line);
                        }
                    
                    //for (int i = 0; i < number_of_lines; i++)
                    //{
                    //    if (float_type == true)
                     //       cout << float_array[i]<<endl;
                     //   else if (float_type == false)
                     //       cout << int_array[i]<<endl;
                    //}
                    cout << "Wczytano plik" << endl;
                }
                _getch();
                myfile.close();

                

                break;
            };
            case 1:
            {
                cout << "Wybrano opcje: 2. Zapisz plik"<<endl;
                if (data == true)
                {
                    cout << "Wprowadz sciezke do pliku wraz z formatem .csv: ";
                    cin >> file_path;
                    //file_path = "C:\\Users\\kamil\\Downloads\\dane (1) nowe.csv";
                    fstream myfile;
                    myfile.open(file_path, ios::out);
                    myfile << tmp_str[0] << endl;
                    myfile << tmp_str[1] << endl;
                    myfile << tmp_str[2] << endl;
                    myfile << tmp_str[3] << endl;
                    myfile << tmp_str[4] << endl;

                    if (float_type)
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            if (i == 0)
                                myfile << float_array[i] << tmp_str[5] << endl;
                            else
                                myfile << float_array[i] << endl;
                        }
                    else
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            if (i == 0)
                                myfile << int_array[i] << tmp_str[5] << endl;
                            else
                                myfile << int_array[i] << endl;
                        }

                    myfile.close();
                }
                else
                {
                    cout << "Nie wczytano danych" << endl;
                    _getch();
                }
                break;
            }
            case 2:
            {
                cout << "Wybrano opcje: 3. Sortowanie algorytmem babelkowym";
                _getch();
                break;
            }
            case 3:
            {
                cout << "Wybrano opcje: 4. Sortowanie algorytmem szybkim";
                _getch();
                break;
            }
            case 4:
            {
                cout << "Wybrano opcje: 5. Sortowanie przez zliczanie";
                _getch();
                break;
            }
            case 5:
            {
                cout << "Wybrano opcje: 6. Budowanie BST i kopca";
                _getch();
                break;
            }
            case 6:
            {
                cout << "Wybrano opcje: 7. Sortowanie kopcowe";
                _getch();
                break;
            }
            case 8:
            {
                cout << "Wybrano opcje: 9. OBLICZENIA TESTOWE";
                if (data == true)
                {

                    tmp_str[4] += ";MIN;MAX;SREDNIA";

                    if (float_type)
                        tmp_str[5] = ";" + to_string(t_min(float_array, number_of_lines)) + ";" + to_string(t_max(float_array, number_of_lines)) + ";" + to_string(t_average(float_array, number_of_lines));
                    else
                        tmp_str[5] = ";" + to_string(t_min((float*)int_array, number_of_lines)) + ";" + to_string(t_max((float*)int_array, number_of_lines)) + ";" + to_string(t_average((float*)int_array, number_of_lines));
                    cout << endl << "Obliczono wartosc minimalna, maksymalna, oraz srednia dla wczytanych danych.";
                }
                else
                    cout <<endl<< "Nie wczytano danych" << endl;
                _getch();
                break;
            }
            }
        }
    }
    delete[] int_array;
    delete[] float_array;
}
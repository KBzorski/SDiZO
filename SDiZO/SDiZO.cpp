#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <chrono>

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

void szybkie_sortowanie(int pierwszy, int rozmiar, float* tablica)
{
    int i = 0;
    int j = 0;
    float piwot = tablica[rozmiar];
    for (j = i = pierwszy; i < rozmiar; i++)
        if (tablica[i] < piwot)
        {
            swap(tablica[i], tablica[j]);
            j++;
        }
    swap(tablica[rozmiar], tablica[j]);
    if (pierwszy < j - 1)
        szybkie_sortowanie(pierwszy, j - 1, tablica);
    if (j + 1 < rozmiar)
        szybkie_sortowanie(j + 1, rozmiar, tablica);
}
void szybkie_sortowanie(int pierwszy, int rozmiar, int* tablica)
{
    int i = 0;
    int j = 0;
    int piwot = tablica[rozmiar];
    for (j = i = pierwszy; i < rozmiar; i++)
        if (tablica[i] < piwot)
        {
            swap(tablica[i], tablica[j]);
            j++;
        }
    swap(tablica[rozmiar], tablica[j]);
    if (pierwszy < j - 1)
        szybkie_sortowanie(pierwszy, j - 1, tablica);
    if (j + 1 < rozmiar)
        szybkie_sortowanie(j + 1, rozmiar, tablica);
}
bool sortowanie_bombelkowe(int rozmiar, float* tablica)
{
    bool sorted = true;
    for (int i = 0; i < rozmiar; i++)
        if (tablica[i] > tablica[i + 1])
        {
            if (sorted == true)
                sorted = false;
            swap(tablica[i], tablica[i + 1]);
        }
    if (sorted == false)
    {
        for (int j = 1; j < rozmiar; j++)
            for (int i = 0; i < rozmiar; i++)
                if (tablica[i] > tablica[i + 1])
                    swap(tablica[i], tablica[i + 1]);
    }
    else
        cout << endl << "Plik wejsciowy nie wymaga sortowania!" << endl;
    return sorted;
}
bool sortowanie_bombelkowe(int rozmiar, int* tablica)
{
    bool sorted = true;
    for (int i = 0; i < rozmiar; i++)
        if (tablica[i] > tablica[i + 1])
        {
            if (sorted == true)
                sorted = false;
            swap(tablica[i], tablica[i + 1]);
        }
    if (sorted == false)
    {
        for (int j = 1; j < rozmiar; j++)
            for (int i = 0; i < rozmiar; i++)
                if (tablica[i] > tablica[i + 1])
                    swap(tablica[i], tablica[i + 1]);
    }
    else
        cout << endl << "Plik wejsciowy nie wymaga sortowania!" << endl;
    return sorted;
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
    float* input_table_f = new float[1];;
    int* input_table_i = new int[1];
    int number_of_lines=0;
    string tmp_str[6] = {"","","","","",""};

    bool data = false;

    chrono::duration<double, std::milli> Time_Bombelkowe;
    chrono::duration<double, std::milli> Time_Quick;

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
                    if (float_type == false)
                    {
                        input_table_i = new int[number_of_lines];
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            input_table_i[i] = int_array[i];
                        }
                    }
                    else
                    {
                        input_table_f = new float[number_of_lines];
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            input_table_f[i] = float_array[i];
                        }
                    }
                    
                    cout << "Wczytano plik" << endl;
                }
                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
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
                    cout << "Zapisano plik";
                    cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                    _getch();
                }
                else
                {
                    cout << "Nie wczytano danych" << endl;
                    cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                    _getch();
                }
                break;
            }
            case 2:
            {
                cout << "Wybrano opcje: 3. Sortowanie algorytmem babelkowym"<<endl<<"Trwa sortowanie...";
                bool sorted = false;
                if (data == true)
                {                  
                    if (float_type == false)
                    {
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            int_array[i] = input_table_i[i];
                        }
                    }
                    else
                    {
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            float_array[i] = input_table_f[i];
                        }
                    }
                    auto start = chrono::high_resolution_clock::now();
                    if (float_type == true)
                        sorted=sortowanie_bombelkowe( number_of_lines - 1, float_array);
                    else
                        sorted=sortowanie_bombelkowe(number_of_lines - 1, int_array);
                    auto finish = chrono::high_resolution_clock::now();
                    Time_Bombelkowe = finish - start;
                    if (sorted == false)
                    {
                        cout << endl << "Sortowanie zakonczone";
                        cout << endl << "Czas sortowania:" << Time_Bombelkowe.count() << "ms"; 
                        
                    }
                }
                else
                    cout << endl << "Nie wczytano danych";
                
               
                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                _getch();
                break;
            }
            case 3:
            {
                cout << "Wybrano opcje: 4. Sortowanie algorytmem szybkim" << endl << "Trwa sortowanie...";
                
                if (data == true)
                {
                    if (float_type == false)
                    {
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            int_array[i] = input_table_i[i];
                        }
                    }
                    else
                    {
                        for (int i = 0; i < number_of_lines; i++)
                        {
                            float_array[i] = input_table_f[i];
                        }
                    }
                    bool check = false;
                    for (int i = 0; i < number_of_lines - 1; i++)
                        if (float_type == true)
                            {
                                if (float_array[i] > float_array[i + 1])
                                {
                                    check = true;
                                    break;
                                }
                            }
                        else
                            {
                                if (int_array[i] > int_array[i + 1])
                                {
                                    check = true;
                                    break;
                                }
                            }
                    if (check == true)
                    {
                        auto start = chrono::high_resolution_clock::now();
                        if (float_type == true)
                            szybkie_sortowanie(0, number_of_lines - 1, float_array);
                        else
                            szybkie_sortowanie(0, number_of_lines - 1, int_array);
                        auto finish = chrono::high_resolution_clock::now();
                        Time_Quick = finish - start;
                        cout << endl << "Sortowanie zakonczone";
                        cout << endl << "Czas sortowania:" << Time_Quick.count() << "ms";
                        
                    }
                    else
                        cout << endl << "Plik wejsciowy nie wymaga sortowania!" << endl;              
                }
                else
                    cout <<endl<< "Nie wczytano danych";           
                
                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                _getch();
                break;
            }
            case 4:
            {
                cout << "Wybrano opcje: 5. Sortowanie przez zliczanie";

                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                _getch();
                break;
            }
            case 5:
            {
                cout << "Wybrano opcje: 6. Budowanie BST i kopca";
                _getch();

                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                break;
            }
            case 6:
            {
                cout << "Wybrano opcje: 7. Sortowanie kopcowe";

                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
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
                cout << endl << "Wcisnij dowolny klawisz aby powrocic do menu" << endl;
                _getch();
                break;
            }
            }
        }
    }
    delete[] int_array;
    delete[] float_array;
    delete[] input_table_f;
    delete[] input_table_i;
}
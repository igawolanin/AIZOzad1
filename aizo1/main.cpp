#include <iostream> //for input and output
#include <string> //using strings
#include <fstream> //reading from file
#include <cstdlib> //using random numbers

using namespace std;
template <typename T>
class Sorter {
public:
    /* -----HELP CLASEES----- */
    enum class PivotType {
            LEFT,    // Skrajny lewy element
            RIGHT,   // Skrajny prawy element
            MIDDLE,  // Środkowy element
            RANDOM   // Losowy element
        };

    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    
    
    /* -----QUICKSORT----- */
    void quicksortLeft(T* tab, int size) {
        quicksort(tab, 0, size - 1, PivotType::LEFT);
        }

        // Sortowanie z pivotem prawym
    void quicksortRight(T* tab, int size) {
        quicksort(tab, 0, size - 1, PivotType::RIGHT);
        }

        // Sortowanie z pivotem środkowym
    void quicksortMiddle(T* tab, int size) {
        quicksort(tab, 0, size - 1, PivotType::MIDDLE);
        }

        // Sortowanie z pivotem losowym
    void quicksortRandom(T* tab, int size) {
        quicksort(tab, 0, size - 1, PivotType::RANDOM);
        }
    
    
    void quicksort(T* tab, int left, int right, PivotType pivotType) {
        if (left < right) {  // Rekurencyjne sortowanie tylko wtedy, gdy left < right
            int pivot_index = partition(tab, left, right, pivotType);  // Ustal pivot i przeprowadź partycjonowanie
            quicksort(tab, left, pivot_index - 1, pivotType);   // Rekurencyjne sortowanie lewej części tablicy
            quicksort(tab, pivot_index + 1, right, pivotType);  // Rekurencyjne sortowanie prawej części tablicy
        }
    }

    // Funkcja partycjonująca - wybiera pivot, przestawia elementy w tablicy
    int partition(T* tab, int left, int right, PivotType pivotType) {
        int pivot_index = choosePivot(tab, left, right, pivotType);  // Wybierz pivot na podstawie typu
        T pivot_value = tab[pivot_index]; // Pobierz wartość pivota
        swap(tab[pivot_index], tab[right]); // Przenieś pivot na koniec tablicy (do ostatniej pozycji)
        int store_index = left;  // Zmienna, która będzie przechowywać indeks elementu, który powinien znaleźć się po lewej stronie pivota

        for (int i = left; i < right; i++) {
            if (tab[i] < pivot_value) {  // Jeśli bieżący element jest mniejszy od pivota
                swap(tab[i], tab[store_index]);  // Zamień miejscami elementy
                store_index++;  // Zwiększ indeks miejsca, w którym powinien być pivot
            }
        }

        swap(tab[store_index], tab[right]); // Przenieś pivot na swoje ostateczne miejsce
        return store_index;  // Zwróć indeks, na którym znajduje się pivot po partycjonowaniu
    }

    // Funkcja wybierająca pivot na podstawie podanego typu
    int choosePivot(T* tab, int left, int right, PivotType pivotType) {
        switch (pivotType) {
            case PivotType::LEFT:
                return left; // Skrajny lewy element tablicy
            case PivotType::RIGHT:
                return right; // Skrajny prawy element tablicy
            case PivotType::MIDDLE:
                return left + (right - left) / 2; // Środkowy element tablicy
            case PivotType::RANDOM:
                return left + std::rand() % (right - left + 1); // Losowy element tablicy
            default:
                return right; // Domyślnie prawy pivot
        }
    }
    
    
    
    
    /* -----HEAP SORT----- */
    void heapify(T* tab, int size, int i) {
        int largest = i;           // Korzeń
        int left = 2 * i + 1;      // Lewy dziecko
        int right = 2 * i + 2;     // Prawy dziecko

        // Sprawdź, czy lewe dziecko jest większe od korzenia
        if (left < size && tab[left] > tab[largest])
            largest = left;

        // Sprawdź, czy prawe dziecko jest większe od największego elementu
        if (right < size && tab[right] > tab[largest])
            largest = right;

        // Jeśli największy element nie jest korzeniem
        if (largest != i) {
            swap(tab[i], tab[largest]);  // Zamień korzeń z największym elementem
            // Rekurencyjnie porządkuj poddrzewo
            heapify(tab, size, largest);
        }
    }

    void heapsort(T* tab, int size) {
        // Budowanie kopca (porządkowanie tablicy)
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(tab, size, i);
        }

        // Sortowanie kopca
        for (int i = size - 1; i > 0; i--) {
            // Zamień obecny korzeń (największy element) z ostatnim elementem tablicy
            swap(tab[0], tab[i]);

            // Zbuduj kopiec na zmniejszonym zbiorze elementów
            heapify(tab, i, 0);
        }
    }
    
    
    
    /* -----SHELL SORT----- */
    void shellsortShell(T* tab, int size) {
        int gap = size / 2;  // Początkowy odstęp

        while (gap > 0) {
            for (int i = gap; i < size; i++) {
                T temp = tab[i];
                int j = i;
                while (j >= gap && tab[j - gap] > temp) {
                    tab[j] = tab[j - gap];
                    j -= gap;
                }
                tab[j] = temp;
            }
            gap /= 2;  // Zmniejszanie odstępu
        }
    }
    
    void shellSortHibbard(T* tab, int size) {
        int k = 1;
        while ((1 << k) - 1 < size) {
            k++;  // Zwiększamy k aż gap będzie większy lub równy size
        }

        k--;  // Teraz k jest największym możliwym takim, że (2^k - 1) < size
        while (k >= 0) {
            int gap = (1 << k) - 1;  // Obliczamy gap na podstawie wzoru Hibbarda
            for (int i = gap; i < size; i++) {
                T temp = tab[i];
                int j = i;
                while (j >= gap && tab[j - gap] > temp) {
                    tab[j] = tab[j - gap];
                    j -= gap;
                }
                tab[j] = temp;
            }
            k--;  // Zmniejszamy k
        }
    }
    
    
    /* -----INSERTION SORT----- */
    void insertionSort(T* tab, int size) {
        for (int i = 1; i < size; i++) {
            T key = tab[i];   // Wybieramy element do wstawienia
            int j = i - 1;

            // Przesuwamy większe elementy o jedno miejsce w prawo
            while (j >= 0 && tab[j] > key) {
                tab[j + 1] = tab[j];
                j--;
            }

            // Wstawiamy element na odpowiednią pozycję
            tab[j + 1] = key;
        }
    }
};















template <typename T>
void readArrayFromFile(T*& tab, int& size, const string& filename) {
    if (tab!= nullptr) delete[] tab;
    ifstream file(filename);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    // Wczytujemy rozmiar tablicy z pliku i przypisujemy do zmiennej size
    file >> size;

    // Alokujemy pamięć na tablicę odpowiedniego typu
    tab = new T[size];

    // Wczytujemy kolejne elementy tablicy
    for (int i = 0; i < size; ++i) {
        file >> tab[i];
    }
}

template <typename T>
void printArray(T* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename T>
void copyArray(T*& cloneArray, T* originalArray, int size) {
    // Jeśli tablica klonowa już istnieje, to ją zwolnij
    if (originalArray == nullptr || size <= 0) {
            cout << "Error: originalArray is not initialized or has invalid size.\n";
            return;
    }
    
    if (cloneArray != nullptr) {
        delete[] cloneArray;
    }
    
    cloneArray = new T[size];
    
    // Kopiujemy zawartość tablicy
    for (int i = 0; i < size; ++i) {
        cloneArray[i] = originalArray[i];
    }
}

void generateRandomIntArray(int*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab;
    }
    tab = new int[size];
    for (int i = 0; i < size; ++i) {
        // Generowanie losowej liczby int w pełnym zakresie
        tab[i] = rand() % 200000 - 100000;  // Zakres od -100000 do 100000 (można dostosować)
    }
}

// Funkcja do generowania tablicy losowej dla typu float
void generateRandomFloatArray(float*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab;
    }
    tab = new float[size]; // Alokacja pamięci na tablicę float
    for (int i = 0; i < size; ++i) {
        tab[i] = static_cast<float>(rand()) / RAND_MAX * (2 * std::numeric_limits<float>::max()) - std::numeric_limits<float>::max();   // Generowanie losowych liczb float (0 - 100.0)
    }
}


int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    int* intArray = nullptr;
    float* floatArray = nullptr;
    int* cloneIntArray = nullptr;
    float* cloneFloatArray = nullptr;
    int size = 0;
    int clonesize = 0;
        
    int dataTypeChoice;
    int choice;
    bool isFloat = false;
    
    Sorter<float> floatSorter;
    Sorter<int> intSorter;
    
    
    do {
        cout << "Choose data type:\n";
        cout << "1. int\n";
        cout << "2. float\n";
        cout << "3. EXIT\n\n";
        cin >> dataTypeChoice;

        if (dataTypeChoice == 3) break;

        if (dataTypeChoice == 1) {
            isFloat = false;
        }
        else if (dataTypeChoice == 2) {
            isFloat = true;
        }
        else {
            cout << "Incorrect choice, try again\n";
            continue;
        }
        
        
    do {
        cout << "\nMenu\n";
        cout << "1. Read array from file\n";
        cout << "2. Generate array of given size with random numbers\n";
        cout << "3. Output lastly created array\n";
        cout << "4. Sort the array with chosen algorithm\n";
        cout << "5. Output sorted array\n";
        cout << "6. EXIT\n";
        cin >> choice;
        switch(choice) {
            case 1:
            {
                // Wczytanie tablicy z pliku
                string filename;
                cout << "Enter filename: \n";
                cin >> filename;
                
                if (isFloat) {
                    readArrayFromFile(floatArray, size, filename);
                } else {
                    readArrayFromFile(intArray, size, filename);
                }
                break;
            }
            case 2:
            {
                cout << "Enter the size of the array: \n";
                cin >> size;
                if (isFloat) {
                    generateRandomFloatArray(floatArray, size);
                } else {
                    generateRandomIntArray(intArray, size);
                }
                break;
            }
                
            case 3:
            {
                if (isFloat)
                {
                    if (floatArray != nullptr && size > 0)
                        printArray(floatArray, size);
                    else
                        cout << "No array\n";
                    break;
                }
                else if (!isFloat)
                {
                    if (intArray != nullptr && size > 0)
                    {
                        printArray(intArray, size);
                    }
                    else
                        cout << "no array\n";
                }
                break;
            }
            case 4:
            {
                if (isFloat)
                {
                    copyArray(cloneFloatArray, floatArray, size);
                    clonesize = size;
                    int sortChoice;
                    cout << "Choose sorting algorithm:\n";
                    cout << "1. Insertion Sort\n";
                    cout << "2. Shell Sort\n";
                    cout << "3. Heap Sort\n";
                    cout << "4. Quick Sort\n";
                    cin >> sortChoice;
                    if (isFloat) {
                        // Przekazanie obiektu sortera do funkcji sortującej
                        switch(sortChoice) {
                            case 1:
                                floatSorter.insertionSort(cloneFloatArray, size); // Insertion Sort
                                break;
                            case 2:
                            {
                                int shellChoice;
                                cout << "Choose Shell Sort variant:\n";
                                cout << "1. Classic Shell Sort\n";
                                cout << "2. Shell Sort with Hibbard's gaps\n";
                                cin >> shellChoice;
                                switch(shellChoice) {
                                    case 1:
                                    {
                                        floatSorter.shellsortShell(cloneFloatArray, size);
                                        break;
                                    }
                                    case 2:
                                    {
                                        floatSorter.shellSortHibbard(cloneFloatArray, size);
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice. Returning to previous menu.\n";
                                        break;
                                }
                            case 3:
                                {
                                    floatSorter.heapsort(cloneFloatArray, size);
                                    break;
                                }
                            case 4:
                                {
                                    int pivotChoice;
                                    cout << "Choose pivot selection strategy for Quick Sort:\n";
                                    cout << "1. Left\n";
                                    cout << "2. Right\n";
                                    cout << "3. Middle\n";
                                    cout << "4. Random\n";
                                    cin >> pivotChoice;
                                    
                                    switch(pivotChoice) {
                                        case 1:
                                        {
                                            floatSorter.quicksortLeft(cloneFloatArray, size);
                                            break;
                                        }
                                        case 2:
                                        {
                                            floatSorter.quicksortRight(cloneFloatArray, size);
                                            break;
                                        }
                                        case 3:
                                        {
                                            floatSorter.quicksortMiddle(cloneFloatArray, size);
                                            break;
                                        }
                                        case 4:
                                        {
                                            floatSorter.quicksortRandom(cloneFloatArray, size);
                                            break;
                                        }
                                    }
                                    break;
                                }
                            default:
                                cout << "Invalid choice. Try again.\n";
                                break;
                            }
                        }
                    }
                }
                else if (!isFloat)
                {
                    copyArray(cloneIntArray, intArray, size);
                    clonesize = size;
                    int sortChoice;
                    cout << "Choose sorting algorithm:\n";
                    cout << "1. Insertion Sort\n";
                    cout << "2. Shell Sort\n";
                    cout << "3. Heap Sort\n";
                    cout << "4. Quick Sort\n";
                    cin >> sortChoice;
                    switch(sortChoice) {
                        case 1:
                        {
                            intSorter.insertionSort(cloneIntArray, clonesize); // Insertion Sort
                            break;
                        }
                        case 2:
                        {
                            int shellChoice;
                            cout << "Choose Shell Sort variant:\n";
                            cout << "1. Classic Shell Sort\n";
                            cout << "2. Shell Sort with Hibbard's gaps\n";
                            cin >> shellChoice;
                            switch(shellChoice) {
                                case 1:
                                {
                                    intSorter.shellsortShell(cloneIntArray, clonesize);
                                    break;
                                }
                                case 2:
                                {
                                    intSorter.shellSortHibbard(cloneIntArray, clonesize);
                                    break;
                                }
                                default:
                                    cout << "Invalid choice. Returning to previous menu.\n";
                                    break;
                            }
                        case 3:
                            {
                                intSorter.heapsort(cloneIntArray, clonesize);
                                break;
                            }
                        case 4:
                            {
                                int pivotChoice;
                                cout << "Choose pivot selection strategy for Quick Sort:\n";
                                cout << "1. Left\n";
                                cout << "2. Right\n";
                                cout << "3. Middle\n";
                                cout << "4. Random\n";
                                cin >> pivotChoice;
                                
                                switch(pivotChoice) {
                                    case 1:
                                    {
                                        intSorter.quicksortLeft(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 2:
                                    {
                                        intSorter.quicksortRight(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 3:
                                    {
                                        intSorter.quicksortMiddle(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 4:
                                    {
                                        intSorter.quicksortRandom(cloneIntArray, clonesize);
                                        break;
                                    }
                                }
                                break;
                            }
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                        }
                    }
                }
                break;
            }
            case 5:
            {
                if (isFloat)
                {
                    if (cloneFloatArray != nullptr && clonesize > 0)
                        printArray(cloneFloatArray, clonesize);
                    else
                        cout << "No array\n";
                }
                else if (!isFloat)
                {
                    if (cloneIntArray != nullptr && clonesize > 0)
                        printArray(cloneIntArray, size);
                    else
                        cout << "no array\n";
                    break;
                }
                break;
            }
        }
    } while (choice != 6);
    if (isFloat) {
        delete[] floatArray;
        floatArray = nullptr;
    } else {
        delete[] intArray;
        intArray = nullptr;
    }

} while (dataTypeChoice != 3);
    return 0;
}

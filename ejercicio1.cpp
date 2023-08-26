#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

int main() {
    int N; // Elemento que se utilizara para ingresar el input
    std::cout << "Ingrese la cantidad de números aleatorios a generar: ";
    std::cin >> N;

    // Generar numeros aleatorios y escribirlos en un archivo
    std::ofstream outFile("numeros.txt");
    srand(time(nullptr)); // Inicializar semilla de generación de números aleatorios

    auto start_gen = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        int randomNumber = rand() % 1000; // Generar numeros entre 0 y 999
        outFile << randomNumber;
        if (i < N - 1) {
            outFile << ",";
        }
    }
    auto end_gen = std::chrono::high_resolution_clock::now();
    outFile.close();

    // Calcular el tiempo de generacion
    auto duration_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end_gen - start_gen).count();

    // Leer números desde el archivo y almacenarlos en un arreglo dinámico
    std::ifstream inFile("numeros.txt");
    int* Array = new int[N]; // Crearion de arreglo para almacenar los numeros
    auto start_read = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        char comma; // Para leer la coma que separa los números en el archivo
        inFile >> Array[i] >> comma;
    }
    auto end_read = std::chrono::high_resolution_clock::now();
    inFile.close();

    // Tiempo de lectura
    auto duration_read = std::chrono::duration_cast<std::chrono::milliseconds>(end_read - start_read).count();

    // Ordenar el arreglo de números
    auto start_sort = std::chrono::high_resolution_clock::now();
    std::sort(Array, Array + N);
    auto end_sort = std::chrono::high_resolution_clock::now();

    // Tiempo para ordenar
    auto duration_sort = std::chrono::duration_cast<std::chrono::milliseconds>(end_sort - start_sort).count();

    // Escribir los números ordenados en un archivo
    std::ofstream sortedFile("numeros_ordenados.txt");
    auto start_write = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sortedFile << Array[i];
        if (i < N - 1) {
            sortedFile << ",";
        }
    }
    auto end_write = std::chrono::high_resolution_clock::now();
    sortedFile.close();

    // Tiempo de escritura
    auto duration_write = std::chrono::duration_cast<std::chrono::milliseconds>(end_write - start_write).count();

    // Liberar la memoria Heap ya que se termino de utilzarla
    delete[] Array;

    std::cout << "Proceso completado." << std::endl;

    auto total_duration = duration_gen + duration_read + duration_sort + duration_write;

    double speedup_gen = static_cast<double>(total_duration) / duration_gen;
    double speedup_read = static_cast<double>(total_duration) / duration_read;
    double speedup_sort = static_cast<double>(total_duration) / duration_sort;
    double speedup_write = static_cast<double>(total_duration) / duration_write;

    std::cout << "Speedup Generacion: " << speedup_gen << std::endl;
    std::cout << "Speedup Lectura: " << speedup_read << std::endl;
    std::cout << "Speedup Ordenar: " << speedup_sort << std::endl;
    std::cout << "Speedup Escritura: " << speedup_write << std::endl;

    double final_duration = (speedup_gen + speedup_read + speedup_sort + speedup_write) / 4;
    std::cout << "Final speedrun: " << final_duration << std::endl;

    return 0;
}

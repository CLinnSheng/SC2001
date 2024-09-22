#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <map>
#include <chrono>

int insertion_sort(std::vector<int>& arr)
{
    int keyComparsion = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            keyComparsion++;
            std::swap(arr[j - 1], arr[j]);
            j--;
        }
    }

    return keyComparsion;
}

int merge(std::vector<int>& arr, int left, int right, int mid)
{
    int keyComparison = 0;
    std::vector<int> left_half(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> right_half(arr.begin() + mid + 1, arr.begin() + right + 1);

    int pointer_L = 0, pointer_R = 0;

    while (pointer_L < left_half.size() && pointer_R < right_half.size())
    {
        keyComparison++;

        if (left_half[pointer_L] < right_half[pointer_R]) arr[left] = left_half[pointer_L++];
        else arr[left] = right_half[pointer_R++];

        left++;
    }

    while (pointer_L < left_half.size())
        arr[left++] = left_half[pointer_L++];
    
    while (pointer_R < right_half.size())
        arr[left++] = right_half[pointer_R++];

    return keyComparison;
}

int merge_sort(std::vector<int>& arr, int left, int right)
{
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;

    return merge_sort(arr, left, mid) + merge_sort(arr,  mid + 1,  right) + merge(arr, left, right, mid);
}

int insertion_sort_hybrid(std::vector<int>& arr, int left, int right)
{
    int keyComparison = 0;

    for (int i = left + 1; i <= right; i++)
    {
        int j = i;
        while (j > left)
        {
            keyComparison++;
            if (arr[j - 1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
                j--;
            }
            else break;
        }
    }
    return keyComparison;
}

int hybrid_sort(std::vector<int>& arr, int left, int right, int S)
{
    if (right - left <= S) return insertion_sort_hybrid(arr, left, right);
    
    int mid = left + (right - left) / 2;
    
    return hybrid_sort(arr, left, mid, S) + hybrid_sort(arr, mid + 1, right, S) + merge(arr, left, right, mid);
}

std::vector<int> generateDataSet(int size, int largest_number) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, largest_number);

    std::vector<int> dataset(size);
    std::generate(dataset.begin(), dataset.end(), [&]() { return dis(gen); });
    return dataset;
}

void writeOutput1(std::string filename, std::vector<int>& dataSizes, std::vector<int>& keyComparisons, std::vector<double>& timeTakens)
{
    std::ofstream outputFile(filename);

    outputFile << "Input Sizes,Key Comparison,Time Taken(ms)" << std::endl;
    for (int i = 0; i < dataSizes.size(); i++)
        outputFile << dataSizes[i] << "," << keyComparisons[i] << "," << timeTakens[i] << std::endl;
    
    outputFile.close();
}

// void writeOutput2(std::string filename, std::vector<int>& thresholdVals, std::vector<int>& keyComparisons, std::vector<double>& timeTakens)
// {
//     std::ofstream outputFile(filename);

//     outputFile << "Threshold Value,Key Comparison,Time Taken(ms)" << std::endl;
//     for (int i = 0; i < thresholdVals.size(); i++)
//         outputFile << thresholdVals[i] << "," << keyComparisons[i] << "," << timeTakens[i] << std::endl;
    
//     outputFile.close();
// }
// void question_b_i(const std::map<int, std::vector<int>>& dataSets)
// {
//     const int THRESHOLD = 10;
//     std::vector<int> x_inputSize, y_KeyComparisons;
//     std::vector<double> timeTaken;
    
//     for (const auto&[dataSize, dataSet] : dataSets)
//     {
//         std::vector<int> copyDataSet = dataSet;
//         auto start_timestamp = std::chrono::high_resolution_clock::now();        
//         auto keyComparisons = hybrid_sort(copyDataSet, 0, copyDataSet.size() - 1, THRESHOLD);
//         auto end_timestamp = std::chrono::high_resolution_clock::now();        
//         x_inputSize.emplace_back(dataSize);
//         y_KeyComparisons.emplace_back(keyComparisons);        
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_timestamp - start_timestamp);
//         timeTaken.emplace_back(duration.count());       
//     }

//     writeOutput1("new_output1.csv", x_inputSize, y_KeyComparisons, timeTaken);    
// }

// void question_b_ii(const std::map<int, std::vector<int>>& dataSets)
// {
//     const int SIZE = 1000000;
    
//     int initial_thresholdvalue = 1;
//     std::vector<int> x_thresholdval, y_KeyComparisons;
//     std::vector<double> timeTaken;
    
//     for (int i = initial_thresholdvalue; i < 126; i++)
//     {
//         std::vector<int> copyDataSet = dataSets.at(SIZE);
//         auto start_timestamp = std::chrono::high_resolution_clock::now();        
//         auto keyComparisons = hybrid_sort(copyDataSet, 0, copyDataSet.size() - 1, i);
//         auto end_timestamp = std::chrono::high_resolution_clock::now();        
//         x_thresholdval.emplace_back(i);
//         y_KeyComparisons.emplace_back(keyComparisons);        
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_timestamp - start_timestamp);
//         timeTaken.emplace_back(duration.count());           
//     }
    
//     writeOutput2("new_output2.csv", x_thresholdval, y_KeyComparisons, timeTaken);    
// }

// void question_b_iii(const std::map<int, std::vector<int>>& dataSets)
// {
//     // the size we choosing is 1,000,000 -> 5,000,000
//     int starting_size = 1000000;
    
//     for (int i = 1; i <= 5; i++)
//     {
//         std::vector<int> copyDataSet = dataSets.at(starting_size * i);
//         auto mergeC
//     }
// }

void GenerateTime(const std::map<int, std::vector<int>>& dataSets)
{
    const int THRESHOLD = 13;
    std::vector<int> x_inputSize, y_KeyComparisons;
    std::vector<double> timeTaken;
    
    for (const auto&[dataSize, dataSet] : dataSets)
    {
        if (dataSize > 1000000) break;
        std::vector<int> copyDataSet = dataSet;
        auto start_timestamp = std::chrono::high_resolution_clock::now();        
        auto keyComparisons = hybrid_sort(copyDataSet, 0, copyDataSet.size() - 1, THRESHOLD);
        auto end_timestamp = std::chrono::high_resolution_clock::now();        
        x_inputSize.emplace_back(dataSize);
        y_KeyComparisons.emplace_back(keyComparisons);        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_timestamp - start_timestamp);
        timeTaken.emplace_back(duration.count());       
    }

    writeOutput1("time_hybrid.csv", x_inputSize, y_KeyComparisons, timeTaken);   
    x_inputSize.clear(); y_KeyComparisons.clear(); timeTaken.clear();

    for (const auto&[dataSize, dataSet] : dataSets)
    {
        if (dataSize > 1000000) break;
        std::vector<int> copyDataSet = dataSet;
        auto start_timestamp = std::chrono::high_resolution_clock::now();        
        auto keyComparisons = merge_sort(copyDataSet, 0, copyDataSet.size() - 1);
        auto end_timestamp = std::chrono::high_resolution_clock::now();        
        x_inputSize.emplace_back(dataSize);
        y_KeyComparisons.emplace_back(keyComparisons);        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_timestamp - start_timestamp);
        timeTaken.emplace_back(duration.count());       
    }

    writeOutput1("time_merge.csv", x_inputSize, y_KeyComparisons, timeTaken);   

}
int main()
{
    
    std::srand(time(0));
    std::set<int> dataSizes;
    
    for (int i = 1; i <= 10; i++)
        for (int j = 3; j < 7; j++)
            dataSizes.insert(i * std::pow(10, j));

    std::map<int, std::vector<int>> dataSets;

    // Generating dataset
    for (const auto& dataSize : dataSizes)
        dataSets[dataSize] = generateDataSet(dataSize, 1000);

    // b) i)
    // Setting Threshold to 10
    // question_b_i(dataSets);
    
    // b) ii)
    // Set N to 1,000,000
    // question_b_ii(dataSets);
    
    // c)
    // question_b_iii(dataSets);
    GenerateTime(dataSets);    
    return 0;
}

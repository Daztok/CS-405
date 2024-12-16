// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

#pragma warning(suppress : 4996)

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for performance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    {
        // DONE: transform each character based on an xor of the key modded constrained to key length using a mod
        output[i] = source[i] ^ key[i % key_length]; // apply xor encryption or decryption
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    // create a string to hold the file content
    std::string file_text;

    // open the file for reading
    std::ifstream file(filename);
    if (!file.is_open())
    {
        // throw an error if the file cannot be opened
        throw std::runtime_error("could not open file: " + filename);
    }

    // DONE: read the file content into the string using a stringstream
    std::ostringstream ss;
    ss << file.rdbuf();
    file_text = ss.str(); // convert the stringstream to a string

    // return the file content as a string
    return file_text;
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    {
        // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    // open the file for writing
    std::ofstream file(filename);
    if (!file.is_open())
    {
        // throw an error if the file cannot be opened
        throw std::runtime_error("could not open file: " + filename);
    }

    // get the current timestamp
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream timestamp;
    timestamp << std::put_time(&tm, "%Y-%m-%d"); // format the timestamp as yyyy-mm-dd

    // DONE: write the student name, timestamp, key, and data to the file
    file << student_name << '\n';
    file << timestamp.str() << '\n';
    file << key << '\n';
    file << data;

    // close the file (optional since destructor handles it)
    file.close();
}

int main()
{
    std::cout << "Encryption Decryption Test!" << std::endl;

    // input file format
    // Line 1: <students name>
    // Line 2: <Lorem Ipsum Generator website used>
    // Lines 3+: <lorem ipsum generated with 3 paragraphs> 

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrypteddatafile.txt";
    const std::string source_string = read_file(file_name); // read the input file
    const std::string key = "password"; // encryption and decryption key

    // get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // DONE: encrypt sourceString with key
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // DONE: save encrypted_string to file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // DONE: decrypt encryptedString with key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // DONE: save decrypted_string to file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;
}
    // Run program: Ctrl + F5 or Debug > Start Without Debugging menu
    // Debug program: F5 or Debug > Start Debugging menu

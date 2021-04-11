#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/task3.h"
#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3test
{
	TEST_CLASS(lab3test)
	{
		string GetDirectoryName(string path) {
			const size_t last_slash_idx = path.rfind('\\');
			if (std::string::npos != last_slash_idx)
			{
				return path.substr(0, last_slash_idx + 1);
			}
			return "";
		}
	public:
		
		TEST_METHOD(empty_file)
		{
			//char fileNameIn[22] = "test_txt/test1_in.txt";
			//char fileNameOut[23] = "test_txt/test1_out.txt";
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test1_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test1_out.txt";
			task3 task;
			int size;
			try
			{
				task.readList(fileNameIn);
				task.Dijkstra(size);
				task.writeList(fileNameOut);
			}
			catch (out_of_range e)
			{
				Assert::AreEqual(e.what(), "Graph is empty");
			}
		}
		TEST_METHOD(zero_city)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test2_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test2_out.txt";
			task3 task;
			int size;
			try
			{
				task.readList(fileNameIn);
				task.Dijkstra(size);
				task.writeList(fileNameOut);
			}
			catch (out_of_range e)
			{
				Assert::AreEqual(e.what(), "Graph is empty");
			}
		}
		TEST_METHOD(noTask_city)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test3_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test3_out.txt";
			task3 task;
			int size;
			try
			{
				task.readList(fileNameIn);
				task.Dijkstra(size);
				task.writeList(fileNameOut);
			}
			catch (out_of_range e)
			{
				Assert::AreEqual(e.what(), "Missing value");
			}
		}
		TEST_METHOD(easy_test)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test4_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test4_out.txt";
			task3 task;
			int size;
			int* answer;
			int* rightAnswer = new int[3] {0,1,2};
			task.readList(fileNameIn);
			answer = task.Dijkstra(size);
			for (size_t i = 0; i < size; i++)
			{
				Assert::AreEqual(answer[i], rightAnswer[i]);
			}
			task.writeList(fileNameOut);
		}
		TEST_METHOD(easy_test2)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test5_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test5_out.txt";
			task3 task;
			int size;
			int* answer;
			int* rightAnswer = new int[2]{ 0,2 };
			task.readList(fileNameIn);
			answer = task.Dijkstra(size);
			for (size_t i = 0; i < size; i++)
			{
				Assert::AreEqual(answer[i], rightAnswer[i]);
			}
			task.writeList(fileNameOut);
		}
		TEST_METHOD(no_path)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test6_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test6_out.txt";
			task3 task;
			int size;
			int* answer;
			try
			{
				task.readList(fileNameIn);
				answer = task.Dijkstra(size);
				task.writeList(fileNameOut);
			}
			catch (out_of_range e)
			{
				Assert::AreEqual(e.what(), "Result not found");
			}
		}
		TEST_METHOD(test)
		{
			string fileNameIn = std::string(TEST_CASE_DIRECTORY) + "test_txt/test7_in.txt";
			string fileNameOut = std::string(TEST_CASE_DIRECTORY) + "test_txt/test7_out.txt";
			task3 task;
			int size;
			int* answer;
			int* rightAnswer = new int[4]{ 0,2,3,4 };
			task.readList(fileNameIn);
			answer = task.Dijkstra(size);
			for (size_t i = 0; i < size; i++)
			{
				Assert::AreEqual(answer[i], rightAnswer[i]);
			}
			task.writeList(fileNameOut);
		}
	};
}

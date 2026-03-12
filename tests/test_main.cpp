#include <iostream>

// Все файлы собираются в один общий исполняемый
// файл unit_tests

void TestParseDefaultArgs();
void TestParseDepth();
void TestRejectNegativeDepth();
void TestScanReturnsRoot();
void TestScanRespectsDepth();
void TestNodeType();
void TestAddChild();
void TestBuildTreeReturnsRoot();
void TestBuildTreeCreatesChildren();
void TestBuildTreeReturnsNullForEmptyInput();

int main()
{
    TestParseDefaultArgs();
    TestParseDepth();
    TestRejectNegativeDepth();
    TestScanReturnsRoot();
    TestScanRespectsDepth();
    TestNodeType();
    TestAddChild();
    TestBuildTreeReturnsRoot();
    TestBuildTreeCreatesChildren();
    TestBuildTreeReturnsNullForEmptyInput();

    std::cout << "unit_tests passed" << std::endl;
    return 0;
}

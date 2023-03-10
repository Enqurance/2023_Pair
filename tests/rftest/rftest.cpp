#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyProjectUnitTest
{
    TEST_CLASS(MyTestClass)
            {
                    public:
                    TEST_METHOD(MyTestMethod1)
                    {
                        // Your test code here
                        Assert::AreEqual(1, 1);
                    }

                    TEST_METHOD(MyTestMethod2)
                    {
                        // Your test code here
                        Assert::IsTrue(true);
                    }
            };
}

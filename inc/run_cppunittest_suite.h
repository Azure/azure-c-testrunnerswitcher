#ifndef RUN_CPPUNITTEST_SUITE_H
#define RUN_CPPUNITTEST_SUITE_H

#include "macro_utils/macro_utils.h"
#include "ctest.h"
#include "CppUnitTest.h" // IWYU pragma: export

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define RUN_TESTS_WITH_CPP_UNITTEST(test_suite) \
    /* These externs are needed to force linking the current unit */ \
    extern C_LINKAGE const TEST_FUNCTION_DATA MU_C2(TestListHead_, test_suite); \
    static const TEST_FUNCTION_DATA* entry_test_function_data = &MU_C2(TestListHead_, test_suite); \
    TEST_CLASS(DummyTestClass) \
    { \
        /* For some obscure reason, using IMPLEMENT_CPP_UNIT_FIXTURE here does not work, so we'll just hand craft it */ \
        static const EXPORT_METHOD::Microsoft::VisualStudio::CppUnitTestFramework::TestClassInfo* CALLING_CONVENTION MU_C2(GetTestClassInfo_, test_suite)() \
        { \
            ALLOCATE_TESTDATA_SECTION_CLASS static const ::Microsoft::VisualStudio::CppUnitTestFramework::ClassMetadata CppUnitTestClassMetadata = { L"TestClassInfo", reinterpret_cast<const unsigned char*>(__FUNCTION__), reinterpret_cast<const unsigned char*>(__FUNCDNAME__) }; \
            static const ::Microsoft::VisualStudio::CppUnitTestFramework::TestClassInfo s_Info = { &__New, &__Delete, &CppUnitTestClassMetadata }; \
            __GetTestVersion(); \
            return &s_Info; \
        } \
    }; \

#endif /* RUN_CPPUNITTEST_SUITE_H */

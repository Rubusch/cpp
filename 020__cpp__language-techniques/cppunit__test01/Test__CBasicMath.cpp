/* cppunit test program */
#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "CBasicMath.h"

using namespace CppUnit;
using namespace std;

class Test__CBasicMath : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(Test__CBasicMath);

	CPPUNIT_TEST(test__add);
	CPPUNIT_TEST(test__multiply);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void test__add(void);
	void test__multiply(void);

private:
	CBasicMath *mTestObj;
};

/*----------------------------------------------------------------------------*/

void Test__CBasicMath::test__add(void)
{
	CPPUNIT_ASSERT( 5 == mTestObj->add(2, 3) );
}

void Test__CBasicMath::test__multiply(void)
{
	CPPUNIT_ASSERT( 6 == mTestObj->multiply(2, 3) );
}

/*----------------------------------------------------------------------------*/

void Test__CBasicMath::setUp(void)
{
	mTestObj = new CBasicMath();
}

void Test__CBasicMath::tearDown(void)
{
	delete mTestObj;
	mTestObj = nullptr;
}

/*----------------------------------------------------------------------------*/

CPPUNIT_TEST_SUITE_REGISTRATION( Test__CBasicMath );

int main(int argc, char* argv[])
{
	// inform test-listener about test results
	CPPUNIT_NS::TestResult testResult;

	// register listener for collecting the test result
	CPPUNIT_NS::TestResultCollector collectedResults;
	testResult.addListener(&collectedResults);

	// register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testResult.addListener(&progress);

	// insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testResult);

	// output results in compiler format
	CPPUNIT_NS::CompilerOutputter compilerOutputter(&collectedResults, std::cerr);
	compilerOutputter.write();

	// (opt) output xml for jenkins cppunit plugin
	ofstream xmlFileOut("Test__CBasicMath.xml");
	XmlOutputter xmlOut(&collectedResults, xmlFileOut);
	xmlOut.write();

	// return 0 if tests were successful
	return (collectedResults.wasSuccessful() ? 0 : 1);
}


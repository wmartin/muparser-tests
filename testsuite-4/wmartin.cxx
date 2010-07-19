#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class WmartinTest : public CppUnit::TestFixture {
public:
	CPPUNIT_TEST_SUITE (WmartinTest);
	CPPUNIT_TEST (testCroesnick_asr_0013);
	CPPUNIT_TEST_SUITE_END ();

	static double _doubleSum (double arg1, double arg2) {
		return (arg1 + arg2)*2;
	}

	void testCroesnick_asr_0013 () {
		mu::Parser parser;
		double res;
		double res2;

		res2 = parser.ParseCmdCode();

		parser.SetExpr ("244 - 44 - 100 -99");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res2, 0.000001);     
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (WmartinTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}


#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <muParser/muParser.h>

#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

class UserDefinitionsTest : public CppUnit::TestFixture {
public:
	CPPUNIT_TEST_SUITE (UserDefinitionsTest);
	CPPUNIT_TEST (testOperatorDef);
	CPPUNIT_TEST (testPriority);
	CPPUNIT_TEST (testInfixDef);
	CPPUNIT_TEST (testPostfixDef);
	CPPUNIT_TEST (testComplexExpression);
	CPPUNIT_TEST_SUITE_END ();

	static double _doubleSum (double arg1, double arg2) {
		return (arg1 + arg2)*2;
	}

	static double _sub (double arg1, double arg2) {
		return arg1 - arg2;
	}

	static double _infixOpr (double arg) {
		return arg*arg;
	}

	static double _postfixOpr1 (double arg) {
		return arg*1000.0;
	}

	static double _postfixOpr2 (double arg) {
		return arg*1000000.0;
	}

	void testOperatorDef () {
		mu::Parser parser;
		double res;

		parser.DefineOprt("doubleSum", &_doubleSum, 0);

		parser.SetExpr ("2 doubleSum 3");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (10.0, res, 0.000001);

		parser.SetExpr ("((2 doubleSum 3) doubleSum (-9))/2");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);     
	}

	void testPriority () {
		mu::Parser parser;
		double res;

		parser.DefineOprt("doubleSum", &_doubleSum, 0);
		parser.DefineOprt("_sub", &_sub, 1);

		parser.SetExpr ("3 doubleSum 4 _sub 2");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (10.0, res, 0.000001);
	}

	void testInfixDef () {
		mu::Parser parser;
		double res;

		parser.DefineInfixOprt ("~", &_infixOpr);

		parser.SetExpr ("~3");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (9.0, res, 0.000001);
		
		parser.SetExpr ("~(-3)");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (9.0, res, 0.000001);
		
		parser.SetExpr ("~(~2)");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (16.0, res, 0.000001);
	}

	void testPostfixDef () {
		mu::Parser parser;
		double res;

        parser.DefinePostfixOprt ("K", &_postfixOpr1);
        parser.DefinePostfixOprt ("M", &_postfixOpr2);

		parser.SetExpr ("3K");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (3000.0, res, 0.000001);
		
		parser.SetExpr ("2.012M");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (2012000.0, res, 0.000001);
		
		parser.SetExpr ("(0.000000001K)M");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1.0, res, 0.000001);
	}
	
	void testComplexExpression () {
		mu::Parser parser;
		double res;

		parser.DefineInfixOprt ("~", &_infixOpr);
        parser.DefinePostfixOprt ("K", &_postfixOpr1);
        parser.DefinePostfixOprt ("M", &_postfixOpr2);

		parser.SetExpr ("~1.0K");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (1000000.0, res, 0.000001);
		
		parser.SetExpr ("((~0.5)K)M");
		res = parser.Eval ();
		CPPUNIT_ASSERT_DOUBLES_EQUAL (250000000.0, res, 0.000001);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION (UserDefinitionsTest);

int main (int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry ();
    runner.addTest (registry.makeTest ());
    bool wasSuccessful = runner.run ("", false);
    return (wasSuccessful != 0) ? 0 : 1;
}

